/**
 * @file font_converter.c
 * @brief font converter; convert a font (.ttf) in a .c source file
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-01
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

#include <SDL.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <windows.h>

/**
 * Local variables
 */
static uint8_t bufEntry[500000];  /*store glyph entries*/
static uint32_t posEntry = 0;
static uint8_t bufRaw[500000];    /*store glyph raw*/
static uint32_t posRaw = 0;
static SDL_Surface *ptrScreen = NULL;

/**
 * Private functions
 */
static void DisplayUsage(const char *execName);
static void DisplayInit(void);
static uint32_t GetPx(const SDL_Surface *surface, uint16_t x, uint16_t y);
static uint16_t GetHeighFont(TTF_Font *ptrFont);
static void SavePseudoBlendedCar1Bpp(TTF_Font *ptrFont, uint16_t idCar);
static void SavePseudoBlendedCar4Bpp(TTF_Font *ptrFont, uint16_t idCar);
static void CopyToFile(FILE *file);
static void CreateFontFile(const char *fileIn, const char *fileOut, uint8_t bpp, uint8_t h, uint8_t minCar, uint8_t maxCar);


/**
 * @function main
 * @brief entry point
 * @param <std context>
 * @return --
 */
int main(int argc, char** argv) {

  if(argc != 7) {
    DisplayUsage(argv[0]);
  }
  else {
    DisplayInit();
    CreateFontFile(
      argv[1],        /*input .ttf file*/
      argv[6],        /*output .c file name*/
      atoi(argv[2]),  /*bpp (1 / 4)*/
      atoi(argv[3]),  /*font height (in pt, not px!)*/
      atoi(argv[4]),  /*min glyph #id*/
      atoi(argv[5])); /*max glyph #id*/
  }

  return 0;
}


/**
 * @function DisplayUsage
 * @brief help
 * @param const char *execName: program name
 * @return none
 */
static void DisplayUsage(const char *execName) {
  printf("\nusage: %s ttfFile bpp height min max outFile", execName);
  printf("\nwhere:");
  printf("\n  <ttfFile> is the input font file name + extension");
  printf("\n  <bpp> bit per pixel (4bpp supported, 1bpp experimental)");
  printf("\n  <height> font height, in pt (not px !)");
  printf("\n  <min> min glyph #id, ascii std (e.g. 32 eq 'from space')");
  printf("\n  <max> max glyph #id, ascii std (e.g. 90 eq 'to Z')");
  printf("\ne.g.: %s myFont.ttf 4 12 32 90 font12pt.c", execName);
}


/**
 * @function GetHeighFont
 * @brief return the font height, in pixels
 * @param TTF_Font *ptrFont
 * @return uint16_t: font height
 */
static uint16_t GetHeighFont(TTF_Font *ptrFont) {
  uint16_t hCar = 0;
  SDL_Color color = {255, 255, 255};
  SDL_Surface *surface = TTF_RenderText_Blended(ptrFont, "Mp", color);
  if(surface) {
    hCar = surface->h;
    SDL_FreeSurface(surface);
  }
  else {
    exit(1);
  }
  return hCar;
}


/**
 * @function SavePseudoBlendedCar1Bpp
 * @brief convert & save a 1BPP glyph in the RAM buffers
 * @param TTF_Font *ptrFont: SDL font
 * @param uint16_t idCar: ASCII #id
 * @return none
 */
