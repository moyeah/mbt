#include "mbt_dialog.h"
#include "mbt_connectiondialog.h"

static const gchar *default_dialog_title = "ModBus Tool - Connection";

G_DEFINE_TYPE (MbtConnectionDialog, mbt_connection_dialog, GTK_TYPE_DIALOG);

static void
serial_connect_cb (GtkWidget *widget,
                   gpointer   data)
{
  gtk_dialog_response (GTK_DIALOG (data),
                       MBT_RESPONSE_SERIAL_CONNECT);
}

static void
button_clicked (GtkWidget *widget,
                gpointer   data)
{
  gtk_dialog_response (GTK_DIALOG (data),
                       MBT_RESPONSE_SETTINGS);
}

static void
mbt_connection_dialog_init (MbtConnectionDialog *dialog)
{
  gtk_window_set_title (GTK_WINDOW (dialog), default_dialog_title);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);

  GtkWidget *content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  GtkWidget *frame = gtk_frame_new ("Connection");
  gtk_container_set_border_width (GTK_CONTAINER (frame), 5);
  gtk_box_pack_start (GTK_BOX (content_area),
                      frame,
                      FALSE, FALSE, 0);
  gtk_widget_show (frame);

  GtkWidget *vbox = gtk_vbutton_box_new ();
  gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), vbox);
  gtk_widget_show (vbox);

  GtkWidget *button = gtk_button_new_with_mnemonic ("MODBUS _Serial");
  gtk_box_pack_start (GTK_BOX (vbox),
                      button,
                      FALSE, FALSE, 0);
  gtk_widget_show (button);
  g_signal_connect (GTK_WIDGET (button),
                    "clicked",
                    G_CALLBACK (serial_connect_cb),
                    (gpointer) dialog);

  button = gtk_button_new_with_mnemonic ("MODBUS _TCP/IP");
  gtk_box_pack_start (GTK_BOX (vbox),
                      button,
                      FALSE, FALSE, 0);
  gtk_widget_show (button);

  GtkWidget *hsep = gtk_hseparator_new ();
  gtk_box_pack_start (GTK_BOX (vbox),
                      hsep,
                      FALSE, FALSE, 0);
  gtk_widget_show (hsep);

  button = gtk_button_new_with_mnemonic ("C_hange Communication Settings");
  gtk_box_pack_start (GTK_BOX (vbox),
                      button,
                      FALSE, FALSE, 0);
  gtk_widget_show (button);
  g_signal_connect (GTK_WIDGET (button),
                    "clicked",
                    G_CALLBACK (button_clicked),
                    (gpointer) dialog);

  button = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog),
                                button,
                                GTK_RESPONSE_CANCEL);
  gtk_widget_show (button);
}

static void
mbt_connection_dialog_class_init (MbtConnectionDialogClass *klass)
{
}

MbtConnectionDialog*
mbt_connection_dialog_new (MbtWindow *parent_instance)
{
  g_return_val_if_fail (MBT_IS_WINDOW (parent_instance), 0);

  GtkWidget *dialog = GTK_WIDGET (g_object_new (MBT_TYPE_CONNECTION_DIALOG,
                                                NULL));
  gtk_window_set_transient_for (GTK_WINDOW (dialog),
                                GTK_WINDOW (parent_instance));  

  return MBT_CONNECTION_DIALOG (dialog);
}

gint
mbt_connection_dialog_run (MbtConnectionDialog *dialog)
{
  g_return_val_if_fail (MBT_IS_CONNECTION_DIALOG (dialog), 0);

  return gtk_dialog_run (GTK_DIALOG (dialog));
}