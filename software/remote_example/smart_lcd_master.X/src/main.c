/**
 * @file main.c
 * @brief entry point (master side)
 * @author Duboisset Philippe
 * @version 0.1b
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

#include "main.h"
#include "ticks.h"
#include "uc.h"
#include "delay.h"
#include "serial_remote.h"


int32_t main(void) {

  UcInit();
  TicksInit();

  /*main loop*/
  while(1) {

    /*GUI task*/
    SerialRemoteTask();
    
    //MyUserProcessGoesHere();

    /*CPU limiter*/
    DelayMs(1);
  }

  return -1;
}
