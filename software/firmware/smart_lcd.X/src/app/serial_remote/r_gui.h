/**
 * @file r_gui.h
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

#ifndef _r_gui_h_
#define _r_gui_h_

#include "main.h"

int8_t R_GUI_GetLastAddedObject(void);  /*cast g_obj_st* to u32: portability issue? */
int8_t R_GUI_Debug(void);
int8_t R_GUI_ReadSignal(void);
int8_t R_GUI_SetAlign(void);
int8_t R_GUI_SetColor(void);
int8_t R_GUI_ClearAll(void);
int8_t R_GUI_SetGroup(void);
int8_t R_GUI_SetSignal(void);
int8_t R_GUI_GroupDisable(void);
int8_t R_GUI_GroupNotify(void);
int8_t R_GUI_GroupRefresh(void);
int8_t R_GUI_W_ButtonSetPlacementOrder(void);
int8_t R_GUI_W_ButtonAdd(void);
int8_t R_GUI_W_CheckBoxAdd(void);
int8_t R_GUI_W_FrameAdd(void);
int8_t R_GUI_W_GraphSetGridSpacing(void);
int8_t R_GUI_W_GraphAdd(void);
int8_t R_GUI_W_GraphAddCurveToGraph(void);
int8_t R_GUI_W_GraphAddSampleToCurve(void);
int8_t R_GUI_W_LedAdd(void);
int8_t R_GUI_W_RadioAdd(void);
int8_t R_GUI_W_RotaryButtonAdd(void);
int8_t R_GUI_W_RotaryValueAdd(void);
int8_t R_GUI_W_RotaryValueLock(void);  /*cast u32 to g_obj_st*: portability issue? */
int8_t R_GUI_W_RotaryValueSetMinMax(void);
int8_t R_GUI_W_RotaryValueSetDotPos(void);
//////g_obj_st /*@null@*/ *GUI_W_ScrollerAdd(const rect_st *rec, g_obj_st *refreshObj, scroll_param_st *param);
int8_t R_GUI_W_SliderAdd(void);
int8_t R_GUI_W_TextAdd(void);
int8_t R_GUI_W_UsrEntryAdd(void);
int8_t R_GUI_W_ValueBoxAdd(void);
int8_t R_GUI_M_FileBrowser(void);
int8_t R_GUI_M_KeyboardCreate(void);
int8_t R_GUI_M_ListAdd(void);
int8_t R_GUI_M_ListAddCategoryToList(void);
int8_t R_GUI_M_ListAddItemToList(void);
int8_t R_GUI_M_ListAddFieldToLastItem(void);
int8_t R_GUI_M_ListDeleteContent(void);
int8_t R_GUI_M_ListGetSelectedItemUid(void);
int8_t R_GUI_M_ListGetSelectedItemField(void);
int8_t R_GUI_M_Popup(void);

#endif
