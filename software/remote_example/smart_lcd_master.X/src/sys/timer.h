/**
 * @file timer.h
 * @brief software timer implementation
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

#ifndef _timer_h_
#define _timer_h_

#include "main.h"
#include "ticks.h"

typedef ticks_t timer_t;

/**
 * @function GetTimeout
 * @brief return the ticks value which correspond to actual ticks + desired delay
 * @param uint32_t u32delayMs: desired delay (in ms)
 * @return timer_t: ticks value
 */
timer_t GetTimeout(uint32_t u32delayMs);

/**
 * @function GetPeriodicTimeout
 * @brief return the periodic ticks value which correspond to actual ticks + desired delay, and round the value to
 * a multiple of u32delayMs
 * @param uint32_t u32delayMs: periodic desired delay (in ms)
 * @return timer_t: ticks value
 */
timer_t GetPeriodicTimeout(uint32_t u32delayMs);

/**
 * @function IsTimerElapsed
 * @brief checks if the timer is elapsed
 * @param timer_t timer: ticks delay
 * @return BOOL: TRUE if delay is finished, FALSE otherwise
 */
BOOL IsTimerElapsed(timer_t timer);

#endif
