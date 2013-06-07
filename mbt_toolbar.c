#include <gtk/gtk.h>

#include "mbt_toolbar.h"

G_DEFINE_TYPE (MbtToolBar, mbt_toolbar, GTK_TYPE_TOOLBAR);

static GtkWidget*
_mbt_button_new_from_stock (const gchar *stock_id, GtkWidget *toolbar)
{
  GtkToolItem *button = gtk_tool_button_new_from_stock (stock_id);
  gtk_toolbar_insert (GTK_TOOLBAR (toolbar), button, -1);
  gtk_widget_show (GTK_WIDGET (button));

  return GTK_WIDGET (button);
}

static void
_mbt_separator_new (GtkWidget *toolbar)
{
  GtkToolItem *item = gtk_separator_tool_item_new ();
  gtk_toolbar_insert (GTK_TOOLBAR (toolbar), item, -1);
  gtk_widget_show (GTK_WIDGET (item));
}

static void
mbt_toolbar_init (MbtToolBar *_toolbar)
{
  /* Toolbar */
  GtkWidget *toolbar = GTK_WIDGET (_toolbar);

  /* Tool buttons */
  _toolbar->connect = _mbt_button_new_from_stock (GTK_STOCK_CONNECT,
                                                  toolbar);
  _toolbar->disconnect = _mbt_button_new_from_stock (GTK_STOCK_DISCONNECT,
                                                     toolbar);
  _mbt_separator_new (toolbar);
  _toolbar->comm = _mbt_button_new_from_stock (GTK_STOCK_PREFERENCES,
                                               toolbar);
  _mbt_separator_new (toolbar);
  _toolbar->quit = _mbt_button_new_from_stock (GTK_STOCK_QUIT,
                                               toolbar);
}

static void
mbt_toolbar_class_init (MbtToolBarClass *klass)
{
}

MbtToolBar*
mbt_toolbar_new (void)
{
  return g_object_new (MBT_TYPE_TOOLBAR,
                       "toolbar-style", GTK_TOOLBAR_ICONS,
                       NULL);
}