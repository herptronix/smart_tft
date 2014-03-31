/**
 * @file sprite_converter.c
 * @brief sprite converter
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-01
 *
 * @detail:
 *   convert a 256 colors (or less) picture in a .c file. Supported format: bmp, jpg, png...
 *   If your picture has more than 256 colors, use <The Gimp> to palletize it
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

#include <windows.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>


/**
 * For now, only the 8BPP mode is handled -> 256 different colors
 */
#define NB_MAX_COL 256

/**
 * Local variables
 */
static uint32_t colors[NB_MAX_COL];   /*store the different colors found in the picture (std 32bits AARRGGBB mode)*/
static uint32_t nbCol;                /*number of different colors of the picture*/
static SDL_Surface *ptrScreen = NULL; /*pointer to the screen surface -- SDL specific, don't touch*/

/**
 * Private functions
 */
static void DisplayUsage(const char *execName);
static void DisplayInit(void);
static uint32_t GetPx(const SDL_Surface *surface, uint16_t x, uint16_t y);
static void SaveImg(const char *str, uint16_t x, uint16_t y);


/**
 * @function main
 * @brief entry point
 * @param <std context>
 * @return --
 */
int main(int argc, char** argv) {


  if(argc != 4) {
    DisplayUsage(argv[0]);
  }
  else {
    DisplayInit();
    SaveImg(argv[1], (uint16_t)atoi(argv[2]), (uint16_t)atoi(argv[3]));
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
  printf("\nusage: %s imageFile pixelColorKeyX pixelColorKeyY", execName);
  printf("\nwhere:");
  printf("\n  <imageFile> is the image file name + extension");
  printf("\n  <pixelColorKeyX> is X coordinate of the pixel that defines the color key");
  printf("\n  <pixelColorKeyY> is Y coordinate of the pixel that defines the color key");
  printf("\ne.g.: %s myPicture.png 0 0", execName);
}


/**
 * @function FindColor
 * @brief search the #id of a specific color
 * @param uint32_t color: 32 bits color
 * @return #id (0 to nbCol-1) if found, -1 otherwise
 */
static int16_t FindColor(uint32_t color) {

  int16_t ii, res = -1;

  for(ii = 0; ii < nbCol && res == -1; ii++) {
    if(colors[ii] == color) res = ii;
  }
  return res;
}


/**
 * @function AddColor
 * @brief store (if not already stored) a color
 * @param uint32_t color: 32 bits color
 * @return 0 (stored / already stored), -1 error (cannot store anymore)
 */
static int16_t AddColor(uint32_t color) {

  int16_t id, res = -1;

  id = FindColor(color);

  /*current color is not already stored?*/
  if(id < 0) {

    /*try to store it*/
    if(nbCol < NB_MAX_COL) {
      colors[nbCol] = color;
      nbCol++;
      res = 0;
    }
  }

  /*already stored*/
  else {
    res = 0;
  }

  return res;
}


/**
 * @function CreateLut
 * @brief parse the image, store all the colors used
 * @param const SDL_Surface *img: pointer to the image
 * @param uint16_t xKey, yKey: coord of the pixel to use for color key (transparency)
 * @return 0 success, -1 error
 */
static int16_t CreateLut(const SDL_Surface *img, uint16_t xKey, uint16_t yKey) {

  int16_t x, y, err = 0, res = -1;
  nbCol = 0;

  if(xKey < img->w && yKey < img->h) {

    /*store the color key first*/
    err = AddColor(GetPx(img, xKey, yKey));

    /*then, for each horizontal line*/
    for(y = 0; y < img->h && err == 0; y++) {

      /*for each pixel of the current line*/
      for(x = 0; x < img->w && err == 0; x++) {

        /*store (if not already stored) the pixel color*/
        err = AddColor(GetPx(img, x, y));
      }
    }

    if(err == 0) res = 0;
  }
  else {
    printf("\nCreateLut: error: coordinates out of picture.");
  }

  return res;
}


/**
 * @function SaveLut
 * @brief write the different stored colors in the output file
 * @param FILE *file: pointer to the output file
 * @return 0 success, -1 error
 */
int16_t SaveLut(FILE *file) {

  int16_t ii, res = -1;
  char car;

  do {

    /*source code: lut declaration*/
    res = fprintf(file, "\nconst uint8_t lut_file[] = {");
    if(res < 0) break;

    /*source code: number of colors contained in the lut*/
    res = fprintf(file, "\n  0x%02X, 0x%02X, /*Number of colors*/\n", nbCol >> 8, nbCol & 0x00FF);
    if(res < 0) break;

    for(ii = 0; ii < nbCol && res >= 0; ii++) {

      /*choose the end-of-line glyph*/
      /*if the current color is not the last one, put a ','*/
      if(ii != nbCol - 1) {
        car = ',';
      }
      /*otherwise, nothing will be put after this line, so don't put a ','*/
      else {
        car = ' ';
      }

      /*source code: one color entry*/
      res = fprintf(file, "\n  0x%02X, 0x%02X, 0x%02X%c",
                        (colors[ii] >> 16) & 0xFF,    /*red*/
                          (colors[ii] >> 8) & 0xFF,   /*green*/
                            colors[ii]       & 0xFF,  /*blue*/
                             car);                    /*end of line*/
    }
    if(res < 0) break;

    /*source code: end of lut declaration*/
    res = fprintf(file, "\n};\n");

  } while(0);

  /*normalize return value*/
  if(res >= 0) {
    res = 0;
  }
  else {
    res = -1;
  }

  return res;
}


/**
 * @function SaveSprite
 * @brief fills the .c file
 * @param FILE *file: pointer to the output file
 * @param const SDL_Surface *img: sdl surface containing the image
 * @return none
 */
static void SaveSprite(FILE *file, const SDL_Surface *img) {

  uint16_t x, y, cnt;
  char car;

  fprintf(file, "\nconst uint8_t sprite_file[] = {\n");
  fprintf(file, "\n  %d, /*bpp*/", 8);
  fprintf(file, "\n  0x%02X, 0x%02X, /*width*/", img->w >> 8, img->w & 0xFF);
  fprintf(file, "\n  0x%02X, 0x%02X, /*height*/\n", img->h >> 8, img->h & 0xFF);

  fprintf(file, "\n  /*Sprite raw*/\n");
  cnt = 0;
  for(y = 0; y < img->h; y++) {
    for(x = 0; x < img->w; x++) {
      if(cnt % 20 == 0) fprintf(file, "\n  ");
      car = (y == img->h - 1 && x == img->w - 1)? ' ': ',';
      fprintf(file, "0x%02X%c ", FindColor(GetPx(img, x, y)), car);
      cnt++;
    }
  }

  fprintf(file, "\n};\n");
}


/**
 * @function SaveImg
 * @brief create the .c file
 * @param const char *filename: output file name
 * @param uint16_t xKey, yKey: coord of the pixel to use for color key (transparency)
 * @return none
 */
static void SaveImg(const char *filename, uint16_t xKey, uint16_t yKey) {

  FILE *file = NULL;
  SDL_Surface *img;

  file = fopen("sprite.c", "w+");

  if(file != NULL) {

    /*load image in RAM, in a SDL_Surface struct*/
    img = IMG_Load(filename);

    if(img != NULL) {
      fprintf(file, "\n#include \"resources.h\"\n\n");

      /*create LUT*/
      if(CreateLut(img, xKey, yKey) == 0) {

        /*copy LUT to .c file*/
        SaveLut(file);

        /*copy img to .c file*/
        SaveSprite(file, img);
      }

      SDL_FreeSurface(img);
      fclose(file);
    }
    else {
      printf("\n error: <%s> not found / not supported", filename);
    }
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
}
