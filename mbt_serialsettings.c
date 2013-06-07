#include <gtk/gtk.h>

#include "mbt_settings.h"

G_DEFINE_TYPE (MbtSettings, mbt_settings, GTK_LIST_STORE);

enum {
  SERIAL_SETTINGS,
  ETHERNET_SETTINGS,

  N_SETTINGS
};

enum {
  BR_110,
  BR_300,
  BR_600,
  BR_1200,
  BR_2400,
  BR_4800,
  BR_9600,
  BR_14400,
  BR_19200,
  BR_38400,
  BR_56000,
  BR_57600,
  BR_115200,
  BR_128000,
  BR_256000,

  N_BR
};

static const gchar *mbt_setting[] = {
  "Serial Settings",   "Ethernet Settings",
  NULL
};

static const gchar *mbt_baud_rate[] = {
  "110",   "300",   "600",    "1200",   "2400",
  "4800",  "9600",  "14400",  "19200",  "38400",
  "56000", "57600", "115200", "128000", "256000",
  NULL
};

static void
mbt_settings_init (MbtSettings *_settings)
{
  _settings = gtk_list_store_new (N_SETTINGS,
                                  G_TYPE_STRING,
                                  G_TYPE_STRING);

  GtkTreeIter iter;

  gtk_list_store_append (_settings, &iter);
  gtk_list_store_set (_settings, &iter,
                      SERIAL_SETTINGS, "Serial Settings",
                      ETHERNET_SETTINGS, "Ethernet Settings",
                      -1);

  GtkListStore *baud_rate = gtk_list_store_new (N_BAUDRATES,
                                                G_TYPE_STRING,
                                                G_TYPE_UINT);
  _settings->baud_rate = baud_rate;
  gtk_list_store_append (baud_rate, &iter);
  gtk_list_store_set (baud_rate, &iter,
                      BR_110,    "110",    110,
                      BR_300,    "300",    300,
                      BR_600,    "600",    600,
                      BR_1200,   "1200",   1200,
                      BR_2400,   "2400",   2400,
                      BR_4800,   "4800",   4800,
                      BR_9600,   "9600",   9600,
                      BR_14400,  "14400",  14400,
                      BR_19200,  "19200",  19200, 
                      BR_38400,  "38400",  38400,
                      BR_56000,  "56000",  56000,
                      BR_57600,  "57600",  57600,
                      BR_115200, "115200", 115200,
                      BR_128000, "128000", 128000,
                      BR_256000, "256000", 256000,
                      -1);
}

static void
mbt_settings_class_init (MbtSettingsClass *klass)
{
}

MbtSettings*
mbt_settings_new (void)
{
  GtkTreeStore *store = g_object_new (MBT_TYPE_SETTINGS,
                                      NULL);
  return store;
}