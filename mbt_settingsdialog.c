#include "mbt_dialog.h"
#include "mbt_settingsdialog.h"

static const gchar *default_dialog_title = "ModBus Tool - Settings";

G_DEFINE_TYPE (MbtSettingsDialog, mbt_settings_dialog, GTK_TYPE_DIALOG);

static GtkWidget*
_mbt_frame_new (const gchar *label)
{
  GtkWidget *frame = gtk_frame_new (label);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 5);

  return frame;
}

static GtkWidget*
_mbt_table_new (guint rows, guint columns)
{
  GtkWidget *table = gtk_table_new (rows, columns, FALSE);
  gtk_table_set_row_spacings (GTK_TABLE (table), 5);
  gtk_table_set_col_spacings (GTK_TABLE (table), 5);
  gtk_container_set_border_width (GTK_CONTAINER (table), 5);

  return table;
}

static GtkWidget*
_mbt_label_new_with_mnemonic (const gchar *str)
{
  GtkWidget *label = gtk_label_new_with_mnemonic (str);
  gtk_misc_set_alignment (GTK_MISC (label),
                          0, 0.5);

  return label;
}

static GtkWidget*
_mbt_combo_box_text_new (GtkWidget *label)
{
  GtkWidget *combobox = gtk_combo_box_text_new ();
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), combobox);

  return combobox;
}

static GtkWidget*
_mbt_entry_new_with_max_length (gint max, GtkWidget *label)
{
  GtkWidget *entry = gtk_entry_new_with_max_length (max);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), entry);

  return entry;
}

static void
_mbt_combobox_fill (GtkWidget *combobox, GList *list)
{
  guint n;

  if (!list)
    gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                               "Not available");

  else
  {
    for (n = 0; n < g_list_length (list); list = g_list_next (list))
    {
      gtk_combo_box_append_text (
        GTK_COMBO_BOX (combobox),
        (const gchar *) g_list_nth_data (list, n));
    }
  }

  gtk_combo_box_set_active (GTK_COMBO_BOX (combobox), 0);
}

static void
_mbt_combobox_set_active (GtkWidget *combobox,
                          GList     *list,
                          GString   *string)
{
  if (!list || !string)
    return;

  gint n;
  gint i = -1;

  for (n = 0; n < g_list_length (list); list = g_list_next (list))
    {
      i++;
      if (g_string_equal (g_string_new (g_list_nth_data (list, n)),
                          string))
      {
        gtk_combo_box_set_active (GTK_COMBO_BOX (combobox), i);
        return;
      }
    }
}

static void
combobox_changed_cb (GtkWidget *combobox,
                     gpointer   data)
{
  GString *string = (GString *) data;
  gchar *active = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (combobox));
  string = g_string_new (active);
g_print ("%s\n", active);
g_print ("%s\n", string->str);
  g_free (active);
}

static void
combobox1_changed_cb (GtkWidget *combobox,
                      gpointer   data)
{
  MbtWindow *window = MBT_WINDOW (data);
  gchar *active = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT (combobox));
  window->serial_comm->address = g_string_new (active);
g_print ("%s\n", active);
//g_print ("%s\n", string->str);
  g_free (active);
}

static void
mbt_settings_dialog_init (MbtSettingsDialog *_dialog)
{
  GtkWindow *dialog = GTK_WINDOW (_dialog);
  gtk_window_set_title (dialog, default_dialog_title);
  gtk_window_set_position (dialog, GTK_WIN_POS_CENTER);
  gtk_window_set_modal (dialog, TRUE);
  gtk_window_set_resizable (dialog, FALSE);
}

static void
mbt_settings_dialog_class_init (MbtSettingsDialogClass *klass)
{
}

