/**
 * @file r_gui.c
 * @brief GUI serialized commands (master side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-17
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

#include "serial_tx.h"
#include "r_gui.h"

/* GUI_DBG_DispMemUsage */
void R_GUI_Debug(bool bDebug) {
  TxMsgPutByte(OP_DEBUG_CFG);
  TxMsgPutByte((uint8_t) bDebug);
}

/* R_GUI_SaveLastObj */
void R_GUI_SaveLastObj(uint16_t offset) {
  TxMsgPutByte(OP_GUI_GET_LAST_OBJ);
  TxMsgPut(offset);
}

/* GUI_ReadSignal
 * ARG: - */
void R_GUI_ReadSignal(void) {
  TxMsgPutByte(OP_GUI_READ_SIGNAL);
}

/* GUI_SetAlign
 * ARG: - */
void R_GUI_SetAlign(gui_align_t align) {
  TxMsgPutByte(OP_GUI_SET_ALIGN);
  TxMsgPut(align);
}

/* SetColor
 * ARG: id (u16) color(u16) */
void R_GUI_SetColor(uint16_t id, color_t color) {
  TxMsgPutByte(OP_GUI_SET_COLOR);
  TxMsgPut(id);
  TxMsgPut(color);
}

/* GUI_ClearAll
 * ARG: -  */
void R_GUI_ClearAll(void) {
  TxMsgPutByte(OP_GUI_CLEAR_ALL);
}

/* GUI_SetGroup
 * ARG: group(u8) */
void R_GUI_SetGroup(group_t group) {
  TxMsgPutByte(OP_GUI_SET_GROUP);
  TxMsgPut(group);
}

/* GUI_SetSignal
 * ARG: event(u8) sig(u16) */
void R_GUI_SetSignal(event_e event, signal_t sig) {
  TxMsgPutByte(OP_GUI_SET_SIGNAL);
  TxMsgPutByte( event);
  TxMsgPut(sig);
}

/* GUI_GroupDisable
 * ARG: group(u8) bDisable(u8) */
void R_GUI_GroupDisable(group_t group, bool bDisable) {
  TxMsgPutByte(OP_GUI_GROUP_DISABLE);
  TxMsgPut(group);
  TxMsgPutByte(bDisable);
}

/* GUI_GroupNotify
 * ARG: group(u8) bNotify(u8) */
void R_GUI_GroupNotify(group_t group, bool bNotify) {
  TxMsgPutByte(OP_GUI_GROUP_NOTIFY);
  TxMsgPut(group);
  TxMsgPutByte(bNotify);
}

/* GUI_GroupRefresh
 * ARG: group(u8) bRefresh(u8) */
void R_GUI_GroupRefresh(group_t group, bool bRefresh) {
  TxMsgPutByte(OP_GUI_GROUP_REFRESH);
  TxMsgPut(group);
  TxMsgPutByte(bRefresh);
}

/* GUI_W_ButtonSetPlacementOrder
 * ARG: order(u8) */
void R_GUI_W_ButtonSetPlacementOrder(btn_placeOrder_e order) {
  TxMsgPutByte(OP_GUI_W_BUTTON_SET_PLACEMENT_ORDER);
  TxMsgPutByte(order);
}

/* GUI_W_ButtonAdd
 * ARG: rec(rect_st), txt(*txt), img(u16) */
void R_GUI_W_ButtonAdd(const rect_st *rec, const void *txt, gui_img_t img) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_BUTTON_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(txt);
    TxMsgPut(img);
  }
}

/* GUI_W_CheckBoxAdd
 * ARG: rec(rect_st), txt(*txt), offset(u16) */
void R_GUI_W_CheckBoxAdd(const rect_st *rec, const void *txt, uint16_t offset) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_CHECKBOX_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(txt);
    TxMsgPut(offset);
  }
}

/* GUI_W_FrameAdd
 * ARG: rec(rect_st), txt(*txt) */
void R_GUI_W_FrameAdd(const rect_st *rec, const void *txt) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_FRAME_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(txt);
  }
}

/* GUI_W_GraphSetGridSpacing
 * ARG: h(u16), v(u16)*/
void R_GUI_W_GraphSetGridSpacing(length_t h, length_t v) {
  TxMsgPutByte(OP_GUI_W_GRAPH_SET_GRID_SPACING);
  TxMsgPut(h);
  TxMsgPut(v);
}

/* GUI_W_GraphAdd
 * ARG: rec(rect_st), grid(u8), tmRefresh(u16) */
void R_GUI_W_GraphAdd(const rect_st *rec, e_grid_type grid, uint16_t tmRefresh) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_GRAPH_ADD);
    TxMsgPutRect(rec);
    TxMsgPutByte(grid);
    TxMsgPut(tmRefresh);
  }
}

