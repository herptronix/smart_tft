/**
 * @file uart.h
 * @brief PIC32 uart driver
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

#ifndef _uart_h_
#define _uart_h_

#include "main.h"

/**
 * @function UartMaskRxInterrupt
 * @brief mask RX ISR
 * @param none
 * @return none
 */
void UartMaskRxInterrupt(void);

/**
 * @function UartUnmaskRxInterrupt
 * @brief unmask RX ISR
 * @param none
 * @return none
 */
void UartUnmaskRxInterrupt(void);

/**
 * @function UartConfigure
 * @brief configure & turn on the uart
 * @param uint32_t speed: desired speed, in bauds
 * @return none
 */
void UartConfigure(uint32_t speed);

/**
 * @function UartRegisterRxISR
 * @brief register an external function as RX ISR handler
 * @param void (*pFunc)(uint8_t byte): pointer to the external handler
 * @return none
 */
void UartRegisterRxISR(void (*pFunc)(uint8_t byte));

/**
 * @function UartSendByte
 * @brief put a byte on TX
 * @param uint8_t b: byte
 * @return none
 */
void UartSendByte(uint8_t b);

#endif
