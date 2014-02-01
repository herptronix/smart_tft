/**
 * @file p2d_font.c
 * @brief p2d font management (limited to 1BPP and 4BPP)
 * @author Duboisset Philippe
 * @version 0.4b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-04-07 initial version
 *  0.2b  2013-07-23 small modification (disp. window restoration to NULL)
 *  0.3b  2013-09-07 implementation of P2D_GetGlyphWidth() & P2D_PutGlyph()
 *  0.4b  2014-01-30 small bug fix (setWnd issue)
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


#include "p2d_internal.h"


/**
 * Private defines
 */
enum {
  FONT_1BPP = 1,
  FONT_4BPP,
  FONT_INVALID
};

enum {    /*font file header*/
  BPP_TYPE = 0,     /*1st byte represents the font type (FONT_1BPP / FONT_4BPP)*/
  BPP_GMIN,         /*2nd byte is the first glyph ID; e.g. 'a'*/
  BPP_GMAX,         /*3rd byte is the last glyph ID; e.g. 'z'*/
  BPP_HEIGHT,       /*4th byte is the font height (all glyphs have the same height)*/
  BPP_INDEX         /*5th byte is the start of the glyph table entries; each entry is composed by the enumeration below*/
};
enum {    /*glyph entry*/
  BPP_ENTRY_WIDTH,  /*1st byte is the glyph width*/
  BPP_OFFSET_HL,    /*next bytes form the glyph offset, where HL is the MSB and LL the LSB*/
  BPP_OFFSET_LH,            /*offsets are relative to the "raw address"*/
  BPP_OFFSET_LL,            /*the raw address is located just after the glyph table entries*/
  BPP_ENTRY_SIZE
};

/**
 * private variables
 */
static uint8_t fontType;                    /*type of font*/
static const uint8_t *index;                /*pointer to the glyph table*/
static const uint8_t *raw;                  /*pointer to the first glyph*/
static uint8_t glyphMin, glyphMax;          /*minimum & maximum supported glyph ID (~ASCII code)*/
static uint8_t height;                      /*font height; all glyph contained in a font have the same height*/
static lut4bpp_st lut;                      /*local lut, for 4BPP fonts*/

/**
 * Local functions prototypes
 */
static int8_t OpenBPP(const uint8_t *fontFile);
static const uint8_t *GetGlyphAddr(uint8_t id);
static uint8_t GetGlyphWidth(uint8_t id);
static void PutGlyph(const rect_st *rec, const uint8_t *ptrGlyph);
static void PutFast_1BPP(const rect_st *rec, const uint8_t *ptr, uint32_t cntPxClip);
static void PutSlow_1BPP(const rect_st *rec, const uint8_t *ptr);
static void NextBit_1BPP(uint8_t *mask, const uint8_t **ptr);
static void PutFast_4BPP(const rect_st *rec, const uint8_t *ptr, uint32_t cntPxClip);
static void PutSlow_4BPP(const rect_st *rec, const uint8_t *ptr);
static void NextBit_4BPP(uint8_t *mask, const uint8_t **ptr);


/**
 * @function P2D_SetFont
 * @brief Set the current font
 * @param const uint8_t *pFile: pointer to the font file; read-only.
 * @return 0: ok, -1: error
 */
int8_t P2D_SetFont(const uint8_t *pFile) {

  int8_t res = -1;

  if(pFile != NULL) {
    /*retrieve the font type, and open the font*/
    fontType = pFile[0];
    switch(fontType) {

      case FONT_1BPP:
      case FONT_4BPP:
        res = OpenBPP(pFile);
        break;

      default:
        break;
    }
  }

  /*if any error, force current type to FONT_INVALID*/
  if(res < 0) {
    fontType = FONT_INVALID;
  }

  /*always initialize the lut for 4BPP fonts*/
  if(fontType == FONT_4BPP) {
    (void) P2D_InitLut4BPP(&lut, NULL, LUT_E_GRADIENT);
  }

  return res;
}


