/**
 * @file gui_obj.c
 * @brief generic object implementation
 * @author Duboisset Philippe
 * @version 0.4b
 * @date (yyyy-mm-dd)
 *  0.1b  2013-07-13: initial version
 *  0.2b  2013-08-20: implementation of base & top layer handling
 *  0.3b  2013-11-01: bug correction in HandleTouchEvent and implementation of touchscreen hysteresis
 *  0.4b  2013-11-23: add GUI_ReadLastSignal (for slave mode)
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
#include "gui_m.h"
#include "gui_w.h"

/**
 * Local defines
 */
#define OBJ_S_BLINK         (state_t) 0x0001
#define OBJ_S_NOTIFIED      (state_t) 0x0002
#define OBJ_S_PRESSED       (state_t) 0x0004
#define OBJ_S_DISABLED      (state_t) 0x0008
#define OBJ_S_FOCUSABLE     (state_t) 0x0010
#define OBJ_S_FOCUSED       (state_t) 0x0020
#define OBJ_S_NEED_REFRESH  (state_t) 0x0040
#define OBJ_S_STATIC        (state_t) 0x0080


/**
 * g_context_st
 */
typedef struct {
  g_obj_st /*@null@*/ *lastAddedObj;
  group_t group;
} g_context_st;


/**
 * Local variables
 */
static g_obj_st /*@null@*/ *headBase = NULL;                  /*head of linked list containing all generic objects in the base layer*/
static g_obj_st /*@null@*/ *lastAddedObj = NULL;              /*last added generic object*/
static g_obj_st /*@null@*/ *headTop = NULL;                   /*head of linked list containing all generic objects contained in the top layer*/
void *addrStart = NULL;                                       /*lower address usable by the GUI; graphic resources are allocated before this addr*/
static bool bTopLayerActive = false;                          /*top layer enable / disable*/
static group_t group = 0;                                     /*current group value*/
static signal_t signal = 0;                                   /*curent signal, coming from widgets of the active layer*/
static signal_t lastSignal = 0;                               /*last non-null signal, coming from widgets of the active layer*/
static timer_t tmrBlink = 0;                                  /*timer for notification blinkin*/
static bool bBlink = false;                                   /*notification blink state*/
static coord_t x, y;                                          /*touchscreen coords, taken at the begining of GUI_DrawObject*/
static pGuiUsrTask_t /*@null@*/ pUserTask = NULL;             /*pointer to current user handler*/
static pGuiInternalTask_t /*@null@*/ pInternalTask = NULL;    /*pointer to internal handler (e.g. keyboard handler)*/
static g_context_st savedContext;                             /*for switch between base/top layer*/

/**
 * Local functions
 */
static void HandleTouchEvent(coord_t x, coord_t y, g_obj_st *obj);
static void HandleSignal(const g_obj_st *obj);
static bool StateGet(const g_obj_st /*@null@*/ *obj, state_t state);
static void StateSet(g_obj_st /*@null@*/ *obj, state_t state, bool b);
static g_obj_st /*@null@*/ *GetObjectList(void);


/**
 * @function GUI_Init
 * @brief Initialize the GUI; call me first !
 * @param none
 * @return none
 */
void GUI_Init(void) {

  /*load graphic resources (color LUT for sprites)*/
  GraphInit();

  /*save the current stack address; all data before this address belongs to GraphInit*/
  addrStart = salloc(0);

  /*some macro need a specific init.*/
  GUI_M_KeyboardInit();

  /*delete all & clear screen*/
  //GUI_ClearAll(); /*no, the user does it manually*/
}


/**
 * @function GUI_TopLayerOpen
 * @brief enable the top layer (store current context & object, start new context & object list)
 * @param pGuiInternalTask_t p: internal task which will be called in GUI_DrawObject
 * @return none
 */
