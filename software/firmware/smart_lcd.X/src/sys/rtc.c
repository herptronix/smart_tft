/**
 * @file rtc.c
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

#include "rtc.h"
#include "timer.h"


/**
 * private variables definition
 */
static uint8_t sec = 0, min = 0, hour = 0, date = 1, mon = 1, year = 113;


/**
 * @function RtcTask
 * @brief Software RTC task; shall be called in main loop
 * @param none
 * @return none
 */
void RtcTask(void) {

  const uint8_t maxDate[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  static timer_t timer = 0;
  uint8_t tmp;

  if(IsTimerElapsed(timer)) {

    timer = GetPeriodicTimeout(1000);

    sec++;
    if(sec > 59) {
      sec = 0;
      min++;

      if(min > 59) {
        min = 0;
        hour++;

        if(hour > 23) {
          hour = 0;

          tmp = maxDate[mon - 1];
          if(tmp == 28 && year % 4 == 0) tmp++;

          date++;
          if(date > tmp) {
            date = 1;
            mon++;

            if(mon > 12) {
              mon = 1;
              year++;
            }
          }
        }
      }
    }
  }
}


/**
 * @function RtcGetTimeStamp
 * @brief return timestamp (current time)
 * @param none
 * @return uint32_t: std timestamp
 */
uint32_t RtcGetTimeStamp(void) {

  uint32_t res = 0;

	res =	((uint32_t)year - 80) << 25
			| (uint32_t)mon << 21
			| (uint32_t)date << 16
			| (uint32_t)hour << 11
			| (uint32_t)min << 5
			| (uint32_t)sec >> 1;

  return res;
}
