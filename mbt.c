#include <gtk/gtk.h>

#include "mbt_window.h"

int
main (int argc, char *argv[])
{
  if (!g_thread_supported ())
    g_thread_init (NULL);

  gdk_threads_init ();

  gdk_threads_enter ();

  gtk_init (&argc, &argv);

  MbtWindow *window = mbt_window_new (NULL);
  gtk_widget_show (GTK_WIDGET (window));

guint16 message[] = { 0x00, 0x01 };
guint16 mbt_crc_gen (guint16 message[], gint len);
g_print ("crc_reg: %0.4X\n", mbt_crc_gen (message, 2));

unsigned char buf[] = { 0x00, 0x01 };
unsigned int crc(unsigned char *buf,int start,int cnt);
g_print ("crc: %0.4X\n", crc (buf, 0, 2));

  gtk_main ();

  gdk_threads_leave ();

  return 0;
}