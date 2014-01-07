/**
 * @file ssm.h
 * @brief shared memory (slave side)
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

#ifndef _ssm_h_
#define _ssm_h_

#include "main.h"

/**
 * a byte array (SSM_SIZE bytes) is stored into the PIC32 RAM;
 * SSM read and write operations are based on offset (between 0 and SSM_SIZE-1), not on physical addresses
 * variable shall fulfill alignment rules: an U16 shall have its offset%2==0, an U32 shall have its offset%4==0...
 */
#define SSM_SIZE 2048


void * SSM_GetAddress(uint16_t offset, uint8_t align);
int8_t SSM_WriteI8(uint16_t offset, int8_t val);
int8_t SSM_WriteU8(uint16_t offset, uint8_t val);
int8_t SSM_WriteI16(uint16_t offset, int16_t val);
int8_t SSM_WriteU16(uint16_t offset, uint16_t val);
int8_t SSM_WriteI32(uint16_t offset, int32_t val);
int8_t SSM_WriteU32(uint16_t offset, uint32_t val);
int8_t SSM_ReadI8(uint16_t offset, int8_t *val);
int8_t SSM_ReadU8(uint16_t offset, uint8_t *val);
int8_t SSM_ReadI16(uint16_t offset, int16_t *val);
int8_t SSM_ReadU16(uint16_t offset, uint16_t *val);
int8_t SSM_ReadI32(uint16_t offset, int32_t *val);
int8_t SSM_ReadU32(uint16_t offset, uint32_t *val);

#endif
