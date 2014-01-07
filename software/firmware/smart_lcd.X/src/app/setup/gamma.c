/**
 * @file gamma.c
 * @brief quick & dirty functions for gamma adjustement
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-03
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

#include "setup.h"
#include "p2d.h"
#include "gui.h"
#include "gui_w.h"
#include "gui_m.h"
#include "ff.h"
#include "resources.h"

#define SIG_EXIT 1

/**
 * Local variables
 */
static const char *strFile = "gamma.cfg";  /*located at the root of the SD card*/
static bool bChanged;

/**
 * gamma_entry_st
 */
typedef struct {
  const uint8_t addr, max;
  const char *nameMsb, *nameLsb;
  uint8_t oldValMsb, sliderValMsb;
  uint8_t oldValLsb, sliderValLsb;
} gamma_entry_st;

enum {
  GAMMA_VRP0_1,
  GAMMA_RP0_1,
  GAMMA_KP0_1,
  GAMMA_KP2_3,
  GAMMA_KP4_5,
  GAMMA_VNP0_1,
  GAMMA_RN0_1,
  GAMMA_KN0_1,
  GAMMA_KN2_3,
  GAMMA_KN4_5,
  _GAMMA_CNT
};

static gamma_entry_st gamma[_GAMMA_CNT] = {
  {0x36, 31, "VRP0", "VRP1", 0, 127, 0, 127},
  {0x35,  7,  "RP0",  "RP1", 0, 127, 0, 127},
  {0x30,  7,  "KP1",  "KP0", 0, 127, 0, 127},
  {0x31,  7,  "KP3",  "KP2", 0, 127, 0, 127},
  {0x32,  7,  "KP5",  "KP4", 0, 127, 0, 127},
  {0x3D, 31, "VNP0", "VNP1", 0, 127, 0, 127},
  {0x3C,  7,  "RN0",  "RN1", 0, 127, 0, 127},
  {0x37,  7,  "KN1",  "KN0", 0, 127, 0, 127},
  {0x38,  7,  "KN3",  "KN2", 0, 127, 0, 127},
  {0x39,  7,  "KN5",  "KN4", 0, 127, 0, 127}
};


/**
 * Local functions
 */
static void GammaHandler(signal_t sig);
static void UpdateRegisters(bool bForceRefresh);
static void GammaSaveConfig(void);


/**
 * @function GammaLoadConfig
 * @brief Configure the ILI932x gamma with the <gamma.cfg> file content
 * @param none
 * @return none TODO: return & robustness enhancement
 */
void GammaLoadConfig(void) {

  FIL pFile;
  UINT byteRead;
  int8_t res = -1;
  uint8_t ii;

  /*get the param stored on the SD card*/
  if(f_open(&pFile, strFile, FA_OPEN_EXISTING | FA_READ) == FR_OK) {

    res = 0;
    for(ii = 0; ii < _GAMMA_CNT && res == 0; ii++) {
      if(f_read(&pFile, &gamma[ii].sliderValMsb, sizeof(gamma[ii].sliderValMsb), &byteRead) != FR_OK) res = -1;
      if(f_read(&pFile, &gamma[ii].sliderValLsb, sizeof(gamma[ii].sliderValLsb), &byteRead) != FR_OK) res = -1;
    }

    f_close(&pFile);
  }

  /*read error? set all param to mid point*/
  if(res < 0) {
    for(ii = 0; ii < _GAMMA_CNT; ii++) {
      gamma[ii].sliderValMsb = 127;
      gamma[ii].sliderValLsb = 127;
    }
  }

  /*update physical registers (force)*/
  UpdateRegisters(true);
}


/**
 * @function GammaTask
 * @brief gamma adjustement: init. task
 * @param none
 * @return none
 */
