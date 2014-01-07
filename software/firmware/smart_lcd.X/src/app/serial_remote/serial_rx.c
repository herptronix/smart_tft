/**
 * @file serial_rx.c
 * @brief RX functions (slave side)
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

#ifdef SMART_TFT_SLAVE_MODE

/**
 * Local variables
 */
typedef enum { MSG_STOPPED, MSG_STARTING, MSG_STARTED, MSG_STOPPING } rx_fsm_e;
static volatile rx_fsm_e rxFsm;                     /*RX state machine*/
static volatile uint8_t tokenSkipCnt;               /*TOKEN_SKIP counter*/
static volatile uint16_t rxLen;                     /*message lenght*/
static uint8_t rxBuf[RX_BUFF_SIZE];                 /*message buffer*/
static uint8_t *pRxBuf;                             /*pointer to the current byte being parsed*/
static bool bErr;                                   /*parsing error flag*/
static uint8_t endianPermut32[4] = {0, 1, 2, 3};    /*U32/I32 permutation table, for little/big endian support*/
static uint8_t endianPermut16[2] = {0, 1};          /*U16/I16 permutation table, for little/big endian support*/


/**
 * Local functions
 */
static void GenericExtract(uint8_t *out, uint8_t size);
static void RxIsr(uint8_t byte);
static void RxAdd(uint8_t byte);


/**
 * @function RxInit
 * @brief initialize the RX part
 * @param none
 * @return none
 */
void RxInit(void) {
  UartRegisterRxISR(&RxIsr);
  RxAck();
}


/**
 * @function RxAck
 * @brief re enable the reception & clear errors
 * @param none
 * @return none
 */
void RxAck(void) {
  rxFsm = MSG_STOPPED;
  tokenSkipCnt = 0;
  rxLen = 0;
  pRxBuf = NULL;
  bErr = false;
  UartUnmaskRxInterrupt();
}


/**
 * @function RxStatus
 * @brief return RX status (~ message parsing state in fact...)
 * @param none
 * @return int8_t: 0 ok, -1 error
 */
int8_t RxStatus(void) {
  return (bErr == true) ? -1: 0;
}


/**
 * @function RxIsMsgReceived
 * @brief check if a message has been received
 * @param none
 * @return bool: true -> received
 */
bool RxIsMsgReceived(void) {
  return (pRxBuf == NULL) ? false : true;
}


/**
 * @function RxIsEmpty
 * @brief check if a message has been completly parsed
 * @param none
 * @return bool: true -> completed
 */
bool RxIsEmpty(void) {
  return (rxLen > 0) ? false: true;
}


/**
 * @function ExtractU8
 * @brief extract a u8 from the message, increment the current msg position (+1), decrement msg length (-1)
 * @param none
 * @return uint8_t: the extracted u8; 0 if error
 */
uint8_t RxGetU8(void) {
  uint8_t res = 0;

  if(RxIsMsgReceived() && bErr == false && rxLen > 0) {
    res = *pRxBuf;
    rxLen--;
    pRxBuf++;
  }
  else {
    bErr = true;
  }

  return res;
}


/**
 * @function ExtractU16
 * @brief extract a u16 from the message, increment the current msg position (+2), decrement msg length (-2)
 * @param none
 * @return uint16_t: the extracted u16; 0 if error
 */
uint16_t RxGetU16(void) {
  uint16_t res = 0;
  GenericExtract((uint8_t *) &res, sizeof(res));
  return res;
}


/**
 * @function ExtractI16
 * @brief extract a i16 from the message, increment the current msg position (+2), decrement msg length (-2)
 * @param none
 * @return int16_t: the extracted i16; 0 if error
 */
int16_t RxGetI16(void) {
  int16_t res = 0;
  GenericExtract((uint8_t *) &res, sizeof(res));
  return res;
}


/**
 * @function ExtractU32
 * @brief extract a u32 from the message, increment the current msg position (+4), decrement msg length (-4)
 * @param none
 * @return uint32_t: the extracted u32; 0 if error
 */
uint32_t RxGetU32(void) {
  uint32_t res = 0;
  GenericExtract((uint8_t *) &res, sizeof(res));
  return res;
}


