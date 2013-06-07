#ifndef __MBT_SETTINGS_H__
#define __MBT_SETTINGS_H__

G_BEGIN_DECLS

#define MBT_TYPE_SETTINGS            (mbt_settings_get_type ())
#define MBT_SETTINGS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_SETTINGS, MbtSettings))
#define MBT_IS_SETTINGS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_SETTINGS))
#define MBT_SETTINGS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_SETTINGS, MbtSettingsClass))

#define MBT_IS_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_SETTINGS))
#define MBT_SETTINGS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_SETTINGS, MbtSettingsClass))

typedef struct _MbtSettings      MbtSettings;
typedef struct _MbtSettingsClass MbtSettingsClass;

struct _MbtSettings
{
  GtkListStore parent_instance;

  GtkListStore *baud_rates;
};

struct _MbtSettingsClass
{
  GtkListStoreClass parent_class;
};

GType        mbt_settings_get_type (void) G_GNUC_CONST;
MbtSettings* mbt_settings_new      (void);

G_END_DECLS

#endif /* __MBT_SETTINGS_H__ */