/**
 * @function P2D_GetTextHeight
 * @brief return the current font height
 * @param none
 * @return length_t: current font height
 */
length_t P2D_GetTextHeight(void) {
  length_t h = 0;
  if(fontType != FONT_INVALID) h = (length_t) height;
  return h;
}


/**
 * @function P2D_GetTextWidth
 * @brief return the string width, in pixel, according to the current font
 * @param const void *ptr: string
 * @return length_t: string width
 */
length_t P2D_GetTextWidth(const void /*@null@*/ *ptr) {
  length_t w = 0;
  const uint8_t *str = (const uint8_t *) ptr;

  /*compute the string width*/
  if(fontType != FONT_INVALID && str != NULL) {
    while(*str != 0) {
      if(*str >= glyphMin && *str <= glyphMax) {
        w += GetGlyphWidth(*str);
      }
      str++;
    }
  }
  return w;
}


/**
 * @function P2D_GetGlyphWidth
 * @brief return width the width of a given glyph, in pixel, according to the current font
 * @param uint8_t g: glyph
 * @return length_t: glyph's width
 */
length_t P2D_GetGlyphWidth(uint8_t g) {
  length_t w = 0;

  if(fontType != FONT_INVALID) {
    w = GetGlyphWidth(g);
  }

  return w;
}


/**
 * @function P2D_PutGlyph
 * @brief Display a glyph at a given position
 * @param coord_t x, y: position to put the text; correspond to the top-left of the first string char
 * @param uint8_t glyph
 * @return none
 */
void P2D_PutGlyph(coord_t x, coord_t y, uint8_t glyph) {
  uint8_t str[2];
  str[0] = glyph;
  str[1] = 0;
  P2D_PutText(x, y, str);
}


/**
 * @function P2D_PutText
 * @brief Display a text at a given position
 * @param coord_t x, y: position to put the text; correspond to the top-left of the first string char
 * @param const void *ptr: string
 * @return none
 */
void P2D_PutText(coord_t x, coord_t y, const void /*@null@*/ *ptr) {

  const uint8_t *ptrGlyph;
  rect_st rec;
  const uint8_t *str = (const uint8_t *) ptr;

  /*print something only if the current font is valid & the str is not null*/
  if(fontType != FONT_INVALID && str != NULL) {

    rec.x = x;
    rec.y = y;
    rec.w = 0;
    rec.h = height;

    /*recompute the color lut*/
    if(fontType == FONT_4BPP) {
      P2D_UpdateLut4BPP(&lut);
    }

    /*put glyphs until \0 */
    while(*str != 0) {

      /*put the glyph only if it exists in the current font*/
      if(*str >= glyphMin && *str <= glyphMax) {

        /*retrieve glyph address & width, according to the current font*/
        ptrGlyph = GetGlyphAddr(*str);
        rec.w = GetGlyphWidth(*str);

        /*Put he glyph on screen & increment x with the glyph width*/
        PutGlyph(&rec, ptrGlyph);
        rec.x += rec.w;
      }

      str++;
    }

    SetWnd(NULL);
  }
}


/**
 * @function OpenBPP
 * @brief Opens a BPP font & sets font properties in the static global variables
 * @param const uint8_t *fontFile: pointer to the font; shall be checked by caller functions
 * @return 0: ok, -1: error
 */
static int8_t OpenBPP(const uint8_t *fontFile) {

  int8_t res = -1;
  uint16_t glyphCnt;

  /*gets min & max glyph ID*/
  glyphMin = fontFile[BPP_GMIN];
  glyphMax = fontFile[BPP_GMAX];

  /*gets glyph height*/
  if(glyphMin <= glyphMax) {
    height = fontFile[BPP_HEIGHT];

    /*retreives index & raw addresses*/
    if(height > 0) {

      index = &fontFile[BPP_INDEX];

      glyphCnt = (glyphMax - glyphMin) + 1;
      raw = &fontFile[BPP_INDEX + BPP_ENTRY_SIZE * glyphCnt];

      /*at this point, the font seems to be valid*/
      res = 0;
    }
  }

  return res;
}


