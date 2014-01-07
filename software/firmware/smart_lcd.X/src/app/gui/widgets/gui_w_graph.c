/**
 * @file gui_w_graph.c
 * @brief graph implementation
 * @author Duboisset Philippe
 * @version 0.2b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13  : initial version
 *  0.2b  2013-08-27  : Add grid
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

#include "gui_w_graph.h"

/**
 * local functions
 */
static void GraphDraw(void *g_obj, void *obj);
static void GraphRefresh(void *g_obj, void *obj);
static void GridDisabled(void);
static void GridDot_h(void);
static void GridDot_v(void);
static void GridDot_hv(void);

/**
 * curve
 */
typedef struct curve_t {
  uint8_t *data;                    /*pointer to the samples; len = object width*/
  struct curve_t /*@null@*/ *next;  /*pointer to the next curve of the graph*/
  color_t color;                    /*color of the curve*/

  uint16_t posDisp;
  uint16_t posIns;
} curve_st;

/**
 * grid draw function
 */
typedef void (*pGridFunction) (void);

/**
 * graph
 */
typedef struct {
  curve_st *curve;        /*pointer to the first curve of the graph*/
  coord_t *lut;           /*internal lut used for display (value to coord_t translation)*/
  pGridFunction fGrid;    /*pointer to the grid draw function*/

  timer_t timer;          /*internal timer*/
  uint16_t refreshTime;   /*auto refresh time, in ms*/
  coord_t xt, yt;         /*xt & yt (will contain relative coordinates of the point touched into the graph*/

  color_t colBack;
  color_t colGrid;
} graph_st;

/**
 * local variables
 */
static const pGridFunction arGrid[_GRAPH_GRID_CNT] = {
  &GridDisabled,
  &GridDot_h,
  &GridDot_v,
  &GridDot_hv
};
static color_t colBack, colGrid;
static rect_st rec;
static uint16_t pxCnt;
static length_t hStep = 10, vStep = 10;


/**
 * @function GUI_W_GraphSetGridSpacing
 * @brief set the grid spacing
 * @param length_t h: horizontal spacing, in pixel (min = 2px)
 * @param length_t v: vertical spacing, in pixel (min = 2px)
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
void GUI_W_GraphSetGridSpacing(length_t h, length_t v) {
  if(h > 1) hStep = h;
  if(v > 1) vStep = v;
}


/**
 * @function GUI_W_GraphAdd
 * @brief add graph container
 * @param const rect_st *_rec: graph dimension
 * @param uint16_t refreshTime: refresh period, in ms
 * @return g_obj_st *: pointer to the associated generic object if succedeed, NULL if error.
 */
g_obj_st /*@null@*/ *GUI_W_GraphAdd(const rect_st *_rec, e_grid_type grid, uint16_t refreshTime) {

  g_obj_st *g_obj = NULL, *res = NULL;
  graph_st *graph = NULL;
  uint16_t cnt;
  int32_t i32;

  /*check parameters*/
  if(_rec != NULL && _rec->w > 2) {

    /*allocate a generic object*/
    g_obj = GUI_AddGenericObject();
    if(g_obj != NULL) {

      /*allocate & init the graph*/
      graph = salloc(sizeof(graph_st));
      if(graph != NULL) {

        graph->curve = NULL;
        graph->refreshTime = refreshTime;
        graph->timer = 0;
        graph->colBack = GetColor(G_COL_E_BACKGROUND);
        graph->colGrid = GetColor(G_COL_TEXT);

        if(grid >= _GRAPH_GRID_CNT) grid = GRAPH_GRID_DISABLED;
        graph->fGrid = arGrid[grid];

        /*allocate the display LUT; => 256 entries (8bits)*/
        graph->lut = salloc(sizeof(coord_t) * 256);
        if(graph->lut != NULL) {

          /*performs <value to coord> translation only one time, use LUT when displaying*/
          for(cnt = 0; cnt < 256; cnt++) {
            i32 = _rec->y + _rec->h - 1;
            i32 = i32 - (((int32_t)cnt * _rec->h) / 256);
            graph->lut[cnt] = (coord_t) i32;
          }

          /*linkage between generic obj & graph*/
          g_obj->rec = *_rec;
          g_obj->draw = GraphDraw;
          g_obj->task = GraphRefresh;
          g_obj->obj = graph;

          res = g_obj;
        }
      }
    }
  }
  return res;
}


