#ifndef __MBT_MB_DATA_ITEM_H__
#define __MBT_MB_DATA_ITEM_H__

#include "mbtmb.h"

G_BEGIN_DECLS

#define MBT_TYPE_MB_DATA_ITEM             (mbt_mb_data_item_get_type ())
#define MBT_MB_DATA_ITEM(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MB_DATA_ITEM, MbtMBDataItem))
#define MBT_IS_MB_DATA_ITEM(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MB_DATA_ITEM))
#define MBT_MB_DATA_ITEM_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MB_DATA_ITEM))
#define MBT_IS_MB_DATA_ITEM_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MB_DATA_ITEM))
#define MBT_MB_DATA_ITEM_GET_CLASS(klass) (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MB_DATA_ITEM, MbtMBDataItemClass))

typedef struct _MbtMBDataItem        MbtMBDataItem;
typedef struct _MbtMBDataItemPrivate MbtMBDataItemPrivate;
typedef struct _MbtMBDataItemClass   MbtMBDataItemClass;

struct _MbtMBDataItem
{
  MbtMB mb;

  /*< private >*/
  MbtMBDataItemPrivate *priv;
};

struct _MbtMBDataItemClass
{
  MbtMBClass parent_class;
};

#define MBT_IS_MB_DATA_ITEM_ADDRESS(add) ((add) >= 0x0000 && (add) <= 0xFFFF)

#define mbt_mb_data_item_set_tag(mb,tag) (mbt_mb_set_tag (MBT_MB (mb), tag))
#define mbt_mb_data_item_get_tag(mb)     (mbt_mb_get_tag (MBT_MB (mb)))

GType          mbt_mb_data_item_get_type    (void) G_GNUC_CONST;
MbtMBDataItem* mbt_mb_data_item_new         (guint16        address,
                                             const gchar   *tag);
void           mbt_mb_data_item_set_address (MbtMBDataItem *mb_data_item,
                                             guint16        address);
guint16        mbt_mb_data_item_get_address (MbtMBDataItem *mb_data_item);

G_END_DECLS

#endif /* __MBT_MB_DATA_ITEM_H__*/