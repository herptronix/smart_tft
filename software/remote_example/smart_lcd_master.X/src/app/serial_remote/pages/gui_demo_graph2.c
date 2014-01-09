/**
 * @file gui_demo_graph2.c
 * @brief multiple graphs plus grid demo (serialized, master side)
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

#include "gui_demo_graph2.h"
#include "resources.h"

/*graph dimension*/
#define GRAPH_W               141
#define GRAPH_H               51

/**
 * SSM description
 */
enum {

  OFFSET_START = 0,

  /*used to store the physical address (32bits) of rvalue widgets, for R_GUI_W_GraphAddSampleToCurve(). @4*/
  OFFSET_OBJ1 = OFFSET_START,
      _OFFSET_OBJ1, __OFFSET_OBJ1, ___OFFSET_OBJ1,
  OFFSET_OBJ2,
      _OFFSET_OBJ2, __OFFSET_OBJ2, ___OFFSET_OBJ2,
  OFFSET_OBJ3,
      _OFFSET_OBJ3, __OFFSET_OBJ3, ___OFFSET_OBJ3,

  OFFSET_GRAPH_1,
  OFFSET_GRAPH_2 = GRAPH_W + OFFSET_GRAPH_1,
  OFFSET_GRAPH_3 = GRAPH_W + OFFSET_GRAPH_2,
  OFFSET_GRAPH_4 = GRAPH_W + OFFSET_GRAPH_3,
  OFFSET_GRAPH_5 = GRAPH_W + OFFSET_GRAPH_4,
  OFFSET_GRAPH_6 = GRAPH_W + OFFSET_GRAPH_5,
  
  _MEM_SIZE
};


/**
 * Local variable
 */
static int16_t oldSample[3];

/**
 * Local functions
 */
static void Gui_DemoGraph2Read(void);
static void Gui_DemoGraph2Handler(void);


/**
 * @function Gui_DemoGraph2
 * @brief multiple graphs plus grid demo
 * @param none
 * @return none
 */
void Gui_DemoGraph2(void) {

  rect_st rec;

  Gui_DemoNewPage("Multiple Graphs + grid");

  /*clear memory*/
  R_MEM_Memset(OFFSET_START, _MEM_SIZE, 0);

  /*scrolled graphs*/
  rec = GUI_Rect(165, 20, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_H, 0);
  R_GUI_SaveLastObj(OFFSET_OBJ1);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_1, COLOR_RED);
  
  rec = GUI_Rect(165, 75, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_V, 0);
  R_GUI_SaveLastObj(OFFSET_OBJ2);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_2, COLOR_GREEN);
  
  rec = GUI_Rect(165, 130, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_HV, 0);
  R_GUI_SaveLastObj(OFFSET_OBJ3);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_3, COLOR_BLUE);
  

  /*random graphs*/
  rec = GUI_Rect(15, 20, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_H, 0);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_4, COLOR_RED);

  rec = GUI_Rect(15, 75, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_V, 0);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_5, COLOR_GREEN);

  rec = GUI_Rect(15, 130, GRAPH_W, GRAPH_H);
  R_GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_HV, 0);
  R_GUI_W_GraphAddCurveToGraph(OFFSET_GRAPH_6, COLOR_BLUE);

  R_GUI_SetTask(Gui_DemoGraph2Read);
}


/**
 * @function Gui_DemoGraph2Read
 * @brief Send a <read signal> request to the smart tft
 * @param none
 * @return none
 */
static void Gui_DemoGraph2Read(void) {
  static timer_t tmRefresh = 0;
  if(IsTimerElapsed(tmRefresh)) {
    tmRefresh = GetPeriodicTimeout(30);
    R_GUI_ReadSignal();
    R_GUI_SetTask(Gui_DemoGraph2Handler);
  }
}


/**
 * @function Gui_DemoGraph2Handler
 * @brief Gui_DemoGraph2 handler
 * @param signal_t sig: unused
 * @return none
 */
static void Gui_DemoGraph2Handler(void) {

  uint16_t ii, jj, offset;
  uint8_t sample, arr[GRAPH_W];

  signal_t sig = RxGetU16();

  if(sig == SIG_DEMO_MENU) {
    R_GUI_SetTask(Gui_Demo);
  }
  else {
  
    R_GUI_SetTask(Gui_DemoGraph2Read);
  
    /*3 scrolled graphs*/
    for(ii = 0; ii < 3; ii++) {
      oldSample[ii] += P2D_Rand(10) - 5;
      if(oldSample[ii] < 0) oldSample[ii] = 0;
      else if(oldSample[ii] > 255) oldSample[ii] = 255;
      
      /*yeahh, that's dirty...*/
      if(ii == 0) R_GUI_W_GraphAddSampleToCurve(OFFSET_OBJ1, 0, oldSample[ii]);
      else if(ii == 1) R_GUI_W_GraphAddSampleToCurve(OFFSET_OBJ2, 0, oldSample[ii]);
      else R_GUI_W_GraphAddSampleToCurve(OFFSET_OBJ3, 0, oldSample[ii]);
    }
    
    /*3 random graphs*/
    for(ii = 0; ii < 3; ii++) {
      for(jj = 0; jj < GRAPH_W; jj++) {
        if(jj == 0) sample = 127;
        else sample = arr[jj - 1] + P2D_Rand(10) - 5;
        arr[jj] = sample;
      }
      if(ii == 0) offset = OFFSET_GRAPH_4;
      else if(ii == 1) offset = OFFSET_GRAPH_5;
      else offset = OFFSET_GRAPH_6;
      
      R_MEM_WriteU8Arr(offset, GRAPH_W, arr);
    }
  }
}
