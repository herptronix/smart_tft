/**
 * @file gui_m_keyboard.c
 * @brief keyboard macro
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-09-15  : initial version
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

#include "gui_m_keyboard.h"
#include "gui_w_key.h"
#include "gui_w_usr_entry.h"


/**
 * Local variables
 */
static kbd_type_e type;                             /*current kbd type (US / FR)*/
static const key_entry_st *pKeyList;                /*keys list (content & coords)*/
static kbd_map_e mapId;                             /*current kbd map (STD/ALT/CAPS)*/
static bool bPersistentMap;                         /*current map persistency (i.e. true for CAPS LOCK, false otherwise)*/
static uint8_t cpyPstBuffer[COPY_PASTE_BUFF_SIZE];  /*local copy / paste buffer*/
static g_obj_st /*@null@*/ *pUsrEntryObj;           /*pointer to the user entry object*/
static signal_t sOk, sEsc;                          /*sOk: signal when <ENTER>, sEsc: signal when <ESC>*/


/**
 * Local functions
 */
static signal_t GUI_M_KeyboardHandle(signal_t signal);
static int8_t ComputeCoord(coord_t x, coord_t y, rect_st /*@out@*/ *recWnd, rect_st /*@out@*/ *recEntry, rect_st /*@out@*/ *recKbd);
static void SetMap(kbd_map_e m, bool bPers);
static uint8_t GetGlyph(signal_t sig);


/**
 * @function GUI_M_KeyboardInit
 * @brief initialize the keyboard; shall be called before using other keyboard's functions
 * @param none
 * @return none
 */
void GUI_M_KeyboardInit(void) {
  mapId = KBD_MAP_STD;
  bPersistentMap = false;
  pUsrEntryObj = NULL;
  sOk = 0;
  sEsc = 0;
  GUI_M_KeyboardFlush();
}


/**
 * @function GUI_M_KeyboardFlush
 * @brief clear the internal copy/paste buffer
 * @param none
 * @return none
 */
void GUI_M_KeyboardFlush(void) {
  cpyPstBuffer[0] = 0;
}


/**
 * @function GUI_M_KeyboardCreate
 * @brief open top layer & launch the keyboard
 * @param coord_t x, y: desired coords for window; will be checked/modified
 * @param kbd_type_e _type: keyboard type (KEYBOARD_TYPE_FR_FR, KEYBOARD_TYPE_EN_US...)
 * @param void *kbdBuffer: user entry buffer; used as input/output; will be cast to uint8_t*
 * @param uint16_t bufferSize: size (in bytes) of kbdBuffer
 * @param signal_t _sOk: signal when <ENTER> key
 * @param signal_t _sEsc: signal when <ESC> key
 * @return int8_t: 0 success, -1 error; in case of error, the top layer is automatically closed
 */
