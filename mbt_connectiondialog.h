#ifndef __MBT_CONNECTION_DIALOG_H__
#define __MBT_CONNECTION_DIALOG_H__

G_BEGIN_DECLS

#define MBT_TYPE_CONNECTION_DIALOG            (mbt_connection_dialog_get_type ())
#define MBT_CONNECTION_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_CONNECTION_DIALOG, MbtConnectionDialog))
#define MBT_IS_CONNECTION_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_CONNECTION_DIALOG))
#define MBT_CONNECTION_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_CONNECTION_DIALOG, MbtConnectionDialogClass))
#define MBT_IS_CONNECTION_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_CONNECTION_DIALOG))
#define MBT_CONNECTION_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_CONNECTION_DIALOG, MbtConnectionDialogClass))

typedef struct _MbtConnectionDialog      MbtConnectionDialog;
typedef struct _MbtConnectionDialogClass MbtConnectionDialogClass;

struct _MbtConnectionDialog
{
  GtkDialog parent_instance;
};

struct _MbtConnectionDialogClass
{
  GtkDialogClass parent_class;
};

GType                mbt_connection_dialog_get_type (void) G_GNUC_CONST;
MbtConnectionDialog* mbt_connection_dialog_new      (MbtWindow*);
gint                 mbt_connection_dialog_run      (MbtConnectionDialog*);

G_END_DECLS

#endif /* __MBT_CONNECTION_DIALOG_H__ */