/**
 * @file gui_demo_sd.c
 * @brief SD card operation
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

#include "gui_demo_sd.h"
#include "resources.h"
#include "ff.h"

#ifdef INCLUDE_GUI_DEMO


#define SIG_IMG_NEXT  1
#define SIG_IMG_PREV  2

/**
 * local variable
 */
static int16_t idImg;
static bool bRefresh;

/**
 * local function
 */
void Gui_DemoSDHandler(signal_t sig);


/**
 * @function Gui_DemoSD
 * @brief sd card demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoSD(signal_t sig) {

  rect_st rec;

  idImg = 0;
  bRefresh = true;

  Gui_DemoNewPage("SD card");

  /*next*/
  rec = GUI_Rect(161, 218, 60, 20);
  GUI_W_ButtonSetPlacementOrder(G_BTN_PLACE_IMG_R_TEXT_L);
  GUI_W_ButtonAdd(&rec, "next", G_IMG_RIGHT_ARROW);
  GUI_W_ButtonSetPlacementOrder(0);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_IMG_NEXT);

  /*previous*/
  rec = GUI_Rect(100, 218, 60, 20);
  GUI_W_ButtonAdd(&rec, "prev.", G_IMG_LEFT_ARROW);
  GUI_SetSignal(E_PUSHED_TO_RELEASED, SIG_IMG_PREV);

  /* => page creation is now completed. Jump to the page's handler*/
  GUI_SetUserTask(Gui_DemoSDHandler);

  SetFont(G_FONT_DEFAULT);
}


/**
 * @function Gui_DemoSDHandler
 * @brief SD card demo handler
 * @param signal_t sig: signal coming from widgets
 * @return none
 */
void Gui_DemoSDHandler(signal_t sig) {

  const int16_t wImg = 240;
  const int16_t hImg = 180;

  char fileName[20];
  color_t arCol[wImg * sizeof(color_t)];
  FIL file;
  rect_st rec;
  int16_t x, y;
  UINT dummy;

  switch(sig) {

    /*next picture*/
    case SIG_IMG_NEXT:
      idImg++;
      bRefresh = true;
      break;

    /*previous picture*/
    case SIG_IMG_PREV:
      idImg--;
      bRefresh = true;
      break;

    /*'menu' button*/
    case SIG_DEMO_MENU:
      GUI_SetUserTask(Gui_Demo);
      break;

      default:
      break;
  }

  if(bRefresh) {

    /*build file name*/
    if(idImg < 0) idImg = 5;
    else if(idImg > 5) idImg = 0;
    sprintf(fileName, "PICTURES/%02d.pic", idImg);

    if(f_open(&file, fileName, FA_READ) == FR_OK) {

      /*create the picture rect*/
      rec = GUI_Rect((LCD_GetWidth() - wImg) / 2,
                     (LCD_GetHeight() - hImg) / 2 - 5,
                     wImg,
                     hImg);

      /*configure P2D*/
      P2D_SetClip(&rec);
      LCD_SetWnd(&rec);
      LCD_SetPos(rec.x, rec.y);

      /*read each line of the picture*/
      for(y = 0; y < hImg; y++) {
        f_read(&file, &arCol, wImg * sizeof(color_t), &dummy);

        /*put it on the screen*/
        for(x = 0; x < wImg; x++) {
          LCD_Put(arCol[x]);
        }
      }
    }

    /*release the file when finished*/
    f_close(&file);

    /*done*/
    bRefresh = false;
  }
}

#endif
