/**
 * @file opList.c
 * @brief serialized op code + link to the corresponding function (slave side)
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

#include "opList.h"
#include "r_p2d.h"
#include "r_gui.h"
#include "r_mem.h"

#ifdef SMART_TFT_SLAVE_MODE

const OpFunc_t opList[_S_NB_OP] = {

  NULL,                                 //OP_NOP
  &R_GUI_Debug,                         //OP_DEBUG_CFG
  &R_P2D_Clear,                         //OP_P2D_CLEAR
  &R_P2D_SetColor,                      //OP_P2D_SET_COLOR,
  &R_P2D_SetColors,                     //OP_P2D_SET_COLORS,
  &R_P2D_SetDisplayMode,                //OP_P2D_SET_DISPLAY_MODE,
  &R_P2D_P2D_SetAlpha,                  //OP_P2D_SET_ALPHA,
  &R_P2D_SetLineType,                   //OP_P2D_SET_LINE_TYPE,
  &R_P2D_SetPixel,                      //OP_P2D_SET_PIXEL,
  &R_P2D_Line,                          //OP_P2D_LINE,
  &R_P2D_Rect,                          //OP_P2D_RECT,
  &R_P2D_FillRect,                      //OP_P2D_FILL_RECT,
  &R_P2D_SetClip,                       //OP_P2D_SET_CLIP,
  &R_P2D_GetLcdWidth,                   //OP_P2D_GET_LCD_W,
  &R_P2D_GetLcdHeight,                  //OP_P2D_GET_LCD_H,
  &R_P2D_SetFont,                       //OP_P2D_SET_FONT,
  &R_P2D_GetTextHeight,                 //OP_P2D_GET_TEXT_H,
  &R_P2D_GetTextWidth,                  //OP_P2D_GET_TEXT_W,
  &R_P2D_GetGlyphWidth,                 //OP_P2D_GET_GLYPH_W,
  &R_P2D_PutGlyph,                      //OP_P2D_PUT_GLYPH,
  &R_P2D_PutText,                       //OP_P2D_PUT_TEXT,
  &R_P2D_Circle,                        //OP_P2D_CIRCLE,
  &R_P2D_FillCircle,                    //OP_P2D_FILL_CIRCLE,
  &R_P2D_Poly,                          //OP_P2D_POLY,
  &R_P2D_FillPoly,                      //OP_P2D_FILL_POLY,
  &R_P2D_SpriteGetWidth,                //OP_P2D_SPRITE_GET_W,
  &R_P2D_SpriteGetHeight,               //OP_P2D_SPRITE_GET_H,
  &R_SetLut,                            //OP_P2D_SET_LUT
  &R_Sprite,                            //OP_P2D_SPRITE,
  NULL,                                 //OP_RESERVED_0X1D,
  NULL,                                 //OP_RESERVED_0X1E,
  NULL,                                 //OP_RESERVED_0X1F,
  &R_GUI_GetLastAddedObject,            //OP_GUI_GET_LAST_OBJ
  &R_GUI_ReadSignal,                    //OP_GUI_READ_SIGNAL
  &R_GUI_SetAlign,                      //OP_GUI_SET_ALIGN
  &R_GUI_SetColor,                      //OP_GUI_SET_COLOR
  &R_GUI_ClearAll,                      //OP_GUI_CLEAR_ALL
  &R_GUI_SetGroup,                      //OP_GUI_SET_GROUP
  &R_GUI_SetSignal,                     //OP_GUI_SET_SIGNAL
  &R_GUI_GroupDisable,                  //OP_GUI_GROUP_DISABLE
  &R_GUI_GroupNotify,                   //OP_GUI_GROUP_NOTIFY
  &R_GUI_GroupRefresh,                  //OP_GUI_GROUP_REFRESH
  &R_GUI_W_ButtonSetPlacementOrder,     //OP_GUI_W_BUTTON_SET_PLACEMENT_ORDER
  &R_GUI_W_ButtonAdd,                   //OP_GUI_W_BUTTON_ADD
  &R_GUI_W_CheckBoxAdd,                 //OP_GUI_W_CHECKBOX_ADD
  &R_GUI_W_FrameAdd,                    //OP_GUI_W_FRAME_ADD
  &R_GUI_W_GraphSetGridSpacing,         //OP_GUI_W_GRAPH_SET_GRID_SPACING
  &R_GUI_W_GraphAdd,                    //OP_GUI_W_GRAPH_ADD
  &R_GUI_W_GraphAddCurveToGraph,        //OP_GUI_W_GRAPH_ADD_CURVE_TO_GRAPH
  &R_GUI_W_GraphAddSampleToCurve,       //OP_GUI_W_GRAPH_ADD_SAMPLE_TO_CURVE
  &R_GUI_W_LedAdd,                      //OP_GUI_W_LED_ADD
  &R_GUI_W_RadioAdd,                    //OP_GUI_W_RADIO_ADD
  &R_GUI_W_RotaryButtonAdd,             //OP_GUI_W_ROTARY_BUTTON_ADD
  &R_GUI_W_RotaryValueAdd,              //OP_GUI_W_ROTARY_VALUE_ADD
  &R_GUI_W_RotaryValueLock,             //OP_GUI_W_ROTARY_VALUE_LOCK
  &R_GUI_W_RotaryValueSetMinMax,        //OP_GUI_W_ROTARY_VALUE_SET_MIN_MAX
  &R_GUI_W_RotaryValueSetDotPos,        //OP_GUI_W_ROTARY_VALUE_SET_DOT_POS
  NULL,                                 //OP_GUI_W_SCROLLER_ADD
  &R_GUI_W_SliderAdd,                   //OP_GUI_W_SLIDER_ADD
  &R_GUI_W_TextAdd,                     //OP_GUI_W_TEXT_ADD
  &R_GUI_W_UsrEntryAdd,                 //OP_GUI_W_USR_ENTRY_ADD
  &R_GUI_W_ValueBoxAdd,                 //OP_GUI_W_VALUEBOX_ADD
  &R_GUI_M_FileBrowser,                 //OP_GUI_M_FILE_BROWSER
  &R_GUI_M_KeyboardCreate,              //OP_GUI_M_KEYBOARD_CREATE
  &R_GUI_M_ListAdd,                     //OP_GUI_M_LIST_ADD
  &R_GUI_M_ListAddCategoryToList,       //OP_GUI_M_LIST_ADD_CATEGORY_TO_LIST
  &R_GUI_M_ListAddItemToList,           //OP_GUI_M_LIST_ADD_ITEM_TO_LIST
  &R_GUI_M_ListAddFieldToLastItem,      //OP_GUI_M_LIST_ADD_FIELD_TO_LAST_ITEM
  &R_GUI_M_ListDeleteContent,           //OP_GUI_M_LIST_DELETE_CONTENT
  &R_GUI_M_ListGetSelectedItemUid,      //OP_GUI_M_LIST_GET_SELECTED_ITEM_UID
  &R_GUI_M_ListGetSelectedItemField,    //OP_GUI_M_LIST_GET_SELECTED_ITEM_FIELD
  &R_GUI_M_Popup,                       //OP_GUI_M_POPUP
  &R_MEM_WriteU8,                       //OP_MEM_WRITE_U8
  &R_MEM_WriteU16,                      //OP_MEM_WRITE_U16
  &R_MEM_WriteI16,                      //OP_MEM_WRITE_I16
  &R_MEM_WriteU32,                      //OP_MEM_WRITE_U32
  &R_MEM_WriteI32,                      //OP_MEM_WRITE_I32
  &R_MEM_WriteU8Arr,                    //OP_MEM_WRITE_U8_ARR
  &R_MEM_WriteStr,                      //OP_MEM_WRITE_STR
  &R_MEM_Memset,                        //OP_MEM_MEMSET
  &R_MEM_ReadU8,                        //OP_MEM_READ_U8
  &R_MEM_ReadU16,                       //OP_MEM_READ_U16
  &R_MEM_ReadI16,                       //OP_MEM_READ_I16
  &R_MEM_ReadU32,                       //OP_MEM_READ_U32
  &R_MEM_ReadI32,                       //OP_MEM_READ_I32
  &R_MEM_ReadU8Arr,                     //OP_MEM_READ_U8_ARR
  &R_MEM_ReadStr                        //OP_MEM_READ_STR
};

#endif