void GUI_TopLayerOpen(pGuiInternalTask_t p) {

  coord_t yl;

  if(bTopLayerActive == false) {

    /*save the base layer context*/
    savedContext.lastAddedObj = lastAddedObj;
    savedContext.group = group;

    /*make a fake alpha(128) on the whole screen*/
    P2D_SetClip(NULL);
    P2D_SetColor(0xFFFF);
    P2D_SetLineType(LINE_DOT);
    P2D_SetDisplayMode(DISPLAY_TRANSPARENT);
    for(yl = 0; yl < P2D_GetLcdHeight(); yl++) {
      P2D_Line(yl % 2, yl, P2D_GetLcdWidth() - yl % 2, yl);
    }
    P2D_SetLineType(LINE_SOLID);
    P2D_SetDisplayMode(DISPLAY_SOLID);

    /*new context*/
    headTop = NULL;
    lastAddedObj = NULL;
    group = 0;
    bTopLayerActive = true;
    pInternalTask = p;
  }
}


/**
 * @function GUI_TopLayerClose
 * @brief close the top layer (delete all object contained in top layer, restore base layer context)
 * @param none
 * @return none
 */
void GUI_TopLayerClose(void) {

  g_obj_st *ptr = NULL;

  if(bTopLayerActive == true) {

    /*free the memory area used by the top layer*/
    sfreeFrom(headTop);

    /*restore the base layer context*/
    lastAddedObj = savedContext.lastAddedObj;
    group = savedContext.group;
    bTopLayerActive = false;

    /*clear screen*/
    P2D_SetClip(NULL);
    P2D_SetColor(GetColor(G_COL_BACKGROUND));
    P2D_Clear();

    /*force refresh all object*/
    ptr = headBase;
    lastAddedObj = NULL;
    while(ptr != NULL) {
      GUI_ObjSetNeedRefresh(ptr, true);
      ptr = ptr->next;
    }

    pInternalTask = NULL;
  }
}


/**
 * @function GUI_SetUserTask
 * @brief Define a new user task, which will be executed at the end of GUI_DrawObject()
 * @param pGuiUsrTask_t pFunction: new user task
 * @return none
 */
void GUI_SetUserTask(pGuiUsrTask_t pFunction) {
  pUserTask = pFunction;
}


/**
 * @function GUI_AddGenericObject
 * @brief Allocate & initialize a new generic object
 * @param none
 * @return g_obj_st*: pointer to the object if success, NULL otherwise
 */
g_obj_st /*@null@*/ *GUI_AddGenericObject(void) {

  g_obj_st *obj = NULL;

  /*try to allocate memory for the new object*/
  obj = salloc(sizeof(g_obj_st));
  if(obj != NULL) {

    /*set default content for the new object*/
    gmemset(obj, 0, sizeof(g_obj_st));
    GUI_ObjSetNeedRefresh(obj, true);
    obj->group = group;

    /*insert object in the linked list (base or top layer)*/
    if(bTopLayerActive == false) {
      if(headBase == NULL) headBase = obj;
      else if(lastAddedObj != NULL) lastAddedObj->next = obj;
      else { /*cannot happen*/ }
    }
    else {
      if(headTop == NULL) headTop = obj;
      else if(lastAddedObj != NULL) lastAddedObj->next = obj;
      else { /*cannot happen*/ }
    }

    lastAddedObj = obj;
  }

  return obj;
}


/**
 * @function GUI_ClearAll
 * @brief delete all object
 * @param none
 * @return none
 */
void GUI_ClearAll(void) {

  /*delete all memory allocated to objects*/
  sfreeFrom(addrStart);

  /*reset local variables*/
  headBase = headTop = lastAddedObj = NULL;
  signal = lastSignal = 0;
  group = 0;
  tmrBlink = 0;
  bBlink = false;

  /*clear screen*/
  P2D_SetClip(NULL);
  P2D_SetColor(GetColor(G_COL_BACKGROUND));
  P2D_Clear();
}


/**
 * @function GUI_SetGroup
 * @brief Set the group value
 * @param group_t g: new group value
 * @return none
 */
void GUI_SetGroup(group_t g) {
  group = g;
}


/**
 * @function GUI_SetSignal
 * @brief associate a signal to an object event
 * @param event_e event: event
 * @param signal_t signal: signal
 * @return none
 */
void GUI_SetSignal(event_e event, signal_t signal) {
  if(lastAddedObj != NULL && event < E_MAX_EVENT) {
    lastAddedObj->signals[event] = signal;
  }
}


/**
 * @function GUI_ReadSignal
 * @brief return (if any) the signal raised by an object event which does not belong to the upper layer
 * @param none
 * @return signal_t
 */
signal_t GUI_ReadSignal(void) {
  signal_t sig = 0;
  if(bTopLayerActive == false) sig = signal;
  return sig;
}


