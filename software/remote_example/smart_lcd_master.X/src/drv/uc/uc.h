/**
 * @file uc.h
 * @brief PIC32MX795F512L specific functions (init, powermode, ...)
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

#ifndef _uc_h_
#define _uc_h_

#include "main.h"

/**
 * @function UcInit
 * @brief initialize the uC. This function MUST be called at the very beginning of the program
 * @param none
 * @return none
 */
void UcInit(void);

/**
 * @function UcIdle
 * @brief set uC in sleep mode. It will be waked up on a interruption, or when WDT will overflow (configuration bits)
 * @param none
 * @return none
 */
void UcIdle(void);

#endif
