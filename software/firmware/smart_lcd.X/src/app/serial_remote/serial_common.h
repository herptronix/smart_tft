/**
 * @file serial_common.h
 * @brief serial configuration (slave side)
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

#ifndef _serial_common_h
#define _serial_common_h

//#define SERIAL_MASTER
#define SERIAL_SLAVE

#define UART_SPEED  1000000 /*bauds*/

#define TOKEN_START 0x55    /*2 consecutive TOKEN_START mean <message start>*/
#define TOKEN_STOP  0xAA    /*2 consecutive TOKEN_STOP mean <message stop>*/
#define TOKEN_SKIP  0xFE    /*a TOKEN_SKIP is inserted when the user wants to send 2 consecutives TOKEN_STOP without ending the message*/

#ifdef SERIAL_MASTER
  #define RX_BUFF_SIZE 300  /*RX buffer size*/
#endif

#ifdef SERIAL_SLAVE
  #define RX_BUFF_SIZE 5000 /*RX buffer size*/
#endif

#include "uart.h"
#include "serial_tx.h"
#include "serial_rx.h"

#endif
