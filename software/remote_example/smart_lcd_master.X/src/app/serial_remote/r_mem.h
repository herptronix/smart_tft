/**
 * @file r_mem.h
 * @brief Shared Memory Access serialized commands (maser side)
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

void R_MEM_WriteU8(uint16_t offset, uint8_t data);
void R_MEM_WriteU16(uint16_t offset, uint16_t data);
void R_MEM_WriteI16(uint16_t offset, int16_t data);
void R_MEM_WriteU32(uint16_t offset, uint32_t data);
void R_MEM_WriteI32(uint16_t offset, int32_t data);
void R_MEM_WriteU8Arr(uint16_t offset, uint16_t len, const uint8_t *data);
void R_MEM_WriteStr(uint16_t offset, uint16_t len, const void *str);
void R_MEM_Memset(uint16_t offset, uint16_t len, uint8_t fill);
void R_MEM_ReadU8(uint16_t offset);
void R_MEM_ReadU16(uint16_t offset);
void R_MEM_ReadI16(uint16_t offset);
void R_MEM_ReadU32(uint16_t offset);
void R_MEM_ReadI32(uint16_t offset);
void R_MEM_ReadU8Arr(uint16_t offset, uint16_t len);
void R_MEM_ReadStr(uint16_t offset, uint16_t maxLen);

#endif
