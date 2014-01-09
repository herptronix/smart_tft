/**
 * @file delay.h
 * @brief blocking delay (approximated) implementation
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
 *
 * Copyright (C) <2013>  Duboisset Philippe <duboisset.philippe@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _delay_h_
#define _delay_h_

#include "main.h"
#include "hw_config.h"

/**
 * @macro Delay100ns
 * @brief bloquing wait of AT LEAST 100 ns
 * @param none
 * @return none
 */
#if SYS_CLK == 80000000
  #define Delay100ns() __asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop"); \
                       __asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop")
#else
  #error SYS_CLK value not handled
#endif

/**
 * @function DelayUs
 * @brief bloquing wait of AT LEAST u16delayUs microseconds
 * @param uint16_t u16delayUs: desired delay (in us)
 * @return none
 */
void DelayUs(uint16_t u16delayUs);

/**
 * @function DelayMs
 * @brief bloquing wait of AT LEAST u16delayMs milliseconds; during this wait, CPU is idle mode
 * @param uint16_t u16delayMs: desired delay (in ms)
 * @return none
 */
void DelayMs(uint16_t u16delayMs);

/**
 * @function DelayS
 * @brief bloquing wait of AT LEAST u16delayS seconds; during this wait, CPU is idle mode
 * @param uint16_t u16delayS: desired delay (in s)
 * @return none
 */
void DelayS (uint16_t u16delayS);

#endif
