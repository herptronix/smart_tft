/**
 * @file gui_demo_rbutton.c
 * @brief rotary encoder / rvalue demo
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

#ifdef INCLUDE_GUI_DEMO

#define SIG_RVAL_FREQ 1
#define SIG_RVAL_AMPL 2
#define SIG_RVAL_OFFSET 3


/**
 * local function
 */
void Gui_DemoRotaryButtonHandler(signal_t sig);

/**
 * local variables
 */
static int32_t frequency = 10000, amplitude = 5000, offset = 0;
static int8_t var8 = 0;
static g_obj_st *pFreqVal, *pAmplitudeVal, *pOffsetVal;


/**
 * @function Gui_DemoRotaryButton
 * @brief rotary encoder / rvalue demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoRotaryButton(signal_t sig) {

  rect_st rec;

  Gui_DemoNewPage("Rotary button");

  /*some text*/
  rec = GUI_Rect(20, 20, 161, 18);
  GUI_W_TextAdd(&rec, "Frequency");
  rec = GUI_Rect(20, 80, 75, 30);
  GUI_W_TextAdd(&rec, "Amplitude");
  rec = GUI_Rect(105, 80, 75, 30);
  GUI_W_TextAdd(&rec, "Offset");

  SetFont(G_FONT_BIG);

  /*frequency value box*/
  rec = GUI_Rect(20, 40, 161, 24);
  pFreqVal = GUI_W_RotaryValueAdd(&rec, &frequency, &var8, "Hz");
  GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_FREQ);
  GUI_W_RotaryValueSetDotPos(NULL, 1);
  GUI_W_RotaryValueSetMinMax(NULL, 0, 2000000000);

  /*amplitude value box*/
  rec = GUI_Rect(20, 100, 75, 24);
  pAmplitudeVal = GUI_W_RotaryValueAdd(&rec, &amplitude, &var8, "V");
  GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_AMPL);
  GUI_W_RotaryValueSetDotPos(NULL, 3);
  GUI_W_RotaryValueSetMinMax(NULL, 0, 10000);

  /*offset value box*/
  rec = GUI_Rect(105, 100, 75, 24);
  pOffsetVal = GUI_W_RotaryValueAdd(&rec, &offset, &var8, "V");
  GUI_SetSignal(E_RELEASED_TO_PUSHED, SIG_RVAL_OFFSET);
  GUI_W_RotaryValueSetDotPos(NULL, 3);
  GUI_W_RotaryValueSetMinMax(NULL, -5000, 5000);

  /*select the active dial (the frequency one, at startup)*/
  GUI_W_RotaryValueLock(pFreqVal, false);
  GUI_W_RotaryValueLock(pAmplitudeVal, true);
  GUI_W_RotaryValueLock(pOffsetVal, true);

  /*rotary encoder*/
  rec = GUI_Rect(200, 40, 90, 90);
  GUI_W_RotaryButtonAdd(&rec, &var8, ROTARY_BTN_GR_30_DEG);

  /* => page creation is now completed. Jump to the page's handler*/
  GUI_SetUserTask(Gui_DemoRotaryButtonHandler);

  SetFont(G_FONT_DEFAULT);
}


/**
 * @function Gui_DemoRotaryButtonHandler
 * @brief rotary encoder / rvalue demo handler
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
void Gui_DemoRotaryButtonHandler(signal_t sig) {

  switch(sig) {

    /*touch on the frequency value box*/
    case SIG_RVAL_FREQ:
      GUI_W_RotaryValueLock(pFreqVal, false);
      GUI_W_RotaryValueLock(pAmplitudeVal, true);
      GUI_W_RotaryValueLock(pOffsetVal, true);
      break;

    /*touch on the amplitude value box*/
    case SIG_RVAL_AMPL:
      GUI_W_RotaryValueLock(pFreqVal, true);
      GUI_W_RotaryValueLock(pAmplitudeVal, false);
      GUI_W_RotaryValueLock(pOffsetVal, true);
      break;

    /*touch on the offset value box*/
    case SIG_RVAL_OFFSET:
      GUI_W_RotaryValueLock(pFreqVal, true);
      GUI_W_RotaryValueLock(pAmplitudeVal, true);
      GUI_W_RotaryValueLock(pOffsetVal, false);
      break;

    /*'menu' button*/
    case SIG_DEMO_MENU:
      GUI_SetUserTask(Gui_Demo);
      break;

      default:
      break;
  }
}

#endif
