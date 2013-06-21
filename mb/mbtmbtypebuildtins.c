
/* Generated data (by glib-mkenums) */

#include "config.h"

#include "mbtmbtypebuildtins.h"

/* enumerations from "mbtmbenums.h" */
GType
mbt_mb_mode_get_type (void) 
{
  static GType etype = 0;
  if (G_UNLIKELY (etype == 0))
    {
      static const GEnumValue values[] = {
        { MBT_MB_RTU, "MBT_MB_RTU", "rtu" },
        { MBT_MB_ASCII, "MBT_MB_ASCII", "ascii" },
        { MBT_MB_TCPIP, "MBT_MB_TCPIP", "tcpip" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static (g_intern_static_string ("MbtMBMode"),
                                                                values);
    }
  return etype;
}


/* Generated data ends here */

