/**
 * @file setup.h
 * @brief quick & dirty setup menu
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

#ifndef _setup_h_
#define _setup_h_

#include "main.h"

/**
 * @function SetupTask
 * @brief First task to be executed; enter setup if touchscreen pressed, run BootTask otherwise
 * @param none
 * @return none
 */
void SetupTask(void);

/**
 * @function SetupMenuDisplayTask
 * @brief Display the setup screen
 * @param none
 * @return none
 */
void SetupMenuDisplayTask(void);

#endif
