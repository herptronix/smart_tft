/**
 * @file salloc.h
 * @brief quick & dirty memory allocator
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

#ifndef _salloc_h_
#define _salloc_h_

#include "main.h"

/**
 * 15-20ko (min) should be given to the allocator for using GUI
 * here, 100ko is given to the allocator
 */
#define SALLOC_SIZE 100000

/**
 * @function salloc
 * @brief allocate memory
 * @param uint32_t byteNeeded: contiguous memory to allocate, in bytes
 * @return void *: pointer to allocated memory if success, NULL if error
 */
void *salloc(uint32_t byteNeeded);

/**
 * @function sfree
 * @brief free memory, from a physical address to the end
 * @param void *ptr: physical address
 * @return none
 */
void sfreeFrom(void *ptr);

/**
 * @function sfreeAll
 * @brief free all the memory allocated by salloc()
 * @param none
 * @return none
 */
void sfreeAll(void);

/**
 * @function sallocGetUsed
 * @brief return the bytes allocated
 * @param none
 * @return uint32_t: bytes allocated
 */
uint32_t sallocGetUsed(void);

/**
 * @function sallocGetTotal
 * @brief return the bytes allocated + bytes allocatable
 * @param none
 * @return uint32_t: SALLOC_SIZE
 */
uint32_t sallocGetTotal(void);

#endif
