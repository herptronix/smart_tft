/**
 * @file serial_remote.h
 * @brief communication with the smart TFT (master side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-17
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

#ifndef _serial_remote_h_
#define _serial_remote_h_

#include "main.h"
#include "serial_common.h"


/**
 * @function SerialRemoteTask
 * @brief remote task; shall be called at each software cycle
 * @param none
 * @return none
 */
void SerialRemoteTask(void);

/**
 * @function R_GUI_SetTask
 * @brief set the current user handler
 * @param void (*pFunc)(void): pointer to the user handler
 * @return none
 */
void R_GUI_SetTask(void (*pFunc)(void));

/**
 * @function R_GUI_SetErrorTask
 * @brief set the user error handler
 * @param void (*pFunc)(void): pointer to the user error handler
 * @return none
 */
void R_GUI_SetErrorTask( void (*pFunc)(void));

/**
 * @function RemoteTask
 * @brief remote task; shall be called in main loop
 * @param none
 * @return none
 */
void RemoteTask(void);

#endif
