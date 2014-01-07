/**
 * @file serial_tx.h
 * @brief TX functions (slave side)
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

#ifndef _serial_tx_h
#define _serial_tx_h

#include "main.h"
#include "p2d.h"

/**
 * @function TxMsgStart
 * @brief start a answer message
 * @param none
 * @return none
 */
void TxMsgStart(void);

/**
 * @function TxMsgStop
 * @brief stop the answer message
 * @param none
 * @return none
 */
void TxMsgStop(void);

/**
 * @function TxMsgPutByte
 * @brief add a byte in the answer message; handle the TOKEN_SKIP
 * @param uint8_t byte
 * @return none
 */
void TxMsgPutByte(uint8_t byte);

/**
 * @function TxMsgPutStr
 * @brief add a string in the answer message
 * @param const void *str: string
 * @return none
 */
void TxMsgPutStr(const void *str);

/**
 * @function TxMsgPutRect
 * @brief add a rect_st in the answer message
 * @param const rect_st *rec
 * @return none
 */
void TxMsgPutRect(const rect_st *rec);

/**
 * @function TxMsgPutRaw
 * @brief add a u8 array in the answer message
 * @param const void *p: pointer to the first byte of u8 array
 * @param uint16_t len: size of the array
 * @return none
 */
void TxMsgPutRaw(const void *p, uint16_t len);

/*put whatever in the answer */
#define TxMsgPut(data) TxMsgPutRaw( (const void *) &(data), sizeof(data))

#endif
