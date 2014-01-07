/**
 * @file rtc.h
 * @brief quick & dirty software rtcc, needed for FAT-Fs
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-09-20
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

#ifndef _rtc_h_
#define _rtc_h_

#include "main.h"

/**
 * @function RtcTask
 * @brief Software RTC task; shall be called in main loop
 * @param none
 * @return none
 */
void RtcTask(void);

/**
 * @function RtcGetTimeStamp
 * @brief return timestamp (current time)
 * @param none
 * @return uint32_t: std timestamp
 */
uint32_t RtcGetTimeStamp(void);

#endif
