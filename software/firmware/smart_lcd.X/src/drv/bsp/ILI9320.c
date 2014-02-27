/**
 * @file ILI9320.c
 * @brief lcd driver
 * @author Duboisset Philippe
 * @version 0.5b
 * @date (yyyy-mm-dd) 2013-04-07
 *                    2013-07-27: improvement of power-on sequence
 *                    2013-08-20: modification of <0x0003, 0x1038> (RGB swap, for compatibility with SDL)
 *                    2013-11-14: LCD_WriteReg is now accessible outside (for gamma ajdustement)
 *                    2014-02-20: support of display orientation (0, 90, 180, 270°)
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

#include "ILI9320.h"
#include "pmp.h"
#include "gpio.h"
#include "delay.h"



#define CS_PORT   G
#define CS_PIN    13
#define RS_PORT   G
#define RS_PIN    12
#define RST_PORT  D
#define RST_PIN   2
#define CS_SELECT   {GPIO_SetPin(CS_PORT , CS_PIN , 0); Delay100ns();}
#define CS_UNSELECT {GPIO_SetPin(CS_PORT , CS_PIN , 1); Delay100ns();}
#define RS_REGISTER {GPIO_SetPin(RS_PORT , RS_PIN , 0); Delay100ns();}
#define RS_DATA     {GPIO_SetPin(RS_PORT , RS_PIN , 1); Delay100ns();}
#define RST_SET      GPIO_SetPin(RST_PORT, RST_PIN, 0)
#define RST_RELEASE  GPIO_SetPin(RST_PORT, RST_PIN, 1)


/**
 * private variables
 */
#define T_WAIT 0xFFFE
#define CFGEND 0xFFFF
static length_t lcd_w = 0, lcd_h = 0, xMax = 0, yMax = 0;
static const uint16_t ili9320_cfg[] = {

  /*
   * Configuration & power sequence
   * See ILI9320 application note (V0.92, april 21rd 2007)
   */

  /*osc & Vcore setting*/
  0x00E5, 0x8000, /*0x00E5: Vcore setting*/
  0x0000, 0x0001, /*0x0000: Start Oscillator*/
  T_WAIT,     12, /*§8.2.3. "Wait at least 10ms to let the frequency of oscillator stable" */

  /*power supply setting*/
  0x0010, 0x0000, /*0x0010: Power Control 1: clear*/
  0x0011, 0x0004, /*0x0011: Power Control 2: set VC2-0*/
  0x0012, 0x0000, /*0x0012: Power Control 3: clear*/
  0x0013, 0x0000, /*0x0013: Power Control 4: clear*/
  T_WAIT,    200,
  0x0010, 0x14F0, /*0x0010: Power Control 1*/
  0x0011, 0x0004, /*0x0011: Power Control 2*/
  T_WAIT,     50,
  0x0012, 0x001B, /*0x0012: Power Control 3*/
  T_WAIT,     50,
  0x0013, 0x0F00, /*0x0013: Power Control 4*/
  0x0029, 0x000F, /*0x0029: Power Control 7*/
  T_WAIT,     50,

  /** other registers setting**/
  0x0001, 0x0000, /*0x0001: Driver Output Control 1 [SM;SS]*/
  0x0002, 0x0600, /*0x0002: LCD Driving Wave Control [B/C;EOR]*/

#if DISP_ORIENTATION == 0
  0x0003, 0x1038, /*0x0003: Entry Mode [TRI;DFM;BGR;HWM;ORG;I/D1;I/D0;AM]*/
#elif DISP_ORIENTATION == 180
  0x0003, 0x1008, /*0x0003: Entry Mode [TRI;DFM;BGR;HWM;ORG;I/D1;I/D0;AM]*/
#elif DISP_ORIENTATION == 90
  0x0003, 0x1020, /*0x0003: Entry Mode [TRI;DFM;BGR;HWM;ORG;I/D1;I/D0;AM]*/
#elif DISP_ORIENTATION == 270
  0x0003, 0x1010, /*0x0003: Entry Mode [TRI;DFM;BGR;HWM;ORG;I/D1;I/D0;AM]*/
#else
  #error "DISP_ORIENTATION shall be defined to a correct value"
#endif

  0x0004, 0x0000, /*0x0004: Resize Control [RCV1-0;RCH1-0;RSZ1-0]*/
  0x0007, 0x0000, /*0x0007: Display Control 1 [PTDE1-0;BASEE;GON;DTE;CL;D1;D0]*/
  0x0008, 0x0404, /*0x0008: Display Control 2 [FP3-0;BP3-0]*/
  0x0009, 0x0000, /*0x0009: Display Control 3 [PTS2-0;PTG1-0;ISC3-0]*/
  0x000A, 0x0000, /*0x000A: Display Control 4 [FMARKOE;FMI2-0]*/
  0x000C, 0x0000, /*0x000C: RGB Display Interface Control 1 [ENC2-0;RM;DM1-0;RIM1-0]*/
  0x000D, 0x0000, /*0x000D: Frame Marker Position [FMP8-0]*/
  0x000F, 0x0000, /*0x000F: RGB Display Interface Control 2 [VSPL;HSPL;EPL;DPL]*/
  0x0060, 0xA700, /*0x0060: Driver Output Control 2 [GS;NL5-0;SCN5-0]*/
  0x0061, 0x0003, /*0x0061: Base Image Display Control [NDL;VLE;REV]*/
  0x006A, 0x0000, /*0x006A: Vertical Scroll Control [VL8-0]*/
  0x0090, 0x0010, /*0x0090: Panel Interface Control 1 [DIVI1-0;RTNI4-0]*/
  0x0092, 0x0000, /*0x0092: Panel Interface Control 2 [NOWI2-0]*/
  0x0093, 0x0003, /*0x0093: Panel Interface Control 3 [MCPI2-0]*/
  0x0095, 0x0110, /*0x0095: Panel Interface Control 4 [DIVE1-0;RTNE5-0]*/
  0x0097, 0x0000, /*0x0097: Panel Interface Control 5 [NOWE3-0]*/
  0x0098, 0x0000, /*0x0098: Panel Interface Control 6 [MCPE2-0]*/

  /** Display ON sequence **/
  0x0007, 0x0133, /*0x0007: Display Control 1 [PTDE1-0;BASEE;GON;DTE;CL;D1;D0] -- FINAL TURN ON*/

  CFGEND, CFGEND    /*end*/
};


