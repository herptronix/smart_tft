/**
 * @file r_mem.c
 * @brief Shared Memory Access serialized commands (maser side)
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


/* R_MEM_WriteU8
 * ARG: offset(u16), data(u8) */
void R_MEM_WriteU8(uint16_t offset, uint8_t data) {
  TxMsgPutByte(OP_MEM_WRITE_U8);
  TxMsgPut(offset);
  TxMsgPut(data);
}

/* R_MEM_WriteU16
 * ARG: offset(u16), data(u16) */
void R_MEM_WriteU16(uint16_t offset, uint16_t data) {
  TxMsgPutByte(OP_MEM_WRITE_U16);
  TxMsgPut(offset);
  TxMsgPut(data);
}

/* R_MEM_WriteI16
 * ARG: offset(u16), data(i16) */
void R_MEM_WriteI16(uint16_t offset, int16_t data) {
  TxMsgPutByte(OP_MEM_WRITE_I16);
  TxMsgPut(offset);
  TxMsgPut(data);
}

/* R_MEM_WriteU32
 * ARG: offset(u16), data(u32) */
void R_MEM_WriteU32(uint16_t offset, uint32_t data) {
  TxMsgPutByte(OP_MEM_WRITE_U32);
  TxMsgPut(offset);
  TxMsgPut(data);
}

/* R_MEM_WriteI32
 * ARG: offset(u16), data(i32) */
void R_MEM_WriteI32(uint16_t offset, int32_t data) {
  TxMsgPutByte(OP_MEM_WRITE_I32);
  TxMsgPut(offset);
  TxMsgPut(data);
}

/* R_MEM_WriteU8Arr
 * ARG: offset(u16), len(u16), *data(u8) */
void R_MEM_WriteU8Arr(uint16_t offset, uint16_t len, const uint8_t *data) {
  TxMsgPutByte(OP_MEM_WRITE_U8_ARR);
  TxMsgPut(offset);
  TxMsgPut(len);
  while(len > 0) {
    TxMsgPut(*data);
    data++;
    len--;
  }
}

/* R_MEM_WriteStr
 * ARG: offset(u16), lenMax(u16), *data(u8) */
void R_MEM_WriteStr(uint16_t offset, uint16_t len, const void *str) {
  const uint8_t *p = str;
  TxMsgPutByte(OP_MEM_WRITE_STR);
  TxMsgPut(offset);
  TxMsgPut(len);
  while(p != NULL && *p != 0) {
    TxMsgPut(*p);
    p++;
  }
  TxMsgPutByte(0);  /*string terminaison*/
}

/* R_MEM_Memset
 * ARG: offset(u16), len(u16), fill(u8) */
void R_MEM_Memset(uint16_t offset, uint16_t len, uint8_t fill) {
  TxMsgPutByte(OP_MEM_MEMSET);
  TxMsgPut(offset);
  TxMsgPut(len);
  TxMsgPut(fill);
}

/* R_MEM_ReadU8
 * ARG: offset(u16)*/
void R_MEM_ReadU8(uint16_t offset) {
  TxMsgPutByte(OP_MEM_READ_U8);
  TxMsgPut(offset);
}

/* R_MEM_ReadU16
 * ARG: offset(u16)*/
void R_MEM_ReadU16(uint16_t offset) {
  TxMsgPutByte(OP_MEM_READ_U16);
  TxMsgPut(offset);
}

/* R_MEM_ReadI16
 * ARG: offset(u16)*/
void R_MEM_ReadI16(uint16_t offset) {
  TxMsgPutByte(OP_MEM_READ_I16);
  TxMsgPut(offset);
}

/* R_MEM_ReadU32
 * ARG: offset(u16)*/
void R_MEM_ReadU32(uint16_t offset) {
  TxMsgPutByte(OP_MEM_READ_U32);
  TxMsgPut(offset);
}

/* R_MEM_ReadI32
 * ARG: offset(u16)*/
void R_MEM_ReadI32(uint16_t offset) {
  TxMsgPutByte(OP_MEM_READ_I32);
  TxMsgPut(offset);
}

/* R_MEM_ReadU8Arr
 * ARG: offset(u16)*/
void R_MEM_ReadU8Arr(uint16_t offset, uint16_t len) {
  TxMsgPutByte(OP_MEM_READ_U8_ARR);
  TxMsgPut(offset);
  TxMsgPut(len);
}

/* R_MEM_ReadStr
 * ARG: offset(u16) maxLen(u16)*/
void R_MEM_ReadStr(uint16_t offset, uint16_t maxLen) {
  TxMsgPutByte(OP_MEM_READ_STR);
  TxMsgPut(offset);
  TxMsgPut(maxLen);
}
