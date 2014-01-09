/**
 * @file serial_tx.c
 * @brief TX functions (maser side)
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

#include "serial_common.h"
#include "opList.h"  /*for OP_NOP*/

/**
 * Local variables
 */
static uint8_t lastTxByte;            /*n-1 sent byte*/
static uint8_t seqId;                 /*sequence id, coming from serial_remote*/
static bool bNeedStart;               /*...a start sequence shall be sent first*/
static bool bNeedEnd;                 /*...a stop sequence shall be sent*/


/**
 * @function TxMsgStart
 * @brief start a answer message; actually, the start sequence is sent when
 *   using TxMsgPutByte(), i.e. if there is something usefull to send
 * @param uint8_t s: sequence number
 * @return none
 */
void TxMsgStart(uint8_t s) {
  lastTxByte = 0; /*init to a value != of TOKEN_SKIP*/
  seqId = s;
  bNeedStart = true;
  bNeedEnd = false;
}


/**
 * @function TxMsgStop
 * @brief stop the answer message, only if something has been sent
 * @param none
 * @return bool: if true, something has been sent
 */
bool TxMsgStop(void) {
  if(bNeedEnd) {
    UartSendByte(OP_NOP);     /*OP_NOP is always insterted (issue if the last byte of the user msg is TOKEN_STOP)*/
    UartSendByte(TOKEN_STOP);
    UartSendByte(TOKEN_STOP);
  }
  return bNeedEnd;
}


/**
 * @function TxMsgPutByte
 * @brief add a byte in the answer message; handle the TOKEN_SKIP
 * @param uint8_t byte
 * @return none
 */
void TxMsgPutByte(uint8_t byte) {

  /*send a start sequence first?*/
  if(bNeedStart) {
    bNeedStart = false;
    UartSendByte(TOKEN_START);
    UartSendByte(TOKEN_START);
    TxMsgPutByte(seqId);  /*recursive OK here*/
    bNeedEnd = true;  /*the message will have to be closed*/
  }

  /*add extra token*/
  if(byte == TOKEN_SKIP ||  /*... if the byte to send is equal to the TOKEN_SKIP*/
     (lastTxByte == TOKEN_STOP && byte == TOKEN_STOP)) {  /*... or to avoid untimely STOP_MSG*/
    UartSendByte(TOKEN_SKIP);
  }

  UartSendByte(byte);
  lastTxByte = byte;
}


/**
 * @function TxMsgPutStr
 * @brief add a string in the answer message
 * @param const void *str: string
 * @return none
 */
void TxMsgPutStr(const void *str) {

  const uint8_t *pu8 = (const uint8_t *) str;

  /*send the string (excluding the \0)*/
  if(pu8 != NULL) {
    while(*pu8 != 0) {
      TxMsgPutByte(*pu8);
      pu8++;
    }
  }

  /*manually send the \0 (always)*/
  TxMsgPutByte(0);
}


/**
 * @function TxMsgPutRect
 * @brief add a rect_st in the answer message
 * @param const rect_st *rec
 * @return none
 */
void TxMsgPutRect(const rect_st *rec) {
  if(rec != NULL) {
    TxMsgPut(rec->x);
    TxMsgPut(rec->y);
    TxMsgPut(rec->w);
    TxMsgPut(rec->h);
  }
}


/**
 * @function TxMsgPutRaw
 * @brief add a u8 array in the answer message
 * @param const void *p: pointer to the first byte of u8 array
 * @param uint16_t len: size of the array
 * @return none
 */
void TxMsgPutRaw(const void *p, uint16_t len) {

  const uint8_t *pu8 = (const uint8_t *) p;

  if(pu8 != NULL) {
    while(len > 0) {
      TxMsgPutByte(*pu8);
      pu8++;
      len--;
    }
  }
}