/**
 * @function WriteReg
 * @brief write into a SFR of the LCD
 * @param addr: SFR address; see ILI9320.pdf
 * @param data: 16bit word; see ILI9320.pdf
 * @return none
 */
static void WriteReg(uint16_t addr, uint16_t data) {
  RS_REGISTER;
  PMP_Write(addr);
  RS_DATA;
  PMP_Write(data);
}


/**
 * @function WriteToGram
 * @brief configure the ILI9320 in order to write next PMP data into the graphical buffer
 * @param none
 * @return none
 */
static void WriteToGram(void) {
  RS_REGISTER;
  PMP_Write(0x22);
  RS_DATA;
}


/**
 * @function LCD_WriteReg (user version)
 * @brief write into a SFR of the LCD
 * @param addr: SFR address; see ILI9320.pdf
 * @param data: 16bit word; see ILI9320.pdf
 * @return none
 */
void LCD_WriteReg(uint16_t addr, uint16_t data) {
  WriteReg(addr, data);
  WriteToGram();
}



/**
 * @function LCD_Init
 * @brief turn on & configure the LCD
 * @param none
 * @return none
 */
void LCD_Init(void) {

  uint16_t i;
  uint16_t reg, val;
  bool bDone;

  #if DISP_ORIENTATION == 0 || DISP_ORIENTATION == 180
  lcd_w = 320;
  lcd_h = 240;
  #else
  lcd_w = 240;
  lcd_h = 320;
  #endif

  xMax = lcd_w - 1;
  yMax = lcd_h - 1;

  /*uC configuration*/
  RST_SET; GPIO_SetPinDirection(RST_PORT, RST_PIN, GPIO_PIN_OUTPUT);
  PMP_Init();
  CS_UNSELECT; GPIO_SetPinDirection(CS_PORT, CS_PIN, GPIO_PIN_OUTPUT);
  RS_REGISTER; GPIO_SetPinDirection(RS_PORT, RS_PIN, GPIO_PIN_OUTPUT);

  CS_SELECT;    /*select the controler, for ever (lcd is alone on the PMP)*/
  DelayMs(1);   /*tres >= 1ms*/
  RST_RELEASE;

  /*registers setting*/
  i = 0;
  bDone = false;
  while(bDone == false) {

    reg = ili9320_cfg[i++];
    val = ili9320_cfg[i++];

    if(reg == T_WAIT) {
      DelayMs(val);
    }
    else if(reg == CFGEND) {
      bDone = true;
    }
    else {
      WriteReg(reg, val);
    }
  }

  /*clear windows & position*/
  LCD_SetWnd(NULL);
  LCD_SetPos(0, 0);
}


