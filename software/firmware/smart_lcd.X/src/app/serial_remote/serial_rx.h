/**
 * @file serial_rx.h
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

#ifndef _serial_rx_h
#define _serial_rx_h

#include "main.h"
#include "p2d.h"


/**
 * @function RxInit
 * @brief initialize the RX part
 * @param none
 * @return none
 */
void RxInit(void);

/**
 * @function RxAck
 * @brief re enable the reception & clear errors
 * @param none
 * @return none
 */
void RxAck(void);

/**
 * @function RxStatus
 * @brief return RX status
 * @param none
 * @return int8_t: 0 ok, -1 error
 */
int8_t RxStatus(void);

/**
 * @function RxIsMsgReceived
 * @brief check if a message has been received
 * @param none
 * @return bool: true -> received
 */
bool RxIsMsgReceived(void);

/**
 * @function RxIsEmpty
 * @brief check if a message has been completly parsed
 * @param none
 * @return bool: true -> completed
 */
bool RxIsEmpty(void);

/**
 * @function ExtractU8
 * @brief extract a u8 from the message, increment the current msg position (+1), decrement msg length (-1)
 * @param none
 * @return uint8_t: the extracted u8; 0 if error
 */
uint8_t RxGetU8(void);

/**
 * @function ExtractU16
 * @brief extract a u16 from the message, increment the current msg position (+2), decrement msg length (-2)
 * @param none
 * @return uint16_t: the extracted u16; 0 if error
 */
uint16_t RxGetU16(void);

/**
 * @function ExtractI16
 * @brief extract a i16 from the message, increment the current msg position (+2), decrement msg length (-2)
 * @param none
 * @return int16_t: the extracted i16; 0 if error
 */
int16_t RxGetI16(void);

/**
 * @function ExtractU32
 * @brief extract a u32 from the message, increment the current msg position (+4), decrement msg length (-4)
 * @param none
 * @return uint32_t: the extracted u32; 0 if error
 */
uint32_t RxGetU32(void);

/**
 * @function ExtractI32
 * @brief extract a i32 from the message, increment the current msg position (+4), decrement msg length (-4)
 * @param none
 * @return int32_t: the extracted i32; 0 if error
 */
int32_t RxGetI32(void);

/**
 * @function ExtractRec
 * @brief extract a rect_st from the message, increment the current msg position (+8), decrement msg length (-8)
 * @param rect_st *rec: rec output
 * @return none
 */
void RxGetRec(rect_st *rec);

/**
 * @function ExtractTxt
 * @brief extract a string (\0 terminated), increment the current msg position & decrement msg length according strlen
 * @param const uint8_t **pTxt: will receive the pointer to the str start
 * @return none
 */
void RxGetTxt(const uint8_t **pTxt);

#endif
