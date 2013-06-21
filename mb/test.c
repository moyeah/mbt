#include <stdio.h>

#include "mbtmbdataitem.h"
#include "mbtmbdevice.h"

//#define PAUSE

static void
test_pause (const gchar *text)
{
  g_print (text);

#ifdef PAUSE 
  g_print ("SLEEP\nPress any key to continue.");
  getchar ();
  g_print ("END SLEEP\n\n");
#endif
}

static void
test_print_mbt_mb (GList *mb)
{
  g_print ("\nBEGINING print mbt_mb\n");
  GList *list = g_list_first (mb);
  guint i;
  for (i = 0; i < g_list_length (mb); list = g_list_next (mb), i++)
    {
      MbtMB *_mb = MBT_MB (g_list_nth_data (mb, i));
      g_print ("MbtMB[%d]: %s\n", i, mbt_mb_get_tag (_mb));
    }
  test_pause ("END print mbt_mb\n");
}

static void
test_print_mbt_mb_data_item (GList *mb_data_item)
{
  g_print ("\nBEGINING print mbt_mb_data_item\n");
  GList *list = g_list_first (mb_data_item);
  guint i;
  for (i = 0;
       i < g_list_length (mb_data_item);
       list = g_list_next (mb_data_item), i++)
    {
      MbtMBDataItem *_mb_data_item;
      _mb_data_item = MBT_MB_DATA_ITEM (g_list_nth_data (mb_data_item,
                                                         i));
      g_print ("MbtMBDataItem[%d]: tag: %s, address: %d\n",
               i,
               mbt_mb_data_item_get_tag (_mb_data_item),
               mbt_mb_data_item_get_address (_mb_data_item));
    }
  test_pause ("END print mbt_mb_data_item\n");
}

static void
test_print_mbt_mb_device (GList *mb_device)
{
  g_print ("\nBEGINING print mbt_mb_device\n");
  GList *list = g_list_first (mb_device);
  guint i;
  for (i = 0;
       i < g_list_length (mb_device);
       list = g_list_next (mb_device), i++)
    {
      MbtMBDevice *_mb_device;
      _mb_device = MBT_MB_DEVICE (g_list_nth_data (mb_device, i));

      MbtMBMode mb_mode = mbt_mb_device_get_mode (_mb_device);

      gchar *mode;
      switch (mb_mode)
        {
        case MBT_MB_RTU:
          mode = "RTU";
          break;

        case MBT_MB_ASCII:
          mode = "ASCII";
          break;

        case MBT_MB_TCPIP:
          mode = "TCP/IP";
          break;

        default:
          g_warning ("Unknown Device Mode");
          break;
        }

      g_print ("MbtMBDevice[%d]: tag: %s, mode: %s\n",
               i,
               mbt_mb_device_get_tag (_mb_device),
               mode);

      g_free (mode);
    }
  test_pause ("END print mbt_mb_device\n");
}

static void
test_mbt_mb (void)
{
  g_print ("\nSTART mbt_mb ()\n");

  GList *mb = NULL;

  mb = g_list_append (mb, mbt_mb_new (NULL));
  test_pause ("mb 0 added\n");
  mb = g_list_append (mb, mbt_mb_new (""));
  test_pause ("mb 1 added\n");
  mb = g_list_append (mb, mbt_mb_new ("mb2"));
  test_pause ("mb 2 added\n");

  MbtMB *_mb = mbt_mb_new (NULL);
  test_pause ("mb 3 created\n");
  mbt_mb_set_tag (_mb, "mb3");
  test_pause ("mb 3 set tag\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 3 added\n");

  test_print_mbt_mb (mb);

  g_list_free (mb);
  test_pause ("list mb free\n");

  g_print ("END mbt_mb ()\n");
}