/**
 * @function GUI_ReadLastSignal
 * @brief return (if any) the last non-null signal raised by an object event which does not belong to the upper layer, and clear it
 * @param none
 * @return signal_t
 */
signal_t GUI_ReadLastSignal(void) {
  signal_t sig = 0;
  if(bTopLayerActive == false && lastSignal != 0) {
    sig = lastSignal;
    lastSignal = 0;
  }
  return sig;
}


/**
 * @function GUI_GetLastAddedObject
 * @brief return (if any) the pointer to the last added generic object
 * @param none
 * @return g_obj_st* : NULL of pointer to the last added generic object
 */
g_obj_st /*@null@*/ *GUI_GetLastAddedObject(void) {
  return lastAddedObj;
}


/**
 * @function GUI_ReadTouchScreen
 * @brief return touch screen coord for the current cycle
 * @param coord_t *px, coord_t *py
 * @return none
 */
void GUI_ReadTouchScreen(coord_t /*@out@*/ /*@null@*/ *px, coord_t /*@out@*/ /*@null@*/ *py) {
  if(px != NULL) *px = x;
  if(py != NULL) *py = y;
}


/**
 * @function GUI_DrawObjects
 * @brief handle all object (user event, refresh)
 * @param none
 * @return none
 */
void GUI_DrawObjects(void) {

  g_obj_st *ptr = NULL;
  coord_t newX, newY;

  /*reset signal & read touch screen; only once for all object*/
  signal = 0;
  TouchScreenRead(&newX, &newY);

  /*small hysteresis to compensate touchscreen noise*/
  #define TOUCH_THRES_HYS 2
  if(newX < 0 || newY < 0) {
    x = y = -1;
  }
  else {

    if(x < 0 || y < 0) {
      x = newX;
      y = newY;
    }
    else if(P2D_Abs(newX - x) > TOUCH_THRES_HYS || P2D_Abs(newY - y) > TOUCH_THRES_HYS) {
      x = newX;
      y = newY;
    }
  }


  /*get the object list, according to the active layer*/
  ptr = GetObjectList();

  /*process notification blink*/
  if(IsTimerElapsed(tmrBlink)) {
    bBlink = !bBlink;
    tmrBlink = GetPeriodicTimeout(500);
    while(ptr != NULL) {
      GUI_ObjSetBlink(ptr, bBlink);
      ptr = ptr->next;
    }
  }

  /*process each generic object of the current layer*/
  while(ptr != NULL) {

    /*handle user interaction*/
    HandleTouchEvent(x, y, ptr);

    /*handle object signals*/
    HandleSignal(ptr);

    if(ptr->obj != NULL) {

      /*launch the object task, if any*/
      if(ptr->task != NULL) ptr->task(ptr, ptr->obj);

      /*redraw the object, only if needed*/
      if(GUI_ObjIsNeedRefresh(ptr) && ptr->draw != NULL) {
        P2D_SetClip(&(ptr->rec));
        ptr->draw(ptr, ptr->obj);
        GUI_ObjSetNeedRefresh(ptr, false);
      }
    }

    /*next object*/
    ptr = ptr->next;
  }

  /**
   * execute, if any, the top layer task
   * pInternalTask may close the top layer and return a signal;
   * when closing the top layer, pInternalTask becomes NULL
   * this signal will be given to the user at end of GUI_DrawObjects()
   */
  if(pInternalTask != NULL) signal = pInternalTask(signal);
  
  /**
   * Save the last non null signal (for slave remote)
   */
  if(signal != 0 && pInternalTask == NULL) {
    lastSignal = signal;
  }
  
  /**
   * execute the user task, if no internal task is running
   * DO NOT concate this condition with the previous one in a if/else statement !
   */
  if(pInternalTask == NULL) {
    if(pUserTask != NULL) pUserTask(signal);
  }
}


/**
 * @function GUI_GroupDisable
 * @brief disable or enable a group of object
 * @param group_t g: selected group
 * @param bool p: enable / disable
 * @return none
 */
void GUI_GroupDisable(group_t g, bool p) {
  g_obj_st *ptr = GetObjectList();
  while(ptr != NULL) {
    if(ptr->group == g) GUI_ObjSetDisabled(ptr, p);
    ptr = ptr->next;
  }
}


