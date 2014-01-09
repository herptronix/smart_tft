/**
 * @file r_gui.h
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

#ifndef _r_gui_h_
#define _r_gui_h_

#include "tft_defines.h"
#include "opList.h"


void R_GUI_Debug(bool bDebug);
void R_GUI_SaveLastObj(uint16_t pObjOffset);
void R_GUI_ReadSignal(void);
void R_GUI_SetAlign(gui_align_t align);
void R_GUI_SetColor(uint16_t id, color_t color);
#define R_GUI_SetFont(a) R_P2D_SetFont(a)
void R_GUI_ClearAll(void);
void R_GUI_SetGroup(group_t group);
void R_GUI_SetSignal(event_e event, signal_t sig);
void R_GUI_GroupDisable(group_t group, bool bDisable);
void R_GUI_GroupNotify(group_t group, bool bNotify);
void R_GUI_GroupRefresh(group_t group, bool bRefresh);
void R_GUI_W_ButtonSetPlacementOrder(btn_placeOrder_e order);
void R_GUI_W_ButtonAdd(const rect_st *rec, const void *txt, gui_img_t img);
void R_GUI_W_CheckBoxAdd(const rect_st *rec, const void *txt, uint16_t offset) ;
void R_GUI_W_FrameAdd(const rect_st *rec, const void *txt);
void R_GUI_W_GraphSetGridSpacing(length_t h, length_t v);
void R_GUI_W_GraphAdd(const rect_st *rec, e_grid_type grid, uint16_t tmRefresh);
void R_GUI_W_GraphAddCurveToGraph(uint16_t offset, color_t color);
void R_GUI_W_GraphAddSampleToCurve(uint16_t pObjOffset, uint8_t idCurve, uint8_t sample);
void R_GUI_W_LedAdd(const rect_st *rec, const void *txt, uint16_t offset);
void R_GUI_W_RadioAdd(const rect_st *rec, const void *txt, uint16_t offset, uint8_t id);
void R_GUI_W_RotaryButtonAdd(const rect_st *rec, uint16_t offset, gr_enum_e gr);
void R_GUI_W_RotaryValueAdd(const rect_st *rec, uint16_t offsetI32, uint16_t offsetI8, const void *strUnit);
void R_GUI_W_RotaryValueLock(uint16_t pObjOffset, bool bLock);
void R_GUI_W_RotaryValueSetMinMax(int32_t min, int32_t max);
void R_GUI_W_RotaryValueSetDotPos(uint8_t posDot);
//////void GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param);
void R_GUI_W_SliderAdd(const rect_st *rec, uint16_t offset);
void R_GUI_W_TextAdd(const rect_st *rec, const void *str);
void R_GUI_W_UsrEntryAdd(const rect_st *rec, uint16_t offsetStr, uint16_t len);
void R_GUI_W_ValueBoxAdd(const rect_st *rec, uint16_t offset, valueBoxType_e type, const void *strFormat);
void R_GUI_M_FileBrowser(file_browser_mode_e mode, uint16_t offsetPath, uint16_t len);
void R_GUI_M_KeyboardCreate(coord_t x, coord_t y, kbd_type_e type, uint16_t offsetEntry, uint16_t len, signal_t sigOk, signal_t sigEsc);
void R_GUI_M_ListAdd(const rect_st *rec, bool bHeader, bool bVscroll, bool bHscroll, event_e event, signal_t sig);
void R_GUI_M_ListAddCategoryToList(length_t w, const void *str);
void R_GUI_M_ListAddItemToList(gui_img_t img);
void R_GUI_M_ListAddFieldToLastItem(const void *str);
void R_GUI_M_ListDeleteContent(void);
void R_GUI_M_ListGetSelectedItemUid(void);
void R_GUI_M_ListGetSelectedItemField(uint8_t catId, uint16_t offset, uint16_t len);
void R_GUI_M_Popup(uint8_t btnLeft, uint8_t btnMiddle, uint8_t btnRight, gui_img_t img, const void *str);

#endif
