#include <glib.h>

/* MBT types */
typedef guint8  mbtpdu;
typedef guint8  mbtdata;

/* MODBUS Function Codes */
typedef enum
{
  READ_COILS = 0x01
} MbtMBFuncCode;

/* MODBUS Request PDU */
const mbtpdu*
mbt_req_pdu (MbtMBFuncCode func_code, const mbtdata *data, gsize length)
{
  mbtpdu mbt_pdu[length + 1];

  mbt_pdu[0] = func_code;

  gint i;
  for (i = 1; i <= length; i++)
  {
    mbt_pdu[i] = data[i-1];
  }

gint _i;
for (_i = 0; _i <= length+10; _i++)
{
  g_print ("mbt_pdu[%d] = %0.2X\n", _i, mbt_pdu[_i]);
}

  return &mbt_pdu;
}

int
main (int argc, char *argv[])
{
  mbtdata data[] = { 0x10, 0x20, 0x30, 0x40,
                     0x10, 0x20, 0x30, 0x40,
                     0x10, 0x20, 0x30, 0x40 };

  mbt_req_pdu (READ_COILS, data, 8);

  return 0;
}