/**
 * @function GetGlyphAddr
 * @brief return the raw address of the given glyph
 * @param uint8_t id: glyph id; shall be checked by caller functions
 * @return uint8_t *: pointer to raw
 */
static const uint8_t *GetGlyphAddr(uint8_t id) {
  uint16_t entryPos;
  uint32_t offset;

  /*to ensures easy portability, we build the offset byte per byte instead of
   *casting it directly, like "offset = *((uint32_t *) &index[entryPos]) & 0x00FFFFFF"
   *A direct cast will be sensitive to endianess, implying different files for a same font
   */
  entryPos = (id - glyphMin) * BPP_ENTRY_SIZE;
  offset  = ((uint32_t) index[entryPos + BPP_OFFSET_HL]) << 16;
  offset |= ((uint32_t) index[entryPos + BPP_OFFSET_LH]) << 8;
  offset |=  (uint32_t) index[entryPos + BPP_OFFSET_LL];

  return &raw[offset];
}


/**
 * @function GetGlyphWidth
 * @brief return the width of the given glyph
 * @param uint8_t id: glyph id; shall be checked by caller functions
 * @return uint8_t: glyph width
 */
static uint8_t GetGlyphWidth(uint8_t id) {
  uint16_t entryPos = entryPos = (id - glyphMin) * BPP_ENTRY_SIZE;
  return index[entryPos + BPP_ENTRY_WIDTH];
}


/**
 * @function PutGlyph
 * @brief puts a given glyph to a given position
 * @param const rect_st *rec: contains the position, width & height of the glyph; shall be not null
 * @param const uint8_t *ptrGlyph: glyph stream; shall be not null
 * @return none
 */
static void PutGlyph(const rect_st *rec, const uint8_t *ptrGlyph) {

  uint16_t cntPxGly, cntPxClip;
  rect_st lrec = *rec;

  /*compute the number of pixels composing the glyph*/
  cntPxGly = P2D_GetPixelCnt(rec);

  /*apply the global clip to lrec, & compute the number of pixels composing the modified lrec*/
  P2D_ClipFit(&lrec);
  cntPxClip = P2D_GetPixelCnt(&lrec);
  SetWnd(&lrec);

  /*if the lrec completly fits into the current clip && DISPLAY_SOLID -> optimized procedure*/
  if(context.mode == DISPLAY_SOLID && cntPxClip == cntPxGly) {
    if(fontType == FONT_1BPP) PutFast_1BPP(&lrec, ptrGlyph, cntPxClip);
    else if(fontType == FONT_4BPP) PutFast_4BPP(&lrec, ptrGlyph, cntPxClip);
  }
  /*else, put pixel per pixel... much slower !*/
  else {
    if(fontType == FONT_1BPP) PutSlow_1BPP(rec, ptrGlyph);
    else if(fontType == FONT_4BPP) PutSlow_4BPP(rec, ptrGlyph);
  }
}


/**
 * @function PutFast_1BPP
 * @brief fast procedure for displaying a 1BPP glyph
 * @param const rect_st *rec: contains the position, width & height of the glyph; shall be not null
 * @param const uint8_t *ptr: glyph raw; shall be not null
 * @param uint32_t cntPxClip: number of pixel contained in rec
 * @return none
 */
static void PutFast_1BPP(const rect_st *rec, const uint8_t *ptr, uint32_t cntPxClip) {

  uint8_t mask = 0x80;

  /*just put the glyph stream*/
  while(cntPxClip-- > 0) {
    if(*ptr & mask) Put(context.colFront);
    else Put(context.colBackgrnd);
    NextBit_1BPP(&mask, &ptr);
  }
}