/**
 * @function GUI_W_GraphAddCurveToGraph
 * @brief add a curve into a graph container; number of curve not limited
 * @param g_obj_st *obj: pointer to the graph container
 * @param uint8_t *data: pointer to the curve data
 * @param color_t color: color of the curve
 * @return int8_t: -1 error, >=0 success (return the id of the added curve)
 */
int8_t GUI_W_GraphAddCurveToGraph(g_obj_st /*@null@*/ *obj, uint8_t *data, color_t color) {

  int8_t res = -1;
  graph_st *graph = NULL;
  curve_st *curve = NULL, **seek = NULL;

  if(obj == NULL) obj = GUI_GetLastAddedObject();

  /*check parameters*/
  if(obj != NULL && obj->obj != NULL && obj->draw == GraphDraw) {

    /*allocate the curve*/
    curve = salloc(sizeof(curve_st));

    /*init the curve*/
    if(curve != NULL) {
      curve->data = data;
      curve->next = NULL;
      curve->color = color;
      curve->posDisp = 0;
      curve->posIns = 0;

      /*insert the curve in its corresponding graph*/
      graph = (graph_st *) obj->obj;
      seek = &(graph->curve);
      res = 0;
      while(*seek != NULL) {
        seek = &((*seek)->next);
        res++;
      }
      *seek = curve;
    }
  }

  return res;
}


/**
 * @function GUI_W_GraphAddSampleToCurve
 * @brief add a sample to the curve; by using this function, corresponding curve will be considered as a circular buffer
 * @param g_obj_st *obj: pointer to the graph container
 * @param uint8_t curveId: curve ID
 * @param uint8_t sample: new sample
 * @return none
 */
void GUI_W_GraphAddSampleToCurve(g_obj_st *obj, uint8_t curveId, uint8_t sample) {

  graph_st *graph = NULL;
  curve_st *curve = NULL;

  /*check parameters*/
  if(obj != NULL && obj->obj != NULL && obj->draw == GraphDraw) {

    graph = (graph_st *) obj->obj;
    curve = graph->curve;

    /*go to the corresponding curve*/
    while(curve != NULL && curveId > 0) {
      curve = curve->next;
      curveId--;
    }

    /*if this curve exists,*/
    if(curve != NULL) {

      /*insert the new sample*/
      curve->data[curve->posIns] = sample;

      /*update insertion & display point*/
      curve->posIns++;
      if(curve->posIns > obj->rec.w - 1) curve->posIns = 0;

      curve->posDisp = curve->posIns;
    }
  }
}


/**
 * @function GraphRefresh
 * @brief graph task; force refresh if timer has elapsed, read touch coords inside the graph
 * @param void *_g_obj: generic object
 * @param void *_obj: graph object
 * @return none
 */
static void GraphRefresh(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  graph_st *graph;
  coord_t x, y, xt, yt;

  if(_g_obj != NULL && _obj != NULL) {
    graph = (graph_st*) _obj;
    g_obj = (g_obj_st *) _g_obj;

    /*timer elapsed? refresh graph*/
    if(IsTimerElapsed(graph->timer)) {
      graph->timer = GetPeriodicTimeout(graph->refreshTime);
      GUI_ObjSetNeedRefresh(g_obj, true);
    }

    /*read xt & yt if pressed*/
    if(GUI_ObjIsPressed(g_obj) && GUI_ObjIsDisabled(g_obj) == false) {

      /*at this point, xt & yt are included in the object clip*/
      GUI_ReadTouchScreen(&xt, &yt);

      x = xt - g_obj->rec.x;
      if(x < 0) x = 0;  /*should not happen... robustness purpose*/
      else if(x > g_obj->rec.w) x = g_obj->rec.w;

      y = (coord_t) g_obj->rec.h - (yt - g_obj->rec.y);
      if(y < 0) y = 0;  /*should not happen... robustness purpose*/
      else if(y > g_obj->rec.h) y = g_obj->rec.h;
    }
    else {
      x = y = -1;
    }

    graph->xt = x;
    graph->yt = y;
  }
}