/* GUI_W_GraphAddCurveToGraph
 * ARG: offset(u16), color(u16) */
void R_GUI_W_GraphAddCurveToGraph(uint16_t offset, color_t color) {
  TxMsgPutByte(OP_GUI_W_GRAPH_ADD_CURVE_TO_GRAPH);
  TxMsgPut(offset);
  TxMsgPut(color);
}

/* GUI_W_GraphAddSampleToCurve
 * ARG: idCurve(u8), sample(u8) */
void R_GUI_W_GraphAddSampleToCurve(uint16_t pObjOffset, uint8_t idCurve, uint8_t sample) {
  TxMsgPutByte(OP_GUI_W_GRAPH_ADD_SAMPLE_TO_CURVE);
  TxMsgPut(pObjOffset);
  TxMsgPut(idCurve);
  TxMsgPut(sample);
}

/* GUI_W_LedAdd
 * ARG: rec(rect_st), txt(*txt), offset(u16) */
void R_GUI_W_LedAdd(const rect_st *rec, const void *txt, uint16_t offset) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_LED_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(txt);
    TxMsgPut(offset);
  }
}

/* GUI_W_RadioAdd
 * ARG: rec(rect_st), txt(*txt), offset(u16), id(u8) */
void R_GUI_W_RadioAdd(const rect_st *rec, const void *txt, uint16_t offset, uint8_t id) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_RADIO_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(txt);
    TxMsgPut(offset);
    TxMsgPut(id);
  }
}

/* GUI_W_RotaryButtonAdd
 * ARG: rec(rect_st), offset(u16), gr(u8) */
void R_GUI_W_RotaryButtonAdd(const rect_st *rec, uint16_t offset, gr_enum_e gr) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_ROTARY_BUTTON_ADD);
    TxMsgPutRect(rec);
    TxMsgPut(offset);
    TxMsgPutByte( gr);
  }
}

/* GUI_W_RotaryValueAdd
 * ARG: rec(rect_st), offsetI32(u16), offsetI8(u16), txt(*txt) */
void R_GUI_W_RotaryValueAdd(const rect_st *rec, uint16_t offsetI32, uint16_t offsetI8, const void *strUnit) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_ROTARY_VALUE_ADD);
    TxMsgPutRect(rec);
    TxMsgPut(offsetI32);
    TxMsgPut(offsetI8);
    TxMsgPutStr(strUnit);
  }
}

/* GUI_W_RotaryValueLock
 * ARG: bLock(u8) */
void R_GUI_W_RotaryValueLock(uint16_t pObjOffset, bool bLock) {
  TxMsgPutByte(OP_GUI_W_ROTARY_VALUE_LOCK);
  TxMsgPut(pObjOffset);
  TxMsgPutByte(bLock);
}

/* GUI_W_RotaryValueSetMinMax
 * ARG: min(i32), max(i32) */
void R_GUI_W_RotaryValueSetMinMax(int32_t min, int32_t max) {
  TxMsgPutByte(OP_GUI_W_ROTARY_VALUE_SET_MIN_MAX);
  TxMsgPut(min);
  TxMsgPut(max);
}

/* GUI_W_RotaryValueSetDotPos
 * ARG: posDot(u8) */
void R_GUI_W_RotaryValueSetDotPos(uint8_t posDot) {
  TxMsgPutByte(OP_GUI_W_ROTARY_VALUE_SET_DOT_POS);
  TxMsgPut(posDot);
}

//////void GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param);

/* GUI_W_SliderAdd
 * ARG: rec(rect_st), offset(u16) */
void R_GUI_W_SliderAdd(const rect_st *rec, uint16_t offset) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_SLIDER_ADD);
    TxMsgPutRect(rec);
    TxMsgPut(offset);
  }
}

/* GUI_W_TextAdd
 * ARG: rec(rect_st), str(*txt) */
void R_GUI_W_TextAdd(const rect_st *rec, const void *str) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_TEXT_ADD);
    TxMsgPutRect(rec);
    TxMsgPutStr(str);
  }
}

/* GUI_W_UsrEntryAdd
 * ARG: rec(rect_st), offset(u16), strLen(u16) */
void R_GUI_W_UsrEntryAdd(const rect_st *rec, uint16_t offsetStr, uint16_t len) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_USR_ENTRY_ADD);
    TxMsgPutRect(rec);
    TxMsgPut(offsetStr);
    TxMsgPut(len);
  }
}

/* GUI_W_ValueBoxAdd
 * ARG: rec(rect_st), offset(u16), type(u8), strFormat(*txt) */