MbtSettingsDialog*
mbt_settings_dialog_new (MbtWindow *window)
{
  g_return_val_if_fail (MBT_IS_WINDOW (window), 0);

  /* Refresh Serial Comm Ports */
  MbtSerialComm *serial_comm = window->serial_comm;
  mbt_serial_comm_refresh_ports (serial_comm);
  mbt_serial_comm_get_settings (serial_comm);

  GtkWidget *dialog = GTK_WIDGET (g_object_new (MBT_TYPE_SETTINGS_DIALOG,
                                                NULL));
  gtk_window_set_transient_for (GTK_WINDOW (dialog),
                                GTK_WINDOW (window));

  GtkWidget *content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  GtkWidget *hbox = gtk_hbox_new (FALSE, 5); 
  gtk_box_pack_start (GTK_BOX (content_area),
                      hbox,
                      FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  /* Serial Settings */
  GtkWidget *frame = _mbt_frame_new ("Serial Settings");
  gtk_box_pack_start (GTK_BOX (hbox),
                      frame,
                      FALSE, FALSE, 0);
  gtk_widget_show (frame);

  GtkWidget *table = _mbt_table_new (3, 4);
  gtk_container_add (GTK_CONTAINER (frame), table);
  gtk_widget_show (table);

  GtkWidget *label = _mbt_label_new_with_mnemonic ("_Port");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 1,
                             0, 1);
  gtk_widget_show (label);

  GtkWidget *combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->ports);
  _mbt_combobox_set_active (combobox,
                            serial_comm->ports, 
                            serial_comm->port);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             0, 1);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox_changed_cb),
                    serial_comm->port);

  label = _mbt_label_new_with_mnemonic ("Addr_ess");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             0, 1);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->addresses);
  _mbt_combobox_set_active (combobox,
                            serial_comm->addresses, 
                            serial_comm->address);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             0, 1);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox1_changed_cb),
                    (gpointer) window);
                    //(gpointer) serial_comm->address);

  label = _mbt_label_new_with_mnemonic ("_Baud Rate");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 1,
                             1, 2);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->baud_rates);
  _mbt_combobox_set_active (combobox,
                            serial_comm->baud_rates, 
                            serial_comm->baud_rate);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             1, 2);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox_changed_cb),
                    (gpointer) serial_comm->baud_rate);

  label = _mbt_label_new_with_mnemonic ("Par_ity");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             1, 2);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->parities);
  _mbt_combobox_set_active (combobox,
                            serial_comm->parities, 
                            serial_comm->parity);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             1, 2);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox_changed_cb),
                    (gpointer) serial_comm->parity);

  label = _mbt_label_new_with_mnemonic ("_Stop Bits");
  gtk_table_attach_defaults (GTK_TABLE (table),
                               label,
                               0, 1,
                               2, 3);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->stop_bits);
  _mbt_combobox_set_active (combobox,
                            serial_comm->stop_bits, 
                            serial_comm->stop_bit);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             2, 3);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox_changed_cb),
                    (gpointer) serial_comm->stop_bit);

  label = _mbt_label_new_with_mnemonic ("_Mode");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             2, 3);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->modes);
  _mbt_combobox_set_active (combobox,
                            serial_comm->modes, 
                            serial_comm->mode);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             2, 3);
  gtk_widget_show (combobox);
  g_signal_connect (combobox,
                    "changed",
                    G_CALLBACK (combobox_changed_cb),
                    (gpointer) serial_comm->mode);

  /* Ethernet Settings */
  frame = _mbt_frame_new ("Ethernet Settings");
  gtk_box_pack_start (GTK_BOX (hbox),
                      frame,
                      FALSE, FALSE, 0);
  gtk_widget_show (frame);

  table = _mbt_table_new (3, 2);
  gtk_container_add (GTK_CONTAINER (frame), table);
  gtk_widget_show (table);

  label = _mbt_label_new_with_mnemonic ("_Remote IP Address");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 2,
                             0, 1);
  gtk_widget_show (label);

  GtkWidget *entry = _mbt_entry_new_with_max_length (15, label);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             entry,
                             0, 2,
                             1, 2);
  gtk_widget_show (entry);

  label = _mbt_label_new_with_mnemonic ("Slave A_ddress");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 1,
                             2, 3);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  _mbt_combobox_fill (combobox, serial_comm->addresses);
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             2, 3);
  gtk_widget_show (combobox);

  GtkWidget *button = gtk_button_new_from_stock (GTK_STOCK_CONNECT);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog),
                                button,
                                MBT_RESPONSE_CONNECT);
  gtk_widget_show (button);

  button = gtk_button_new_from_stock (GTK_STOCK_APPLY);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog),
                                button,
                                GTK_RESPONSE_APPLY);
  gtk_widget_show (button);

  button = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
  gtk_dialog_add_action_widget (GTK_DIALOG (dialog),
                                button,
                                GTK_RESPONSE_CANCEL);
  gtk_widget_show (button);


  return MBT_SETTINGS_DIALOG (dialog);
}

gint
mbt_settings_dialog_run (MbtSettingsDialog *dialog)
{
  g_return_val_if_fail (MBT_IS_SETTINGS_DIALOG (dialog), 0);

  return gtk_dialog_run (GTK_DIALOG (dialog));
}