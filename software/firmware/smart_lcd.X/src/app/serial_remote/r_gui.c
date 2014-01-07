/**
 * @file r_gui.c
 * @brief serialized gui decoder (slave side)
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

#include "r_gui.h"
#include "gui.h"
#include "gui_w.h"
#include "gui_m.h"
#include "serial_common.h"
#include "serial_remote.h"
#include "ssm.h"

#ifdef SMART_TFT_SLAVE_MODE

/* GUI_GetLastAddedObject */
int8_t R_GUI_GetLastAddedObject(void) {
  int8_t res = -1; uint16_t offset; const g_obj_st *pObj;
  offset = RxGetU16();    /*(u16) offset to g_obj_st* */
  if(RxStatus() == 0) {
    pObj = GUI_GetLastAddedObject();
    if(SSM_WriteU32(offset, (uint32_t) pObj) == 0) res = 0;
    else Error("GUI_GetLastAddedObject failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_DBG_DispMemUsage */
int8_t R_GUI_Debug(void) {
  int8_t res = -1; uint8_t state;
  state = RxGetU8();        /*(u8) state*/
  if(RxStatus() == 0) {
    GUI_DBG_DispMemUsage(state);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_ReadLastSignal */
int8_t R_GUI_ReadSignal(void) {
  signal_t sig = GUI_ReadLastSignal();
  TxMsgPut(sig);
  return 0;
}

/* GUI_SetAlign */
int8_t R_GUI_SetAlign(void) {
  int8_t res = -1; uint8_t align;
  align = RxGetU8();        /*(u8) align*/
  if(RxStatus() == 0) {
    GUI_SetAlign(align);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* SetColor */
int8_t R_GUI_SetColor(void) {
  int8_t res = -1; uint16_t id, color;
  id = RxGetU16();          /*(u16) id*/
  color = RxGetU16();       /*(u16) color*/
  if(RxStatus() == 0) {
    SetColor(id, color);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_ClearAll */
int8_t R_GUI_ClearAll(void) {
  GUI_ClearAll();
  return 0;
}

/* GUI_SetGroup */
int8_t R_GUI_SetGroup(void) {
  int8_t res = -1; uint8_t group;
  group = RxGetU8();        /*(u8) group*/
  if(RxStatus() == 0) {
    GUI_SetGroup(group);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_SetSignal */
int8_t R_GUI_SetSignal(void) {
  int8_t res = -1; uint8_t event; uint16_t signal;
  event = RxGetU8();        /*(u8) event*/
  signal = RxGetU16();      /*(u16) signal*/
  if(RxStatus() == 0) {
    GUI_SetSignal(event, signal);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_GroupDisable */
int8_t R_GUI_GroupDisable(void) {
  int8_t res = -1; uint8_t group, val;
  group = RxGetU8();        /*(u8) group*/
  val = RxGetU8();          /*(u8) bDisable*/
  if(RxStatus() == 0) {
    GUI_GroupDisable(group, val);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_GroupNotify */
int8_t R_GUI_GroupNotify(void) {
  int8_t res = -1; uint8_t group, val;
  group = RxGetU8();        /*(u8) group*/
  val = RxGetU8();          /*(u8) bNotify*/
  if(RxStatus() == 0) {
    GUI_GroupNotify(group, val);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_GroupRefresh */
int8_t R_GUI_GroupRefresh(void) {
  int8_t res = -1; uint8_t group, val;
  group = RxGetU8();        /*(u8) group*/
  val = RxGetU8();          /*(u8) bRefresh*/
  if(RxStatus() == 0) {
    GUI_GroupRefresh(group, val);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_ButtonSetPlacementOrder */
int8_t R_GUI_W_ButtonSetPlacementOrder(void) {
  int8_t res = -1; uint8_t val;
  val = RxGetU8();          /*(u8) order*/
  if(RxStatus() == 0) {
    GUI_W_ButtonSetPlacementOrder(val);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_ButtonAdd */
int8_t R_GUI_W_ButtonAdd(void) {
  int8_t res = -1; rect_st rec; uint8_t img; const uint8_t *txt;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  img = RxGetU8();        /*(u8) img*/
  if(RxStatus() == 0) {
    if(GUI_W_ButtonAdd(&rec, txt, img) != NULL) res = 0;
    else Error("GUI_W_ButtonAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_CheckBoxAdd */
int8_t R_GUI_W_CheckBoxAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; const uint8_t *txt; uint8_t *pu8;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  offset = RxGetU16();    /*(u16) offset to u8*/
  pu8 = (uint8_t *) SSM_GetAddress(offset, sizeof(uint8_t));
  if(RxStatus() == 0) {
    if(GUI_W_CheckBoxAdd(&rec, txt, pu8) != NULL) res = 0;
    else Error("GUI_W_CheckBoxAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_FrameAdd */
int8_t R_GUI_W_FrameAdd(void) {
  int8_t res = -1; const uint8_t *txt; rect_st rec;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_W_FrameAdd(&rec, txt) != NULL) res = 0;
    else  Error("GUI_W_FrameAdd");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_GraphSetGridSpacing */
int8_t R_GUI_W_GraphSetGridSpacing(void) {
  int8_t res = -1; length_t h, v;
  h = RxGetU16();           /*(u16) horizontal*/
  v = RxGetU16();           /*(u16) vertical*/
  if(RxStatus() == 0) {
    GUI_W_GraphSetGridSpacing(h, v);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_GraphAdd */
int8_t R_GUI_W_GraphAdd(void) {
  int8_t res = -1; rect_st rec; uint8_t grid; uint16_t timer;
  RxGetRec(&rec);         /*(rect_st)*/
  grid = RxGetU8();       /*(u8) grid type*/
  timer = RxGetU16();     /*(u16) timer refresh*/
  if(RxStatus() == 0) {
    if(GUI_W_GraphAdd(&rec, grid, timer) != NULL) res = 0;
    else Error("GUI_W_GraphAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_GraphAddCurveToGraph */
int8_t R_GUI_W_GraphAddCurveToGraph(void) {
  int8_t res = -1; uint16_t offset, color; uint8_t *pu8;
  offset = RxGetU16();      /*(u16) offset to pu8*/
  color = RxGetU16();       /*(u16) color*/
  pu8 = (uint8_t *) SSM_GetAddress(offset, sizeof(uint8_t));
  if(RxStatus() == 0) {
    if(GUI_W_GraphAddCurveToGraph(NULL, pu8, color) >= 0) res = 0;
    else Error("GUI_W_GraphAddCurveToGraph failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_GraphAddSampleToCurve */
int8_t R_GUI_W_GraphAddSampleToCurve(void) {
  int8_t res = -1; uint8_t id, sample; uint16_t offset; uint32_t pObj;
  offset = RxGetU16();      /*(u16) offset to pointer to graph*/
  id = RxGetU8();           /*(u8) id curve*/
  sample = RxGetU8();       /*(u8) sample*/
  if(RxStatus() == 0) {
    SSM_ReadU32(offset, &pObj);
    GUI_W_GraphAddSampleToCurve((g_obj_st *)pObj, id, sample);
    res = 0;
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_LedAdd */
int8_t R_GUI_W_LedAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; const uint8_t *txt; uint8_t *pu8;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  offset = RxGetU16();    /*(u16) offset to u8*/
  pu8 = (uint8_t *) SSM_GetAddress(offset, sizeof(uint8_t));
  if(RxStatus() == 0) {
    if(GUI_W_LedAdd(&rec, txt, pu8) != NULL) res = 0;
    else Error("GUI_W_LedAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RadioAdd */
int8_t R_GUI_W_RadioAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; const uint8_t *txt; uint8_t id, *pu8;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  offset = RxGetU16();    /*(u16) offset to u8*/
  pu8 = (uint8_t *) SSM_GetAddress(offset, sizeof(uint8_t));
  id = RxGetU8();         /*(u8) id*/
  if(RxStatus() == 0) {
    if(GUI_W_RadioAdd(&rec, txt, pu8, id) != NULL) res = 0;
    else Error("GUI_W_RadioAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RotaryButtonAdd */
int8_t R_GUI_W_RotaryButtonAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; uint8_t gr; int8_t *pi8;
  RxGetRec(&rec);         /*(rect_st)*/
  offset = RxGetU16();    /*(u16) offset to i8*/
  pi8 = SSM_GetAddress(offset, sizeof(int8_t));
  gr = RxGetU8();         /*(u8) granularity*/
  if(RxStatus() == 0) {
    if(GUI_W_RotaryButtonAdd(&rec, pi8, gr) != NULL) res = 0;
    else Error("GUI_W_RotaryButtonAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RotaryValueAdd */
int8_t R_GUI_W_RotaryValueAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; const uint8_t *txt; int32_t *pi32; int8_t *pi8;
  RxGetRec(&rec);         /*(rect_st)*/
  offset = RxGetU16();    /*(u16) offset to i32*/
  pi32 = SSM_GetAddress(offset, sizeof(int32_t));
  offset = RxGetU16();    /*(u16) offset to i8*/
  pi8 = SSM_GetAddress(offset, sizeof(int8_t));
  RxGetTxt(&txt);         /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_W_RotaryValueAdd(&rec, pi32, pi8, txt) != NULL) res = 0;
    else Error("GUI_W_RotaryValueAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RotaryValueLock */
int8_t R_GUI_W_RotaryValueLock(void) {
  int8_t res = -1; uint16_t offset; uint8_t bLock; uint32_t pObj;
  offset = RxGetU16();    /*(u16) offset to pointer to rval*/
  bLock = RxGetU8();      /*(u8) bLock*/
  if(RxStatus() == 0) {
    SSM_ReadU32(offset, &pObj);
    if(GUI_W_RotaryValueLock((g_obj_st *)pObj, bLock) == 0) res = 0;
    else Error("GUI_W_RotaryValueLock failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RotaryValueSetMinMax */
int8_t R_GUI_W_RotaryValueSetMinMax(void) {
  int8_t res = -1; int32_t min, max;
  min = RxGetI32();         /*(i32) min*/
  max = RxGetI32();         /*(i32) max*/
  if(RxStatus() == 0) {
    if(GUI_W_RotaryValueSetMinMax(NULL, min, max) == 0) res = 0;
    else Error("GUI_W_RotaryValueSetMinMax failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_RotaryValueSetDotPos */
int8_t R_GUI_W_RotaryValueSetDotPos(void) {
  int8_t res = -1; uint8_t pos;
  pos = RxGetU8();          /*(u8) posDot*/
  if(RxStatus() == 0) {
    if(GUI_W_RotaryValueSetDotPos(NULL, pos) == 0) res = 0;
    else Error("GUI_W_RotaryValueSetDotPos failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

//////g_obj_st /*@null@*/ *GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param);

/* GUI_W_SliderAdd */
int8_t R_GUI_W_SliderAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; uint8_t *pu8;
  RxGetRec(&rec);         /*(rect_st)*/
  offset = RxGetU16();    /*(u16) offset to pu8*/
  pu8 = SSM_GetAddress(offset, sizeof(uint8_t));
  if(RxStatus() == 0) {
    if(GUI_W_SliderAdd(&rec, pu8) != NULL) res = 0;
    else Error("GUI_W_SliderAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_TextAdd */
int8_t R_GUI_W_TextAdd(void) {
  int8_t res = -1; const uint8_t *pTxt; rect_st rec;
  RxGetRec(&rec);         /*(rect_st)*/
  RxGetTxt(&pTxt);        /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_W_TextAdd(&rec, pTxt) != NULL) res = 0;
    else Error("GUI_W_TextAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_UsrEntryAdd */
int8_t R_GUI_W_UsrEntryAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset, size; uint8_t *pu8;
  RxGetRec(&rec);         /*(rect_st)*/
  offset = RxGetU16();    /*(u16) offset to pu8*/
  pu8 = SSM_GetAddress(offset, sizeof(uint8_t));
  size = RxGetU16();      /*(u16) max str size*/
  if(RxStatus() == 0) {
    if(GUI_W_UsrEntryAdd(&rec, pu8, size, false) != NULL) res = 0;
    else Error("GUI_W_UsrEntryAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_W_ValueBoxAdd */
int8_t R_GUI_W_ValueBoxAdd(void) {
  int8_t res = -1; rect_st rec; uint16_t offset; void *pv; uint8_t type; const uint8_t *txt;
  RxGetRec(&rec);         /*(rect_st)*/
  offset = RxGetU16();    /*(u16) offset to pv*/
  pv = SSM_GetAddress(offset, sizeof(uint8_t));
  type = RxGetU8();       /*(u8) type*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_W_ValueBoxAdd(&rec, pv, type, (const char *) txt) != NULL) res = 0;
    else Error("GUI_W_ValueBoxAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_FileBrowser */
int8_t R_GUI_M_FileBrowser(void) {
  int8_t res = -1; uint16_t offset, size; uint8_t *pu8, mode;
  mode = RxGetU8();         /*(u8) mode*/
  offset = RxGetU16();      /*(u16) offset to pu8*/
  pu8 = SSM_GetAddress(offset, sizeof(uint8_t));
  size = RxGetU16();        /*(u16) max str size*/
  if(RxStatus() == 0) {
    if(GUI_M_FileBrowser(mode, (char *) pu8, size) == 0) res = 0;
    else Error("GUI_M_FileBrowser failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_KeyboardCreate */
int8_t R_GUI_M_KeyboardCreate(void) {
  int8_t res = -1; uint16_t offset, size, sOk, sEsc; uint8_t *pu8, type; int16_t x, y;
  x = RxGetI16();           /*(i16) x*/
  y = RxGetI16();           /*(i16) y*/
  type = RxGetU8();         /*(u8) type*/
  offset = RxGetU16();      /*(u16) offset to pu8*/
  pu8 = SSM_GetAddress(offset, sizeof(uint8_t));
  size = RxGetU16();        /*(u16) max str size*/
  sOk = RxGetU16();         /*(u16) sOk*/
  sEsc = RxGetU16();        /*(u16) sEsc*/
  if(RxStatus() == 0) {
    if(GUI_M_KeyboardCreate(x, y, type, pu8, size, sOk, sEsc) == 0) res = 0;
    else Error("GUI_M_KeyboardCreate failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_ListAdd */
int8_t R_GUI_M_ListAdd(void) {
  int8_t res = -1; rect_st rec; uint8_t bHeader, bVscroll, bHscroll, event; uint16_t signal;
  RxGetRec(&rec);           /*(rect_st)*/
  bHeader = RxGetU8();      /*(u8) bHeader*/
  bVscroll = RxGetU8();     /*(u8) bVscroll*/
  bHscroll = RxGetU8();     /*(u8) bHscroll*/
  event = RxGetU8();        /*(u8) event*/
  signal = RxGetU16();      /*(u16) signal*/
  if(RxStatus() == 0) {
    if(GUI_M_ListAdd(&rec, bHeader, bVscroll, bHscroll, event, signal) != NULL) res = 0;
    else Error("GUI_M_ListAdd failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_ListAddCategoryToList */
int8_t R_GUI_M_ListAddCategoryToList(void) {
  int8_t res = -1; uint16_t w; const uint8_t *txt;
  w = RxGetU16();         /*(u16) w*/
  RxGetTxt(&txt);         /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_M_ListAddCategoryToList(w, txt) == 0) res = 0;
    else Error("GUI_M_ListAddCategoryToList failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_ListAddItemToList */
int8_t R_GUI_M_ListAddItemToList(void) {
  int8_t res = -1; uint8_t sprite;
  sprite = RxGetU8();       /*(u8) sprite*/
  if(RxStatus() == 0) {
    if(GUI_M_ListAddItemToList(sprite, NULL) == 0) res = 0;
    else Error("GUI_M_ListAddItemToList failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_ListAddFieldToLastItem */
int8_t R_GUI_M_ListAddFieldToLastItem(void) {
  int8_t res = -1; const uint8_t *txt;
  RxGetTxt(&txt);         /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_M_ListAddFieldToLastItem(txt) == 0) res = 0;
    else Error("GUI_M_ListAddFieldToLastItem failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_ListDeleteContent */
int8_t R_GUI_M_ListDeleteContent(void) {
  (void) GUI_M_ListDeleteContent();
  return 0;
}

/* GUI_M_ListGetSelectedItemUid */
int8_t R_GUI_M_ListGetSelectedItemUid(void) {
  uint16_t uid;
  GUI_M_ListGetSelectedItemUid(&uid);
  TxMsgPut(uid);
  return 0;
}

/* GUI_M_ListGetSelectedItemField */
int8_t R_GUI_M_ListGetSelectedItemField(void) {
  int8_t res = -1; void *pv; uint8_t catId; uint16_t offset, size;
  catId = RxGetU8();        /*(u8) catId*/
  offset = RxGetU16();      /*(u16) offset to pv*/
  pv = SSM_GetAddress(offset, sizeof(uint8_t));
  size = RxGetU16();        /*(u16) max len pv*/
  if(RxStatus() == 0) {
    if(GUI_M_ListGetSelectedItemField(catId, pv, size) == 0) res = 0;
    else Error("GUI_M_ListGetSelectedItemField failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

/* GUI_M_Popup */
int8_t R_GUI_M_Popup(void) {
  int8_t res = -1; uint8_t btnLeft, btnMiddle, btnRight, img; const uint8_t *txt;
  btnLeft = RxGetU8();      /*(u8) btnLeft*/
  btnMiddle = RxGetU8();    /*(u8) btnMiddle*/
  btnRight = RxGetU8();     /*(u8) btnRight*/
  img = RxGetU8();          /*(u8) img*/
  RxGetTxt(&txt);           /*(sz_txt)*/
  if(RxStatus() == 0) {
    if(GUI_M_Popup(btnLeft, btnMiddle, btnRight, img, txt) == 0) res = 0;
    else Error("GUI_M_Popup failure");
  }
  else Error(EXTRACT_ERROR_MSG);
  return res;
}

#endif
