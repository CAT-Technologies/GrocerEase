#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/bluetooth.h>

#include <glib.h>
#include <gio/gio.h>

using namespace std;

const u_char LE_ADV_REPORT = 0x02;

//based on hcitool lescan
bool receiveAdv(int dd, std::chrono::seconds timeout)
{
    u_char buff[HCI_MAX_EVENT_SIZE];
    u_char *ptr;
    hci_filter filter;

    hci_filter_clear(&filter);
    hci_filter_set_ptype(HCI_EVENT_PKT, &filter);
    hci_filter_set_event(EVT_LE_META_EVENT, &filter);

    if (setsockopt(dd, SOL_HCI, HCI_FILTER, &filter, sizeof(filter)) < 0) {
        printf("Could not set socket options\n");
        return false;
    }

    using namespace std::chrono;
    time_point<steady_clock> start = steady_clock::now();
    while (steady_clock::now() - start < timeout) {
        if (read(dd, buff, sizeof(buff)) < 0) {
            std::this_thread::sleep_for(milliseconds(20));
            continue;
        }

        ptr = buff + (1 + HCI_EVENT_HDR_SIZE);
        evt_le_meta_event *meta = reinterpret_cast<evt_le_meta_event *>(ptr);

        if (meta->subevent != LE_ADV_REPORT)
            continue;

        le_advertising_info *info = reinterpret_cast<le_advertising_info *>(meta->data + 1);
        char addr[18];
        ba2str(&info->bdaddr, addr);
        int rssi = info->data[info->length]; //intentional, isn't out of bounds
        cout << "Detected device: " << addr << " " << rssi << endl;
    }

    return true;
}

bool scan(unsigned timeout)
{
    int devId = hci_get_route(nullptr);
    int dd = hci_open_dev(devId);
    if (devId < 0 || dd < 0) {
        cerr << "Could not open device\n";
        return false;
    }

    uint8_t localAddr = LE_PUBLIC_ADDRESS; //LE_PUBLIC_ADDRESS to use public on local device, LE_RANDOM_ADDRESS to use random
    uint8_t scanType = 0x01; //0x01 = active, 0x00 = passive
    uint8_t filterPolicy = 0x00; //0x00 = don't use whitelist, 0x01 = use whitelist
    uint16_t interval = htobs(0x0010); //no idea, default for all except 'g' or 'l' filters that use htobs(0x0012)
    uint16_t window = htobs(0x0010); //no idea, default for all except 'g' or 'l' filters that use htobs(0x0012)
    uint8_t filterDup = 0x00; // 0x01 = filter duplicates, 0x00 = receive duplicates
    int hciTimeout = 10000; // this is timeout for communication with the local adapter, not scanning

    if (hci_le_set_scan_parameters(dd, scanType, interval, window, localAddr, filterPolicy, hciTimeout) < 0) {
        cerr << "Set scan parameters failed\n";
        hci_close_dev(dd);
        return false;
    }

    uint8_t scanEnable = 0x01;
    if (hci_le_set_scan_enable(dd, scanEnable, filterDup, hciTimeout) < 0) {
        cerr << "Enable scan failed\n";
        hci_close_dev(dd);
        return false;
    }

    if (receiveAdv(dd, std::chrono::seconds(timeout)) < 0) {
        cerr << "Could not receive advertising events\n";
        hci_close_dev(dd);
        return false;
    }

    hci_close_dev(dd);
    return true;
}

GDBusProxy *connect(const char *addr)
{
    GError *err = nullptr;
    char objPath[sizeof("/org/bluez/hci0/dev_DA_06_9E_3A_E2_5C")] = "/org/bluez/hci0/dev_DA_06_9E_3A_E2_5C";
    GDBusProxy *devProxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM, G_DBUS_PROXY_FLAGS_NONE, nullptr, "org.bluez", objPath, "org.bluez.Device1", nullptr, &err);

    if (!devProxy) {
        cerr << "Device " << addr << " not available:" << err->message << endl;
        g_clear_error(&err);
        return nullptr;
    }
    if (!g_dbus_proxy_call_sync(devProxy, "Connect", nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &err)) {
        cerr << "Failed to connect: " << err->message << "(" << err->code << ")\n";
        g_clear_error(&err);
        if (!g_dbus_proxy_call_sync(devProxy, "Pair", nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &err)) {
            cerr << "Failed to connect: " << err->message << "(" << err->code << ")\n";
            g_clear_error(&err);
            return nullptr;
        }
    }
    return devProxy;
}

bool disconnect(GDBusProxy *devProxy)
{
    GError *err = nullptr;
    if (!g_dbus_proxy_call_sync(devProxy, "Disconnect", nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &err)) {
        cerr << "Failed to disconnect - " << err->message << "(" << err->code << ")\n";
        g_clear_error(&err);
        return false;
    }
    return true;
}

GVariant *read()
{
    const char *objPath("/org/bluez/hci0/dev_DA_06_9E_3A_E2_5C/service0013/char0014");

    GVariantBuilder *b = g_variant_builder_new(G_VARIANT_TYPE("({sv})"));
    g_variant_builder_add (b, "{sv}", "offset", g_variant_new_uint16(0));
    GVariant *args = g_variant_builder_end(b);

    GError *err = nullptr;
    GDBusProxy *charProxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SYSTEM, G_DBUS_PROXY_FLAGS_NONE, nullptr, "org.bluez", objPath, "org.bluez.GattCharacteristic1", nullptr, &err);
    GVariant *ret = g_dbus_proxy_call_sync(charProxy, "ReadValue", args, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &err);
    if (ret == FALSE) {
        cerr << "Failed to read - " << err->message << "(" << err->code << ")\n";
        g_clear_error(&err);
        return nullptr;
    }

    return ret;
}

int main()
{
    scan(3);
    GDBusProxy *proxy = connect("DA:06:9E:3A:E2:5C");
    GVariant *ret = read();
    disconnect(proxy);
    return 0;
}