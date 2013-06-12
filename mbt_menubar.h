#ifndef __MBT_MENUBAR_H__
#define __MBT_MENUBAR_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MBT_TYPE_MENUBAR            (mbt_menubar_get_type ())
#define MBT_MENUBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MENUBAR, MbtMenuBar))
#define MBT_IS_MENUBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MENUBAR))
#define MBT_MENUBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MENUBAR, MbtMenuBarClass))
#define MBT_IS_MENUBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MENUBAR))
#define MBT_MENUBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MENUBAR, MbtMenuBarClass))

typedef struct _MbtMenuBar      MbtMenuBar;
typedef struct _MbtMenuBarClass MbtMenuBarClass;

struct _MbtMenuBar
{
  GtkMenuBar parent_instance;

  GtkWidget *file;
  GtkWidget *connect;
  GtkWidget *disconnect;
  GtkWidget *quit;

  GtkWidget *settings;
  GtkWidget *comm;

  GtkWidget *help;
  GtkWidget *about;
};

struct _MbtMenuBarClass
{
  GtkMenuBarClass parent_class;
};

GType       mbt_menubar_get_type (void) G_GNUC_CONST;
MbtMenuBar* mbt_menubar_new      (void);

G_END_DECLS

#endif /* __MBT_MENUBAR_H__ */