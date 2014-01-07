/**
 * @file serial_remote.h
 * @brief serial remote (slave side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-23
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


/**
 * @function SerialRemoteTask
 * @brief serial remote task; called at each software cycles, from main() through pCurrentTask pointer
 * @param none
 * @return none
 */
void SerialRemoteTask(void);


/**
 * @function DisplayWaitMsg
 * @brief Display the waiting msg, at startup
 * @param none
 * @return none
 */
void ErrorMsg(const char *file, const char *function, uint16_t line, const char *str);
#define Error(str) ErrorMsg(__FILE__, __FUNCTION__, __LINE__, str)  /*quick & dirty error macro*/
extern const char *EXTRACT_ERROR_MSG; /*the most common error*/

#endif
