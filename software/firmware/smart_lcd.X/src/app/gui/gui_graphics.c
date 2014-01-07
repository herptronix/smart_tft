/**
 * @file gui_graphics.c
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

#include "gui_graphics.h"
#include "resources.h"

/**
 * sprite_sheet_st
 * sprite sheet, where all sprites have the same width & height
 */
typedef struct sprite_sheet_t {
  struct sprite_sheet_t *next;
  const void *ptrFile;
  lut8bpp_st *arLut[G_NB_LUT];
  gui_img_t from, to;
} sprite_sheet_st;


/**
 * local variables
 */
static color_t arColors[G_NB_COLORS];         /*color LUT for widgets*/
static const void *arFonts[G_NB_FONT];        /*font LUT*/
static sprite_sheet_st *spriteSheet = NULL;   /*head of list of sprite sheets*/
static gui_font_t fontId;                     /*current font used*/
static gui_align_t align;
static uint8_t lutId;


/**
 * local functions
 */
static sprite_sheet_st /*@null@*/ *GetSpriteSheet(gui_img_t idSprite);
static int8_t SpriteSheetAdd(const void *ptrFile, gui_img_t from, gui_img_t to);
static int8_t SpriteSheetAddLut(const void *ptrFileLut, uint8_t idLut, lutmode_t mode);
static length_t GetW(const sprite_sheet_st /*@null@*/ *sp);
static length_t GetH(const sprite_sheet_st /*@null@*/ *sp);


/**
 * @function GraphInit
 * @brief initialize graphic resources; may allocate memory (e.g. for sprite CLUT)
 * @param none
 * @return none
 */
void GraphInit(void) {

  /*color LUT*/
  arColors[G_COL_BACKGROUND]      = P2D_Color(200, 200, 200);
  arColors[G_COL_E_BACKGROUND]    = P2D_Color(255, 255, 255);
  arColors[G_COL_L_BACKGROUND]    = P2D_Color(180, 180, 180);
  arColors[G_COL_KBD_BACKGROUND]  = P2D_Color(80 , 80 , 80 );
  arColors[G_COL_KBD_KEY]         = P2D_Color(230, 230, 230);
  arColors[G_COL_KBD_KEY_ENTER]   = P2D_Color(200, 255, 200);
  arColors[G_COL_KBD_KEY_ESC]     = P2D_Color(255, 200, 200);
  arColors[G_COL_KBD_KEY_FN]      = P2D_Color(200, 200, 255);
  arColors[G_COL_TEXT]            = P2D_Color(0  , 0  , 0  );
  arColors[G_COL_TEXT_REVERSE]    = P2D_Color(255, 255, 255);
  arColors[G_COL_D_TEXT]          = P2D_Color(127, 127, 127);
  arColors[G_COL_UPPER_REC]       = P2D_Color(255, 255, 255);
  arColors[G_COL_LOWER_REC]       = P2D_Color(127, 127, 127);
  arColors[G_COL_SPECIAL]         = P2D_Color(0  , 150, 230);
  arColors[G_COL_LED_ON]          = P2D_Color(0  , 255, 0  );
  arColors[G_COL_LED_OFF]         = P2D_Color(255, 0  , 0  );

  /*font LUT*/
  arFonts[G_FONT_DEFAULT]        = FontFreeSerif_4bpp_n_16;
  arFonts[G_FONT_BOLD]           = FontFreeSerif_4bpp_b_16;
  arFonts[G_FONT_ITALIC]         = FontFreeSerif_4bpp_i_16;
  arFonts[G_FONT_DIGIT]          = Digit_4bpp_n_16;
  arFonts[G_FONT_BIG]            = FontFreeSerif_4bpp_n_20;
  arFonts[G_FONT_VERY_BIG]       = FontFreeSerif_4bpp_n_24;
  arFonts[G_FONT_SMALL]          = FontFreeSerif_4bpp_n_16;
  arFonts[G_FONT_SYMBOL]         = FontSymbol;

  /*sprite sheets registration*/
  /*pack00: action*/
  SpriteSheetAdd(spriteFile00, G_IMG_OK, G_IMG_WARNING);
  SpriteSheetAddLut(spriteLutFile00, G_LUT_NORMAL, LUT_E_COPY | LUT_O_COLOR_KEY);
  SpriteSheetAddLut(spriteLutFile00, G_LUT_DISABLED, LUT_E_COPY | LUT_O_BLACK_AND_WHITE | LUT_O_COLOR_KEY);

  /*pack01: device*/
  SpriteSheetAdd(spriteFile01, G_IMG_DEVICE, G_IMG_CLOCK);
  SpriteSheetAddLut(spriteLutFile01, G_LUT_NORMAL, LUT_E_COPY | LUT_O_COLOR_KEY);

  /*pack02: files*/
  SpriteSheetAdd(spriteFile02, G_IMG_FILE_INFO, G_IMG_FILE_UNKNOWN);
  SpriteSheetAddLut(spriteLutFile02, G_LUT_NORMAL, LUT_E_COPY | LUT_O_COLOR_KEY);

  /*pack03: misc*/
  SpriteSheetAdd(spriteFile03, G_IMG_CALC, G_IMG_USER_BLUE2);
  SpriteSheetAddLut(spriteLutFile03, G_LUT_NORMAL, LUT_E_COPY | LUT_O_COLOR_KEY);

  /*pack03: 32x32, for popup*/
  SpriteSheetAdd(spriteFile04, G_IMG_BIG_ERROR, G_IMG_BIG_NO_SIGNAL);
  SpriteSheetAddLut(spriteLutFile04, G_LUT_NORMAL, LUT_E_COPY | LUT_O_COLOR_KEY);

  /*default settings*/
  SetLut(G_LUT_NORMAL);
  GUI_SetAlign(G_ALIGN_DEFAULT);
  SetFont(G_FONT_DEFAULT);
}


