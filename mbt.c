#include <gtk/gtk.h>

#include "mbt_window.h"

int
main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);

  MbtWindow *window = mbt_window_new (NULL);
  gtk_widget_show (GTK_WIDGET (window));

  gtk_main ();

  return 0;
}