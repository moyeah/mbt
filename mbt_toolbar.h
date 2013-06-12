#ifndef __MBT_TOOLBAR_H__
#define __MBT_TOOLBAR_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define MBT_TYPE_TOOLBAR            (mbt_toolbar_get_type ())
#define MBT_TOOLBAR(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_TOOLBAR, MbtToolBar))
#define MBT_IS_TOOLBAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_TOOLBAR))
#define MBT_TOOLBAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_TOOLBAR, MbtToolBarClass))
#define MBT_IS_TOOLBAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_TOOLBAR))
#define MBT_TOOLBAR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_TOOLBAR, MbtToolBarClass))

typedef struct _MbtToolBar      MbtToolBar;
typedef struct _MbtToolBarClass MbtToolBarClass;

struct _MbtToolBar
{
  GtkToolbar parent_instance;

  GtkWidget *connect;
  GtkWidget *disconnect;
  GtkWidget *comm;
  GtkWidget *quit;
};

struct _MbtToolBarClass
{
  GtkToolbarClass parent_class;
};

GType       mbt_toolbar_get_type (void) G_GNUC_CONST;
MbtToolBar* mbt_toolbar_new      (void);

G_END_DECLS

#endif /* __MBT_TOOLBAR_H__ */