/**
 * @file gui_demo_graph2.c
 * @brief multiple graphs plus grid demo
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

#ifdef INCLUDE_GUI_DEMO

/*graph dimension*/
#define GRAPH_W               141
#define GRAPH_H               51

/*number of graph*/
#define NB_MAX_CURVE          6

/*widgets signal*/
#define SIG_ADD_CURVE         1
#define SIG_CHECKBOX_CIRCULAR 2
#define SIG_BTN_NEXT          3

/**
 * Local variable
 */
static uint16_t fps, frameCount;
static uint8_t wdtTrig, *data;
static g_obj_st *pGraph, *pGraphCirc1, *pGraphCirc2, *pGraphCirc3;
static int16_t oldSample[NB_MAX_CURVE];

/**
 * Local functions
 */
static void Gui_DemoGraph2Handler(signal_t sig);
static void WdtCallback(void);


/**
 * @function Gui_DemoGraph2
 * @brief multiple graphes plus grid demo
 * @param signal_t sig: unused
 * @return none
 */
void Gui_DemoGraph2(signal_t sig) {

  rect_st rec;
  int8_t res = -1, ii;

  /*init.*/
  frameCount = fps = 0;
  wdtTrig = 0;

  do {

    Gui_DemoNewPage("Multiple Graphs + grid");

    /*allocate memory for curves*/
    data = salloc( (uint16_t) NB_MAX_CURVE * GRAPH_W);
    if(data == NULL) break;
    gmemset(data, 127, (uint16_t) NB_MAX_CURVE * GRAPH_W);
    for(ii = 0; ii < NB_MAX_CURVE; ii++) oldSample[ii] = 127;

    /*create the graph*/
    rec = GUI_Rect(15, 20, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_H, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[0 * GRAPH_W], COLOR_RED);

    /*create the graph*/
    rec = GUI_Rect(165, 20, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_H, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[1 * GRAPH_W], COLOR_RED);
    pGraphCirc1 = pGraph;

    /*create the graph*/
    rec = GUI_Rect(15, 75, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_V, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[2 * GRAPH_W], COLOR_GREEN);

    /*create the graph*/
    rec = GUI_Rect(165, 75, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_V, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[3 * GRAPH_W], COLOR_GREEN);
    pGraphCirc2 = pGraph;

    /*create the graph*/
    rec = GUI_Rect(15, 130, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_HV, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[4 * GRAPH_W], COLOR_BLUE);

    /*create the graph*/
    rec = GUI_Rect(165, 130, GRAPH_W, GRAPH_H);
    pGraph = GUI_W_GraphAdd(&rec, GRAPH_GRID_DOT_HV, 0);
    if(pGraph == NULL) break;
    GUI_W_GraphAddCurveToGraph(pGraph, &data[5 * GRAPH_W], COLOR_BLUE);
    pGraphCirc3 = pGraph;

    /*FPS box*/
    rec = GUI_Rect(15, 188, 55, 20);
    if(GUI_W_ValueBoxAdd(&rec, &fps, BOX_T_UINT16, "%d fps") == NULL) break;

    res = 0;

  } while(0);


  if(res == 0) {
    /*done; go to handler*/
    GUI_SetUserTask(Gui_DemoGraph2Handler);
  }
  else {
    /*serious error, exit*/
    GUI_SetUserTask(Gui_Demo);
  }
}


/**
 * @function Gui_DemoGraph2Handler
 * @brief Gui_DemoGraph2 handler
 * @param signal_t sig: unused
 * @return none
 */
static void Gui_DemoGraph2Handler(signal_t sig) {

  uint16_t ii, jj;

  if(sig == SIG_DEMO_MENU) {
    GUI_SetUserTask(Gui_Demo);
  }
  else {

    for(ii = 0; ii < NB_MAX_CURVE; ii++) {

      /*normal graph: recompute all samples*/
      if(ii % 2 == 0) {
        for(jj = 0; jj < GRAPH_W; jj++) {
          oldSample[ii] += P2D_Rand(10) - 5;
          if(oldSample[ii] < 0) oldSample[ii] = 0;
          else if(oldSample[ii] > 255) oldSample[ii] = 255;
          data[ii * GRAPH_W + jj] = oldSample[ii];
        }
      }
      /*circular (~scrolled) graph: just add some samples*/
      else {
        for(jj = 0; jj < 1 /*number of samples to add*/; jj++) {
          oldSample[ii] += P2D_Rand(10) - 5;
          if(oldSample[ii] < 0) oldSample[ii] = 0;
          else if(oldSample[ii] > 255) oldSample[ii] = 255;

          /*yeahh, that's dirty...*/
          if(ii == 1) GUI_W_GraphAddSampleToCurve(pGraphCirc1, 0, oldSample[ii]);
          else if(ii == 3) GUI_W_GraphAddSampleToCurve(pGraphCirc2, 0, oldSample[ii]);
          else if(ii == 5) GUI_W_GraphAddSampleToCurve(pGraphCirc3, 0, oldSample[ii]);
        }
      }
    }

    /*update fps count*/
    frameCount++;
    if(wdtTrig == 0) {
      wdtTrig = 1;
      TicksSetWatchdog(WdtCallback, 1000);
    }
  }
}


/**
 * @function WdtCallback
 * @brief small callback function for computing FPS
 * @param none
 * @return none
 */
static void WdtCallback(void) {
  if(frameCount > 0) {
    fps = frameCount;
    frameCount = 0;
    wdtTrig = 0;
  }
}

#endif
