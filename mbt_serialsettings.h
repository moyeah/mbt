#ifndef __MBT_SERIAL_SETTINGS_H__
#define __MBT_SERIAL_SETTINGS_H__

G_BEGIN_DECLS

#define MBT_TYPE_SERIAL_SETTINGS            (mbt_serial_settings_get_type ())
#define MBT_SERIAL_SETTINGS(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_SERIAL_SETTINGS, MbtSerialSettings))
#define MBT_IS_SERIAL_SETTINGS(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_SERIAL_SETTINGS))
#define MBT_SERIAL_SETTINGS_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_SERIAL_SETTINGS, MbtSerialSettingsClass))

#define MBT_IS_SERIAL_SETTINGS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_SERIAL_SETTINGS))
#define MBT_SERIAL_SETTINGS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_SERIAL_SETTINGS, MbtSerialSettingsClass))

typedef struct _MbtSerialSettings      MbtSerialSettings;
typedef struct _MbtSerialSettingsClass MbtSerialSettingsClass;

struct _MbtSerialSettings
{
  GHashTable parent_instance;

  GHashTable *baud_rates;
};

struct _MbtSerialSettingsClass
{
  GHashTableClass parent_class;
};

GType              mbt_serial_settings_get_type (void) G_GNUC_CONST;
MbtSerialSettings* mbt_serial_settings_new      (void);

G_END_DECLS

#endif /* __MBT_SERIAL_SETTINGS_H__ */