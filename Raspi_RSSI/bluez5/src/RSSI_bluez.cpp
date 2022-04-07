#include <rssi.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

#include <time.h>
#include <unistd.h>

class Adapter {
    const char* bt_addr;
    int hci_deviceid;

    int hciSocket;
    uint16_t hciHandle;

    int l2capSock;
    struct sockaddr_l2 sockAddr;
    struct l2cap_conninfo l2capConnInfo;
    socklen_t l2capConnInfoLen;

    void init();

public:
    Adapter(int hci_deviceid, const char* bt_addr);
    Adapter(const char * bt_addr);

    int getHciDeviceId();
    int8_t read_rssi(int to);
};

Adapter::Adapter(int hci_deviceid, const char* bt_addr) {
    this->hci_deviceid = hci_deviceid;
    this->bt_addr = bt_addr;
    init();
}
Adapter::Adapter(const char* bt_addr) {
    this->bt_addr = bt_addr;
    if (hci_get_route(NULL) >= 0)
        this->hci_deviceid = hci_get_route(NULL);
    init();
}

void Adapter::init(){
    int result;
    
    bdaddr_t tmp = {{0, 0, 0, 0, 0, 0}};
    bdaddr_t *addr = &tmp;

    printf("INIT with: %s via hci%d\n", bt_addr, hci_deviceid);


    hciSocket = hci_open_dev(hci_deviceid);
    printf("HCISOCKET: %d\n", hciSocket);
    printf("l2capSock %s\n", (l2capSock == -1) ? strerror(errno) : "success");

    // create socket
    l2capSock = socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    printf("L2CAPSOCK: %d\n", l2capSock);
    printf("l2capSock %s\n", (l2capSock == -1) ? strerror(errno) : "success");


    // bind
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.l2_family = AF_BLUETOOTH;
    bacpy(&sockAddr.l2_bdaddr, addr);
    sockAddr.l2_cid = htobs(ATT_CID);

    result = bind(l2capSock, (struct sockaddr*) &sockAddr, sizeof(sockAddr));
    printf("BIND: %d\n", result);
    printf("bind %s\n", (result == -1) ? strerror(errno) : "success");

    // connect
    memset(&sockAddr, 0, sizeof(sockAddr));

    sockAddr.l2_family = AF_BLUETOOTH;
    str2ba(bt_addr, &sockAddr.l2_bdaddr);
    sockAddr.l2_bdaddr_type = BDADDR_LE_RANDOM; // BDADDR_LE_PUBLIC/RANDOM
    sockAddr.l2_cid = htobs(ATT_CID);

    result = connect(l2capSock, (struct sockaddr *) &sockAddr,
            sizeof(sockAddr));
    printf("CONNECT L2CAPSOCK: %d\n", result);
    printf("connect %i %s\n", result,
            (result == -1) ? strerror(errno) : "success");

    l2capConnInfoLen = sizeof(l2capConnInfo);
    getsockopt(l2capSock, SOL_L2CAP, L2CAP_CONNINFO, &l2capConnInfo,
            &l2capConnInfoLen);
    hciHandle = l2capConnInfo.hci_handle;

    printf("GETSOCKOPT L2CAPSOCK: %d\n", result);
    printf("getsockopt %i %s\n", result,
            (result == -1) ? strerror(errno) : "success");
}

int Adapter::getHciDeviceId(){
    return hci_deviceid;
}

int8_t Adapter::read_rssi(int to) {
    int8_t rssi = 200;

    int result = hci_read_rssi(hciSocket, hciHandle, &rssi, to);
    printf("hci_read_rssi: %i %s\n", result,
            (result == -1) ? strerror(errno) : "success");

    return rssi;
}

void sleep(int ms){
    clock_t end_time = clock() + ms * CLOCKS_PER_SEC/1000;
    while (clock() < end_time) {}
}


int main(int argc, const char* argv[]) {

    Adapter myAdapter(0, argv[1]);
    Adapter myAdapter2(1, argv[1]);

    int counter = 0;

    while (true) {
        printf("%d: Adapter %d: RSSI: %i ", counter, myAdapter.getHciDeviceId(), myAdapter.read_rssi(100));
        printf("%d: Adapter %d: RSSI: %i ", counter, myAdapter2.getHciDeviceId(), myAdapter2.read_rssi(100));

        sleep(1000);
        counter++;
    }
}