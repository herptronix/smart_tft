/**
 * @file gui_m_popup.c
 * @brief some popup messages
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-10-10
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

#include "gui_m_popup.h"
#include "gui_w.h"
#include "resources.h"

#define POPUP_W 230
#define POPUP_H 100
#define BTN_W 65
#define BTN_H 19
#define PITCH 5

/**
 * popup_btn_st
 */
typedef struct {
  const char *str;
  gui_img_t icon;
  signal_t sig;
} popup_btn_st;


/**
 * Local functions
 */
static signal_t GUI_M_PopupHandle(signal_t signal);
static int8_t AddButtons(const rect_st *rec, gui_m_popup_e btnLeft, gui_m_popup_e btnMiddle, gui_m_popup_e btnRight);
static int8_t AddSpriteAndText(const rect_st *rec, gui_img_t img, const void *usrStr);

/**
 * Local variables
 */
static const popup_btn_st arButton[_POPUP_BTN_CNT] = {

  /*POPUP_BTN_NONE*/
  {"", 0, 0},

  /*POPUP_BTN_OK*/
  {"Ok", G_IMG_OK, POPUP_SIG_BTN_OK},

  /*POPUP_BTN_YES*/
  {"Yes", G_IMG_OK, POPUP_SIG_BTN_YES},

  /*POPUP_BTN_NO*/
  {"No", G_IMG_NO, POPUP_SIG_BTN_NO},

  /*POPUP_BTN_CANCEL*/
  {"Cancel", G_IMG_ERROR, POPUP_SIG_BTN_CANCEL},

  /*POPUP_BTN_SAVE*/
  {"Save", G_IMG_SAVE, POPUP_SIG_BTN_SAVE},

  /*POPUP_BTN_DISCARD*/
  {"Discard", G_IMG_ERROR, POPUP_SIG_BTN_DISCARD},
};


/**
 * @function GUI_M_Popup
 * @brief open top layer & launch a popup
 * @param gui_m_popup_e btn xxx: left/middle/right buttons
 * @param gui_img_t img: image of the popup
 * @param const void *usrStr: user message
 * @return int8_t: 0 success, -1 error; in case of error, the top layer is automatically closed
 */
int8_t GUI_M_Popup(gui_m_popup_e btnLeft, gui_m_popup_e btnMiddle, gui_m_popup_e btnRight, gui_img_t img, const void *usrStr) {

  int8_t res = -1;
  rect_st rec;

  /*popup dimension*/
  rec.w = POPUP_W;
  rec.h = POPUP_H;
  rec.x = ((coord_t) P2D_GetLcdWidth() - rec.w) / 2;
  rec.y = ((coord_t) P2D_GetLcdHeight() - rec.h) / 2;

  /*open the top layer*/
  GUI_TopLayerOpen(GUI_M_PopupHandle);

  /*draw the popup background*/
  P2D_SetColors(GetColor(G_COL_BACKGROUND), GetColor(G_COL_BACKGROUND));
  P2D_FillRect(&rec);

  /*create the popup*/
  SetFont(G_FONT_DEFAULT);
  if(AddButtons(&rec, btnLeft, btnMiddle, btnRight) == 0) {

    /*add the user text and display the sprite*/
    if(AddSpriteAndText(&rec, img, usrStr) == 0) res = 0;
  }

  /*in case of error, kill top layer*/
  if(res < 0) {
    GUI_TopLayerClose();
  }

  return res;
}


/**
 * @function AddButtons
 * @brief add buttons in the popup
 * @param const rect_st *rec: popup dimension
 * @param gui_m_popup_e btnLeft: left button (see gui_m_popup_e)
 * @param gui_m_popup_e btnMiddle: left middle (see gui_m_popup_e)
 * @param gui_m_popup_e btnRight: left right (see gui_m_popup_e)
 * @return int8_t: 0 success, -1 error
 */
static int8_t AddButtons(const rect_st *rec, gui_m_popup_e btnLeft, gui_m_popup_e btnMiddle, gui_m_popup_e btnRight) {

  int8_t res = -1;
  rect_st lrec;
  g_obj_st *obj = NULL;

  /*button rect*/
  lrec.w = BTN_W;
  lrec.h = BTN_H;
  lrec.y = rec->y + rec->h - lrec.h - PITCH;
  lrec.x = rec->x + rec->w - lrec.w - PITCH;

  do {

    /*right*/
    if(btnRight > POPUP_BTN_NONE && btnRight < _POPUP_BTN_CNT) {
      obj = GUI_W_ButtonAdd(&lrec, arButton[btnRight].str, arButton[btnRight].icon);
      if(obj == NULL) break;
      else {
        GUI_SetSignal(E_PUSHED_TO_RELEASED, arButton[btnRight].sig);
        lrec.x = lrec.x - lrec.w - PITCH;
      }
    }

    /*middle*/
    if(btnMiddle > POPUP_BTN_NONE && btnMiddle < _POPUP_BTN_CNT) {
      obj = GUI_W_ButtonAdd(&lrec, arButton[btnMiddle].str, arButton[btnMiddle].icon);
      if(obj == NULL) break;
      else {
        GUI_SetSignal(E_PUSHED_TO_RELEASED, arButton[btnMiddle].sig);
        lrec.x = lrec.x - lrec.w - PITCH;
      }
    }

    /*left*/
    if(btnLeft > POPUP_BTN_NONE && btnLeft < _POPUP_BTN_CNT) {
      obj = GUI_W_ButtonAdd(&lrec, arButton[btnLeft].str, arButton[btnLeft].icon);
      if(obj == NULL) break;
      else GUI_SetSignal(E_PUSHED_TO_RELEASED, arButton[btnLeft].sig);
    }

    res = 0;

  } while(0);

  return res;
}


/**
 * @function AddSpriteAndText
 * @brief add a text area and display the popup img
 * @param const rect_st *rec: popup dimension
 * @param gui_img_t img: popup img
 * @param const void *usrStr: popup text
 * @return int8_t: 0 success, -1 error
 */
static int8_t AddSpriteAndText(const rect_st *rec, gui_img_t img, const void *usrStr) {

  int8_t res = -1;

  coord_t yImg, xImg, wImg;

  rect_st lrec;
  lrec.x = rec->x;
  lrec.y = rec->y;
  lrec.w = rec->w - 2*PITCH;
  lrec.h = rec->h - BTN_H - 2*PITCH;

  /*img*/
  xImg = lrec.x + PITCH;
  wImg = SpriteGetHeight(img);
  yImg = lrec.y + ((coord_t)lrec.h - wImg) / 2;
  Sprite(xImg, yImg, img);

  /*text area*/
  wImg += 2*PITCH;
  lrec.x += wImg;
  lrec.w -= wImg;
  GUI_SetAlign(G_ALIGN_V_CENTER);
  if(GUI_W_TextAdd(&lrec, usrStr) != NULL) res = 0;

  GUI_SetAlign(0);

  return res;
}


/**
 * @function GUI_M_PopupHandle
 * @brief popup handler (internal task type <pGuiInternalTask_t>)
 * @param signal coming from top layer widget only
 * @return signal_t: popup's button signal
 */
static signal_t GUI_M_PopupHandle(signal_t signal) {

  signal_t res = 0;

  if(signal != 0) {
    GUI_TopLayerClose();
    res = signal;
  }

  return signal;
}
