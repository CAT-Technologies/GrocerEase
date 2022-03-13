#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <glib.h>
#include <gio/gio.h>

#define BLUEZ_BUS_NAME "org.bluez"
#define BLUEZ_INTF_ADAPTER "org.bluez.Adapter"

static GDBusConnection *dbus_conn = NULL;
static GMainLoop *main_loop;

//RUN FILE command - include glib - gcc `pkg-config --cflags glib-2.0` rssi.cpp `pkg-config --libs glib-2.0`
//Mostly code would be revised as due to lack of compatability issues

struct handler_data
 {	
  const char *bt_address;
  short rssi;
};

/*
 * Callback function for the DeviceFound signal from the org.bluez.Adapter
 * interface.
 */
static void
device_found_handler (GDBusConnection *connection,
                        const gchar *sender_name,
                        const gchar *object_path,
                        const gchar *interface_name,
                        const gchar *signal_name,
                        GVariant *parameters,
                        gpointer user_data)
{
  char *device_address;
  gboolean res;
  short rssi;
  GVariant *property_dict;
  struct handler_data *data = (struct handler_data *)user_data;

  /*
   * Paramter format: sa{sv}
   * Only interested in the RSSI so lookup that entry in the properties
   * dictionary.
   */
  g_variant_get(parameters, "(&s*)", &device_address, &property_dict);

  if (strcmp(data->bt_address, device_address)) {
    /* Not the device of interest */
    return;
  }

  res = g_variant_lookup(property_dict, "RSSI", "n",
			 &rssi);
  if (!res) {
    printf("Unable to get device address from dbus\n");
    g_main_loop_quit(main_loop);
    return;
  }
  
  data->rssi = rssi;
  g_main_loop_quit(main_loop);
}

/*
 * Gets the RSSI for a given BT device address.
 */
static short
get_rssi(const char *bt_address)
{
  GError *error = NULL;
  GVariant *reply = NULL;
  char *adapter_object = NULL;
  struct handler_data data;
  
  data.bt_address = bt_address;

  main_loop = g_main_loop_new(NULL, FALSE);
  if (!main_loop) {
    printf("Error creating main loop\n");
    return 0;
  }

  dbus_conn = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
  if (error) {
    printf("Unable to get dbus connection\n");
    return 0;
  }

  /* Get the default BT adapter. Needed to start device discovery */
  reply = g_dbus_connection_call_sync(dbus_conn,
				      BLUEZ_BUS_NAME,
				      "/",
				      "org.bluez.Manager",
				      "DefaultAdapter",
				      NULL, 
				      G_VARIANT_TYPE("(o)"),
				      G_DBUS_CALL_FLAGS_NONE,
				      -1,
				      NULL,
				      &error);

  if (error) {
    printf("Unable to get managed objects: %s\n", error->message);
    return 0;
  }
  g_variant_get(reply, "(&o)", &adapter_object);

  /* Register a handler for DeviceFound signals to read the device RSSI */
  g_dbus_connection_signal_subscribe(dbus_conn,
				     NULL,
				     "org.bluez.Adapter",
				     "DeviceFound",
				     NULL,
				     NULL,
				     0,
				     device_found_handler,
				     &data,
				     NULL);

  /* Start device discovery */
  reply = g_dbus_connection_call_sync(dbus_conn,
				     BLUEZ_BUS_NAME,
				     adapter_object,
				     "org.bluez.Adapter",
				     "StartDiscovery",
				     NULL,
				     NULL,
				     G_DBUS_CALL_FLAGS_NONE,
				     -1,
				     NULL,
				     &error);

  if (error) {
    printf("Unable to start discovery: %s\n", error->message);
    return 0;
  }

  g_main_loop_run(main_loop);

  return data.rssi;
}

int
main (int argc, char **argv)
{
  short rssi = 0;

  if (argc != 2) {
    printf("Usage: %s <bt addresss>\n", argv[0]);
    return -1;
  }

  while (1) {
    rssi = get_rssi(argv[1]);
    printf("Device %s, rssi=%d\n", argv[1], rssi);
  }

  return 0;
}
