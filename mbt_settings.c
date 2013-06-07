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
  _settings = gtk_tree_store_new (N_SETTINGS,
                                  G_TYPE_STRING,
                                  G_TYPE_STRING);

  GtkTreeIter type;
  GtkTreeIter settings;

  gtk_tree_store_append (_settings, &type, NULL);
  gtk_tree_store_append (_settings, &type,
                         SERIAL_SETTINGS, "Serial Settings",
                         ETHERNET_SETTINGS, "Ethernet Settings",
                         -1);

  gtk_tree_store_append (_settings, &set

  
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