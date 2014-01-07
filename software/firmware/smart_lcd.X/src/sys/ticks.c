/**
 * @file ticks.c
 * @brief 1ms absolute time reference
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-04-07 : initial version
 *  0.2b  2013-09-20 : Add TicksSetExternalCallback() for FatFS support
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

#include "ticks.h"
#include "tmr.h"
#include "sem.h"


/**
 * private variables definition
 */
static volatile ticks_t u64AbsoluteTicks = 0;   /*absolute ticks value, incremeted by interruption*/
static volatile ticks_t u64ReadableTicks = 0;   /*final ticks value, provided to the user*/
static volatile sem_t sem = SEM_UNLOCKED;       /*atomic accessible variable, used to lock writes on u64Ticks2*/

static ticks_t u64wdtTimer;
static void (*wdtFunc)(void) = NULL;
static void (*extFunc)(void) = NULL;

/**
 * private functions prototypes
 */
static void TicksCallback(void);



/**
 * @function TicksInit
 * @brief initialize the aboslute 1ms reference clock
 * @param none
 * @return none
 */
void TicksInit(void) {
  u64AbsoluteTicks = u64ReadableTicks = 0;  /*time reference begin to 0ms*/
  SemUnlock(sem);
  TmrSetFrequency(TMR_1, 1000);             /*Set ticks to 1ms (1000 -> 1kHz)*/
  TmrSetCallback(TMR_1, TicksCallback);     /*Associate timer interruption to TicksCallback() function*/
  TmrLaunch(TMR_1);                         /*Start timer*/
}


/**
 * @function TicksGet
 * @brief return the number of the ms elapsed since TicksInit() call
 * @param none
 * @return ticks_t: ms
 */
ticks_t TicksGet(void) {
  ticks_t ticks;
  SemLock(sem);
  ticks = u64ReadableTicks;
  SemUnlock(sem);
  return ticks;
}


/**
 * @function TicksSetWatchdog
 * @brief enable a watchdog function
 * @param void (*function)(void): function to execute when reaching a delay
 * @param ticks_t delay: dela, in ms
 * @return none
 */
void TicksSetWatchdog(void (*function)(void), ticks_t delay) {
  TmrStop(TMR_1);
  wdtFunc = function;
  u64wdtTimer = u64AbsoluteTicks + delay;
  TmrLaunch(TMR_1);
}


/**
 * @function TicksSetExternalCallback
 * @brief enable a external function, which will be called every ticks
 * @param void (*function)(void): pointer to the extern function
 * @return none
 */
void TicksSetExternalCallback(void (*function)(void)) {
  TmrStop(TMR_1);
  extFunc = function;
  TmrLaunch(TMR_1);
}


/**
 * @function TicksCallback
 * @brief clock incrementation
 * @param none
 * @return none
 */
static void TicksCallback(void) {
  u64AbsoluteTicks++;                     /*always increment the absolute time reference*/
  if(IsSemUnlocked(sem)) {
    u64ReadableTicks = u64AbsoluteTicks;  /*update u64ReadableTicks if unlocked*/
  }

  if(extFunc != NULL) {
    extFunc();
  }

  if(wdtFunc != NULL && u64AbsoluteTicks > u64wdtTimer) {
    wdtFunc();
    wdtFunc = NULL;
  }
}
