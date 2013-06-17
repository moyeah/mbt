#ifndef __MBT_MB_MASTER_H__
#define __MBT_MB_MASTER_H__

#include "mbtmbenums.h"

#include <glib-object.h>

G_BEGIN_DECLS

#define MBT_TYPE_MB_MASTER             (mbt_mb_master_get_type ())
#define MBT_MB_MASTER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MB_MASTER, MbtMBMaster))
#define MBT_IS_MB_MASTER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MB_MASTER))
#define MBT_MB_MASTER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MB_MASTER))
#define MBT_IS_MB_MASTER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MB_MASTER))
#define MBT_MB_MASTER_GET_CLASS(klass) (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MB_MASTER, MbtMBMasterClass))

typedef struct _MbtMBMaster        MbtMBMaster;
typedef struct _MbtMBMasterPrivate MbtMBMasterPrivate;
typedef struct _MbtMBMasterClass   MbtMBMasterClass;

struct _MbtMBMaster
{
  GObject parent_instance;

  /*< private >*/
  MbtMBMasterPrivate *priv;
};

struct _MbtMBMasterClass
{
  GObject parent_class;
};

GType        mbt_mb_master_get_type (void) G_GNUC_CONST;
MbtMBMaster* mbt_mb_master_new      (const gchar *name);
void         mbt_mb_master_set_name (MbtMBMaster *mb_master,
                                     const gchar *name);
const gchar* mbt_mb_master_get_name (MbtMBMaster *mb_master);
void         mbt_mb_master_set_mode (MbtMBMaster *mb_master,
                                     MbtMBMode    mode);
MbtMBMode    mbt_mb_master_get_mode (MbtMBMaster *mb_master);

G_END_DECLS

#endif /* __MBT_MB_MASTER_H__ */