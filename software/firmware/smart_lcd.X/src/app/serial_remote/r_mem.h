/**
 * @file r_mem.h
 * @brief serialized memory functions decoder (slave side)
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

#ifndef _r_mem_h
#define _r_mem_h

#include "opList.h"

int8_t R_MEM_WriteU8(void);
int8_t R_MEM_WriteU16(void);
int8_t R_MEM_WriteI16(void);
int8_t R_MEM_WriteU32(void);
int8_t R_MEM_WriteI32(void);
int8_t R_MEM_WriteU8Arr(void);
int8_t R_MEM_WriteStr(void);
int8_t R_MEM_Memset(void);
int8_t R_MEM_ReadU8(void);
int8_t R_MEM_ReadU16(void);
int8_t R_MEM_ReadI16(void);
int8_t R_MEM_ReadU32(void);
int8_t R_MEM_ReadI32(void);
int8_t R_MEM_ReadU8Arr(void);
int8_t R_MEM_ReadStr(void);

#endif
