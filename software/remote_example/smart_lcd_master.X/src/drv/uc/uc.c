/**
 * @file uc.c
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

#include "uc.h"
#include "hw_config.h"


/**
 * @function UcInit
 * @brief initialize the uC. This function MUST be called at the very beginning of the program
 * @param none
 * @return none
 */
void UcInit(void) {

  /*configure the uc & its peripherals to run at 80MHz*/
  SYSTEMConfigPerformance(SYS_CLK);

  /*enable interrupts*/
  INTEnableSystemMultiVectoredInt();

  /*disable JTAG to release function GPIO*/
  DDPCON = 0x0000;

  /*Configure GPIO B as digital (analog input by default, wtf...)*/
  AD1PCFG = 0xFFFF;
}


/**
 * @function UcIdle
 * @brief set uC in sleep mode. It will be waked up on a interruption, or when WDT will overflow (configuration bits)
 * @param none
 * @return none
 */
void UcIdle(void) {
  ClearWDT();       /*clear & enable WDT timer*/
  EnableWDT();      /*WDT enabled, but only used for counting; when overflows, does not reset the CPU*/
  PowerSaveIdle();  /*sleep mode -- CPU will awake on interruptions or WDT timer overflow*/
  DisableWDT();
}
