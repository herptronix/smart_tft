/**
 * @file pmp.h
 * @brief pmp driver
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

#ifndef _pmp_h_
#define _pmp_h_

#include "main.h"

#define _PMP_DIRTY_SPEED_

/**
 * @function PMP_Init
 * @brief initialize the PMP
 * @param none
 * @return none
 */
void PMP_Init(void);


#ifdef _PMP_DIRTY_SPEED_
  #define PMP_Write(data) {PMDIN = data;} /*really dirty implementation for maximum speed; lcd timings may not be respected! */
#else
  #define PMP_Write(data) {PMDIN = data; while(PMMODE & 0x8000);} /* "clean" implementation; 0x8000: BUSY bit*/
#endif

#endif