/**
 * @function GUI_GroupNotify
 * @brief notify or not a group of object
 * @param group_t g: selected group
 * @param bool p: notified / not notified
 * @return none
 */
void GUI_GroupNotify(group_t g, bool p) {
  g_obj_st *ptr = GetObjectList();
  while(ptr != NULL) {
    if(ptr->group == g) GUI_ObjSetNotified(ptr, p);
    ptr = ptr->next;
  }
}


/**
 * @function GUI_GroupRefresh
 * @brief force refresh o group of object
 * @param group_t g: selected group
 * @param bool p
 * @return none
 */
void GUI_GroupRefresh(group_t g, bool p) {
  g_obj_st *ptr = GetObjectList();
  while(ptr != NULL) {
    if(ptr->group == g) GUI_ObjSetNeedRefresh(ptr, p);
    ptr = ptr->next;
  }
}


/**
 * @function GUI_ObjIsNotified
 * @brief return the flag <Notified> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsNotified(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_NOTIFIED);
}


/**
 * @function GUI_ObjSetNotified
 * @brief set the flag <Notified> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetNotified(g_obj_st /*@null@*/ *obj, bool p) {
  if(obj == NULL) obj = lastAddedObj;
  GUI_ObjSetBlink(obj, p);  /*execute first !*/
  StateSet(obj, OBJ_S_NOTIFIED, p);
}


/**
 * @function GUI_ObjIsPressed
 * @brief return the flag <Pressed> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsPressed(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_PRESSED);
}


/**
 * @function GUI_ObjSetPressed
 * @brief set the flag <Pressed> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetPressed(g_obj_st /*@null@*/ *obj, bool p) {
  if(GUI_ObjIsPressed(obj) != p) {
    StateSet(obj, OBJ_S_PRESSED, p);
    if(GUI_ObjIsStatic(obj) == false) GUI_ObjSetNeedRefresh(obj, true);
  }
}


/**
 * @function GUI_ObjIsDisabled
 * @brief return the flag <Disabled> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsDisabled(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_DISABLED);
}


/**
 * @function GUI_ObjSetDisabled
 * @brief set the flag <Disabled> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetDisabled(g_obj_st /*@null@*/ *obj, bool p) {
  if(obj == NULL) obj = lastAddedObj;
  if(GUI_ObjIsDisabled(obj) != p) {
    StateSet(obj, OBJ_S_DISABLED, p);
    GUI_ObjSetNeedRefresh(obj, true);
  }
}


/**
 * @function GUI_ObjIsFocusable
 * @brief return the flag <Focusable> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsFocusable(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_FOCUSABLE);
}


/**
 * @function GUI_ObjSetFocusable
 * @brief set the flag <Focusable> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetFocusable(g_obj_st /*@null@*/ *obj, bool p) {
  if(obj == NULL) obj = lastAddedObj;
  StateSet(obj, OBJ_S_FOCUSABLE, p);
}


/**
 * @function GUI_ObjIsFocused
 * @brief return the flag <Focused> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsFocused(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_FOCUSED);
}


/**
 * @function GUI_ObjSetBlink
 * @brief set the flag <Blink> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetBlink(g_obj_st /*@null@*/ *obj, bool p) {
  if(GUI_ObjIsDisabled(obj) == false && GUI_ObjIsNotified(obj) && GUI_ObjIsBlink(obj) != p) {
    StateSet(obj, OBJ_S_BLINK, p);
    GUI_ObjSetNeedRefresh(obj, true);
  }
}


/**
 * @function GUI_ObjIsBlink
 * @brief return the flag <Blink> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsBlink(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_BLINK);
}


/**
 * @function GUI_ObjSetFocused
 * @brief set the flag <Focused> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetFocused(g_obj_st /*@null@*/ *obj, bool p) {

  g_obj_st *ptr;

  if(obj == NULL) obj = lastAddedObj;
  if(obj != NULL) {

    /*if focus == true, we shall check that the given object can receive focus */
    if(p == true)  {
      if(GUI_ObjIsFocusable(obj) && GUI_ObjIsDisabled(obj) == false && GUI_ObjIsFocused(obj) == false) {

        /*find & clear previously focused object*/
        ptr = GetObjectList();

        while(ptr != NULL) {
          if(GUI_ObjIsFocused(ptr)) {
            StateSet(ptr, OBJ_S_FOCUSED, false);
            GUI_ObjSetNeedRefresh(ptr, true);
          }
          ptr = ptr->next;
        }

        /*give focus to object*/
        StateSet(obj, OBJ_S_FOCUSED, true);
        GUI_ObjSetNeedRefresh(obj, true);
      }
    }
    else {
      if(GUI_ObjIsFocused(obj)) {
        StateSet(obj, OBJ_S_FOCUSED, false);
        GUI_ObjSetNeedRefresh(obj, true);
      }
    }
  }
}


