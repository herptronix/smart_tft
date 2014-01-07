/**
 * @file keymap.c
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

#include "keymap.h"

/**
 * keyboard_en_us
 * QWERTY (US version) keyboard
 */
static const key_entry_st keyboard_en_us[KEY_MAX_COUNT] = {  /*KEY_MAX_COUNT: GCC does not support flexible array init...*/

  /*note: x & y are relative (to the top-left of keyboard) coordinates*/
  /* x   y   w   h   std       caps      altgr    */

  {  0,  0, 18, 18, {'~'     , '`'     ,  0      }},
  { 19,  0, 18, 18, {'1'     , '!'     ,  0      }},
  { 38,  0, 18, 18, {'2'     , '@'     ,  0      }},
  { 57,  0, 18, 18, {'3'     , '#'     ,  0      }},
  { 76,  0, 18, 18, {'4'     , '$'     ,  0      }},
  { 95,  0, 18, 18, {'5'     , '%'     ,  0      }},
  {114,  0, 18, 18, {'6'     , '^'     ,  0      }},
  {133,  0, 18, 18, {'7'     , '&'     ,  0      }},
  {152,  0, 18, 18, {'8'     , '*'     ,  0      }},
  {171,  0, 18, 18, {'9'     , '('     ,  0      }},
  {190,  0, 18, 18, {'0'     , ')'     ,  0      }},
  {209,  0, 18, 18, {'-'     , '_'     ,  0      }},
  {228,  0, 18, 18, {'='     , '+'     ,  0      }},
  {247,  0, 32, 18, {K_DELETE, K_DELETE, K_DELETE}},

  {  0, 19, 25, 18, {K_TAB   , K_TAB   , K_TAB   }},
  { 26, 19, 18, 18, {'q'     , 'Q'     ,  0      }},
  { 45, 19, 18, 18, {'w'     , 'W'     ,  0      }},
  { 64, 19, 18, 18, {'e'     , 'E'     ,  0      }},
  { 83, 19, 18, 18, {'r'     , 'R'     ,  0      }},
  {102, 19, 18, 18, {'t'     , 'T'     ,  0      }},
  {121, 19, 18, 18, {'y'     , 'Y'     ,  0      }},
  {140, 19, 18, 18, {'u'     , 'U'     ,  0      }},
  {159, 19, 18, 18, {'i'     , 'I'     ,  0      }},
  {178, 19, 18, 18, {'o'     , 'O'     ,  0      }},
  {197, 19, 18, 18, {'p'     , 'P'     ,  0      }},
  {216, 19, 18, 18, {'{'     , '['     ,  0      }},
  {235, 19, 18, 18, {'}'     , ']'     ,  0      }},
  {254, 19, 25, 18, {'|'     , '\\'    ,  0      }},

  {  0, 38, 32, 18, {K_CAPSL , K_CAPSL , K_CAPSL }},
  { 33, 38, 18, 18, {'a'     , 'A'     ,  0      }},
  { 52, 38, 18, 18, {'s'     , 'S'     ,  0      }},
  { 71, 38, 18, 18, {'d'     , 'D'     ,  0      }},
  { 90, 38, 18, 18, {'f'     , 'F'     ,  0      }},
  {109, 38, 18, 18, {'g'     , 'G'     ,  0      }},
  {128, 38, 18, 18, {'h'     , 'H'     ,  0      }},
  {147, 38, 18, 18, {'j'     , 'J'     ,  0      }},
  {166, 38, 18, 18, {'k'     , 'K'     ,  0      }},
  {185, 38, 18, 18, {'l'     , 'L'     ,  0      }},
  {204, 38, 18, 18, {':'     , ';'     ,  0      }},
  {223, 38, 18, 18, {'"'     , '\''    ,  0      }},
  {242, 38, 37, 18, {K_ENTER , K_ENTER , K_ENTER }},

  {  0, 57, 22, 18, {K_CAPS  , K_CAPS  , K_CAPS  }},
  { 23, 57, 18, 18, {'z'     , 'Z'     ,  0      }},
  { 42, 57, 18, 18, {'x'     , 'X'     ,  0      }},
  { 61, 57, 18, 18, {'c'     , 'C'     ,  0      }},
  { 80, 57, 18, 18, {'v'     , 'V'     ,  0      }},
  { 99, 57, 18, 18, {'b'     , 'B'     ,  0      }},
  {118, 57, 18, 18, {'n'     , 'N'     ,  0      }},
  {137, 57, 18, 18, {'m'     , 'M'     ,  0      }},
  {156, 57, 18, 18, {','     , '<'     ,  0      }},
  {175, 57, 18, 18, {'.'     , '>'     ,  0      }},
  {194, 57, 18, 18, {'/'     , '?'     ,  0      }},
  {213, 57, 36, 18, {K_CAPS  , K_CAPS  , K_CAPS  }},
  {250, 57, 29, 18, {K_ESC   , K_ESC   , K_ESC   }},

  {  0, 76, 18, 18, {K_CX    , K_CX    , K_CX    }},
  { 19, 76, 18, 18, {K_CC    , K_CC    , K_CC    }},
  { 38, 76, 18, 18, {K_CV    , K_CV    , K_CV    }},
  { 57, 76, 94, 18, {' '     , ' '     ,  0      }},

  { -1, -1,  0,  0, { 0      ,  0      ,  0      }} /*stub*/
};
static const keyboard_style_st keyboard_en_us_style = {
  279, 94,
  G_FONT_SMALL, G_FONT_SYMBOL
};



