#include "config.h"

#include "mbtmbdataitem.h"

struct _MbtMBDataItemPrivate
{
  guint32 address;
};

enum {
  PROP_0,

  PROP_ADDRESS,

  N_PROPERTIES
};

static void mbt_mb_data_item_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void mbt_mb_data_item_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);

G_DEFINE_TYPE (MbtMBDataItem, mbt_mb_data_item, MBT_TYPE_MB);

static void
mbt_mb_data_item_class_init (MbtMBDataItemClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->set_property = mbt_mb_data_item_set_property;
  gobject_class->get_property = mbt_mb_data_item_get_property;

  g_object_class_install_property (gobject_class,
                                   PROP_ADDRESS,
                                   g_param_spec_uint ("address",
                                                      _("Address"),
                                                      _("Address of data"),
                                                      0x0000,
                                                      0xFFFF,
                                                      0x0000,
                                                      G_PARAM_READWRITE));

  g_type_class_add_private (klass, sizeof (MbtMBDataItem));
}

static void
mbt_mb_data_item_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  MbtMBDataItem *mb_data_item = MBT_MB_DATA_ITEM (object);

  switch (prop_id)
    {
    case PROP_ADDRESS:
        mbt_mb_data_item_set_address (mb_data_item,
                                      g_value_get_uint (value));
        break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_data_item_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  MbtMBDataItem *mb_data_item = MBT_MB_DATA_ITEM (object);
  MbtMBDataItemPrivate *priv = mb_data_item->priv;

  switch (prop_id)
    {
    case PROP_ADDRESS:
      g_value_set_uint (value, priv->address);

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
mbt_mb_data_item_init (MbtMBDataItem *mb_data_item)
{
  MbtMBDataItemPrivate *priv;

  mb_data_item->priv = G_TYPE_INSTANCE_GET_PRIVATE (mb_data_item,
                                                    MBT_TYPE_MB_DATA_ITEM,
                                                    MbtMBDataItemPrivate);

  priv = mb_data_item->priv;

  priv->address = 0x0000;

  mbt_mb_data_item_set_address (mb_data_item, 0x0000);

  mbt_mb_data_item_set_tag (mb_data_item, NULL);
}

MbtMBDataItem*
mbt_mb_data_item_new (guint16      address,
                      const gchar *tag)
{
  g_return_val_if_fail (MBT_IS_MB_DATA_ITEM_ADDRESS (address), NULL);

  MbtMBDataItem *mb_data_item = g_object_new (MBT_TYPE_MB_DATA_ITEM, NULL);

  mbt_mb_data_item_set_address (mb_data_item, address);

  mbt_mb_data_item_set_tag (mb_data_item, tag);

  return mb_data_item;
}

void
mbt_mb_data_item_set_address (MbtMBDataItem *mb_data_item,
                              guint16        address)
{
  g_return_if_fail (MBT_IS_MB_DATA_ITEM (mb_data_item));
  g_return_if_fail (MBT_IS_MB_DATA_ITEM_ADDRESS (address));

  MbtMBDataItemPrivate *priv = mb_data_item->priv;

  if (priv->address != address)
    {
      priv->address = address;

      g_object_notify (G_OBJECT (mb_data_item), "address");
    }
}

guint16
mbt_mb_data_item_get_address (MbtMBDataItem *mb_data_item)
{
  g_return_val_if_fail (MBT_IS_MB_DATA_ITEM (mb_data_item), 0);

  return mb_data_item->priv->address;
}