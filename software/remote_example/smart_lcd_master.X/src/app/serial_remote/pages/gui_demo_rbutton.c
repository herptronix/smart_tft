/**
 * @file gui_demo_rbutton.c
 * @brief rotary encoder / rvalue demo (serialized, master side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-01
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

#include "gui_demo_rbutton.h"

enum {
  SIG_RVAL_FREQ = 1,
  SIG_RVAL_AMPL,
  SIG_RVAL_OFFSET
};

enum {

  OFFSET_START = 0,

  /*used to store the physical address (32bits) of rvalue widgets, for R_GUI_W_RotaryValueLock()*/
  OFFSET_OBJ1 = OFFSET_START,
      _OFFSET_OBJ1, __OFFSET_OBJ1, ___OFFSET_OBJ1,
  OFFSET_OBJ2,
      _OFFSET_OBJ2, __OFFSET_OBJ2, ___OFFSET_OBJ2,
  OFFSET_OBJ3,
      _OFFSET_OBJ3, __OFFSET_OBJ3, ___OFFSET_OBJ3,
  
  OFFSET_I32_FREQ,
      _OFFSET_I32_FREQ, __OFFSET_I32_FREQ, ___OFFSET_I32_FREQ,
  OFFSET_I32_AMPL,
      _OFFSET_I32_AMPL, __OFFSET_I32_AMPL, ___OFFSET_I32_AMPL,
  OFFSET_I32_OFF,
      _OFFSET_I32_OFF, __OFFSET_I32_OFF, ___OFFSET_I32_OFF,
  
  OFFSET_I8,
  
  _MEM_SIZE
};


/**
 * local function
 */
static void Gui_DemoRotaryButtonRead(void);
static void Gui_DemoRotaryButtonHandler(void);

/**
 * local variables
 */
static int32_t frequency = 10000, amplitude = 5000, offset = 0;


/**
 * @function Gui_DemoRotaryButton
 * @brief rotary encoder / rvalue demo
 * @param none
 * @return none
 */
void Gui_DemoRotaryButton(void) {

  rect_st rec;

  Gui_DemoNewPage("Rotary button");
  
  R_MEM_Memset(OFFSET_START, _MEM_SIZE, 0);
  R_MEM_WriteI32(OFFSET_I32_FREQ, frequency);
  R_MEM_WriteI32(OFFSET_I32_AMPL, amplitude);
  R_MEM_WriteI32(OFFSET_I32_OFF, offset);

  /*some text*/
  rec = GUI_Rect(20, 20, 161, 18);
  R_GUI_W_TextAdd(&rec, "Frequency");
  rec = GUI_Rect(20, 80, 75, 30);
  R_GUI_W_TextAdd(&rec, "Amplitude");
  rec = GUI_Rect(105, 80, 75, 30);
  R_GUI_W_TextAdd(&rec, "Offset");

  R_GUI_SetFont(G_FONT_BIG);

  /*frequency value box*/
  rec = GUI_Rect(20, 40, 161, 24);
  R_GUI_W_RotaryValueAdd(&rec, OFFSET_I32_FREQ, OFFSET_I8, "Hz");
  R_GUI_SaveLastObj(OFFSET_OBJ1);
  R_GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_FREQ);
  R_GUI_W_RotaryValueSetDotPos(1);
  R_GUI_W_RotaryValueSetMinMax(0, 2000000000);

  /*amplitude value box*/
  rec = GUI_Rect(20, 100, 75, 24);
  R_GUI_W_RotaryValueAdd(&rec, OFFSET_I32_AMPL, OFFSET_I8, "V");
  R_GUI_SaveLastObj(OFFSET_OBJ2);
  R_GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_AMPL);
  R_GUI_W_RotaryValueSetDotPos(3);
  R_GUI_W_RotaryValueSetMinMax(0, 10000);

  /*offset value box*/
  rec = GUI_Rect(105, 100, 75, 24);
  R_GUI_W_RotaryValueAdd(&rec, OFFSET_I32_OFF, OFFSET_I8, "V");
  R_GUI_SaveLastObj(OFFSET_OBJ3);
  R_GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_OFFSET);
  R_GUI_W_RotaryValueSetDotPos(3);
  R_GUI_W_RotaryValueSetMinMax(-5000, 5000);

  /*select the active value box (the frequency one, at startup)*/
  R_GUI_W_RotaryValueLock(OFFSET_OBJ1, false);
  R_GUI_W_RotaryValueLock(OFFSET_OBJ2, true);
  R_GUI_W_RotaryValueLock(OFFSET_OBJ3, true);

  /*rotary encoder*/
  rec = GUI_Rect(200, 40, 90, 90);
  R_GUI_W_RotaryButtonAdd(&rec, OFFSET_I8, ROTARY_BTN_GR_30_DEG);

  R_GUI_SetFont(G_FONT_DEFAULT);
  
  /* => page creation is now completed. Jump to the page's handler*/
  R_GUI_SetTask(Gui_DemoRotaryButtonRead);
}


/**
 * @function Gui_DemoRotaryButtonRead
 * @brief Send <read signal> <read frequency> <read amplitude> and <read offset> requests to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoRotaryButtonRead(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_MEM_ReadI32(OFFSET_I32_FREQ);
    R_MEM_ReadI32(OFFSET_I32_AMPL);
    R_MEM_ReadI32(OFFSET_I32_OFF);
    R_GUI_SetTask(Gui_DemoRotaryButtonHandler);
  }
}


/**
 * @function Gui_DemoRotaryButtonHandler
 * @brief handle previous requests
 * @param none
 * @return none
 */
void Gui_DemoRotaryButtonHandler(void) {

  signal_t sig = RxGetU16();
  frequency = RxGetI32();
  amplitude = RxGetI32();
  offset = RxGetI32();

  R_GUI_SetTask(Gui_DemoRotaryButtonRead);
  
  if(RxStatus() == 0) {
  
    /**
     * random process on read values
     */
    //DDS_Write(frequency);
    //DAC_Write(CHANNEL_AMPLITUDE, amplitude);
    //DAC_Write(CHANNEL_OFFSET, offset);
    //...

    /*handle user signal, if any*/
    switch(sig) {

      /*touch on the frequency value box*/
      case SIG_RVAL_FREQ:
        R_GUI_W_RotaryValueLock(OFFSET_OBJ1, false);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ2, true);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ3, true);
        break;

      /*touch on the amplitude value box*/
      case SIG_RVAL_AMPL:
        R_GUI_W_RotaryValueLock(OFFSET_OBJ1, true);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ2, false);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ3, true);
        break;

      /*touch on the offset value box*/
      case SIG_RVAL_OFFSET:
        R_GUI_W_RotaryValueLock(OFFSET_OBJ1, true);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ2, true);
        R_GUI_W_RotaryValueLock(OFFSET_OBJ3, false);
        break;

      /*'menu' button*/
      case SIG_DEMO_MENU:
        R_GUI_SetTask(Gui_Demo);
        break;

      default:
        break;
    }
  }
}