static void
test_mbt_mb_data_item (void)
{
  g_print ("\nSTART mbt_mb_data_item ()\n");

  guint16 i = 0;
  GList *mb_data_item = NULL;

  mb_data_item = g_list_append (mb_data_item,
                                mbt_mb_data_item_new (++i, NULL));
  test_pause ("mb_data_item 0 added\n");
  mb_data_item = g_list_append (mb_data_item,
                                mbt_mb_data_item_new (++i, ""));
  test_pause ("mb_data_item 1 added\n");
  mb_data_item = g_list_append (mb_data_item,
                                mbt_mb_data_item_new (++i,
                                                      "mb_data_item2"));
  test_pause ("mb_data_item 2 added\n");

  MbtMBDataItem *_mb_data_item = mbt_mb_data_item_new (++i, NULL);
  test_pause ("mb_data_item 3 created\n");
  mbt_mb_data_item_set_tag (_mb_data_item, "mb_data_item3");
  test_pause ("mb_data_item 3 set tag\n");
  mb_data_item = g_list_append (mb_data_item, _mb_data_item);
  test_pause ("mb_data_item 3 added\n");

  _mb_data_item = mbt_mb_data_item_new (0x0000, "mb_data_item4");
  test_pause ("mb_data_item 4 created\n");
  mbt_mb_data_item_set_address (_mb_data_item, ++i);
  test_pause ("mb_data_item 4 set address\n");
  mb_data_item = g_list_append (mb_data_item, _mb_data_item);
  test_pause ("mb_data_item 4 added\n");

  _mb_data_item = mbt_mb_data_item_new (++i, "");
  mbt_mb_set_tag (MBT_MB (_mb_data_item), "mb_data_item5");
  test_pause ("mb_data_item by mb_set_tag 5 set tag\n");
  mb_data_item = g_list_append (mb_data_item, _mb_data_item);
  test_pause ("mb_data_item 5 added\n");

  test_print_mbt_mb_data_item (mb_data_item);

  g_list_free (mb_data_item);
  test_pause ("list mb_data_item free\n");

  g_print ("END mbt_mb_data_item ()\n");
}

static void
test_mbt_mb_mbt_mb_data_item (void)
{
  g_print ("\nSTART mbt_mb_mbt_mb_data_item ()\n");

  guint16 i = 0;
  GList *mb = NULL;

  mb = g_list_append (mb, MBT_MB (mbt_mb_data_item_new (++i, NULL)));
  test_pause ("mb 0 added\n");
  mb = g_list_append (mb, MBT_MB (mbt_mb_data_item_new (++i, "")));
  test_pause ("mb 1 added\n");
  mb = g_list_append (mb, MBT_MB (mbt_mb_data_item_new (++i, "mb2")));
  test_pause ("mb 2 added\n");

  MbtMB *_mb = MBT_MB (mbt_mb_data_item_new (++i, NULL));
  test_pause ("mb 3 created\n");
  mbt_mb_data_item_set_tag (MBT_MB_DATA_ITEM (_mb), "mb3");
  test_pause ("mb 3 set tag\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 3 added\n");

  _mb = MBT_MB (mbt_mb_data_item_new (0x0000, "mb4"));
  test_pause ("mb 4 created\n");
  mbt_mb_data_item_set_address (MBT_MB_DATA_ITEM (_mb), ++i);
  test_pause ("mb 4 set address\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 4 added\n");

  _mb = MBT_MB (mbt_mb_data_item_new (++i, ""));
  mbt_mb_set_tag (_mb, "mb5");
  test_pause ("mb 5 set tag\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 5 added\n");

  test_print_mbt_mb (mb);
  test_print_mbt_mb_data_item (mb);

  g_list_free (mb);
  test_pause ("list mb free\n");

  g_print ("END mbt_mb_mbt_mb_data_item ()\n");
}

