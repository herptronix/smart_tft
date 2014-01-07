/**
 * @file adc.h
 * @brief adc driver
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

#ifndef _adc_h_
#define _adc_h_

#include "main.h"

#define ADC_MAX_VALUE           1023  /*adc full scale*/

/**
 * @macro ADC_SelectChannel
 * @brief select a channel to sample
 * @param c: channel, range [0-15], equivalent to ANx
 * @return none
 */
#define ADC_SelectChannel(c)    AD1CHS = c << 16

/**
 * @macro ADC_StartSampling
 * @brief start sampling
 * @param none
 * @return none
 */
#define ADC_StartSampling()     AD1CON1 |= 0x0002

/**
 * @macro ADC_StartConversion
 * @brief stop sampling & start conversion
 * @param none
 * @return none
 */
#define ADC_StartConversion()   AD1CON1 &= ~0x0002

/**
 * @macro ADC_IsBusy
 * @brief check the ADC status
 * @param none
 * @return true if the adc is converting, false if the adc has completed its conversion
 */
#define ADC_IsBusy()            (!(AD1CON1 & 0x0001))

/**
 * @macro ADC_Read
 * @brief return the result of the conversion
 * @param none
 * @return result of the conversion
 */
#define ADC_Read()              ADC1BUF0

/**
 * @macro ADC_Init
 * @brief initialize the adc
 * @param none
 * @return none
 */
#define ADC_Init()             {AD1CON1 = 0x0000;   /*OFF, out=i16, manual sample/convert*/ \
                                AD1CON2 = 0x0000;   /*Vref+ =AVdd, Vref-=AVss, MUXA only*/ \
                                AD1CON3 = 0x0109;   /*PER_CLK, 1 Tad auto-sample (dummy), Tad = 2*(9+1)*12.5ns */ \
                                AD1CSSL = 0x0000;   /*No scanned inputs*/ \
                                AD1CON1 |= 0x8000;} /*ADC ON*/

#endif
