#ifndef __MBT_MB_H__
#define __MBT_MB_H__

#include <glib.h>
#include <glib-object.h>
#include <glib/gi18n.h>

G_BEGIN_DECLS

#define MBT_TYPE_MB             (mbt_mb_get_type ())
#define MBT_MB(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_MB, MbtMB))
#define MBT_IS_MB(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_MB))
#define MBT_MB_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_MB), MbtMBClass)
#define MBT_IS_MB_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_MB))
#define MBT_MB_GET_CLASS(klass) (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_MB, MbtMBClass))

typedef struct _MbtMB        MbtMB;
typedef struct _MbtMBPrivate MbtMBPrivate;
typedef struct _MbtMBClass   MbtMBClass;

struct _MbtMB
{
  GObject gobject;

  /*< private >*/
  MbtMBPrivate *priv;
};

struct _MbtMBClass
{
  GObjectClass parent_class;
};

GType        mbt_mb_get_type (void) G_GNUC_CONST;
MbtMB*       mbt_mb_new      (const gchar *tag);
void         mbt_mb_set_tag  (MbtMB       *mb,
                              const gchar *tag);
const gchar* mbt_mb_get_tag  (MbtMB       *mb);

G_END_DECLS

#endif /* __MBT_MB_H__ */