/**
 * @file ssm.c
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

#include "ssm.h"

#ifdef SMART_TFT_SLAVE_MODE

/**
 * Local variables
 */
static uint8_t __attribute__ ((aligned(8))) ssm[SSM_SIZE];

/**
 * Local functions
 */
static bool SSM_IsValid(uint16_t offset, uint8_t size);
static int8_t GenericWrite(uint16_t offset, uint8_t size, const void *data);
static int8_t GenericRead(uint16_t offset, uint8_t size, void *dataOut);


/**
 * @function SSM_GetAddress
 * @brief retrieve the physical address of a variable
 * @param uint16_t offset: variable offset
 * @param uint8_t align: alignment rule
 * @return void *: pointer to the variable
 */
void *SSM_GetAddress(uint16_t offset, uint8_t align) {

  void *res = NULL;

  /*return the physical address*/
  if(SSM_IsValid(offset, align)) {
    res = (void *) &ssm[offset];
  }

  return res;
}


/*prefer explicit variable types instead of one generic macro here...*/
//#define SSM_Write(offset, val) GenericWrite(offset, sizeof(val), (const void *) &(val))
//#define SSM_Read(offset, val) GenericRead(offset, sizeof(val), (void *) &(val))
int8_t SSM_WriteI8(uint16_t offset, int8_t val)     {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_WriteU8(uint16_t offset, uint8_t val)    {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_WriteI16(uint16_t offset, int16_t val)   {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_WriteU16(uint16_t offset, uint16_t val)  {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_WriteI32(uint16_t offset, int32_t val)   {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_WriteU32(uint16_t offset, uint32_t val)  {return GenericWrite(offset, sizeof(val), &val);}
int8_t SSM_ReadI8(uint16_t offset, int8_t *val)     {return GenericRead(offset, sizeof(*val), val);}
int8_t SSM_ReadU8(uint16_t offset, uint8_t *val)    {return GenericRead(offset, sizeof(*val), val);}
int8_t SSM_ReadI16(uint16_t offset, int16_t *val)   {return GenericRead(offset, sizeof(*val), val);}
int8_t SSM_ReadU16(uint16_t offset, uint16_t *val)  {return GenericRead(offset, sizeof(*val), val);}
int8_t SSM_ReadI32(uint16_t offset, int32_t *val)   {return GenericRead(offset, sizeof(*val), val);}
int8_t SSM_ReadU32(uint16_t offset, uint32_t *val)  {return GenericRead(offset, sizeof(*val), val);}


/**
 * @function SSM_IsValid
 * @brief check the validity of a given offset/size
 * @param uint16_t offset
 * @param uint8_t size
 * @return bool
 */
static bool SSM_IsValid(uint16_t offset, uint8_t size) {

  bool bValid = false;

  if(size > 0                             /*size/align shall be >= 1*/
     && size < SSM_SIZE                   /*size/align shall not be greater than SSM_SIZE; usually, size/align is 1/2/4.*/
      && offset < (SSM_SIZE - size)       /*data is within the memory*/
       && offset % size == 0) {           /*offset is correctly aligned (we consider that size == align)*/

      bValid = true;
  }

  return bValid;
}


/**
 * @function GenericRead
 * @brief read from shared memory
 * @param uint16_t offset: variable offset
 * @param uint8_t size: number of bytes to read
 * @param void *dataOut: write destination
 * @return int8_t: 0 success, -1 error
 */
static int8_t GenericRead(uint16_t offset, uint8_t size, void *dataOut) {

  int8_t res = -1;
  uint8_t ii, *p;

  /*correct input ?*/
  if(dataOut != NULL && SSM_IsValid(offset, size)) {

    p = (uint8_t *) dataOut;
    for(ii = 0; ii < size; ii++) {
      p[ii] = ssm[offset + ii];
    }

    /*success*/
    res = 0;
  }

  return res;
}


/**
 * @function GenericWrite
 * @brief write from shared memory
 * @param uint16_t offset: variable offset
 * @param uint8_t size: number of bytes to write
 * @param const void *dataIn: read source
 * @return int8_t: 0 success, -1 error
 */
static int8_t GenericWrite(uint16_t offset, uint8_t size, const void *dataIn) {

  int8_t res = -1;
  uint8_t ii;
  const uint8_t *p;

  /*correct input ?*/
  if(dataIn != NULL && SSM_IsValid(offset, size)) {

    p = (const uint8_t *) dataIn;
    for(ii = 0; ii < size; ii++) {
      ssm[offset + ii] = p[ii];
    }

    /*success*/
    res = 0;
  }

  return res;
}

#endif