static void SavePseudoBlendedCar1Bpp(TTF_Font *ptrFont, uint16_t idCar) {

  unsigned char str[2] = {0, 0};
  uint16_t x, y;
  uint32_t colorPx;
  SDL_Color color = {255, 255, 255};
  str[0] = idCar;

  /*generate the glyph*/
  SDL_Surface *surface = TTF_RenderText_Blended(ptrFont, (char*)str, color);

  if(surface) {

    /*add the glyph entry (width & address) in bufEntry[]*/
    bufEntry[posEntry++] = surface->w;
    bufEntry[posEntry++] = (posRaw >> 16) & 0xFF;
    bufEntry[posEntry++] = (posRaw >> 8) & 0xFF;
    bufEntry[posEntry++] = posRaw & 0xFF;

    char mask;
    unsigned char byte = 0;
    char posBit = 7;

    /*store pixels in bufRaw[]; 1 bit == 1 pixel*/
    for(y = 0; y < surface->h; y++) {
      for(x = 0; x < surface->w; x++) {

        colorPx = GetPx(surface, x, y);
        if(colorPx < 0x7F000000) mask = 0;
        else mask = 1;

        mask <<= posBit;
        byte |= mask;
        posBit--;

        /*store only when a byte is complete (8 pixels)*/
        if(posBit < 0) {
          posBit = 7;
          bufRaw[posRaw++] = byte;
          byte = 0;
        }
      }
    }

    /*store the last bits, if any*/
    if(posBit != 7) {
        bufRaw[posRaw++] = byte;
    }
    SDL_FreeSurface(surface);
  }
  else {
    /*nothing, the glyph does not exist in the specified font file*/
  }
}


/**
 * @function SavePseudoBlendedCar4Bpp
 * @brief convert & save a 4BPP glyph in the RAM buffers
 * @param TTF_Font *ptrFont: SDL font
 * @param uint16_t idCar: ASCII #id
 * @return none
 */
static void SavePseudoBlendedCar4Bpp(TTF_Font *ptrFont, uint16_t idCar) {

  unsigned char str[2] = {0, 0};
  uint16_t x, y;
  uint32_t colorPx;
  SDL_Color color = {255, 255, 255};
  str[0] = idCar;

  /*generate the glyph*/
  SDL_Surface *surface = TTF_RenderText_Blended(ptrFont, (char*)str, color);

  if(surface) {

    /*add the glyph entry (width & address) in bufEntry[]*/
    bufEntry[posEntry++] = surface->w;
    bufEntry[posEntry++] = (posRaw >> 16) & 0xFF;
    bufEntry[posEntry++] = (posRaw >> 8) & 0xFF;
    bufEntry[posEntry++] = posRaw & 0xFF;

    char mask;
    unsigned char byte = 0;
    char posBit = 4;

    /*store pixels in bufRaw[]; 4 bits == 1 pixel*/
    for(y = 0; y < surface->h; y++) {
      for(x = 0; x < surface->w; x++) {

        colorPx = GetPx(surface, x, y);
        if(colorPx < 0x08FFFFFF) mask = 0;
        else if(colorPx < 0x18FFFFFF) mask = 1;
        else if(colorPx < 0x28FFFFFF) mask = 2;
        else if(colorPx < 0x38FFFFFF) mask = 3;
        else if(colorPx < 0x48FFFFFF) mask = 4;
        else if(colorPx < 0x58FFFFFF) mask = 5;
        else if(colorPx < 0x68FFFFFF) mask = 6;
        else if(colorPx < 0x78FFFFFF) mask = 7;
        else if(colorPx < 0x88FFFFFF) mask = 8;
        else if(colorPx < 0x98FFFFFF) mask = 9;
        else if(colorPx < 0xA8FFFFFF) mask = 10;
        else if(colorPx < 0xB8FFFFFF) mask = 11;
        else if(colorPx < 0xC8FFFFFF) mask = 12;
        else if(colorPx < 0xD8FFFFFF) mask = 13;
        else if(colorPx < 0xE8FFFFFF) mask = 14;
        else mask = 15;

        mask <<= posBit;
        byte |= mask;
        posBit -= 4;

        /*store only when a byte is complete (8 pixels)*/
        if(posBit < 0) {
          posBit = 4;
          bufRaw[posRaw++] = byte;
          byte = 0;
        }
      }
    }

    /*store the last bits, if any*/
    if(posBit != 7) {
        bufRaw[posRaw++] = byte;
    }
    SDL_FreeSurface(surface);
  }
  else {
    /*nothing, the glyph does not exist in the specified font file*/
  }
}