/**
 * @function GUI_ObjIsNeedRefresh
 * @brief return the flag <NeedRefresh> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsNeedRefresh(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_NEED_REFRESH);
}


/**
 * @function GUI_ObjSetNeedRefresh
 * @brief set the flag <NeedRefresh> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetNeedRefresh(g_obj_st /*@null@*/ *obj, bool p) {
  if(obj == NULL) obj = lastAddedObj;
  StateSet(obj, OBJ_S_NEED_REFRESH, p);
}


/**
 * @function GUI_ObjSetStatic
 * @brief set the flag <Static> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetStatic(g_obj_st /*@null@*/ *obj, bool p) {
  StateSet(obj, OBJ_S_STATIC, p);
}


/**
 * @function GUI_ObjIsStatic
 * @brief return the flag <Static> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsStatic(const g_obj_st /*@null@*/ *obj) {
  return StateGet(obj, OBJ_S_STATIC);
}


/**
 * @function HandleTouchEvent
 * @brief handle user event
 * @param coord_t x, coord_t y: touchscreen input
 * @param g_obj_st *obj: object to handle
 * @return none
 */
static void HandleTouchEvent(coord_t x, coord_t y, g_obj_st *obj) {

  bool inClip, isTouch;

  isTouch = (x >= 0 && y >= 0) ? true: false;
  inClip = P2D_IsInClip( &(obj->rec), x, y);

  /* Compute the current event state of the object, depending of
   * the previous state and the touchscreen input */
  switch(obj->event) {
    case E_RELEASED:
      if(inClip) obj->event = E_RELEASED_TO_PUSHED;
      break;

    case E_RELEASED_TO_PUSHED:
      obj->event = E_PUSHED;
      break;

    case E_PUSHED:
      if(isTouch == false) obj->event = E_PUSHED_TO_RELEASED;
      else if(inClip == false) obj->event = E_RELEASED;
      break;

    case E_PUSHED_TO_RELEASED:
      obj->event = E_RELEASED;
      break;

    default:
      obj->event = E_RELEASED;
      break;
  }

  if(inClip) {
    GUI_ObjSetPressed(obj, true);
    GUI_ObjSetFocused(obj, true);
  }
  else {
    GUI_ObjSetPressed(obj, false);
  }
}


/**
 * @function HandleSignal
 * @brief handle generic object signals
 * @param const g_obj_st *obj: object to handle
 * @return none
 */
static void HandleSignal(const g_obj_st *obj) {

  /*signals are enabled only if the object is enabled*/
  if(GUI_ObjIsDisabled(obj) == false) {

    switch(obj->event) {

      case E_RELEASED_TO_PUSHED:
      case E_PUSHED:
      case E_PUSHED_TO_RELEASED:
      case E_RELEASED:  /*beware, this leads to signal flood*/
        if(obj->signals[obj->event] != 0) signal = obj->signals[obj->event];
        break;

      default:
        break;
    }
  }
}


/**
 * local utils functions
 */
static bool StateGet(const g_obj_st /*@null@*/ *obj, state_t state) {
  bool res = false;
  if(obj != NULL && (obj->state & state) != 0) res = true;
  return res;
}

static void StateSet(g_obj_st /*@null@*/ *obj, state_t state, bool p) {
  if(obj != NULL) {
    if(p == false) obj->state &= ~state;
    else           obj->state |= state;
  }
}

/**
 * @function GetObjectList
 * @brief return the active object list, according topLayer
 * @param none
 * @return object list
 */
static g_obj_st /*@null@*/ *GetObjectList(void) {
  g_obj_st *ptr;
  if(bTopLayerActive == false) ptr = headBase;
  else ptr = headTop;
  return ptr;
}
