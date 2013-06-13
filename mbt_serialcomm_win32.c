#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501

#include <tchar.h>
#include <windows.h>

#include "mbt_serialcomm_win32.h"

#define MAX_VALUE_NAME 16383

static const gchar *mbt_baud_rate[] = {
  "110",   "300",   "600",    "1200",   "2400",
  "4800",  "9600",  "14400",  "19200",  "38400",
  "56000", "57600", "115200", "128000", "256000",
  NULL
};

static const gchar *mbt_parity[] = {
  "None", "Even", "Odd",
  NULL
};

static const gchar *mbt_stop_bits[] = {
  "1", "1.5", "2",
  NULL
};

static const gchar *mbt_mode[] = {
  "RTU", "ASCII",
  NULL
};

G_DEFINE_TYPE (MbtSerialComm, mbt_serial_comm, G_TYPE_OBJECT);

static GList*
_mbt_get_serial_ports (void)
{
  HKEY hKey;
  DWORD retCode = RegOpenKeyEx (HKEY_LOCAL_MACHINE,
                                "HARDWARE\\DEVICEMAP\\SERIALCOMM",
                                0,
                                KEY_READ,
                                &hKey);
  if (retCode != ERROR_SUCCESS)
    return NULL;

  DWORD cValues;
  DWORD cbMaxValueData;
  retCode = RegQueryInfoKey (hKey,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             &cValues,
                             NULL,
                             &cbMaxValueData,
                             NULL,
                             NULL);

  if (!cValues)
    return NULL;

  DWORD i;
  TCHAR achValue[MAX_VALUE_NAME];
  DWORD cchValue = MAX_VALUE_NAME;
  TCHAR achData[MAX_VALUE_NAME];
  DWORD cchData = MAX_VALUE_NAME;

  GList *list = NULL;

  for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
  {
    achValue[0] = '\0';
    cchValue = MAX_VALUE_NAME;
    achData[0] = '\0';
    cchData = MAX_VALUE_NAME;
    
    retCode = RegEnumValue (hKey,
                            i,
                            achValue,
                            &cchValue,
                            NULL,
                            NULL,
                            achData,
                            &cchData);
    if (retCode == ERROR_SUCCESS)
      list = g_list_append (list, (gpointer) achData);
  }

  RegCloseKey (hKey);

  return list;
}

static GList*
_mbt_get_param (const gchar *param[])
{
  GList *list = NULL;
  gint i;

  if (param)
  {
    for (i = 0; param[i]; i++)
    {
      list = g_list_append (list, (gpointer) g_strdup (param[i]));
    }

    return list;
  }

  for (i = 1; i <= 255; i++)
  {
    list = g_list_append (list, (gpointer) g_strdup_printf ("%d", i));
  }

  return list;
}

static void
mbt_serial_comm_init (MbtSerialComm *serial_comm)
{
  /* Set available parameters */
  serial_comm->ports = _mbt_get_serial_ports ();
  serial_comm->addresses = _mbt_get_param (NULL);
  serial_comm->baud_rates = _mbt_get_param (mbt_baud_rate);
  serial_comm->parities = _mbt_get_param (mbt_parity);
  serial_comm->stop_bits = _mbt_get_param (mbt_stop_bits);
  serial_comm->modes = _mbt_get_param (mbt_mode);

  /* Set default parameters */
  if (!serial_comm->ports)
    return;
  serial_comm->port =
      g_string_new (g_list_nth_data (serial_comm->ports, 0));
  serial_comm->address =
    g_string_new (g_list_nth_data (serial_comm->addresses, 0));

  /* Get system parameters */
  mbt_serial_comm_get_settings (serial_comm);
}

static void
mbt_serial_comm_class_init (MbtSerialCommClass *klass)
{
}

MbtSerialComm*
mbt_serial_comm_new (void)
{
  return g_object_new (MBT_TYPE_SERIAL_COMM,
                       NULL);
}