/**
 * @function LCD_GetWidth
 * @brief return the width of the screen
 * @param none
 * @return coord_t: width of the screen
 */
length_t LCD_GetWidth(void) {
  return lcd_w;
}


/**
 * @function LCD_GetHeight
 * @brief return the height of the screen
 * @param none
 * @return coord_t: height of the screen
 */
length_t LCD_GetHeight(void) {
  return lcd_h;
}


/**
 * @function LCD_SetPos
 * @brief set the cursor position
 * @param x: cursor x
 * @param y: cursor y
 * @return none
 */
void LCD_SetPos(coord_t x, coord_t y) {

#if DISP_ORIENTATION == 0
  WriteReg(0x0020, y);
  WriteReg(0x0021, x);
#elif DISP_ORIENTATION == 180
  WriteReg(0x0020, yMax - y);
  WriteReg(0x0021, xMax - x);
#elif DISP_ORIENTATION == 90
  WriteReg(0x0020, xMax - x);
  WriteReg(0x0021, y);
#elif DISP_ORIENTATION == 270
  WriteReg(0x0020, x);
  WriteReg(0x0021, yMax - y);
#endif

  WriteToGram();
}


/**
 * @function LCD_SetWnd
 * @brief set the hardware window
 * @param *rec: pointer to the window clip
 * @return uint32_t: number of pixels contained in the window
 */
void LCD_SetWnd(const rect_st *rec) {
  rect_st lrect;
  if(rec != NULL) {
    lrect = *rec;
  }
  else {
    lrect.x = 0;
    lrect.y = 0;
    lrect.w = lcd_w;
    lrect.h = lcd_h;
  }

#if DISP_ORIENTATION == 0
  WriteReg(0x0050, lrect.y);
  WriteReg(0x0051, lrect.y + lrect.h - 1);
  WriteReg(0x0052, lrect.x);
  WriteReg(0x0053, lrect.x + lrect.w - 1);
#elif DISP_ORIENTATION == 180
  WriteReg(0x0051, yMax - lrect.y);
  WriteReg(0x0050, yMax - (lrect.y + lrect.h - 1));
  WriteReg(0x0053, xMax - lrect.x);
  WriteReg(0x0052, xMax - (lrect.x + lrect.w - 1));
#elif DISP_ORIENTATION == 90
  WriteReg(0x0052, lrect.y);
  WriteReg(0x0053, lrect.y + lrect.h - 1);
  WriteReg(0x0051, xMax - lrect.x);
  WriteReg(0x0050, xMax - (lrect.x + lrect.w - 1));
#elif DISP_ORIENTATION == 270
  WriteReg(0x0053, yMax - lrect.y);
  WriteReg(0x0052, yMax - (lrect.y + lrect.h - 1));
  WriteReg(0x0050, lrect.x);
  WriteReg(0x0051, lrect.x + lrect.w - 1);
#endif

  LCD_SetPos(lrect.x, lrect.y);
  WriteToGram();
}


/**
 * @function LCD_Put
 * @brief put a pixel on the display, and increment the cursor position
 * @param col: pixel color
 * @return none
 */
void LCD_Put(color_t col) {
  PMP_Write(col);
}
