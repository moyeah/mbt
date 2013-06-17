#include "mbt_window.h"
#include "mbt_dialog.h"
#include "mbt_connectiondialog.h"
#include "mbt_settingsdialog.h"

enum {
  PROP_0,

  PROP_MENUBAR,
  PROP_TOOLBAR,

  N_PROPERTIES
};

static GParamSpec *mbt_properties[N_PROPERTIES] = { NULL, };

static const gchar *default_window_title = "ModBus Tool";
static const gint default_window_width = 800;
static const gint default_window_height = 600;

G_DEFINE_TYPE (MbtWindow, mbt_window, GTK_TYPE_WINDOW);

static void settings_dialog (GtkWidget *, gpointer);

static void
connection_dialog (GtkWidget *widget,
                   gpointer   _window)
{
  MbtWindow *window = MBT_WINDOW (_window);

  MbtConnectionDialog *dialog =
    mbt_connection_dialog_new (window);

  gint result = mbt_connection_dialog_run (dialog);
  switch (result)
    {
    case MBT_RESPONSE_SERIAL_CONNECT:
      gtk_widget_destroy (GTK_WIDGET (dialog));
GError *error = NULL;
GThread *t1 = g_thread_create ((GThreadFunc) mbt_serial_comm_read,
                               (gpointer) window->serial_comm,
                               FALSE,
                               &error);
GThread *t2 = g_thread_create ((GThreadFunc) mbt_serial_comm_write,
                               (gpointer) window->serial_comm,
                               FALSE,
                               &error);
      break;

    case MBT_RESPONSE_SETTINGS:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      settings_dialog (NULL, (gpointer) window);
      break;

    case GTK_RESPONSE_CANCEL:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      break;

    default:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      break;
    }
}

static void
settings_dialog (GtkWidget *widget,
                 gpointer   _window)
{
  MbtWindow *window = MBT_WINDOW (_window);

  MbtSettingsDialog *dialog = mbt_settings_dialog_new (window);

  gint result = mbt_settings_dialog_run (dialog);
  switch (result)
  {
    case MBT_RESPONSE_CONNECT:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      connection_dialog (NULL, (gpointer) window);
      break;

    case GTK_RESPONSE_APPLY:
      {
        window->serial_comm->port =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->port)));
        window->serial_comm->address =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->address)));
        window->serial_comm->baud_rate =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->baud_rate)));
        window->serial_comm->parity =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->parity)));
        window->serial_comm->stop_bit =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->stop_bit)));
        window->serial_comm->mode =
          g_string_new (
            gtk_combo_box_text_get_active_text (
              GTK_COMBO_BOX_TEXT (dialog->mode)));

        mbt_serial_comm_set_settings (window->serial_comm);

        gtk_widget_destroy (GTK_WIDGET (dialog));

        break;
    }

    case GTK_RESPONSE_CANCEL:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      mbt_serial_comm_get_settings (window->serial_comm);
      break;

    default:
      gtk_widget_destroy (GTK_WIDGET (dialog));
      break;
  }
}

static gboolean
exit_app (GtkWidget *widget,
          GdkEvent  *event,
          gpointer   data)
{
  gtk_main_quit ();
  return FALSE;
}

static void
mbt_window_init (MbtWindow *window)
{
  /* Serial Communication Init */
  window->serial_comm = mbt_serial_comm_new ();

  /* Apply window properties */
  gtk_window_set_title (GTK_WINDOW (window), default_window_title);
  gtk_window_set_default_size (GTK_WINDOW (window),
                               default_window_width,
                               default_window_height);
  gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

  /* Main container */
  GtkWidget *vbox = gtk_vbox_new (FALSE, 0);
  window->mvbox = vbox;
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  /* Menu Bar */
  MbtMenuBar *menubar = mbt_menubar_new ();
  window->menubar = menubar;
  gtk_box_pack_start (GTK_BOX (window->mvbox),
                      GTK_WIDGET (menubar),
                      FALSE, FALSE, 0);
  gtk_widget_show (GTK_WIDGET (menubar));
  g_signal_connect (menubar->connect,
                    "activate",
                    G_CALLBACK (connection_dialog),
                    (gpointer) window);
  g_signal_connect (menubar->comm,
                    "activate",
                    G_CALLBACK (settings_dialog),
                    (gpointer) window);
  g_signal_connect (menubar->quit,
                    "activate",
                    G_CALLBACK (exit_app),
                    NULL);

  /* Toolbar */
  MbtToolBar *toolbar = mbt_toolbar_new ();
  window->toolbar = toolbar;
  gtk_box_pack_start (GTK_BOX (window->mvbox),
                      GTK_WIDGET (toolbar),
                      FALSE, FALSE, 0);
  gtk_widget_show (GTK_WIDGET (toolbar));
  g_signal_connect (toolbar->connect,
                    "clicked",
                    G_CALLBACK (connection_dialog),
                    window);
  g_signal_connect (toolbar->comm,
                    "clicked",
                    G_CALLBACK (settings_dialog),
                    window);
  g_signal_connect (toolbar->quit,
                    "clicked",
                    G_CALLBACK (exit_app),
                    NULL);

  g_signal_connect (GTK_WIDGET (window),
                    "delete-event",
                    G_CALLBACK (exit_app),
                    NULL);
}

static void
mbt_window_set_property (GObject      *object,
                         guint         property_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
  MbtWindow *window = MBT_WINDOW (object);

  switch (property_id)
    {
    case PROP_MENUBAR:
      window->menubar = g_value_get_object (value);
      break;

    case PROP_TOOLBAR:
      window->toolbar = g_value_get_object (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
mbt_window_get_property (GObject    *object,
                         guint       property_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
  MbtWindow *window = MBT_WINDOW (object);

  switch (property_id)
    {
    case PROP_MENUBAR:
      g_value_set_object (value, mbt_window_get_menubar (window));
      break;

    case PROP_TOOLBAR:
      g_value_set_object (value, mbt_window_get_toolbar (window));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
mbt_window_class_init (MbtWindowClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = mbt_window_set_property;
  gobject_class->get_property = mbt_window_get_property;

  mbt_properties[PROP_MENUBAR] =
    g_param_spec_object ("menubar",
                         "Menubar",
                         "The menubar of this window",
                         MBT_TYPE_MENUBAR,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  mbt_properties[PROP_TOOLBAR] =
    g_param_spec_object ("toolbar",
                         "Toolbar",
                         "The toolbar of this window",
                         MBT_TYPE_TOOLBAR,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  g_object_class_install_properties (gobject_class,
                                     N_PROPERTIES,
                                     mbt_properties);
}

MbtWindow*
mbt_window_new (GtkWindow *parent_instance)
{
  return g_object_new (MBT_TYPE_WINDOW,
                       "transient-for", parent_instance,
                       "type", GTK_WINDOW_TOPLEVEL,
                       NULL);
}

MbtMenuBar*
mbt_window_get_menubar (MbtWindow *window)
{
  g_return_val_if_fail (MBT_IS_WINDOW (window), 0);

  return window->menubar;
}

MbtToolBar*
mbt_window_get_toolbar (MbtWindow *window)
{
  g_return_val_if_fail (MBT_IS_WINDOW (window), 0);

  return window->toolbar;
}