void R_GUI_W_ValueBoxAdd(const rect_st *rec, uint16_t offset, valueBoxType_e type, const void *strFormat) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_W_VALUEBOX_ADD);
    TxMsgPutRect(rec);
    TxMsgPut(offset);
    TxMsgPutByte(type);
    TxMsgPutStr(strFormat);
  }
}

/* GUI_M_FileBrowser
 * ARG: mode(u8), offset(u16), strMaxLen(u6) */
void R_GUI_M_FileBrowser(file_browser_mode_e mode, uint16_t offsetPath, uint16_t len) {
  TxMsgPutByte(OP_GUI_M_FILE_BROWSER);
  TxMsgPutByte( mode);
  TxMsgPut(offsetPath);
  TxMsgPut(len);
}

/* GUI_M_KeyboardCreate
 * ARG: x(i16), y(i16), type(u8), offset(u16), strMaxLen(u16) */
void R_GUI_M_KeyboardCreate(coord_t x, coord_t y, kbd_type_e type, uint16_t offsetEntry, uint16_t len, signal_t sigOk, signal_t sigEsc) {
  TxMsgPutByte(OP_GUI_M_KEYBOARD_CREATE);
  TxMsgPut(x);
  TxMsgPut(y);
  TxMsgPutByte( type);
  TxMsgPut(offsetEntry);
  TxMsgPut(len);
  TxMsgPut(sigOk);
  TxMsgPut(sigEsc);
}

/* GUI_M_ListAdd
 * ARG: rec(rect_st), bHeader(u8), bHscroll(u8), bVscroll(u8), event(u8), sig(u16) */
void R_GUI_M_ListAdd(const rect_st *rec, bool bHeader, bool bVscroll, bool bHscroll, event_e event, signal_t sig) {
  if(rec != NULL) {
    TxMsgPutByte(OP_GUI_M_LIST_ADD);
    TxMsgPutRect(rec);
    TxMsgPutByte(bHeader);
    TxMsgPutByte(bVscroll);
    TxMsgPutByte(bHscroll);
    TxMsgPutByte(event);
    TxMsgPut(sig);
  }
}

/* GUI_M_ListAddCategoryToList
 * ARG: w(u16), str(*txt) */
void R_GUI_M_ListAddCategoryToList(length_t w, const void *str) {
  TxMsgPutByte(OP_GUI_M_LIST_ADD_CATEGORY_TO_LIST);
  TxMsgPut(w);
  TxMsgPutStr(str);
}

/* GUI_M_ListAddItemToList
 * ARG: img(u8) */
void R_GUI_M_ListAddItemToList(gui_img_t img) {
  TxMsgPutByte(OP_GUI_M_LIST_ADD_ITEM_TO_LIST);
  TxMsgPut(img);
}

/* GUI_M_ListAddFieldToLastItem
 * ARG: str(*txt) */
void R_GUI_M_ListAddFieldToLastItem(const void *str) {
  TxMsgPutByte(OP_GUI_M_LIST_ADD_FIELD_TO_LAST_ITEM);
  TxMsgPutStr(str);
}

/* GUI_M_ListDeleteContent
 * ARG: - */
void R_GUI_M_ListDeleteContent(void) {
  TxMsgPutByte(OP_GUI_M_LIST_DELETE_CONTENT);
}

/* GUI_M_ListGetSelectedItemUid
 * ARG: offset(u16) */
void R_GUI_M_ListGetSelectedItemUid(void) {
  TxMsgPutByte(OP_GUI_M_LIST_GET_SELECTED_ITEM_UID);
}

/* GUI_M_ListGetSelectedItemField
 * ARG: catId(u8), offset(u16), strMaxLen(u16) */
void R_GUI_M_ListGetSelectedItemField(uint8_t catId, uint16_t offset, uint16_t len) {
  TxMsgPutByte(OP_GUI_M_LIST_GET_SELECTED_ITEM_FIELD);
  TxMsgPut(catId);
  TxMsgPut(offset);
  TxMsgPut(len);
}

/* GUI_M_Popup
 * ARG: btnLeft(u8), btnMiddle(u8), btnRight(u8), img(u8), str(*txt)*/
void R_GUI_M_Popup(uint8_t btnLeft, uint8_t btnMiddle, uint8_t btnRight, gui_img_t img, const void *str) {
  TxMsgPutByte(OP_GUI_M_POPUP);
  TxMsgPut(btnLeft);
  TxMsgPut(btnMiddle);
  TxMsgPut(btnRight);
  TxMsgPut(img);
  TxMsgPutStr(str);
}
