/**
 * @file main.h
 * @brief SMART TFT software entry point
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd) 2013-11-01
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

#ifndef _main_h_
#define _main_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <plib.h>
#include <p32xxxx.h>

/**
 * SMART_TFT_SLAVE_MODE
 * Comment this flag if you want to embbed your application directly on the smart TFT.
 * Otherwise, the smart TFT executes orders coming from the serial comm
 */
#define SMART_TFT_SLAVE_MODE

/**
 * INCLUDE_GUI_DEMO
 * uncomment this flag if you want to exclude the gui demonstration from the compilation time
 * it will save 3-4% of flash memory
 */
#define INCLUDE_GUI_DEMO

/*current task; executed at each software cycle, in the main loop*/
extern void (*pCurrentTask) (void);

#endif