int8_t GUI_M_KeyboardCreate(coord_t x, coord_t y, kbd_type_e _type, void *kbdBuffer, uint16_t bufferSize, signal_t _sOk, signal_t _sEsc) {

  const key_entry_st *pEntry;
  uint8_t *buff;
  rect_st rec, recWnd, recEntry, recKbd;
  bool bError = false;
  int8_t res = -1;

  /*open the top layer*/
  GUI_TopLayerOpen(GUI_M_KeyboardHandle);

  /*locals init*/
  pKeyList = NULL;
  buff = (uint8_t *) kbdBuffer;
  SetMap(KBD_MAP_STD, true);          /*always start in STD map*/
  buff[bufferSize - 1] = 0;           /*always  ensure that the user buffer is \0 terminated*/
  sEsc = _sEsc;
  sOk = _sOk;

  /*check type, then retrieve keys array address*/
  if(_type < KEYBOARD_TYPE_COUNT) {
    type = _type;
    pKeyList = arKeyboard[type];
  }

  /*set the font now (needed for calculation above)*/
  SetFont(arKeyboardStyle[type]->fontKbd);

  /*get window, user entry & keyboard coordinates; checks also if the selected keyboard fits into the lcd*/
  if(pKeyList != NULL && ComputeCoord(x, y, &recWnd, &recEntry, &recKbd) == 0) {

    /*clear window content*/
    P2D_SetColor(GetColor(G_COL_KBD_BACKGROUND));
    P2D_SetClip(&recWnd);
    P2D_FillRect(&recWnd);

    /*add user entry*/
    pUsrEntryObj = GUI_W_UsrEntryAdd(&recEntry, buff, bufferSize, true);
    if(pUsrEntryObj != NULL) {

      /*key configuration*/
      GUI_SetGroup(1);
      GUI_KeySetConf(arKeyboardStyle[type]->fontKbd, arKeyboardStyle[type]->fontSymb, &mapId); /*key config: font key, font symbol & current map pointer*/

      /*instanciate each key*/
      pEntry = pKeyList;
      while(pEntry != NULL && pEntry->x >= 0 && bError == false) {

        rec.x = pEntry->x + recKbd.x;
        rec.y = pEntry->y + recKbd.y;
        rec.w = pEntry->w;
        rec.h = pEntry->h;

        if(GUI_AddKey(&rec, pEntry->glyph) != NULL) {

          /*special key (ENTER/ESC...) trig signal when the key is released*/
          if(pEntry->glyph[0] < (uint8_t) ' ') {
            GUI_SetSignal(E_PUSHED_TO_RELEASED, pEntry->glyph[0]);
          }
          /*printable glyph? trig signal as soon as the key is pressed*/
          else {
            GUI_SetSignal(E_RELEASED_TO_PUSHED, pEntry->glyph[0]);
          }
        }
        else {
          bError = true; /*not enougth memory :/ */
        }

        pEntry++; /*next key*/
      }

      GUI_SetGroup(0);
      if(bError == false) res = 0;
    }
  }

  /*in case of error, kill top layer*/
  if(res < 0) {
    GUI_TopLayerClose();
  }

  return res;
}


/**
 * @function GUI_M_KeyboardHandle
 * @brief keyboard handler (internal task type <pGuiInternalTask_t>)
 * @param signal coming from top layer widget only
 * @return signal_t: sOk/sEsc or 0
 */
static signal_t GUI_M_KeyboardHandle(signal_t signal) {

  uint8_t glyph;
  uint8_t strGlyph[2];
  signal_t quitSig;

  /*quitSig is set to 0; will take another value if <ENTER> or <ESC> key*/
  quitSig = 0;

  /*something pressed / released?*/
  if(signal != 0) {

    /*retrieve the real glyph according to signal AND current map (CAPS / ALT / STD)*/
    glyph = GetGlyph(signal);

    switch(glyph) {

      /*key <CAPS> ? CAPS map, non persistent*/
      case K_CAPS:
        SetMap(KBD_MAP_CAPS, false);
        break;

      /*key <CAPS LOCK> ? CAPS map, persistent*/
      case K_CAPSL:
        SetMap(KBD_MAP_CAPS, true);
        break;

      /*key <ALTGR> ? ALTGR map, non persistent*/
      case K_ALTGR:
        SetMap(KBD_MAP_ALTGR, false);
        break;

      /*key <DELETE> ? delete current selection / glyph*/
      case K_DELETE:
        GUI_W_UsrEntryDelete(pUsrEntryObj);
        break;

      /*key <K_CC> ? <CTRL> + <C> (Copy)*/
      case K_CC:
        GUI_W_UsrEntryGetSelection(pUsrEntryObj, cpyPstBuffer, COPY_PASTE_BUFF_SIZE);
        break;

      /*key <K_CX> ? <CTRL> + <X> (Cut); equivalent to <CTRL> + <C>, and DELETE if cpyPstBuffer is not empty*/
      case K_CX:
        GUI_W_UsrEntryGetSelection(pUsrEntryObj, cpyPstBuffer, COPY_PASTE_BUFF_SIZE);
        if(cpyPstBuffer[0] != 0) GUI_W_UsrEntryDelete(pUsrEntryObj);
        break;

      /*key <K_CV> ? <CTRL> + <V> (Paste)*/
      case K_CV:
        GUI_W_UsrEntryInsert(pUsrEntryObj, cpyPstBuffer);
        break;

      /*key <TAB> ? select all entry content*/
      case K_TAB:
        GUI_W_UsrEntrySelectAll(pUsrEntryObj);
        break;

      /*<ENTER>*/
      case K_ENTER:
        quitSig = sOk;
        break;

      /*<ESC>*/
      case K_ESC:
        quitSig = sEsc;
        break;

      /*... should be a regular printable glyph*/
      default:
        if(glyph >= (uint8_t) ' ') {  /*always ensure that glyph is printable*/
          strGlyph[0] = glyph;
          strGlyph[1] = (uint8_t) '\0';
          GUI_W_UsrEntryInsert(pUsrEntryObj, strGlyph);

          /*reset mapping if not persistent (e.g. CAPS + 'a' = 'A', then return to a std keyboard*/
          if(bPersistentMap == false) SetMap(KBD_MAP_STD, true);
        }
        break;
    }
  }

  /*if <ENTER> or <ESC>, return the corresponding signal and close the top layer*/
  if(quitSig != 0) {
    GUI_TopLayerClose();
  }
  return quitSig;
}


