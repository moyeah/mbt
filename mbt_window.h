#ifndef __MBT_WINDOW_H__
#define __MBT_WINDOW_H__

#include <gtk/gtk.h>

#include "mbt_menubar.h"
#include "mbt_toolbar.h"
#include "mbt_serialcomm_win32.h"

#ifdef G_OS_WIN32
#include "mbt_serialcomm_win32.h"
#endif /* G_OS_WIN32 */

G_BEGIN_DECLS

#define MBT_TYPE_WINDOW            (mbt_window_get_type ())
#define MBT_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_WINDOW, MbtWindow))
#define MBT_IS_WINDOW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_WINDOW))
#define MBT_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_WINDOW, MbtWindowClass))
#define MBT_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_WINDOW))
#define MBT_WINDOW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_WINDOW, MbtWindowClass))

typedef struct _MbtWindow      MbtWindow;
typedef struct _MbtWindowClass MbtWindowClass;

struct _MbtWindow
{
  GtkWindow parent_instance;

  GtkWidget     *mvbox;
  MbtMenuBar    *menubar;
  MbtToolBar    *toolbar;
  MbtSerialComm *serial_comm;
};

struct _MbtWindowClass
{
  GtkWindowClass parent_class;
};

GType       mbt_window_get_type    (void) G_GNUC_CONST;
MbtWindow*  mbt_window_new         (GtkWindow*);
MbtMenuBar* mbt_window_get_menubar (MbtWindow*);
MbtToolBar* mbt_window_get_toolbar (MbtWindow*);

G_END_DECLS

#endif /* __MBT_WINDOW_H__ */