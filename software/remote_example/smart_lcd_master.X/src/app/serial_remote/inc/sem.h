/**
 * @file sem.h
 * @brief atomic operation (basic exclusion mechanism for interruption routines)
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

#ifndef _sem_h_
#define _sem_h_

#include "main.h"

/*
 * SemLock & SemUnlock shall be use by the low priority software (e.g. main function)
 * IsSemLocked & IsSemUnlocked shall be use by the high priority software (e.g. interrupts)
 */

/*semaphore type (unsigned char)*/
#define sem_t               uint8_t

/*semaphore state*/
#define SEM_LOCKED          0x55
#define SEM_UNLOCKED        0xAA

/*lock & unlock operation are atomic (semaphore goes from SEM_LOCKED to SEM_UNLOCKED
 * in one non-interruptable instruction) write access on 'a' shall be atomic*/
#define SemLock(a)          (a = SEM_LOCKED)
#define SemUnlock(a)        (a = SEM_UNLOCKED)

/*semaphore status read -- don't care if atomic or not*/
#define IsSemLocked(a)      (a == SEM_LOCKED? 1: 0)
#define IsSemUnlocked(a)    (a == SEM_UNLOCKED? 1: 0)

#endif