/**
 * @function GUI_GetAlign
 * @brief return the current alignment
 * @param none
 * @return gui_align_t: current alignment
 */
gui_align_t GUI_GetAlign(void) {
  return align;
}


/**
 * @function GUI_SetAlign
 * @brief define the alignment
 * @param gui_align_t a: new alignment; see gui_align_t type
 * @return none
 */
void GUI_SetAlign(gui_align_t a) {
  align = a;
}


/**
 * @function SetFont
 * @brief define the font which shall be used by the GUI
 * @param gui_font_t font: < G_NB_FONT
 * @return none
 */
void SetFont(gui_font_t font) {
  if(font < G_NB_FONT) fontId = font;
  P2D_SetFont(arFonts[fontId]);
}


/**
 * @function GetCurrentFont
 * @brief retrieve the id of the current font used by the GUI
 * @param none
 * @return gui_font_t: current font
 */
gui_font_t GetCurrentFont(void) {
  return fontId;
}


/**
 * @function GetColor
 * @brief retrieve a color of the GUI palette
 * @param uint16_t idCol: id of the color; shall be < G_NB_COLORS
 * @return color_t : color (here, in RGB565 format)
 */
color_t GetColor(uint16_t idCol) {
  color_t color = COLOR_BLACK;
  if(idCol < G_NB_COLORS) color = arColors[idCol];
  return color;
}


/**
 * @function SetColor
 * @brief define a color of the GUI palette
 * @param uint16_t idCol: id of the color; shall be < G_NB_COLORS
 * @param color_t col: color (here, in RGB565 format)
 * @return none
 */
void SetColor(uint16_t idCol, color_t col) {
  if(idCol < G_NB_COLORS) arColors[idCol] = col;
}


/**
 * @function SetLut
 * @brief select the GUI lut to use for the sprites
 * @param uint8_t lut: lut to use; shall be < G_NB_LUT
 * @return none
 */
void SetLut(uint8_t lut) {
  if(lut < G_NB_LUT) lutId = lut;
}


/**
 * @function SpriteGetWidth
 * @brief get the width of a sprite
 * @param gui_img_t idSprite: sprite uid
 * @return length_t: width of the sprite, 0 if the sprite does not exist
 */
length_t SpriteGetWidth(gui_img_t idSprite) {
  return GetW(GetSpriteSheet(idSprite));
}


/**
 * @function SpriteGetHeight
 * @brief get the height of a sprite
 * @param gui_img_t idSprite: sprite uid
 * @return length_t: height of the sprite, 0 if the sprite does not exist
 */
length_t SpriteGetHeight(gui_img_t idSprite) {
  return GetH(GetSpriteSheet(idSprite));
}


/**
 * @function Sprite
 * @brief display a sprite
 * @param coord_t x0, coord_t y0: absolute coords
 * @param gui_img_t idSprite: sprite uid
 * @return none
 */