/**
 * keyboard_fr_fr
 * AZERTY (FR version) keyboard
 */
static const key_entry_st keyboard_fr_fr[KEY_MAX_COUNT] = {  /*KEY_MAX_COUNT: GCC does not support flexible array init...*/

  /* x   y   w   h   std       caps      altgr    */

  {  0,  0, 18, 18, {'²'     ,  0      ,  0      }},
  { 19,  0, 18, 18, {'&'     , '1'     ,  0      }},
  { 38,  0, 18, 18, {'é'     , '2'     , '~'     }},
  { 57,  0, 18, 18, {'"'     , '3'     , '#'     }},
  { 76,  0, 18, 18, {'\''    , '4'     , '{'     }},
  { 95,  0, 18, 18, {'('     , '5'     , '['     }},
  {114,  0, 18, 18, {'-'     , '6'     , '|'     }},
  {133,  0, 18, 18, {'è'     , '7'     , '`'     }},
  {152,  0, 18, 18, {'_'     , '8'     , '\\'    }},
  {171,  0, 18, 18, {'ç'     , '9'     , '^'     }},
  {190,  0, 18, 18, {'à'     , '0'     , '@'     }},
  {209,  0, 18, 18, {')'     , '°'     , ']'     }},
  {228,  0, 18, 18, {'='     , '+'     , '}'     }},
  {247,  0, 32, 18, {K_DELETE, K_DELETE, K_DELETE}},

  {  0, 19, 25, 18, {K_TAB   , K_TAB   , K_TAB   }},
  { 26, 19, 18, 18, {'a'     , 'A'     , 'â'     }},
  { 45, 19, 18, 18, {'z'     , 'Z'     , 'ä'     }},
  { 64, 19, 18, 18, {'e'     , 'E'     , 'Â'     }},
  { 83, 19, 18, 18, {'r'     , 'R'     , 'Ä'     }},
  {102, 19, 18, 18, {'t'     , 'T'     , 'ê'     }},
  {121, 19, 18, 18, {'y'     , 'Y'     , 'ë'     }},
  {140, 19, 18, 18, {'u'     , 'U'     , 'Ê'     }},
  {159, 19, 18, 18, {'i'     , 'I'     , 'Ë'     }},
  {178, 19, 18, 18, {'o'     , 'O'     , 'î'     }},
  {197, 19, 18, 18, {'p'     , 'P'     , 'ï'     }},
  {216, 19, 18, 18, {'^'     , '¨'     ,  0      }},
  {235, 19, 18, 18, {'$'     , '£'     , '¤'     }},
  {254, 19, 25, 18, {K_ENTER , K_ENTER , K_ENTER }},

  {  0, 38, 32, 18, {K_CAPSL , K_CAPSL , K_CAPSL }},
  { 33, 38, 18, 18, {'q'     , 'Q'     , 'Î'     }},
  { 52, 38, 18, 18, {'s'     , 'S'     , 'Ï'     }},
  { 71, 38, 18, 18, {'d'     , 'D'     , 'ô'     }},
  { 90, 38, 18, 18, {'f'     , 'F'     , 'ö'     }},
  {109, 38, 18, 18, {'g'     , 'G'     , 'Ô'     }},
  {128, 38, 18, 18, {'h'     , 'H'     , 'Ö'     }},
  {147, 38, 18, 18, {'j'     , 'J'     , 'û'     }},
  {166, 38, 18, 18, {'k'     , 'K'     , 'ü'     }},
  {185, 38, 18, 18, {'l'     , 'L'     , 'Û'     }},
  {204, 38, 18, 18, {'m'     , 'M'     , 'Ü'     }},
  {223, 38, 18, 18, {'ù'     , '%'     , 'ÿ'     }},
  {242, 38, 18, 18, {'*'     , 'µ'     ,  0      }},
  {261, 38, 18, 18, {K_ESC   , K_ESC   , K_ESC   }},

  {  0, 57, 22, 18, {K_CAPS  , K_CAPS  , K_CAPS  }},
  { 23, 57, 18, 18, {'<'     , '>'     ,  0      }},
  { 42, 57, 18, 18, {'w'     , 'W'     ,  0      }},
  { 61, 57, 18, 18, {'x'     , 'X'     ,  0      }},
  { 80, 57, 18, 18, {'c'     , 'C'     ,  0      }},
  { 99, 57, 18, 18, {'v'     , 'V'     ,  0      }},
  {118, 57, 18, 18, {'b'     , 'B'     ,  0      }},
  {137, 57, 18, 18, {'n'     , 'N'     ,  0      }},
  {156, 57, 18, 18, {','     , '?'     ,  0      }},
  {175, 57, 18, 18, {';'     , '.'     ,  0      }},
  {194, 57, 18, 18, {':'     , '/'     ,  0      }},
  {213, 57, 18, 18, {'!'     , '§'     ,  0      }},
  {232, 57, 47, 18, {K_CAPS  , K_CAPS  , K_CAPS  }},

  {  0, 76, 18, 18, {K_CX    , K_CX    , K_CX    }},
  { 19, 76, 18, 18, {K_CC    , K_CC    , K_CC    }},
  { 38, 76, 18, 18, {K_CV    , K_CV    , K_CV    }},
  { 57, 76, 94, 18, {' '     , ' '     ,  0      }},
  {152, 76, 30, 18, {K_ALTGR , K_ALTGR , K_ALTGR }},

  { -1, -1,  0,  0, { 0      ,  0      ,  0      }} /*stub*/
};
static const keyboard_style_st keyboard_fr_fr_style = {
  279, 94,
  G_FONT_SMALL, G_FONT_SYMBOL
};



