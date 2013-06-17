#include <glib.h>

/* MBT types */
typedef guint8  mbtpdu;
typedef guint8  mbtdata;
typedef guint8  mbtbyte;
typedef guint16 mbtword;

/* MODBUS Request PDU */
mbtpdu
mbt_req_pdu (MbtFuncCode func_code, mbtdata *data)
{
  mbtpdu mbt_pdu[gsize (data)];

  mbt_pdu = data;
  mbt_pdu[0] = func_code;

  return mbt_pdu
}

/* Word swap byte */
mbtword
mbt_word_swap_byte (const mbtword word)
{
  mbtword word_hi = word << 8;
  mbtword word_lo = word >> 8;
  mbtword word_swapped = word_hi | word_lo;

#ifdef DEBUG
  DEBUG ("mbt_swap_byte");
  g_print ("Word: %0.4X\n", word);
  g_print ("Swapped word: %0.4X\n", word_swapped);
#endif /* DEBUG */

  return word_swapped;
}

/* CRC Generation */
mbtword
mbt_crc_gen (mbtbyte message[], gint len)
{
  mbtword crc_reg = 0xFFFF;

  gint i;
  for (i = 0; i < len; i++)
  {
    crc_reg ^= (mbtword) message[i];

    gint j;
    for (j = 0; j < 8; j++)
    {
      if ((crc_reg & 0x0001) != 0)
      {
        crc_reg >>= 1;
        crc_reg ^= 0xA001;
      }
      else
        crc_reg >>= 1;
    }
  }

  return crc_reg;
}

/* MODBUS Request ADU */
mbtadu
mbt_req_adu (const mbtbyte  slave_address,
             const mbtpdu  *pdu)
{
  mbtadu mtb_adu

  mbt_adu[0] = slave_address;
  mbt_adu

  return mbt_adu;
}