/**
 * @function CopyToFile
 * @brief copy & format RAM buffer in a .c file
 * @param FILE *file: output file
 * @return none
 */
static void CopyToFile(FILE *file) {

  uint16_t cnt;

  fprintf(file, "  /*index table: glyph width, offset hl, lh, ll*/\n");
  for(cnt = 0; cnt < posEntry; cnt += 4) {
    fprintf(file, "  0x%02X, 0x%02X, 0x%02X, 0x%02X,\n", bufEntry[cnt], bufEntry[cnt+1], bufEntry[cnt+2], bufEntry[cnt+3]);
  }

  fprintf(file, "  /*glyph raw*/");
  for(cnt = 0; cnt < posRaw; cnt ++) {

    if(cnt % 20 == 0) fprintf(file, "\n  ");
    if(cnt == posRaw - 1) {
      fprintf(file, "0x%02X", bufRaw[cnt]);
    }
    else {
      fprintf(file, "0x%02X, ", bufRaw[cnt]);
    }
  }
}


/**
 * @function CreateFontFile
 * @brief font convertion, main process
 * @param const char *fileIn: input .ttf file
 * @param const char *fileOut: output .c file name
 * @param uint8_t bpp: bpp (1 / 4)
 * @param uint8_t h: font height (in pt, not px!)
 * @param uint8_t minCar: min glyph #id
 * @param uint8_t maxCar: max glyph #id
 * @return none
 */
static void CreateFontFile(const char *fileIn, const char *fileOut, uint8_t bpp, uint8_t h, uint8_t minCar, uint8_t maxCar) {

  FILE *file = NULL;
  TTF_Font *ptrFont = NULL;
  uint16_t idCar;

  /*open .ttf*/
  ptrFont = TTF_OpenFont(fileIn, h);

  if(ptrFont != NULL) {

    /*create output file*/
    file = fopen(fileOut, "w+");
    if(file != NULL) {

      /*write font header*/
      fprintf(file, "\n#include \"resources.h\"\n\n");
      fprintf(file, "const uint8_t font[] = {\n");
      fprintf(file, "  %d,  /*font type*/\n", bpp == 1? 1:2);
      fprintf(file, "  %d, /*first car ID*/\n", minCar);
      fprintf(file, "  %d, /*number of car*/\n", maxCar);
      fprintf(file, "  %d, /*font height*/\n", GetHeighFont(ptrFont));

      /*generate the font, in RAM*/
      for(idCar = minCar; idCar <= maxCar; idCar++) {
        if(bpp == 1) SavePseudoBlendedCar1Bpp(ptrFont, idCar);
        else SavePseudoBlendedCar4Bpp(ptrFont, idCar);
      }

      /*copy RAM content to output file*/
      CopyToFile(file);
      fprintf(file, "\n};\n");

      /*done*/
      fclose(file);
    }
    else {
      printf("\nError: cannot create <%s>", fileOut);
    }
  }
  else {
    printf("\nError: cannot open <%s>", fileIn);
  }
}


/**
 * @function GetPx
 * @brief return the pixel color (32bits AARRGGBB) of a given coord
 * @param const SDL_Surface *surface: input surface
 * @param uint16_t x, y: input coord
 * @return uint32_t pixel color (AARRGGBB)
 */
static uint32_t GetPx(const SDL_Surface *surface, uint16_t x, uint16_t y) {
  if(surface == NULL) return 0;
  return *((uint32_t*)(surface->pixels) + x + y * surface->w);
}


/**
 * @function DisplayInit
 * @brief init SDL lib
 * @param none
 * @return none
 */
static void DisplayInit(void) {

  if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    printf( "SDL Initialization failed: %s\n", SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit);
  SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=center");
  ptrScreen = SDL_SetVideoMode(320, 240, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(ptrScreen == NULL) {
    printf("Cannot rendering SDL window\n");
    exit(1);
  }

  if(TTF_Init() < 0) {
    printf("Cannot init TTF\n");
    exit(1);
  }
}
