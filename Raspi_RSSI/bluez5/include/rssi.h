#ifndef RSS_H_
#define RSS_H_

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdint.h>

struct sockaddr_l2 {
  sa_family_t l2_family;
  unsigned short l2_psm;
  bdaddr_t l2_bdaddr;
  unsigned short l2_cid;
  uint8_t l2_bdaddr_type;
};

#define L2CAP_CONNINFO 0x02

struct l2cap_conninfo {
  uint16_t hci_handle;
  uint8_t dev_class[3];
};

#define ATT_CID 4
#define BDADDR_ANY_L = const uint8_t &(bdaddr_t) {{0, 0, 0, 0, 0, 0}};
#endif /* RSS_H_ */