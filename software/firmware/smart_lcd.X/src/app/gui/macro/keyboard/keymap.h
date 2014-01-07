/**
 * @file keymap.h
 * @brief key mapping for AZERTY, QWERTY & NUM keyboards
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

#ifndef _keymap_h_
#define _keymap_h_

#include "gui.h"

/**
 * keyboards enumeration
 */
typedef enum {
  KEYBOARD_TYPE_EN_US,
  KEYBOARD_TYPE_FR_FR,
  KEYBOARD_TYPE_NUM,
  KEYBOARD_TYPE_COUNT
} kbd_type_e;

/**
 * alternate mapping enumeration
 */
typedef enum {
  KBD_MAP_STD,    /*standart*/
  KBD_MAP_CAPS,   /*when CAPS / CAPS_LOCK is ON*/
  KBD_MAP_ALTGR,  /*when ALTGR is ON*/
  KBD_MAP_COUNT
} kbd_map_e;

/**
 * special keys enumeration
 * some keys cannot be represented by a glyph, or don't belong to ascii
 * they are defined with an value < 32 (i.e. < to ' ')
 */
enum {
  K_DELETE = 0x01,  /*delete / backspace key*/
  K_ALTGR,          /*AltGr key*/
  K_ENTER,          /*Enter / OK key*/
  K_CAPSL,          /*Caps Lock key*/
  K_ESC,            /*Esc / cancel key*/
  K_CAPS,           /*Caps key*/
  K_CX,             /*Cut*/
  K_CC,             /*Copy*/
  K_CV,             /*Paste*/
  K_TAB,            /*select all*/
  K_SPE_COUNT
};

/**
 * @struct key_entry_st
 * basic key description (position, size & signal when pressed)
 */
typedef struct {
  coord_t x, y;
  length_t w, h;
  uint8_t glyph[KBD_MAP_COUNT];
} key_entry_st;

typedef struct {
  length_t w, h;
  gui_font_t fontKbd, fontSymb;
} keyboard_style_st;

/**
 * array of pointer to the keyboards mapping & styles
 */
#define KEY_MAX_COUNT 65 /*KEY_MAX_COUNT: GCC does not support flexible array init... array len shall be defined ><" */
extern const key_entry_st *arKeyboard[KEYBOARD_TYPE_COUNT];
extern const keyboard_style_st *arKeyboardStyle[KEYBOARD_TYPE_COUNT];

#endif
