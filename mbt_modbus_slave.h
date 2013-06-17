#ifndef __MBT_DIALOG_H__
#define __MBT_DIALOG_H__

#include <glib.h>

G_BEGIN_DECLS

typedef enum {
  MBT_RESPONSE_SERIAL_CONNECT = -100,
  MBT_RESPONSE_CONNECT        = -101,
  MBT_RESPONSE_SETTINGS       = -102
} MbtResponseType;

G_END_DECLS

#endif /* __MBT_DIALOG_H__ */