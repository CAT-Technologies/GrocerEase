#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/poll.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#define MAX_DELAY    2000
#define POLL_TIMEOUT 11000

int debug = 0;

static volatile sig_atomic_t __io_canceled = 0;

static int find_conn(int s, int dev_id, long arg)
{
        struct hci_conn_list_req *cl;
        struct hci_conn_info *ci;
        int i;

        if (!(cl = malloc(10 * sizeof(*ci) + sizeof(*cl)))) {
                perror("Can't allocate memory");
                exit(1);
        }
        cl->dev_id = dev_id;
        cl->conn_num = 10;
        ci = cl->conn_info;

        if (ioctl(s, HCIGETCONNLIST, (void *) cl)) {
                perror("Can't get connection list");
                exit(1);
        }

        for (i = 0; i < cl->conn_num; i++, ci++)
                if (!bacmp((bdaddr_t *) arg, &ci->bdaddr)) {
                        free(cl);
                        return 1;
                }

        free(cl);
        return 0;
}

void int_handler(int sig)
{
    __io_canceled = 1;
}

void btscan(int dev_id, int sock) {
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    int len, flags;

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    printf("Start inquiry ...\n");
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
            name, 0) < 0)
        strcpy(name, "[unknown]");
        printf("%s  %s\n", addr, name);
    }
    free( ii );
}

void usage(char *name)
{
    fprintf(stderr,"Usage: %s [-s] [-r btaddr]\n",name);
    fprintf(stderr,"\n");
    fprintf(stderr,"\t-h          display this text\n");
    fprintf(stderr,"\t-s          scan\n");
    fprintf(stderr,"\t-r btaddr   get rssi on device at address btaddr\n");
    fprintf(stderr,"\n");
    exit(2);
}

int btrssi(char *dest) {
    int dev_id = -1;
    struct hci_conn_info_req *cr;
    bdaddr_t bdaddr;
    int8_t rssi;
    int dd;

    str2ba(dest, &bdaddr);

    if (dev_id < 0) {
        dev_id = hci_for_each_dev(HCI_UP, find_conn, (long) &bdaddr);
        if (dev_id < 0) {
             fprintf(stderr, "Not connected.\n");
             exit(1);
        }
    }

        dd = hci_open_dev(dev_id);
        if (dd < 0) {
                perror("HCI device open failed");
                exit(1);
        }

        cr = malloc(sizeof(*cr) + sizeof(struct hci_conn_info));
        if (!cr) {
                perror("Can't allocate memory");
                exit(1);
        }

        bacpy(&cr->bdaddr, &bdaddr);
        cr->type = ACL_LINK;
        if (ioctl(dd, HCIGETCONNINFO, (unsigned long) cr) < 0) {
                perror("Get connection info failed");
                exit(1);
        }

        if (hci_read_rssi(dd, htobs(cr->conn_info->handle), &rssi, 1000) < 0) {
                perror("Read RSSI failed");
                exit(1);
        }

        printf("RSSI return value: %d\n", rssi);

        free(cr);

        hci_close_dev(dd);

    return 0;
}

int btconnect(char *dest)
{
    int rfsock = -1;
    struct sockaddr_rc addr = { 0 };
    int status;

    // allocate a socket
    rfsock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to server
    if( debug ) printf("Connecting to %s ...\n", dest);
    status = connect(rfsock, (struct sockaddr *)&addr, sizeof(addr));


    if( status < 0 ) {
        perror("Error connecting");
        return -1;
    }
    else {
        if( debug ) printf("Connection established, rfsock = %d\n", rfsock);
        return rfsock;
    }
}

int main(int argc, char **argv)
{
    int dev_id;
    int c;
    int errflg = 0;
    int sock, rfsock = -1;
    int len;
    struct pollfd p;
    unsigned char buf[HCI_MAX_EVENT_SIZE], *ptr;
    hci_event_hdr *hdr;
    struct hci_filter flt;

    signal(SIGINT, int_handler);

    /* Set up the random number generator, for random delays for
     * scan.  This tries to avoid multiple machines running this
     * software from starting at the same time and flooding the
     * network at the same time.
     */
    srand(time(NULL) ^ getpid());

    printf("Open device\n");
    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("Can't open socket");
        exit(1);
    }


   /* Set up an event filter; we only care about inquiry-related
    *  events.
    */
   hci_filter_clear(&flt);
   hci_filter_set_ptype(HCI_EVENT_PKT, &flt);
   hci_filter_set_event(EVT_CMD_COMPLETE, &flt);
   hci_filter_set_event(EVT_CONN_COMPLETE, &flt);
   hci_filter_set_event(EVT_DISCONN_COMPLETE, &flt);
   if (setsockopt(sock, SOL_HCI, HCI_FILTER, &flt, sizeof(flt)) < 0) {
       perror("Can't set HCI filter");
       exit(1);
   }

    /* Process command-line options */
    while ((c = getopt(argc, argv, "hsr:")) != EOF)
    {
      switch(c)
      {
        case 'r':
          /* Now poll for events until a signal tells us to cancel. */
          p.fd = sock;
          p.events = POLLIN | POLLERR | POLLHUP;

              usleep(rand() % MAX_DELAY);
              rfsock = btconnect(optarg);


          while(!__io_canceled) {
              p.revents = 0;
              if (poll(&p, 1, POLL_TIMEOUT) > 0) {
                  len = read(sock, buf, sizeof(buf));
                  if (len < 0)
                      continue;
                  else if (len == 0)
                      break; /* EOF */

                  hdr = (void *) (buf + 1);
                  ptr = buf + (1 + HCI_EVENT_HDR_SIZE);
                  len -= (1 + HCI_EVENT_HDR_SIZE);

                  switch (hdr->evt) {

                      case EVT_CMD_COMPLETE:
                          if( rfsock != -1 ) {
                              usleep(rand() % MAX_DELAY );
                              btrssi(optarg);
                          }
                          break;
                      case EVT_CONN_COMPLETE:
                          if( rfsock != -1 ) {
                              usleep(rand() % MAX_DELAY );
                              btrssi(optarg);
                          }
                          break;

                      case EVT_DISCONN_COMPLETE:
                          usleep(rand() % MAX_DELAY );
                          rfsock = btconnect(optarg);
                          break;
                  }
              }
          }
          break;
        case 's':
          printf("Scan\n");
          btscan(dev_id, sock);
          break;
        case 'h':
          errflg++;
          break;
      }
    }

    if (errflg)
      usage(argv[0]);

    printf("Program finished\n");
    close( rfsock );
    close( sock );
    return 0;
}