/**
 * @function SetMap
 * @brief set the current map of the keyboard
 * @param kbd_map_e m: KBD_MAP_STD / KBD_MAP_CAPS / KBD_MAP_ALTGR
 * @param bool bPers: define map persistency (e.g. true if CAPS_LOCK, false if CAPS)
 * @return none
 */
static void SetMap(kbd_map_e m, bool bPers) {

  /*desired map != current map? set new map & refresh all keys*/
  if(m != mapId) {
    mapId = m;
    bPersistentMap = bPers;
    GUI_GroupRefresh(1, true);
  }
  /*desired map == current map? set standard map & refresh all keys*/
  else {
    mapId = KBD_MAP_STD;
    bPersistentMap = true;
    GUI_GroupRefresh(1, true);
  }
}


/**
 * @function ComputeCoord
 * @brief computes keyboard coords and widgets coords
 * @param coord_t x, coord_t y: desired x & y of the top left window
 * @param rect_st *recWnd: window rect
 * @param rect_st *recEntry: user entry rect
 * @param rect_st *recKbd: (only x & y) position of the first key (top left)
 * @return int8_t: 0 success, -1 the keyboard cannot fit into screen
 */
static int8_t ComputeCoord(coord_t x, coord_t y, rect_st *recWnd, rect_st *recEntry, rect_st *recKbd) {

  int8_t res = -1;
  const length_t pitch = 2;

  /*check x & y*/
  if(x < 0) x = 0;
  if(y < 0) y = 0;

  /*keyboard dimension*/
  recKbd->w = arKeyboardStyle[type]->w;
  recKbd->h = arKeyboardStyle[type]->h;

  if(recKbd->w <= P2D_GetLcdWidth() && recKbd->h <= P2D_GetLcdHeight()) {

    /*user entry bar dimension*/
    recEntry->w = arKeyboardStyle[type]->w;
    recEntry->h = P2D_GetTextHeight() + 2 + 2;  /*+2: upper & lower line of the entry bar, +2: spacing between font and these lines*/

    /*window dimension*/
    recWnd->w = pitch + recKbd->w + pitch;  /*xStart -> 2px grey | keyboard | 2 px grey...*/
    recWnd->h = pitch + recEntry->h + pitch + recKbd->h + pitch;

    /*check if the whole window fit in screen according to x & y*/
    if(x + recWnd->w > LCD_GetWidth()) x = LCD_GetWidth() - recWnd->w;
    if(y + recWnd->h > LCD_GetHeight()) y = LCD_GetHeight() - recWnd->h;

    /*finally, deduce coords*/
    recWnd->x = x;
    recWnd->y = y;
    recEntry->x = recWnd->x + pitch;
    recEntry->y = recWnd->y + pitch;
    recKbd->x = recWnd->x + pitch;
    recKbd->y = recEntry->y + recEntry->h + pitch;

    res = 0;
  }

  return res;
}


/**
 * @function GetGlyph
 * @brief return the glyph corresponding to signal & current map
 * @param signal_t sig: signal coming from keyboard's keys
 * @return uint8_t: corresponding glyph
 */
static uint8_t GetGlyph(signal_t sig) {

  uint8_t glyph = 0;
  const key_entry_st *pEntry = pKeyList;

  /*seek the key corresponding to the signal*/
  while(pEntry != NULL && pEntry->x >= 0 && glyph == 0) {

    /*found. then extract the glyph corresponding to the current map*/
    if(pEntry->glyph[0] == sig && mapId < KBD_MAP_COUNT) {
      glyph = pEntry->glyph[mapId];
    }
    pEntry++;
  }
  return glyph;
}
