#ifndef __MBT_SETTINGS_DIALOG_H__
#define __MBT_SETTINGS_DIALOG_H__

G_BEGIN_DECLS

#define MBT_TYPE_SETTINGS_DIALOG            (mbt_settings_dialog_get_type ())
#define MBT_SETTINGS_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_SETTINGS_DIALOG, MbtSettingsDialog))
#define MBT_IS_SETTINGS_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_SETTINGS_DIALOG))
#define MBT_SETTINGS_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_SETTINGS_DIALOG, MbtSettingsDialogClass))
#define MBT_IS_SETTINGS_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_SETTINGS_DIALOG))
#define MBT_SETTINGS_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_SETTINGS_DIALOG, MbtSettingsDialogClass))

typedef struct _MbtSettingsDialog      MbtSettingsDialog;
typedef struct _MbtSettingsDialogClass MbtSettingsDialogClass;

struct _MbtSettingsDialog
{
  GtkDialog parent_instance;
};

struct _MbtSettingsDialogClass
{
  GtkDialogClass parent_class;
};

GType              mbt_settings_dialog_get_type (void) G_GNUC_CONST;
MbtSettingsDialog* mbt_settings_dialog_new      (MbtWindow*);
gint               mbt_settings_dialog_run      (MbtSettingsDialog*);

G_END_DECLS

#endif /* __MBT_SETTINGS_DIALOG_H__ */