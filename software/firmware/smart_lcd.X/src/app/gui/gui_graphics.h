/**
 * @file gui_graphics.h
 * @brief management of graphic resources
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-10-14
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

#ifndef _gui_graphics_h_
#define _gui_graphics_h_

#include "gui.h"

/**
 * colors palette for widgets
 */
enum {
  G_COL_BACKGROUND,
  G_COL_E_BACKGROUND,
  G_COL_L_BACKGROUND,
  G_COL_KBD_BACKGROUND,
  G_COL_KBD_KEY,
  G_COL_KBD_KEY_ENTER,
  G_COL_KBD_KEY_ESC,
  G_COL_KBD_KEY_FN,
  G_COL_TEXT,
  G_COL_TEXT_REVERSE,
  G_COL_D_TEXT,
  G_COL_UPPER_REC,
  G_COL_LOWER_REC,
  G_COL_SPECIAL,
  G_COL_LED_ON,
  G_COL_LED_OFF,
  G_NB_COLORS
};

/**
 * font palette
 */
enum {
  G_FONT_DEFAULT,
  G_FONT_BOLD,
  G_FONT_ITALIC,
  G_FONT_DIGIT,
  G_FONT_BIG,
  G_FONT_VERY_BIG,
  G_FONT_SMALL,
  G_FONT_SYMBOL,
  G_NB_FONT
};

/**
 * CLUT types, for sprite sheets
 */
enum {
  G_LUT_NORMAL,
  G_LUT_DISABLED,
  G_NB_LUT
};

/**
 * alignment
 */
#define G_ALIGN_DEFAULT   0
#define G_ALIGN_H_LEFT    0x80
#define G_ALIGN_H_CENTER  0x40
#define G_ALIGN_H_RIGHT   0x20
#define G_ALIGN_V_TOP     0x08
#define G_ALIGN_V_CENTER  0x04
#define G_ALIGN_V_BOTTOM  0x02

/**
 * @function GraphInit
 * @brief initialize graphic resources; may allocate memory (e.g. for sprite CLUT)
 * @param none
 * @return none
 */
void GraphInit(void);

/**
 * @function GUI_GetAlign
 * @brief return the current alignment
 * @param none
 * @return gui_align_t: current alignment
 */
gui_align_t GUI_GetAlign(void);

/**
 * @function GUI_SetAlign
 * @brief define the alignment
 * @param gui_align_t a: new alignment; see gui_align_t type
 * @return none
 */
void GUI_SetAlign(gui_align_t a);

/**
 * @function SetFont
 * @brief define the font which shall be used by the GUI
 * @param gui_font_t font: < G_NB_FONT
 * @return none
 */
void SetFont(gui_font_t font);

/**
 * @function GetCurrentFont
 * @brief retrieve the id of the current font used by the GUI
 * @param none
 * @return gui_font_t: current font
 */
gui_font_t GetCurrentFont(void);

/**
 * @function GetColor
 * @brief retrieve a color of the GUI palette
 * @param uint16_t id: id of the color; shall be < G_NB_COLORS
 * @return color_t : color (here, in RGB565 format)
 */
color_t GetColor(uint16_t col);

/**
 * @function SetColor
 * @brief define a color of the GUI palette
 * @param uint16_t id: id of the color; shall be < G_NB_COLORS
 * @param color_t col: color (here, in RGB565 format)
 * @return none
 */
void SetColor(uint16_t id, color_t col);

/**
 * @function SetLut
 * @brief select the GUI lut to use for the sprites
 * @param uint8_t lut: lut to use; shall be < G_NB_LUT
 * @return none
 */
void SetLut(uint8_t lut);

/**
 * @function SpriteGetWidth
 * @brief get the width of a sprite
 * @param gui_img_t idSprite: sprite uid
 * @return length_t: width of the sprite, 0 if the sprite does not exist
 */
length_t SpriteGetWidth(gui_img_t idSprite);

/**
 * @function SpriteGetHeight
 * @brief get the height of a sprite
 * @param gui_img_t idSprite: sprite uid
 * @return length_t: height of the sprite, 0 if the sprite does not exist
 */
length_t SpriteGetHeight(gui_img_t idSprite);

/**
 * @function Sprite
 * @brief display a sprite
 * @param coord_t x0, coord_t y0: absolute coords
 * @param gui_img_t idSprite: sprite uid
 * @return none
 */
void Sprite(coord_t x0, coord_t y0, gui_img_t idSprite);

#endif
