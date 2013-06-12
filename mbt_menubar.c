#include "mbt_menubar.h"

G_DEFINE_TYPE (MbtMenuBar, mbt_menubar, GTK_TYPE_MENU_BAR);

static void
_mbt_set_submenu (GtkWidget *item, GtkWidget *menu)
{
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), menu);
  gtk_widget_show (item);
}

static void
_mbt_append (GtkWidget *menu, GtkWidget *item)
{
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);
}

static GtkWidget*
_mbt_submenu_new (const gchar *label, GtkWidget *menu)
{
  GtkWidget *submenu = gtk_menu_new ();

  GtkWidget *item = gtk_menu_item_new_with_mnemonic (label);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (item), submenu);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);

  return submenu;
}

static GtkWidget*
_mbt_item_new (const gchar *label, GtkWidget *menu)
{
  GtkWidget *item = gtk_menu_item_new_with_mnemonic (label);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);

  return item;
}

static GtkWidget*
_mbt_item_new_from_stock (const gchar *stock_id, GtkWidget *menu)
{
  GtkWidget *item = gtk_image_menu_item_new_from_stock (stock_id, NULL);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);

  return item;
}

static GtkWidget*
_mbt_check_item_new (const gchar *label, GtkWidget *menu)
{
  GtkWidget *item = gtk_check_menu_item_new_with_mnemonic (label);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);

  return item;
}

static void
_mbt_separator_new (GtkWidget *menu)
{
  GtkWidget *item = gtk_separator_menu_item_new ();
  gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
  gtk_widget_show (item);
}

static void
mbt_menubar_init (MbtMenuBar *_menubar)
{
  /* Menu Bar */
  GtkWidget *menubar = GTK_WIDGET (_menubar);

  /* File menu */
  GtkWidget *menu = _mbt_submenu_new ("_File", menubar);
  _menubar->connect = _mbt_item_new_from_stock (GTK_STOCK_CONNECT, menu);
  _menubar->disconnect = _mbt_item_new_from_stock (GTK_STOCK_DISCONNECT, menu);
  _mbt_separator_new (menu);
  _menubar->quit = _mbt_item_new_from_stock (GTK_STOCK_QUIT, menu);

  /* View menu */
  menu = _mbt_submenu_new ("_View", menubar);
  GtkWidget *submenu = _mbt_submenu_new ("_Toolbars", menu);
  _mbt_check_item_new ("_Menu Bar", submenu);
  _mbt_check_item_new ("_Toolbar", submenu);

  /* Settings menu */
  menu = _mbt_submenu_new ("_Settings", menubar);
  _menubar->comm = _mbt_item_new_from_stock (GTK_STOCK_PREFERENCES, menu);

  /* Help menu */
  menu = _mbt_submenu_new ("_Help", menubar);
  _menubar->help = _mbt_item_new_from_stock (GTK_STOCK_HELP, menu);
  _menubar->about = _mbt_item_new_from_stock (GTK_STOCK_ABOUT, menu);
}

static void
mbt_menubar_class_init (MbtMenuBarClass *klass)
{
}

MbtMenuBar*
mbt_menubar_new (void)
{
  return g_object_new (MBT_TYPE_MENUBAR, NULL);
}