/**
 * @function PutSlow_1BPP
 * @brief slow procedure for displaying a 1BPP glyph
 * @param const rect_st *rec: contains the position, width & height of the glyph; shall be not null
 * @param const uint8_t *ptr: glyph raw; shall be not null
 * @return none
 */
static void PutSlow_1BPP(const rect_st *rec, const uint8_t *ptr) {

  uint8_t mask = 0x80;
  coord_t x, y;

  /*for each pixel*/
  for(y = rec->y; y < rec->y + rec->h; y++) {
    for(x = rec->x; x < rec->x + rec->w; x++) {

      /*always puts glyph front*/
      if(*ptr & mask) {
        P2D_SetPixel(x, y, context.colFront);
      }
      /*puts glyph background ONLY if DISPLAY_SOLID*/
      else if(context.mode == DISPLAY_SOLID) {
        P2D_SetPixel(x, y, context.colBackgrnd);
      }

      NextBit_1BPP(&mask, &ptr);
    }
  }
}


/**
 * @function NextBit_1BPP
 * @brief get the next bit to display
 * @param uint8_t *mask: only one bit is set, representing the current glyph pixel
 * @param const uint8_t **ptr: ptr to the current byte which contain the pixel
 * @return none
 */
static void NextBit_1BPP(uint8_t *mask, const uint8_t **ptr) {
  (*mask) >>= 1;
  if(*mask == 0x00) {
    (*ptr)++;
    *mask = 0x80;
  }
}


/**
 * @function PutFast_4BPP
 * @brief fast procedure for displaying a 4BPP glyph
 * @param const rect_st *rec: contains the position, width & height of the glyph; shall be not null
 * @param const uint8_t *ptr: glyph raw; shall be not null
 * @param uint32_t cntPxClip: number of pixel contained in rec
 * @return none
 */
static void PutFast_4BPP(const rect_st *rec, const uint8_t *ptr, uint32_t cntPxClip) {

  uint8_t mask = 0xF0;
  uint8_t color;

  /*just put the glyph stream*/
  while(cntPxClip-- > 0) {
    color = *ptr & mask;
    if(mask == 0xF0) color >>= 4;
    /*color &= 0x0F;   ->be sure that color value does not overlap lut4BPP size*/
    Put(lut.lut[color]);
    NextBit_4BPP(&mask, &ptr);
  }
}


/**
 * @function PutSlow_4BPP
 * @brief slow procedure for displaying a 4BPP glyph
 * @param const rect_st *rec: contains the position, width & height of the glyph; shall be not null
 * @param const uint8_t *ptr: glyph raw; shall be not null
 * @return none
 */
static void PutSlow_4BPP(const rect_st *rec, const uint8_t *ptr) {

  uint8_t mask = 0xF0;
  uint8_t color;
  coord_t x, y;

  /*for each pixel*/
  for(y = rec->y; y < rec->y + rec->h; y++) {
    for(x = rec->x; x < rec->x + rec->w; x++) {

      color = *ptr & mask;
      if(mask == 0xF0) color >>= 4;
      /*color &= 0x0F;   ->be sure that color is in RANGE[0x00-0x0F]*/

      /*always puts glyph front*/
      if(color != 0) {
        P2D_SetPixel(x, y, lut.lut[color]);
      }
      /*puts glyph background ONLY if DISPLAY_SOLID*/
      else if(context.mode == DISPLAY_SOLID) {
        P2D_SetPixel(x, y, lut.lut[0]);
      }

      NextBit_4BPP(&mask, &ptr);
    }
  }
}


/**
 * @function NextBit_4BPP
 * @brief get the next nibble to display
 * @param uint8_t *mask: only one nible to 0xF, representing the current glyph pixel
 * @param const uint8_t **ptr: ptr to the current byte which contain the pixel
 * @return none
 */
static void NextBit_4BPP(uint8_t *mask, const uint8_t **ptr) {
  (*mask) >>= 4;
  if(*mask == 0x00) {
    (*ptr)++;
    *mask = 0xF0;
  }
}
