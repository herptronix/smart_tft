/**
 * @file delay.c
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

#include "delay.h"
#include "timer.h"
#include "uc.h"


/**
 * @function DelayUs
 * @brief bloquing wait of AT LEAST u16delayUs microseconds
 * @param uint16_t u16delayUs: desired delay (in us)
 * @return none
 */
void DelayUs(uint16_t u16delayUs) {
  uint32_t cnt;
  cnt = (uint32_t)u16delayUs * 10;
  while(cnt-- > 0) {
    Delay100ns();
  }
}


/**
 * @function DelayMs
 * @brief bloquing wait of AT LEAST u16delayMs milliseconds; during this wait, CPU is idle mode
 * @param uint16_t u16delayMs: desired delay (in ms)
 * @return none
 */
void DelayMs(uint16_t u16delayMs) {
  timer_t timer = GetTimeout(u16delayMs);
  while(IsTimerElapsed(timer) == FALSE) {
    UcIdle();
  }
}


/**
 * @function DelayS
 * @brief bloquing wait of AT LEAST u16delayS seconds; during this wait, CPU is idle mode
 * @param uint16_t u16delayS: desired delay (in s)
 * @return none
 */
void DelayS(uint16_t u16delayS) {
  timer_t timer = GetTimeout((uint32_t)u16delayS * 1000);
  while(IsTimerElapsed(timer) == FALSE) {
    UcIdle();
  }
}
