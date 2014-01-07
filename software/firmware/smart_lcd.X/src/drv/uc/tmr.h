/**
 * @file tmr.h
 * @brief hardware timer handling
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-04-07
 *
 * See tmr.c for timer interrupts priorities
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

#ifndef _tmr_h_
#define _tmr_h_

#include "main.h"


typedef enum {
  TMR_1 = 1,
  TMR_3 = 3,
  TMR_4,
  TMR_5
} tmr_t; /*available hardware timers enumeration*/


/**
 * @function TmrSetFrequency
 * @brief configure a given timer with a desired frequency
 * @param tmr_t tmr_id: timer id
 * @param uint32_t desiredFrequency: desired frequency, in Hz
 * @return int8_t: 0 sucess, otherwise error
 */
int8_t TmrSetFrequency(tmr_t id, uint32_t freq);

/**
 * @function TmrSetCallback
 * @brief associate a callback function to a given timer
 * @param tmr_t tmr_id: timer id
 * @param *ptrCallback: pointer to a void function(void)
 * @return none
 */
void TmrSetCallback(tmr_t id, void (*callback)(void));

/**
 * @function TmrLaunch
 * @brief enable a given timer, if this one is correctly configured
 * @param tmr_t tmr_id: timer id
 * @return none
 */
void TmrLaunch(tmr_t id);

/**
 * @function TmrStop
 * @brief stop a given timer
 * @param tmr_t tmr_id: timer id
 * @return none
 */
void TmrStop(tmr_t id);

#endif