/**
 * @function GraphDraw
 * @brief graph draw function
 * @param void *_g_obj: generic object
 * @param void *_obj: graph object
 * @return none
 */
static void GraphDraw(void *_g_obj, void *_obj) {

  g_obj_st *g_obj;
  graph_st *graph;
  curve_st *curve;

  uint16_t p0, p1, lim;

  /*retreive generic & specific object*/
  if(_g_obj != NULL && _obj != NULL) {
    g_obj = (g_obj_st *) _g_obj;
    graph =  (graph_st*) _obj;

    colBack = graph->colBack;
    colGrid = graph->colGrid;

    /*P2D configuration*/
    P2D_SetDisplayMode(DISPLAY_SOLID);
    P2D_SetLineType(LINE_SOLID);
    P2D_SetColors(colBack, colBack);

    /*vertical "clean-up" line definition*/
    rec.x = g_obj->rec.x;
    rec.y = g_obj->rec.y;
    rec.w = 1;
    rec.h = g_obj->rec.h;

    lim = g_obj->rec.w - 1;

    /*for each vertical line*/
    for(pxCnt = 0; pxCnt < g_obj->rec.w - 1; pxCnt++) {

      /*clean-up current line by calling the grid function*/
      graph->fGrid();

      /*draw each curve*/
      curve = graph->curve;
      while(curve != NULL) {

        P2D_SetColor(curve->color);

        p0 = (curve->posDisp + pxCnt    ) % g_obj->rec.w;
        p1 = (curve->posDisp + pxCnt + 1) % g_obj->rec.w;
        P2D_Line(rec.x, graph->lut[ curve->data[p0] ], rec.x, graph->lut[ curve->data[p1] ]);

        /*4) next curve*/
        curve = curve->next;
      }

      rec.x++;
    }

    /*last line (always empty)*/
    graph->fGrid();
  }
}


/**
 * grids display functions
 */

/*no grid*/
static void GridDisabled(void) {
  P2D_SetColor(colBack);
  P2D_FillRect(&rec);
}

/*only horizontal grid*/
static void GridDot_h(void) {
  coord_t y;
  if(pxCnt % 2 == 0) {
    P2D_SetColor(colBack);
    P2D_FillRect(&rec);
    for(y = rec.y; y < rec.y + rec.h; y += vStep) P2D_SetPixel(rec.x, y, colGrid);
  }
  else {
    P2D_SetColor(colBack);
    P2D_FillRect(&rec);
  }
}

/*only vertical grid*/
static void GridDot_v(void) {
  if(pxCnt % vStep == 0) {
    P2D_SetColors(colGrid, colBack);
    P2D_SetLineType(LINE_DOT);
    P2D_Line(rec.x, rec.y, rec.x, rec.y + rec.h);
    P2D_SetLineType(LINE_SOLID);
  }
  else {
    P2D_SetColor(colBack);
    P2D_FillRect(&rec);
  }
}

/*horizontal & vertical grid*/
static void GridDot_hv(void) {

  coord_t y;

  if(pxCnt % hStep == 0) {
    P2D_SetColors(colGrid, colBack);
    P2D_SetLineType(LINE_DOT);
    P2D_Line(rec.x, rec.y, rec.x, rec.y + rec.h);
    P2D_SetLineType(LINE_SOLID);
  }
  else if(pxCnt % 2 == 0) {
    P2D_SetColor(colBack);
    P2D_FillRect(&rec);
    for(y = rec.y; y < rec.y + rec.h; y += vStep) P2D_SetPixel(rec.x, y, colGrid);
  }
  else {
    P2D_SetColor(colBack);
    P2D_FillRect(&rec);
  }
}
