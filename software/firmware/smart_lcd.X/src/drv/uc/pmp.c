/**
 * @file pmp.c
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

#include "pmp.h"
#include "hw_config.h"


/**
 * @function PMP_Init
 * @brief initialize the PMP
 * @param none
 * @return none
 */
void PMP_Init(void) {
  PMMODE = 0;
  PMAEN = 0;
  PMCON = 0;
  PMMODEbits.MODE = 2;    /*Intel 80 master interface*/
  PMMODEbits.WAITB = 0;   /*empiric ! */
  PMMODEbits.WAITM = 1;   /*empiric ! */
  PMMODEbits.WAITE = 0;   /*empiric ! */
  PMMODEbits.MODE16 = 1;                          //16 bit mode
  PMCONbits.PTRDEN = 1;                           //enable RD line
  PMCONbits.PTWREN = 1;                           //enable WR line
  PMCONbits.PMPEN = 1;                            //enable PMP
}
