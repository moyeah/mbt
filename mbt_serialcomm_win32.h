#ifndef __MBT_SERIAL_COMM_WIN32_H__
#define __MBT_SERIAL_COMM_WIN32_H__

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define MBT_TYPE_SERIAL_COMM            (mbt_serial_comm_get_type ())
#define MBT_SERIAL_COMM(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj),   MBT_TYPE_SERIAL_COMM, MbtSerialComm))
#define MBT_IS_SERIAL_COMM(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj),   MBT_TYPE_SERIAL_COMM))
#define MBT_SERIAL_COMM_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST    ((klass), MBT_TYPE_SERIAL_COMM, MbtSerialCommClass))
#define MBT_IS_SERIAL_COMM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE    ((klass), MBT_TYPE_SERIAL_COMM))
#define MBT_SERIAL_COMM_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS  ((obj),   MBT_TYPE_SERIAL_COMM, MbtSerialCommClass))

typedef struct _MbtSerialComm      MbtSerialComm;
typedef struct _MbtSerialCommClass MbtSerialCommClass;

struct _MbtSerialComm
{
  GObject parent_instance;

  /* Available parameters */
  GList *ports;
  GList *addresses;
  GList *baud_rates;
  GList *parities;
  GList *stop_bits;
  GList *modes;

  /* Selected parameters */
  GString *port;
  GString *address;
  GString *baud_rate;
  GString *parity;
  GString *stop_bit;
  GString *mode;
};

struct _MbtSerialCommClass
{
  GObjectClass parent_class;
};

GType          mbt_serial_comm_get_type      (void) G_GNUC_CONST;
MbtSerialComm* mbt_serial_comm_new           (void);
void           mbt_serial_comm_refresh_ports (MbtSerialComm*);
void           mbt_serial_comm_get_settings  (MbtSerialComm*);
void           mbt_serial_comm_set_settings  (MbtSerialComm*);
void           mbt_serial_comm_read          (MbtSerialComm*);
void           mbt_serial_comm_write         (MbtSerialComm*);

G_END_DECLS

#endif /* __MBT_SERIAL_COMM_H__ */