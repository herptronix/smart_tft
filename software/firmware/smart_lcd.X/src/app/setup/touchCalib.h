/**
 * @file touchCalib.h
 * @brief quick & dirty functions for touchscreen calibration procedure
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-03
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

#ifndef _touchCalib_h_
#define _touchCalib_h_

#include "main.h"

/**
 * @function TouchLoadConfig
 * @brief Configure the touchscreen with the <touchscr.cfg> file content
 * @param none
 * @return none TODO: return & robustness enhancement
 */
void TouchLoadConfig(void);

/**
 * @function TouchCalibTask
 * @brief Touchscreen calibration: init. task
 * @param none
 * @return none
 */
void TouchCalibTask(void);

#endif
