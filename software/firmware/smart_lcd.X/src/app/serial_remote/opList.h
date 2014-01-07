/**
 * @file opList.h
 * @brief serialized op code
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

#ifndef _opList_h_
#define _opList_h_

#include "main.h"


enum {
  OP_NOP,
  OP_DEBUG_CFG,
  OP_P2D_CLEAR,
  OP_P2D_SET_COLOR,
  OP_P2D_SET_COLORS,
  OP_P2D_SET_DISPLAY_MODE,
  OP_P2D_SET_ALPHA,
  OP_P2D_SET_LINE_TYPE,
  OP_P2D_SET_PIXEL,
  OP_P2D_LINE,
  OP_P2D_RECT,
  OP_P2D_FILL_RECT,
  OP_P2D_SET_CLIP,
  OP_P2D_GET_LCD_W,
  OP_P2D_GET_LCD_H,
  OP_P2D_SET_FONT,
  OP_P2D_GET_TEXT_H,
  OP_P2D_GET_TEXT_W,
  OP_P2D_GET_GLYPH_W,
  OP_P2D_PUT_GLYPH,
  OP_P2D_PUT_TEXT,
  OP_P2D_CIRCLE,
  OP_P2D_FILL_CIRCLE,
  OP_P2D_POLY,
  OP_P2D_FILL_POLY,
  OP_P2D_SPRITE_GET_W,
  OP_P2D_SPRITE_GET_H,
  OP_P2D_SET_LUT,
  OP_P2D_SPRITE,
  OP_RESERVED_0X1D,
  OP_RESERVED_0X1E,
  OP_RESERVED_0X1F,
  OP_GUI_GET_LAST_OBJ,
  OP_GUI_READ_SIGNAL,
  OP_GUI_SET_ALIGN,
  OP_GUI_SET_COLOR,
  OP_GUI_CLEAR_ALL,
  OP_GUI_SET_GROUP,
  OP_GUI_SET_SIGNAL,
  OP_GUI_GROUP_DISABLE,
  OP_GUI_GROUP_NOTIFY,
  OP_GUI_GROUP_REFRESH,
  OP_GUI_W_BUTTON_SET_PLACEMENT_ORDER,
  OP_GUI_W_BUTTON_ADD,
  OP_GUI_W_CHECKBOX_ADD,
  OP_GUI_W_FRAME_ADD,
  OP_GUI_W_GRAPH_SET_GRID_SPACING,
  OP_GUI_W_GRAPH_ADD,
  OP_GUI_W_GRAPH_ADD_CURVE_TO_GRAPH,
  OP_GUI_W_GRAPH_ADD_SAMPLE_TO_CURVE,
  OP_GUI_W_LED_ADD,
  OP_GUI_W_RADIO_ADD,
  OP_GUI_W_ROTARY_BUTTON_ADD,
  OP_GUI_W_ROTARY_VALUE_ADD,
  OP_GUI_W_ROTARY_VALUE_LOCK,
  OP_GUI_W_ROTARY_VALUE_SET_MIN_MAX,
  OP_GUI_W_ROTARY_VALUE_SET_DOT_POS,
  OP_GUI_W_SCROLLER_ADD,
  OP_GUI_W_SLIDER_ADD,
  OP_GUI_W_TEXT_ADD,
  OP_GUI_W_USR_ENTRY_ADD,
  OP_GUI_W_VALUEBOX_ADD,
  OP_GUI_M_FILE_BROWSER,
  OP_GUI_M_KEYBOARD_CREATE,
  OP_GUI_M_LIST_ADD,
  OP_GUI_M_LIST_ADD_CATEGORY_TO_LIST,
  OP_GUI_M_LIST_ADD_ITEM_TO_LIST,
  OP_GUI_M_LIST_ADD_FIELD_TO_LAST_ITEM,
  OP_GUI_M_LIST_DELETE_CONTENT,
  OP_GUI_M_LIST_GET_SELECTED_ITEM_UID,
  OP_GUI_M_LIST_GET_SELECTED_ITEM_FIELD,
  OP_GUI_M_POPUP,
  OP_MEM_WRITE_U8,
  OP_MEM_WRITE_U16,
  OP_MEM_WRITE_I16,
  OP_MEM_WRITE_U32,
  OP_MEM_WRITE_I32,
  OP_MEM_WRITE_U8_ARR,
  OP_MEM_WRITE_STR,
  OP_MEM_MEMSET,
  OP_MEM_READ_U8,
  OP_MEM_READ_U16,
  OP_MEM_READ_I16,
  OP_MEM_READ_U32,
  OP_MEM_READ_I32,
  OP_MEM_READ_U8_ARR,
  OP_MEM_READ_STR,
  _S_NB_OP
};


#ifdef SMART_TFT_SLAVE_MODE
  typedef int8_t (*OpFunc_t) (void);
  extern const OpFunc_t opList[_S_NB_OP];
#endif

#endif