void Sprite(coord_t x0, coord_t y0, gui_img_t idSprite) {

  rect_st dst, src;
  length_t w, h;
  lut8bpp_st *pLut;
  sprite_sheet_st *sp = NULL;

  /*retrieve the sheet containing the idSprite*/
  sp = GetSpriteSheet(idSprite);
  if(sp != NULL) {

    /*get the width & height of idSprite*/
    w = GetW(sp);
    h = GetH(sp);

    /*define destination rect (to screen)*/
    dst.x = x0;
    dst.y = y0;
    dst.w = w;
    dst.h = h;

    /*define source rect (from sheet)*/
    src.x = 0;
    src.y = (idSprite - sp->from) * h;
    src.w = w;
    src.h = h;

    /*select & update the CLUT; if current lut == NULL, select the G_LUT_NORMAL*/
    if(sp->arLut[lutId] != NULL) pLut = sp->arLut[lutId];
    else pLut = sp->arLut[0];
    P2D_SpriteSetLut8BPP(pLut);
    P2D_UpdateLut8BPP(pLut);      /*always update the CLUT! (for colorkey mask)*/

    /*display the sprite*/
    P2D_Sprite(&src, &dst, sp->ptrFile);
  }
}


/**
 * @function GetSpriteSheet
 * @brief retrieve the pointer to the sprite sheet containing the idSprite
 * @param gui_img_t idSprite: sprite uid
 * @return sprite_sheet_st*: pointer to sprite sheet if success, NULL if ot found
 */
static sprite_sheet_st /*@null@*/ *GetSpriteSheet(gui_img_t idSprite) {

  sprite_sheet_st *res = spriteSheet;

  while(res != NULL && (idSprite < res->from || idSprite > res->to)) res = res->next;
  return res;
}


/**
 * @function SpriteSheetAdd
 * @brief add a new sprite sheet in list
 * @param const void *ptrFile: pointer to the sprite file
 * @param gui_img_t from, to: from & to uid
 * @return int8_t: 0 success, -1 error
 */
static int8_t SpriteSheetAdd(const void *ptrFile, gui_img_t from, gui_img_t to) {

  int8_t res = -1;
  sprite_sheet_st **seek = NULL, *pNewSheet = NULL;

  /*allocate a new sheet*/
  pNewSheet = salloc(sizeof(sprite_sheet_st));
  if(pNewSheet != NULL) {

    /*clear all internal pointer*/
    gmemset(pNewSheet, 0, sizeof(sprite_sheet_st));

    /*copy file pointer, from & to uid*/
    pNewSheet->ptrFile = ptrFile;
    pNewSheet->from = from;
    pNewSheet->to = to;

    /*insert the new sheet into the sheets list*/
    seek = &spriteSheet;
    while(*seek != NULL) seek = &((*seek)->next);
    *seek = pNewSheet;

    res = 0;
  }

  return res;
}


/**
 * @function SpriteSheetAddLut
 * @brief create & configure a clut for the last added sheet
 * @param const void *ptrFileLut: pointer to the lut (8bpp) file
 * @param uint8_t idLut: G_LUT_NORMAL / G_LUT_DISABLED...
 * @param lutmode_t mode: lut mode; see lutmode_t type
 * @return int8_t: 0 success, -1 error
 */
static int8_t SpriteSheetAddLut(const void *ptrFileLut, uint8_t idLut, lutmode_t mode) {

  int8_t res = -1;
  sprite_sheet_st *seek = NULL;

  if(spriteSheet != NULL && idLut < G_NB_LUT) {

    /*go to the last added sheet*/
    seek = spriteSheet;
    while(seek->next != NULL) seek = seek->next;

    /*allocate a new lut*/
    seek->arLut[idLut] = salloc(sizeof(lut8bpp_st));
    if(seek->arLut[idLut] != NULL) {

      /*init the lu, according to the given mode*/
      P2D_InitLut8BPP(seek->arLut[idLut], ptrFileLut, mode);
      res = 0;
    }
  }

  return res;
}


/**
 * @function GetW
 * @brief return the width of a tile contained in a sprite sheet
 * @param sprite_sheet_st *sp: pointer to the sprite sheet
 * @return length_t: width of the tile, 0 if sp == NULL
 */
static length_t GetW(const sprite_sheet_st /*@null@*/ *sp) {
  length_t res = 0;
  if(sp != NULL) res = P2D_SpriteGetWidth(sp->ptrFile);
  return res;
}


/**
 * @function GetH
 * @brief return the height of a tile contained in a sprite sheet
 * @param sprite_sheet_st *sp: pointer to the sprite sheet
 * @return length_t: height of the tile, 0 if sp == NULL
 */
static length_t GetH(const sprite_sheet_st /*@null@*/ *sp) {
  length_t res = 0, div;
  if(sp != NULL) {
    div = sp->to - sp->from + 1;
    if(div > 0) res = P2D_SpriteGetHeight(sp->ptrFile) / div;
  }
  return res;
}