/**
 * @function ExtractI32
 * @brief extract a i32 from the message, increment the current msg position (+4), decrement msg length (-4)
 * @param none
 * @return int32_t: the extracted i32; 0 if error
 */
int32_t RxGetI32(void) {
  int32_t res = 0;
  GenericExtract((uint8_t *) &res, sizeof(res));
  return res;
}


/**
 * @function ExtractRec
 * @brief extract a rect_st from the message, increment the current msg position (+8), decrement msg length (-8)
 * @param rect_st *rec: rec output
 * @return none
 */
void RxGetRec(rect_st *rec) {
  rec->x = RxGetI16();
  rec->y = RxGetI16();
  rec->w = RxGetU16();
  rec->h = RxGetU16();
}


/**
 * @function ExtractTxt
 * @brief extract a string (\0 terminated), increment the current msg position & decrement msg length according strlen
 * @param const uint8_t **pTxt: will receive the pointer to the str start
 * @return none
 */
void RxGetTxt(const uint8_t **pTxt) {

  bool bDone = false;

  if(RxIsMsgReceived() && bErr == false) {

    /*begining of the string is the current byte*/
    *pTxt = pRxBuf;

    /*go to the end of the string*/
    while(bDone == false && bErr == false) {

      /*end of message?*/
      if(rxLen == 0) {

        /*message is terminated, but string is still opened? error*/
        if(bDone == false) bErr = true;
      }
      else {

        /*end of string? -> done*/
        if(*pRxBuf == 0) bDone = true;

        /*update the position*/
        rxLen--;
        pRxBuf++;
      }
    }
  }
  else {
    *pTxt = NULL;
  }
}


/**
 * @function GenericExtract
 * @brief extract n bytes
 * @param uint8_t *out: pointer to the first byte of a u8 array (output)
 * @param uint8_t size: number of bytes to extract (2 / 4 / 8)
 * @return int8_t: 0 ok, -1 error
 */
static void GenericExtract(uint8_t *out, uint8_t size) {

  uint8_t ii;
  const uint8_t *perm = NULL;

  if(RxIsMsgReceived() && bErr == false) {

    if(rxLen >= size) {
      /*select the endian table*/
      switch(size) {
        case 2: perm = endianPermut16; break;
        case 4: perm = endianPermut32; break;
        default: break;
      }

      /*extract the variable & update the message pos*/
      if(perm != NULL) {
        for(ii = 0; ii < size; ii++) {
          out[perm[ii]] = *pRxBuf;
          pRxBuf++;
        }
        rxLen -= size;
      }
      else {
        bErr = true;
      }
    }
    else {
      bErr = true;
    }
  }
}


/**
 * @function RxIsr
 * @brief RX interrupt handler
 * @param uint8_t byte: received byte
 * @return none
 */
static void RxIsr(uint8_t byte) {

  switch(rxFsm) {

    case MSG_STOPPED:
      if(byte == TOKEN_START) rxFsm = MSG_STARTING;
      break;

    case MSG_STARTING:
      if(byte == TOKEN_START) rxFsm = MSG_STARTED;
      else rxFsm = MSG_STOPPED;
      break;

    case MSG_STARTED:
      if(byte == TOKEN_STOP) rxFsm = MSG_STOPPING;
      else RxAdd(byte);
      break;

    case MSG_STOPPING:
      if(byte == TOKEN_STOP) {
        UartMaskRxInterrupt();
        pRxBuf = &rxBuf[0];
        rxFsm = MSG_STOPPED;
      }
      else {
        RxAdd(TOKEN_STOP);
        RxAdd(byte);
        rxFsm = MSG_STARTED;
      }
      break;

    default:
      RxInit();
      break;
  }
}


/**
 * @function RxAdd
 * @brief RX byte adder (handle TOKEN SKIP)
 * @param uint8_t byte: received byte
 * @return none
 */
static void RxAdd(uint8_t byte) {

  if(rxLen < RX_BUFF_SIZE) {

    if(byte != TOKEN_SKIP) {
      rxBuf[rxLen] = byte;
      rxLen++;
      tokenSkipCnt = 0;
    }
    else {
      if(tokenSkipCnt == 0) {
        tokenSkipCnt = 1;
      }
      else {
        rxBuf[rxLen] = byte;
        rxLen++;
        tokenSkipCnt = 0;
      }
    }
  }
}

#endif
