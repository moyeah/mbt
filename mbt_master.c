typedef const gchar* mbtmbpdu;

typedef enum
{
  MBT_IDLE,
  MBT_WAITING_REPLY,
  MBT_PROCESSING_REPLY
}MbtMBMasterState;

typedef enum
{
  READ_COILS             = 0x01,
  READ_DISCRITE_INPUTS   = 0x02,
  READ_HOLDING_REGISTERS = 0x03,
  READ_INPUT_RESGISTER   = 0x04,
  WRITE_SINGLE_COIL      = 0x05,
  WRITE_SINGLE_REGISTER  = 0x06,
  READ_EXCEPTION_STATUS  = 0x07,
  DIAGNOSTIC             = 0x08,
  GET_COMM_EVENT_COUNTER = 0x0B
}MbtMBFuncCode;

gint
read_hold_ref (gint slave,
               gint offset,
               gint num_reg,
               gint *reg_table)
{

/* MODBUS Request PDU */
mbtmbpdu
mbt_mb_req_pdu (MbtMBFuncCode _func_code, const gchar data[])
{
  gchar* request (const gchar func_code)
  {
    return g_strconcat (func_code,
                        data,
                        NULL);
  }

  switch (_func_code)
  {
    case READ_COILS:
      return request ('0x01');

    case READ_DISCRITE_INPUTS:
      return request ('0x02');

    case READ_HOLDING_REGISTERS:
      return request ('0x03');

    case READ_INPUT_REGISTERS:
      return request ('0x04');

    case WRITE_SINGLE_COIL:
      return request ('0x05');

    case WRITE_SINGLE_REGISTERS:
      return request ('0x06');

    case READ_EXCEPTION_STATUS:
      return '0x07';

    case DIAGNOSTICS:
      return request ('0x08'); // TODO

    case GET_COMM_EVENT_COUNTER:
      return '0x0B'

    case GET_COMM_EVENT_LOG:
      return '0x0C'
  }

}

/* MODBUS Response PDU */
mbtmbpdu
mbt_mb_rsp_pdu (MbtMBFuncCode func_code, const gchar *data)
{
  
}

mbt_mb_excep_rsp_pdu (MbtFuncCode func_code, request_data) // MODBUS Exception Response PDU
{
  gchar func_code = func_code + 0x80;
  gchar excep_code = 0x01 or 0x02 or 0x03 or 0x04
}

/* MODBUS Request ADU */
void
mbt_mb_req_adu ()
{
}