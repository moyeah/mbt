#ifndef __MBT_MB_DEVICE_H__
#define __MBT_MB_DEVICE_H__

#include "mbtmb.h"
#include "mbtmbtypebuildtins.h"

G_BEGIN_DECLS

#define MBT_TYPE_MB_DEVICE             (mbt_mb_device_get_type ())
#define MBT_MB_DEVICE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MB_DEVICE, MbtMBDevice))
#define MBT_IS_MB_DEVICE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MB_DEVICE))
#define MBT_MB_DEVICE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MB_DEVICE))
#define MBT_IS_MB_DEVICE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MB_DEVICE))
#define MBT_MB_DEVICE_GET_CLASS(klass) (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MB_DEVICE, MbtMBDeviceClass))

typedef struct _MbtMBDevice        MbtMBDevice;
typedef struct _MbtMBDevicePrivate MbtMBDevicePrivate;
typedef struct _MbtMBDeviceClass   MbtMBDeviceClass;

struct _MbtMBDevice
{
  MbtMB mb;

  /*< private >*/
  MbtMBDevicePrivate *priv;
};

struct _MbtMBDeviceClass
{
  MbtMBClass parent_class;
};

#define mbt_mb_device_set_tag(mb,tag) (mbt_mb_set_tag (MBT_MB (mb), tag))
#define mbt_mb_device_get_tag(mb)     (mbt_mb_get_tag (MBT_MB (mb)))

GType        mbt_mb_device_get_type (void) G_GNUC_CONST;
MbtMBDevice* mbt_mb_device_new      (MbtMBMode    mb_mode,
                                     const gchar *tag);
void         mbt_mb_device_set_mode (MbtMBDevice *mb_device,
                                     MbtMBMode    mb_mode);
MbtMBMode    mbt_mb_device_get_mode (MbtMBDevice *mb_device);

G_END_DECLS

#endif /* __MBT_MB_DEVICE_H__ */