void
mbt_serial_comm_refresh_ports (MbtSerialComm *serial_comm)
{
  g_return_if_fail (MBT_IS_SERIAL_COMM (serial_comm));

  serial_comm->ports = _mbt_get_serial_ports ();

  if (!serial_comm->ports)
    serial_comm->port = g_string_new (NULL);
  else
    serial_comm->port =
      g_string_new (g_list_nth_data (serial_comm->ports, 0));
}

void
mbt_serial_comm_get_settings (MbtSerialComm *serial_comm)
{
  g_return_if_fail (MBT_IS_SERIAL_COMM (serial_comm));

  if (!serial_comm->ports)
    return;

  TCHAR *pcCommPort = serial_comm->port->str;

  HANDLE hCom = CreateFile (pcCommPort,
                            GENERIC_READ,
                            0,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL);
  if (hCom == INVALID_HANDLE_VALUE)
    return;

  DCB dcb;
  ZeroMemory (&dcb, sizeof (DCB));
  dcb.DCBlength = sizeof (DCB);

  if (!GetCommState (hCom, &dcb))
    return;

  serial_comm->baud_rate = g_string_new (g_strdup_printf ("%d",
                                                          dcb.BaudRate));

  switch (dcb.Parity)
  {
    case NOPARITY:
      serial_comm->parity = g_string_new ("None");
      break;

    case ODDPARITY:
      serial_comm->parity = g_string_new ("Odd");
      break;

    case EVENPARITY:
      serial_comm->parity = g_string_new ("Even");
      break;

    default:
      serial_comm->parity = g_string_new (NULL);
      break;
  }

  switch (dcb.StopBits)
  {
    case ONESTOPBIT:
      serial_comm->stop_bit = g_string_new ("1");
      break;

    case ONE5STOPBITS:
      serial_comm->stop_bit = g_string_new ("1.5");
      break;

    case TWOSTOPBITS:
      serial_comm->stop_bit = g_string_new ("2");
      break;

    default:
      serial_comm->stop_bit = g_string_new (NULL);
      break;
  }

  switch (dcb.ByteSize)
  {
    case 7:
      serial_comm->mode = g_string_new ("ASCII");
      break;

    case 8:
      serial_comm->mode = g_string_new ("RTU");
      break;

    default:
      serial_comm->mode = g_string_new (NULL);
      break;
  }

  CloseHandle (hCom);
}

void
mbt_serial_comm_set_settings (MbtSerialComm *serial_comm)
{
  if (!serial_comm->ports)
    return;

  TCHAR *pcCommPort = serial_comm->port->str;

  HANDLE hCom = CreateFile (pcCommPort,
                            GENERIC_READ,
                            0,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL);
  if (hCom == INVALID_HANDLE_VALUE)
    return;

  DCB dcb;
  ZeroMemory (&dcb, sizeof (DCB));
  dcb.DCBlength = sizeof (DCB);

  dcb.BaudRate = g_ascii_strtoll (serial_comm->baud_rate->str, 0, 0);

  if (g_strrstr (serial_comm->parity->str, "None"))
    dcb.Parity = NOPARITY;
  else if (g_strrstr (serial_comm->parity->str, "Odd"))
    dcb.Parity = ODDPARITY;
  else if (g_strrstr (serial_comm->parity->str, "Even"))
    dcb.Parity = EVENPARITY;

  if (g_strrstr (serial_comm->stop_bit->str, "1"))
    dcb.StopBits = ONESTOPBIT;
  else if (g_strrstr (serial_comm->stop_bit->str, "1.5"))
    dcb.StopBits = ONE5STOPBITS;
  else if (g_strrstr (serial_comm->stop_bit->str, "2"))
    dcb.StopBits = TWOSTOPBITS;

  if (g_strrstr (serial_comm->mode->str, "ASCII"))
    dcb.ByteSize = 7;
  else if (g_strrstr (serial_comm->mode->str, "RTU"))
    dcb.ByteSize = 8;

  if (!SetCommState (hCom, &dcb))
    return;

  CloseHandle (hCom);
}