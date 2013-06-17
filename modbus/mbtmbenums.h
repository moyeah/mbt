#ifndef __MBT_MB_ENUMS_H__
#define __MBT_MB_ENUMS_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef enum
{
  MBT_MB_RTU,
  MBT_MB_ASCII,
  MBT_MB_TCPIP
} MbtMBMode;

GType mbt_mb_mode_get_type  (void) G_GNUC_CONST;
#define MBT_TYPE_MB_MODE    (mbt_mb_mode_get_type ())
#define MBT_IS_MB_MODE(obj) ((obj) >= MBT_MB_RTU && (obj) <= MBT_MB_TCPIP)

G_END_DECLS

#endif /* __MBT_MB_ENUMS_H__ */