void GammaTask(void) {

  rect_st rec;
  uint8_t ii;
  bChanged = false;

  GUI_ClearAll();

  /*title*/
  rec = GUI_Rect(5, 0, 310, 215);
  SetFont(G_FONT_DEFAULT);
  GUI_W_FrameAdd(&rec, "Gamma correction");

  /*exit button*/
  rec = GUI_Rect(255, 218, 60, 20);
  GUI_W_ButtonAdd(&rec, "Exit", G_IMG_HOME);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_EXIT);

  /*RGB & black/grey/white rects*/
  rec = GUI_Rect(180, 15, 20, 20);
  P2D_SetColor(COLOR_RED);
  P2D_SetClip(NULL);
  P2D_FillRect(&rec);
  rec.x += rec.w;
  P2D_SetColor(COLOR_GREEN);
  P2D_FillRect(&rec);
  rec.x += rec.w;
  P2D_SetColor(COLOR_BLUE);
  P2D_FillRect(&rec);
  rec.x += rec.w;
  P2D_SetColor(COLOR_BLACK);
  P2D_FillRect(&rec);
  rec.x += rec.w;
  P2D_SetColor(P2D_Color(127,127,127));
  P2D_FillRect(&rec);
  rec.x += rec.w;
  P2D_SetColor(COLOR_WHITE);
  P2D_FillRect(&rec);

  /*gamma entries*/
  rec.y = 40;
  rec.h = 15;
  for(ii = 0; ii < _GAMMA_CNT; ii++) {

    /*left (msb) title*/
    rec.x = 10;
    rec.w = 40;
    GUI_W_TextAdd(&rec, gamma[ii].nameMsb);

    /*left (msb) slider*/
    rec.x += rec.w + 5;
    rec.w = 100;
    GUI_W_SliderAdd(&rec, &gamma[ii].sliderValMsb);

    /*right (lsb) title*/
    rec.x += rec.w + 10;
    rec.w = 40;
    GUI_W_TextAdd(&rec, gamma[ii].nameLsb);

    /*right (lsb) slider*/
    rec.x += rec.w + 5;
    rec.w = 100;
    GUI_W_SliderAdd(&rec, &gamma[ii].sliderValLsb);

    rec.y += rec.h + 2;
  }

  GUI_SetUserTask(GammaHandler);
  pCurrentTask = NULL;  /*gamma is handled only in a GUI task*/
}


/**
 * @function GammaHandler
 * @brief gamma page handler
 * @param signal_t sig: input GUI signal
 * @return none
 */
static void GammaHandler(signal_t sig) {

  if(sig != 0) {

    /*exit sig, coming from the button; if modified param, launch a popup; else, return to setup page*/
    if(sig == SIG_EXIT) {
      if(bChanged) {
        GUI_M_Popup(POPUP_BTN_NONE, POPUP_BTN_SAVE, POPUP_BTN_DISCARD, G_IMG_BIG_ASK, "Save changes to SD card?");
      }
      else {
        pCurrentTask = SetupMenuDisplayTask;
      }
    }

    /*save sig, coming from the popup; save & return to setup page*/
    else if(sig == POPUP_SIG_BTN_SAVE) {
      GammaSaveConfig();
      pCurrentTask = SetupMenuDisplayTask;
    }

    /*discard sig, coming from the popup; restore previous gamma & return to setup page*/
    else if(sig == POPUP_SIG_BTN_DISCARD) {
      GammaLoadConfig();
      pCurrentTask = SetupMenuDisplayTask;
    }
    else {
      /*none; cannot happen*/
    }
  }

  /*update physical register (only if values have been changed) */
  UpdateRegisters(false);
}


/**
 * @function UpdateRegisters
 * @brief Update the ILI932x gamma registers
 * @param bool bForceRefresh: if true, force write physical reg, even if values did not change
 * @return none
 */
static void UpdateRegisters(bool bForceRefresh) {

  uint8_t ii;
  uint16_t tmpMsb, tmpLsb, div;

  for(ii = 0; ii < _GAMMA_CNT; ii++) {

    /*convert slider value (8bits) to register value (3 or 5 bits)*/
    div = 256 / (gamma[ii].max + 1);
    if(div == 0) div = 1; /*should not happen*/
    tmpMsb = gamma[ii].sliderValMsb / div;
    tmpLsb = gamma[ii].sliderValLsb / div;

    /*different than old value? refresh*/
    if(tmpMsb != gamma[ii].oldValMsb || tmpLsb != gamma[ii].oldValLsb || bForceRefresh) {
      bChanged = true;
      gamma[ii].oldValMsb = tmpMsb;
      gamma[ii].oldValLsb = tmpLsb;
      LCD_WriteReg(gamma[ii].addr, (tmpMsb << 8) | tmpLsb);
    }
  }
}


/**
 * @function GammaSaveConfig
 * @brief Save the gamma configuration in the <gamma.cfg> file
 * @param none
 * @return none TODO: return & robustness enhancement
 */
static void GammaSaveConfig(void) {
  FIL pFile;
  UINT byteWritten;
  uint8_t ii;

  /*write on SD card*/
  if(f_open(&pFile, strFile, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK) {
    for(ii = 0; ii < _GAMMA_CNT; ii++) {
      (void) f_write(&pFile, &gamma[ii].sliderValMsb, sizeof(gamma[ii].sliderValMsb), &byteWritten);
      (void) f_write(&pFile, &gamma[ii].sliderValLsb, sizeof(gamma[ii].sliderValLsb), &byteWritten);
    }

    f_close(&pFile);
  }
}
