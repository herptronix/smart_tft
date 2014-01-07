/**
 * @file r_mem.c
 * @brief serialized memory functions decoder (slave side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-23
 *
 * Copyright (C) <2013>  Duboisset Philippe <duboisset.philippe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "r_mem.h"
#include "serial_common.h"
#include "serial_remote.h"
#include "ssm.h"

#ifdef SMART_TFT_SLAVE_MODE

/* R_MEM_WriteU8
 * ARG: offset(u16), data(u8) */
int8_t R_MEM_WriteU8(void) {
  int8_t res = -1; uint16_t offset; uint8_t data;
  offset = RxGetU16();
  data = RxGetU8();
  if(RxStatus() == 0) {
    if(SSM_WriteU8(offset, data) == 0) res = 0;
    else Error("R_MEM_WriteU8: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* R_MEM_WriteU16
 * ARG: offset(u16), data(u16) */
int8_t R_MEM_WriteU16(void) {
  int8_t res = -1; uint16_t offset, data;
  offset = RxGetU16();
  data = RxGetU16();
  if(RxStatus() == 0) {
    if(SSM_WriteU16(offset, data) == 0) res = 0;
    else Error("R_MEM_WriteU16: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}


/* R_MEM_WriteI16
 * ARG: offset(u16), data(i16) */
int8_t R_MEM_WriteI16(void) {
  int8_t res = -1; uint16_t offset; int16_t data;
  offset = RxGetU16();
  data = RxGetI16();
  if(RxStatus() == 0) {
    if(SSM_WriteI16(offset, data) == 0) res = 0;
    else Error("R_MEM_WriteI16: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}


/* R_MEM_WriteU32
 * ARG: offset(u16), data(u32) */
int8_t R_MEM_WriteU32(void) {
  int8_t res = -1; uint16_t offset; uint32_t data;
  offset = RxGetU16();
  data = RxGetU32();
  if(RxStatus() == 0) {
    if(SSM_WriteU32(offset, data) == 0) res = 0;
    else Error("R_MEM_WriteU32: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}


/* R_MEM_WriteI32
 * ARG: offset(u16), data(i32) */
int8_t R_MEM_WriteI32(void) {
  int8_t res = -1; uint16_t offset; int32_t data;
  offset = RxGetU16();
  data = RxGetI32();
  if(RxStatus() == 0) {
    if(SSM_WriteI32(offset, data) == 0) res = 0;
    else Error("R_MEM_WriteI32: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}


/* R_MEM_WriteU8Arr
 * BEWARE! for copying raw memory (eg. successive U32), do NOT use if the endianness of master different than the slave one !
 * ARG: offset(u16), len(u16), *data(u8) */
int8_t R_MEM_WriteU8Arr(void) {
  int8_t res = -1; uint16_t offset, size; uint8_t data;
  offset = RxGetU16();
  size = RxGetU16();
  if(RxStatus() == 0) {

    /*copy byte per byte*/
    res = 0;
    while(size > 0 && res == 0) {

      data = RxGetU8();
      if(RxStatus() == 0) {
        if(SSM_WriteU8(offset, data) < 0) {
          res = -1;
          Error("R_MEM_WriteU8Arr: bad offset / size");
        }
      }
      else {
        res = -1;
        Error(EXTRACT_ERROR_MSG);
      }

      offset++;
      size--;
    }
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}


/* R_MEM_WriteStr
 * ARG: offset(u16), lenMax(u16), *data(u8) */
int8_t R_MEM_WriteStr(void) {
  int8_t res = -1; uint16_t offset, size; uint8_t data;
  offset = RxGetU16();
  size = RxGetU16();

  if(RxStatus() == 0 && size > 0) {

    res = 0;
    do {

      size--;

      if(size == 0) data = 0;
      else data = RxGetU8();

      if(RxStatus() == 0) {
        if(SSM_WriteU8(offset, data) < 0) {
          res = -1;
          Error("R_MEM_WriteStr: bad offset / size");
        }
      }
      else {
        res = -1;
        Error(EXTRACT_ERROR_MSG);
      }

      offset++;

    } while(data != 0 && res == 0);
  }
  else Error(EXTRACT_ERROR_MSG);

  return res;
}


/* R_MEM_Memset
 * ARG: offset(u16), len(u16), fill(u8) */
int8_t R_MEM_Memset(void) {
  int8_t res = -1; uint16_t offset, size; uint8_t fill;
  offset = RxGetU16();
  size = RxGetU16();
  fill = RxGetU8();

  if(RxStatus() == 0) {

    res = 0;
    while(size > 0 && res == 0) {
      res = SSM_WriteU8(offset, fill);
      offset++;
      size--;
    }

    if(res != 0) Error("R_MEM_Memset: bad offset / size");
  }
  else Error(EXTRACT_ERROR_MSG);

  return res;
}


/* R_MEM_ReadU8
 * ARG: offset(u16)*/
int8_t R_MEM_ReadU8(void) {
  int8_t res = -1; uint16_t offset; uint8_t data = 0;
  offset = RxGetU16();
  if(RxStatus() == 0) {
    if(SSM_ReadU8(offset, &data) == 0) res = 0;
    else Error("R_MEM_ReadU8: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);

  TxMsgPut(data);
  return res;
}


/* R_MEM_ReadU16
 * ARG: offset(u16)*/
int8_t R_MEM_ReadU16(void) {
  int8_t res = -1; uint16_t offset; uint16_t data = 0;
  offset = RxGetU16();

  if(RxStatus() == 0) {
    if(SSM_ReadU16(offset, &data) == 0) res = 0;
    else Error("R_MEM_ReadU16: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);

  TxMsgPut(data);
  return res;
}


/* R_MEM_ReadI16
 * ARG: offset(u16)*/
int8_t R_MEM_ReadI16(void) {
  int8_t res = -1; uint16_t offset; int16_t data = 0;
  offset = RxGetU16();

  if(RxStatus() == 0) {
    if(SSM_ReadI16(offset, &data) == 0) res = 0;
    else Error("R_MEM_ReadI16: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);

  TxMsgPut(data);
  return res;
}


/* R_MEM_ReadU32
 * ARG: offset(u16)*/
int8_t R_MEM_ReadU32(void) {
  int8_t res = -1; uint16_t offset; uint32_t data = 0;
  offset = RxGetU16();

  if(RxStatus() == 0) {
    if(SSM_ReadU32(offset, &data) == 0) res = 0;
    else Error("R_MEM_ReadU32: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);

  TxMsgPut(data);
  return res;
}


/* R_MEM_ReadI32
 * ARG: offset(u16)*/
int8_t R_MEM_ReadI32(void) {
  int8_t res = -1; uint16_t offset; int32_t data = 0;
  offset = RxGetU16();

  if(RxStatus() == 0) {
    if(SSM_ReadI32(offset, &data) == 0) res = 0;
    else Error("R_MEM_ReadI32: bad offset");
  }
  else Error(EXTRACT_ERROR_MSG);

  TxMsgPut(data);
  return res;
}


/* R_MEM_ReadU8Arr
 * ARG: offset(u16) size(u16)*/
int8_t R_MEM_ReadU8Arr(void) {
  int8_t res = -1; uint16_t offset; uint16_t size; uint8_t data = 0;
  offset = RxGetU16();
  size = RxGetU16();

  if(RxStatus() == 0) {

    res = 0;
    while(size > 0 && res == 0) {
      res = SSM_ReadU8(offset, &data);
      TxMsgPut(data);
      offset++;
      size--;
    }

    if(res != 0) Error("R_MEM_ReadU8Arr: bad offset / size");
  }
  else Error(EXTRACT_ERROR_MSG);

  return res;
}


/* R_MEM_ReadStr
 * ARG: offset(u16) maxLen(u16)*/
int8_t R_MEM_ReadStr(void) {
  int8_t res = -1; uint16_t offset; uint16_t size; uint8_t data = 0;
  offset = RxGetU16();
  size = RxGetU16();

  if(RxStatus() == 0 && size > 0) {

    do {

      size--;

      res = SSM_ReadU8(offset, &data);
      
      if(size == 0 || res < 0) data = 0;

      TxMsgPut(data);
      offset++;

    } while(data != 0);

    if(res != 0) Error("R_MEM_ReadStr: bad offset / size");

  }
  else Error(EXTRACT_ERROR_MSG);

  return res;
}

#endif
