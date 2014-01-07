/**
 * @file gui_w_key.c
 * @brief specific widget for the keyboard
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

#include "gui.h"
#include "keymap.h"


/**
 * key_st
 */
typedef struct {
  uint8_t glyph[KBD_MAP_COUNT];
} key_st;


/**
 * private variables
 */
static gui_font_t keyFont = 0, keySymbFont = 0;
static kbd_map_e *pMapId = NULL;


/**
 * local functions
 */
static void KeyDraw(void *g_obj, void *obj);


/**
 * @function GUI_KeySetConf
 * @brief configure the keys; shall be called before other key's functions
 * @param gui_font_t _keyFont: font to use for regular glyph (from 32 to 255)
 * @param gui_font_t _keySymbFont: font to use for special glyph (< 32, e.g. ENTER, COPY, CAPS...)
 * @return none
 */
void GUI_KeySetConf(gui_font_t _keyFont, gui_font_t _keySymbFont, kbd_map_e *_pMapId) {
  keyFont = _keyFont;
  keySymbFont = _keySymbFont;
  pMapId = _pMapId;
}


/**
 * @function GUI_AddKey
 * @brief ... add a key. Not safe outside the keyboard macro; that's why the file is not in the <widget> folder
 * @param const rect_st *rec: key dimension
 * @param const uint8_t *glyph: glyph array (size KBD_MAP_COUNT). One glyph per map
 * @return g_obj_st: NULL if error, pointer to the generic object otherwise
 */
g_obj_st /*@null@*/ *GUI_AddKey(const rect_st *rec, const uint8_t *glyph) {

  g_obj_st *g_obj = NULL, *res = NULL;
  key_st *key = NULL;

  /*check parameters*/
  if(rec != NULL && glyph != NULL && pMapId != NULL) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate a key*/
      key = salloc(sizeof(key_st));
      if(key != NULL) {

        /*key settings*/
        gmemcpy(key->glyph, glyph, KBD_MAP_COUNT * sizeof(key->glyph[0]));

        /*linkage between generic obj & key*/
        g_obj->rec = *rec;
        g_obj->draw = KeyDraw;
        g_obj->task = NULL;
        g_obj->obj = key;
        res = g_obj;
      }
    }
  }

  return res;
}


/**
 * @function KeyDraw
 * @brief key draw function
 * @param void *_g_obj: pointer to the generic object
 * @param void *_obj: pointer to the key_st object
 * @return none
 */
static void KeyDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  key_st *key;
  color_t colBack, colText;
  coord_t x, y;
  uint8_t glyph;

  /*retrieve generic & specific object*/
  if(_g_obj != NULL && _obj != NULL && *pMapId < KBD_MAP_COUNT) {

    g_obj = (g_obj_st *) _g_obj;
    key =  (key_st*) _obj;

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);

    /*build key string*/
    glyph = key->glyph[*pMapId];

    /*regular glyph*/
    if(glyph >= (uint8_t) ' ') {

      /*pressed object?*/
      if(GUI_ObjIsPressed(g_obj)) {
        colBack = GetColor(G_COL_SPECIAL);
        colText = GetColor(G_COL_TEXT_REVERSE);
      }
      /*normal*/
      else {
        colBack = GetColor(G_COL_KBD_KEY);
        colText = GetColor(G_COL_TEXT);
      }
      SetFont(keyFont);
    }
    /*symbol?*/
    else {

      /*empty key?*/
      if(glyph == 0) {
        colBack = colText = GetColor(G_COL_KBD_BACKGROUND);
      }
      else {

        /*select the background color*/
        if (glyph == K_ENTER) colBack = GetColor(G_COL_KBD_KEY_ENTER);
        else if(glyph == K_ESC) colBack = GetColor(G_COL_KBD_KEY_ESC);
        else colBack = GetColor(G_COL_KBD_KEY_FN);

        /*select the glyph color*/
        if(GUI_ObjIsPressed(g_obj)) colText = GetColor(G_COL_TEXT_REVERSE);
        else colText = GetColor(G_COL_TEXT);
      }

      SetFont(keySymbFont);
    }

    /*background*/
    P2D_SetColors(colBack, colBack);
    P2D_FillRect(&(g_obj->rec));

    /*text*/
    P2D_SetColor(colText);
    x = g_obj->rec.x + (g_obj->rec.w - P2D_GetGlyphWidth(glyph)) / 2;
    y = g_obj->rec.y + (g_obj->rec.h - P2D_GetTextHeight()) / 2;
    P2D_PutGlyph(x, y, glyph);
  }
}