static void
test_mbt_mb_device (void)
{
  g_print ("\nSTART mbt_mb_device ()\n");

  GList *mb_device = NULL;

  mb_device = g_list_append (mb_device,
                             mbt_mb_device_new (MBT_MB_TCPIP, NULL));
  test_pause ("mb_device 0 added\n");
  mb_device = g_list_append (mb_device,
                             mbt_mb_device_new (MBT_MB_RTU, "mb_device1"));
  test_pause ("mb_device 1 added\n");
  mb_device = g_list_append (mb_device,
                             mbt_mb_device_new (MBT_MB_ASCII, ""));
  test_pause ("mb_device 2 added\n");

  MbtMBDevice *_mb_device = mbt_mb_device_new (MBT_MB_TCPIP, NULL);
  test_pause ("mb_device 3 created\n");
  mbt_mb_device_set_tag (_mb_device, "mb_device3");
  test_pause ("mb_device 3 set tag\n");
  mb_device = g_list_append (mb_device, _mb_device);
  test_pause ("mb_device 3 added\n");

  _mb_device = mbt_mb_device_new (MBT_MB_TCPIP, "mb_device4");
  test_pause ("mb_device 4 created\n");
  mbt_mb_device_set_mode (_mb_device, MBT_MB_RTU);
  test_pause ("mb_device 4 set mode\n");
  mb_device = g_list_append (mb_device, _mb_device);
  test_pause ("mb_device 4 added\n");

  _mb_device = mbt_mb_device_new (MBT_MB_ASCII, "");
  mbt_mb_set_tag (MBT_MB (_mb_device), "mb_device5");
  test_pause ("mb_device by mb_set_tag 5 set tag\n");
  mb_device = g_list_append (mb_device, _mb_device);
  test_pause ("mb_device 5 added\n");

  test_print_mbt_mb_device (mb_device);

  g_list_free (mb_device);
  test_pause ("list mb_device_item free\n");

  g_print ("END mbt_mb_device ()\n");
}

static void
test_mbt_mb_mbt_mb_device (void)
{
  g_print ("\nSTART mbt_mb_mbt_mb_device ()\n");

  GList *mb = NULL;

  mb = g_list_append (mb, MBT_MB (mbt_mb_device_new (MBT_MB_RTU, NULL)));
  test_pause ("mb 0 added\n");
  mb = g_list_append (mb, MBT_MB (mbt_mb_device_new (MBT_MB_ASCII, "")));
  test_pause ("mb 1 added\n");
  mb = g_list_append (mb, MBT_MB (mbt_mb_device_new (MBT_MB_TCPIP, "mb2")));
  test_pause ("mb 2 added\n");

  MbtMB *_mb = MBT_MB (mbt_mb_device_new (MBT_MB_RTU, NULL));
  test_pause ("mb 3 created\n");
  mbt_mb_device_set_tag (MBT_MB_DEVICE (_mb), "mb3");
  test_pause ("mb 3 set tag\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 3 added\n");

  _mb = MBT_MB (mbt_mb_device_new (MBT_MB_ASCII, "mb4"));
  test_pause ("mb 4 created\n");
  mbt_mb_device_set_mode (MBT_MB_DEVICE (_mb), MBT_MB_TCPIP);
  test_pause ("mb 4 set mode\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 4 added\n");

  _mb = MBT_MB (mbt_mb_device_new (MBT_MB_RTU, ""));
  mbt_mb_set_tag (_mb, "mb5");
  test_pause ("mb 5 set tag\n");
  mb = g_list_append (mb, _mb);
  test_pause ("mb 5 added\n");

  test_print_mbt_mb (mb);
  test_print_mbt_mb_device (mb);

  g_list_free (mb);
  test_pause ("list mb free\n");

  g_print ("END mbt_mb_mbt_mb_device ()\n");
}

int
main (int   argc,
      char *argv[])
{
  g_type_init ();

  test_mbt_mb ();
  test_mbt_mb_data_item ();
  test_mbt_mb_mbt_mb_data_item ();
  test_mbt_mb_device ();
  test_mbt_mb_mbt_mb_device ();

  return 0;
}