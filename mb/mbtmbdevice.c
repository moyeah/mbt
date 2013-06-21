#include "config.h"

#include "mbtmbdevice.h"
#include "mbtmbenums.h"

struct _MbtMBDevicePrivate
{
  MbtMBMode mb_mode;
};

enum {
  PROP_0,

  PROP_MODE,

  N_PROPERTIES
};

static void mbt_mb_device_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec);
static void mbt_mb_device_get_property (GObject      *object,
                                        guint         prop_id,
                                        GValue       *value,
                                        GParamSpec   *pspec);



G_DEFINE_TYPE (MbtMBDevice, mbt_mb_device, MBT_TYPE_MB);

static void
mbt_mb_device_class_init (MbtMBDeviceClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = mbt_mb_device_set_property;
  gobject_class->get_property = mbt_mb_device_get_property;

  g_object_class_install_property (gobject_class,
                                   PROP_MODE,
                                   g_param_spec_enum ("mode",
                                                      _("Mode"),
                                                      _("Mode type"),
                                                      MBT_TYPE_MB_MODE,
                                                      MBT_MB_TCPIP,
                                                      G_PARAM_READWRITE));

  g_type_class_add_private (klass, sizeof (MbtMBDevicePrivate));
}

static void
mbt_mb_device_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  MbtMBDevice *mb_device = MBT_MB_DEVICE (object);

  switch (prop_id)
    {
    case PROP_MODE:
      mbt_mb_device_set_mode (mb_device, g_value_get_enum (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_device_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  MbtMBDevice *mb_device = MBT_MB_DEVICE (object);
  MbtMBDevicePrivate *priv = mb_device->priv;

  switch (prop_id)
    {
    case PROP_MODE:
      g_value_set_enum (value, priv->mb_mode);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_device_init (MbtMBDevice *mb_device)
{
  MbtMBDevicePrivate *priv;

  mb_device->priv = G_TYPE_INSTANCE_GET_PRIVATE (mb_device,
                                                 MBT_TYPE_MB_DEVICE,
                                                 MbtMBDevicePrivate);

  priv = mb_device->priv;

  priv->mb_mode = MBT_MB_TCPIP;

  mbt_mb_device_set_tag (mb_device, NULL);
}

MbtMBDevice*
mbt_mb_device_new (MbtMBMode    mb_mode,
                   const gchar *tag)
{
  g_return_val_if_fail (MBT_IS_MB_MODE (mb_mode), NULL);

  MbtMBDevice *mb_device = g_object_new (MBT_TYPE_MB_DEVICE, NULL);

  mbt_mb_device_set_mode (mb_device, mb_mode);
  mbt_mb_device_set_tag (mb_device, tag);

  return mb_device;
}

void
mbt_mb_device_set_mode (MbtMBDevice *mb_device,
                        MbtMBMode    mb_mode)
{
  g_return_if_fail (MBT_IS_MB_DEVICE (mb_device));
  g_return_if_fail (MBT_IS_MB_MODE (mb_mode));

  MbtMBDevicePrivate *priv = mb_device->priv;

  if (priv->mb_mode != mb_mode)
    {
      priv->mb_mode = mb_mode;

      g_object_notify (G_OBJECT (mb_device), "mode");
    }
}

MbtMBMode
mbt_mb_device_get_mode (MbtMBDevice *mb_device)
{
  g_return_val_if_fail (MBT_IS_MB_DEVICE (mb_device), 0);

  return mb_device->priv->mb_mode;
}