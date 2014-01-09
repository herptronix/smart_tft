/**
 * @file resources.h
 * @brief graphic resources (font, srites & cluts)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-07-13
 *
 * Copyright (C) <2013>  <duboisset.philippe@gmail.com>
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

#ifndef _resources_h_
#define _resources_h_

#include "main.h"





//#define USE_FONT_DIGIT_4BPP_N_12
//#define USE_FONT_DIGIT_4BPP_N_13
//#define USE_FONT_DIGIT_4BPP_N_14
//#define USE_FONT_DIGIT_4BPP_N_15
#define USE_FONT_DIGIT_4BPP_N_16
//#define USE_FONT_DIGIT_4BPP_N_17
//#define USE_FONT_DIGIT_4BPP_N_18
//#define USE_FONT_DIGIT_4BPP_N_20
//#define USE_FONT_DIGIT_4BPP_N_22
//#define USE_FONT_DIGIT_4BPP_N_25
//#define USE_FONT_DIGIT_4BPP_N_31
//#define USE_FONT_DIGIT_4BPP_N_39

//#define USE_FONT_FREESERIF_4BPP_N_12
//#define USE_FONT_FREESERIF_4BPP_N_14
#define USE_FONT_FREESERIF_4BPP_N_16
//#define USE_FONT_FREESERIF_4BPP_N_18
#define USE_FONT_FREESERIF_4BPP_N_20
//#define USE_FONT_FREESERIF_4BPP_N_22
//#define USE_FONT_FREESERIF_4BPP_N_24

//#define USE_FONT_FREESERIF_4BPP_B_12
//#define USE_FONT_FREESERIF_4BPP_B_14
#define USE_FONT_FREESERIF_4BPP_B_16
//#define USE_FONT_FREESERIF_4BPP_B_18
//#define USE_FONT_FREESERIF_4BPP_B_20
//#define USE_FONT_FREESERIF_4BPP_B_22
//#define USE_FONT_FREESERIF_4BPP_B_24

//#define USE_FONT_FREESERIF_4BPP_I_12
//#define USE_FONT_FREESERIF_4BPP_I_14
#define USE_FONT_FREESERIF_4BPP_I_16
//#define USE_FONT_FREESERIF_4BPP_I_18
//#define USE_FONT_FREESERIF_4BPP_I_20
//#define USE_FONT_FREESERIF_4BPP_I_22
//#define USE_FONT_FREESERIF_4BPP_I_24

extern const uint8_t FontSymbol[];

extern const uint8_t Digit_4bpp_n_12[];
extern const uint8_t Digit_4bpp_n_13[];
extern const uint8_t Digit_4bpp_n_14[];
extern const uint8_t Digit_4bpp_n_15[];
extern const uint8_t Digit_4bpp_n_16[];
extern const uint8_t Digit_4bpp_n_17[];
extern const uint8_t Digit_4bpp_n_18[];
extern const uint8_t Digit_4bpp_n_20[];
extern const uint8_t Digit_4bpp_n_22[];
extern const uint8_t Digit_4bpp_n_25[];
extern const uint8_t Digit_4bpp_n_31[];
extern const uint8_t Digit_4bpp_n_39[];

extern const uint8_t FontFreeSerif_4bpp_n_12[];
extern const uint8_t FontFreeSerif_4bpp_n_14[];
extern const uint8_t FontFreeSerif_4bpp_n_16[];
extern const uint8_t FontFreeSerif_4bpp_n_18[];
extern const uint8_t FontFreeSerif_4bpp_n_20[];
extern const uint8_t FontFreeSerif_4bpp_n_22[];
extern const uint8_t FontFreeSerif_4bpp_n_24[];

extern const uint8_t FontFreeSerif_4bpp_b_12[];
extern const uint8_t FontFreeSerif_4bpp_b_14[];
extern const uint8_t FontFreeSerif_4bpp_b_16[];
extern const uint8_t FontFreeSerif_4bpp_b_18[];
extern const uint8_t FontFreeSerif_4bpp_b_20[];
extern const uint8_t FontFreeSerif_4bpp_b_22[];
extern const uint8_t FontFreeSerif_4bpp_b_24[];

extern const uint8_t FontFreeSerif_4bpp_i_12[];
extern const uint8_t FontFreeSerif_4bpp_i_14[];
extern const uint8_t FontFreeSerif_4bpp_i_16[];
extern const uint8_t FontFreeSerif_4bpp_i_18[];
extern const uint8_t FontFreeSerif_4bpp_i_20[];
extern const uint8_t FontFreeSerif_4bpp_i_22[];
extern const uint8_t FontFreeSerif_4bpp_i_24[];



extern const uint8_t spriteLutFile00[];
extern const uint8_t spriteFile00[];
extern const uint8_t spriteLutFile01[];
extern const uint8_t spriteFile01[];
extern const uint8_t spriteLutFile02[];
extern const uint8_t spriteFile02[];
extern const uint8_t spriteLutFile03[];
extern const uint8_t spriteFile03[];
extern const uint8_t spriteLutFile04[];
extern const uint8_t spriteFile04[];

enum {
  G_IMG_NONE = 0,

  /**
   *  PACK 00
   */
  G_IMG_OK,               /*1*/
  G_IMG_NO,
  G_IMG_ADD,
  G_IMG_REMOVE,
  G_IMG_LEFT_ARROW,
  G_IMG_LEFT_D_ARROW,
  G_IMG_DOWN_ARROW,
  G_IMG_DOWN_D_ARROW,
  G_IMG_RIGHT_ARROW,
  G_IMG_RIGHT_D_ARROW,
  G_IMG_UP_ARROW,
  G_IMG_UP_D_ARROW,
  G_IMG_GO_LEFT,
  G_IMG_GO_DOWN,
  G_IMG_GO_RIGHT,
  G_IMG_GO_UP,
  G_IMG_CONFIG,
  G_IMG_FORBID,
  G_IMG_ERROR,
  G_IMG_SAVE,
  G_IMG_OPEN,
  G_IMG_EDIT,
  G_IMG_INFO,
  G_IMG_HELP,
  G_IMG_HOME,
  G_IMG_REFRESH,
  G_IMG_IMPORTANT,
  G_IMG_EXIT,
  G_IMG_EJECT,
  G_IMG_PAUSE,
  G_IMG_STOP,
  G_IMG_REC,
  G_IMG_FIND,
  G_IMG_ZOOM_1,
  G_IMG_ZOOM_OUT,
  G_IMG_ZOOM_IN,
  G_IMG_ACCEPT,
  G_IMG_DECLINE,
  G_IMG_SORT_DOWN,
  G_IMG_SORT_UP,
  G_IMG_BOOKMARK,
  G_IMG_GRAPH_ADD,
  G_IMG_GRAPH_REMOVE,
  G_IMG_GRAPH_EDIT,
  G_IMG_DOWNLOAD,
  G_IMG_CLEAR,
  G_IMG_CUT,
  G_IMG_DRAG,
  G_IMG_SMILE,
  G_IMG_HISTOGRAM,
  G_IMG_LOCK,
  G_IMG_BULB,
  G_IMG_OSCILLOSCOPE,
  G_IMG_TASK,
  G_IMG_WARNING,

  /**
   *  PACK 01
   */
  G_IMG_DEVICE,
  G_IMG_SND_MUTE,
  G_IMG_SOUND_MIN,
  G_IMG_SOUND_MEDIUM,
  G_IMG_SOUND_MAX,
  G_IMG_BATTERY_MIN,
  G_IMG_BATTERY_MEDIUM,
  G_IMG_BATTERY_GOOD,
  G_IMG_BATTERY_MAX,
  G_IMG_BATTERY_C_MIN,
  G_IMG_BATTERY_C_MEDIUM,
  G_IMG_BATTERY_C_GOOD,
  G_IMG_BATTERY_C_MAX,
  G_IMG_COMPUTER,
  G_IMG_SD_CARD,
  G_IMG_SIGNAL_NONE,
  G_IMG_SIGNAL_MIN,
  G_IMG_SIGNAL_MEDIUM,
  G_IMG_SIGNAL_GOOD,
  G_IMG_SIGNAL_MAX,
  G_IMG_SAFE,
  G_IMG_UNSAFE,
  G_IMG_USB,
  G_IMG_CLOCK,

  /**
   *  PACK 02
   */
  G_IMG_FILE_INFO,
  G_IMG_FILE_APP,
  G_IMG_FILE_APP_WIN,
  G_IMG_FILE_ZIP,
  G_IMG_FILE_AUDIO,
  G_IMG_FILE_PACK,
  G_IMG_FILE_ENCRYPTED,
  G_IMG_FILE_IMPORTANT,
  G_IMG_FILE_TMP,
  G_IMG_FOLDER,
  G_IMG_FILE_FONT,
  G_IMG_FILE_IMGS,
  G_IMG_FILE_IMG,
  G_IMG_FILE_PACK2,
  G_IMG_FILE_HTML,
  G_IMG_FILE_ASM,
  G_IMG_FILE_H,
  G_IMG_FILE_C,
  G_IMG_FILE_TXT,
  G_IMG_FILE_EMPTY,
  G_IMG_FILE_SCRIPT,
  G_IMG_FILE_UNKNOWN,

  /**
   *  PACK 03
   */
  G_IMG_CALC,
  G_IMG_LOCALE_US,
  G_IMG_LOCALE_FR,
  G_IMG_BOMB,
  G_IMG_BOOKS,
  G_IMG_PACKAGE,
  G_IMG_BRICKS,
  G_IMG_CART,
  G_IMG_CREDIT_CARDS,
  G_IMG_DB_ERROR,
  G_IMG_EYE,
  G_IMG_FLAG_BLUE,
  G_IMG_FLAG_GREEN,
  G_IMG_FLAG_ORANGE,
  G_IMG_FLAG_PINK,
  G_IMG_FLAG_PURPLE,
  G_IMG_FLAG_RED,
  G_IMG_FLAG_YELLOW,
  G_IMG_PICTURES,
  G_IMG_WINDOWS,
  G_IMG_MONEY,
  G_IMG_MUSIC,
  G_IMG_SHEETS,
  G_IMG_PACKAGE2,
  G_IMG_ROSETTE,
  G_IMG_TAG_BLUE,
  G_IMG_TAG_GREEN,
  G_IMG_TAG_ORANGE,
  G_IMG_TAG_PINK,
  G_IMG_TAG_PURPLE,
  G_IMG_TAG_RED,
  G_IMG_TAG_YELLOW,
  G_IMG_TUX,
  G_IMG_USER_BLUE,
  G_IMG_USER_PURPLE,
  G_IMG_USER_GREY,
  G_IMG_USER_GREEN,
  G_IMG_USER_ORANGE,
  G_IMG_USER_RED,
  G_IMG_USER_BLUE2,

  /**
   *  PACK 04
   */
  G_IMG_BIG_ERROR,
  G_IMG_BIG_OK,
  G_IMG_BIG_WARNING,
  G_IMG_BIG_INFO,
  G_IMG_BIG_ASK,
  G_IMG_BIG_SAVED,
  G_IMG_BIG_SD_CARD,
  G_IMG_BIG_BATTERY_EMPTY,
  G_IMG_BIG_NO_SIGNAL
};


#endif