/**
 * keyboard_num
 * NUM keyboard
 */
static const key_entry_st keyboard_num[KEY_MAX_COUNT] = {  /*KEY_MAX_COUNT: GCC does not support flexible array init...*/

  /* x   y   w   h   std       caps      altgr    */
  {  0,  0, 26, 26, {'7'     ,  0      ,  0      }},
  { 27,  0, 26, 26, {'8'     ,  0      ,  0      }},
  { 54,  0, 26, 26, {'9'     ,  0      ,  0      }},
  { 81,  0, 26, 26, {K_TAB   ,  0      ,  0      }},

  {  0, 27, 26, 26, {'4'     ,  0      ,  0      }},
  { 27, 27, 26, 26, {'5'     ,  0      ,  0      }},
  { 54, 27, 26, 26, {'6'     ,  0      ,  0      }},
  { 81, 27, 26, 26, {K_DELETE,  0      ,  0      }},

  {  0, 54, 26, 26, {'1'     ,  0      ,  0      }},
  { 27, 54, 26, 26, {'2'     ,  0      ,  0      }},
  { 54, 54, 26, 26, {'3'     ,  0      ,  0      }},
  { 81, 54, 26, 26, {K_ESC   ,  0      ,  0      }},

  {  0, 81, 26, 26, {'0'     ,  0      ,  0      }},
  { 27, 81, 26, 26, {'.'     ,  0      ,  0      }},
  { 54, 81, 26, 26, {'-'     ,  0      ,  0      }},
  { 81, 81, 26, 26, {K_ENTER ,  0      ,  0      }},

  { -1, -1,  0,  0, { 0      ,  0      ,  0      }} /*stub*/
};
static const keyboard_style_st keyboard_num_style = {
  107, 107,
  G_FONT_BIG, G_FONT_SYMBOL
};


/**
 * array of pointer to the above keyboards mapping & styles
 */
const key_entry_st *arKeyboard[KEYBOARD_TYPE_COUNT] = {
  keyboard_en_us,
  keyboard_fr_fr,
  keyboard_num
};
const keyboard_style_st *arKeyboardStyle[KEYBOARD_TYPE_COUNT] = {
  &keyboard_en_us_style,
  &keyboard_fr_fr_style,
  &keyboard_num_style
};
