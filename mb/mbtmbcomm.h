#ifndef __MBT_MB_COMM_H__
#define __MBT_MB_COMM_H__

#include "mbtmb.h"

G_BEGIN_DECLS

#define MBT_TYPE_MB_COMM             (mbt_mb_comm_get_type ())
#define MBT_MB_COMM(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MB_COMM, MbtMBComm))
#define MBT_IS_MB_COMM(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MB_COMM))
#define MBT_MB_COMM_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MB_COMM))
#define MBT_IS_MB_COMM_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MB_COMM))
#define MBT_MB_COMM_GET_CLASS(klass) (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MB_COMM, MbtMBCommClass))

typedef struct _MbtMBComm        MbtMBComm;
typedef struct _MbtMBCommPrivate MbtMBCommPrivate;
typedef struct _MbtMBCommClass   MbtMBCommClass;

struct _MbtMBComm
{
  MbtMB mb;

  /*< private >*/
  MbtMBCommPrivate *priv;
};

struct _MbtMBCoomClass
{
  MbtMBClass parent_class;
};

#define mbt_mb_comm_set_tag(mb,tag) (mbt_mb_set_tag (MBT_MB (mb), tag))
#define mbt_mb_comm_get_tag(mb)     (mbt_mb_get_tag (MBT_MB (mb)))

GType          mbt_mb_comm_get_type    (void) G_GNUC_CONST;
MbtMBComm* mbt_mb_comm_new         (MbtMBMode *mb_mode,
                                    const gchar *tag);

G_END_DECLS

#endif /* __MBT_MB_COMM_H__*/