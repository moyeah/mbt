#include <gtk/gtk.h>

#include "mbt_toolbar.h"
#include "mbt_menubar.h"
#include "mbt_window.h"
#include "mbt_dialog.h"
#include "mbt_settingsdialog.h"

static const gchar *mbt_baud_rate[] = {
  "110",   "300",   "600",    "1200",   "2400",
  "4800",  "9600",  "14400",  "19200",  "38400",
  "56000", "57600", "115200", "128000", "256000",
  NULL
};

static const gchar *mbt_parity[] = {
  "None", "Even", "Odd",
  NULL
};

static const gchar *mbt_stop_bits[] = {
  "1", "1.5", "2",
  NULL
};

static const gchar *mbt_mode[] = {
  "RTU", "ASCII",
  NULL
};

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
mbt_settings_dialog_init (MbtSettingsDialog *dialog)
{
  gtk_window_set_title (GTK_WINDOW (dialog), default_dialog_title);
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);

  GtkWidget *content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  GtkWidget *hbox = gtk_hbox_new (FALSE, 5); 
  gtk_box_pack_start (GTK_BOX (content_area),
                      hbox,
                      FALSE, FALSE, 0);
  gtk_widget_show (hbox);

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
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             0, 1);
  gtk_widget_show (combobox);

  label = _mbt_label_new_with_mnemonic ("Addr_ess");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             0, 1);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  gint i;
  for (i = 1; i <= 255; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 g_strdup_printf ("%d", i));
    }
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             0, 1);
  gtk_widget_show (combobox);

  label = _mbt_label_new_with_mnemonic ("_Baud Rate");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 1,
                             1, 2);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  for (i = 0; mbt_baud_rate[i]; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 mbt_baud_rate[i]);
    }
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             1, 2);
  gtk_widget_show (combobox);

  label = _mbt_label_new_with_mnemonic ("Par_ity");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             1, 2);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  for (i = 0; mbt_parity[i]; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 mbt_parity[i]);
    }
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             1, 2);
  gtk_widget_show (combobox);

  label = _mbt_label_new_with_mnemonic ("_Stop Bits");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             0, 1,
                             2, 3);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  for (i = 0; mbt_stop_bits[i]; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 mbt_stop_bits[i]);
    }
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             1, 2,
                             2, 3);
  gtk_widget_show (combobox);

  label = _mbt_label_new_with_mnemonic ("_Mode");
  gtk_table_attach_defaults (GTK_TABLE (table),
                             label,
                             2, 3,
                             2, 3);
  gtk_widget_show (label);

  combobox = _mbt_combo_box_text_new (label);
  for (i = 0; mbt_mode[i]; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 mbt_mode[i]);
    }
  gtk_table_attach_defaults (GTK_TABLE (table),
                             combobox,
                             3, 4,
                             2, 3);
  gtk_widget_show (combobox);

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
  i = 0;
  for (i = 1; i <= 255; i++)
    {
      gtk_combo_box_append_text (GTK_COMBO_BOX (combobox),
                                 g_strdup_printf ("%d", i));
    }
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
}

static void
mbt_settings_dialog_class_init (MbtSettingsDialogClass *klass)
{
}

MbtSettingsDialog*
mbt_settings_dialog_new (MbtWindow *parent_instance)
{
  g_return_val_if_fail (MBT_IS_WINDOW (parent_instance), 0);

  GtkWidget *dialog = GTK_WIDGET (g_object_new (MBT_TYPE_SETTINGS_DIALOG,
                                                NULL));
  gtk_window_set_transient_for (GTK_WINDOW (dialog),
                                GTK_WINDOW (parent_instance));  

  return MBT_SETTINGS_DIALOG (dialog);
}

gint
mbt_settings_dialog_run (MbtSettingsDialog *dialog)
{
  g_return_val_if_fail (MBT_IS_SETTINGS_DIALOG (dialog), 0);

  return gtk_dialog_run (GTK_DIALOG (dialog));
}