/**
 * @file gui_obj.h
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

#ifndef _gui_obj_h_
#define _gui_obj_h_

#include "gui.h"


typedef uint16_t signal_t;  /*signal emitted by widgets*/
typedef uint8_t state_t;    /*state of a widget (internal use)*/
typedef uint8_t group_t;    /*group of a widget*/
typedef enum {E_RELEASED, E_RELEASED_TO_PUSHED, E_PUSHED, E_PUSHED_TO_RELEASED, E_MAX_EVENT} event_e;
typedef void (*pObjFunc_t) (void *g_obj, void *obj);    /*function pointer used by widgets functions (internal)*/
typedef void (*pGuiUsrTask_t) (signal_t s);             /*user gui pages*/
typedef signal_t (*pGuiInternalTask_t) (signal_t s);    /*macro gui pages (internal)*/


/**
* @struct: g_obj_st
* @brief: generic object definition
*/
typedef struct g_obj_t {

  struct g_obj_t /*@null@*/ *next;  /*next generic object*/

  void *obj;                        /*physical object*/
  pObjFunc_t /*@null@*/ task;       /*task of the object; this one handles specific object refresh*/
  pObjFunc_t /*@null@*/ draw;       /*draw function of the object*/

  rect_st rec;                      /*absolute object window*/
  signal_t signals[E_MAX_EVENT];    /*signals table (one signal per possible event)*/
  state_t state;                    /*object state (disabled, hiden, focused, etc...)*/
  event_e event;                    /*user event (released, pushed, ...)*/
  group_t group;                    /*object group*/

} g_obj_st;

/**
 * @function GUI_Init
 * @brief Initialize the GUI; call me first !
 * @param none
 * @return none
 */
void GUI_Init(void);

/**
 * @function GUI_TopLayerOpen
 * @brief enable the top layer (store current context & object, start new context & object list)
 * @param pGuiInternalTask_t p: internal task which will be called in GUI_DrawObject
 * @return none
 */
void GUI_TopLayerOpen(pGuiInternalTask_t p);

/**
 * @function GUI_TopLayerClose
 * @brief close the top layer (delete all object contained in top layer, restore base layer context)
 * @param none
 * @return none
 */
void GUI_TopLayerClose(void);

/**
 * @function GUI_SetUserTask
 * @brief Define a new user task, which will be executed at the end of GUI_DrawObject()
 * @param pGuiUsrTask_t pFunction: new user task
 * @return none
 */
void GUI_SetUserTask(pGuiUsrTask_t pFunction);

/**
 * @function GUI_ClearAll
 * @brief delete all object
 * @param none
 * @return none
 */
void GUI_ClearAll(void);

/**
 * @function GUI_SetGroup
 * @brief Set the group value
 * @param group_t g: new group value
 * @return none
 */
void GUI_SetGroup(group_t g);

/**
 * @function GUI_SetSignal
 * @brief associate a signal to an object event
 * @param event_e event: event
 * @param signal_t signal: signal
 * @return none
 */
void GUI_SetSignal(event_e event, signal_t signal);

/**
 * @function GUI_ReadSignal
 * @brief return (if any) the signal raised by an object event which does not belong to the upper layer
 * @param none
 * @return signal_t
 */
signal_t GUI_ReadSignal(void);

/**
 * @function GUI_ReadLastSignal
 * @brief return (if any) the last non-null signal raised by an object event which does not belong to the upper layer, and clear it
 * @param none
 * @return signal_t
 */
signal_t GUI_ReadLastSignal(void);

/**
 * @function GUI_ReadTouchScreen
 * @brief return touch screen coord for the current cycle
 * @param coord_t *px, coord_t *py
 * @return none
 */
void GUI_ReadTouchScreen(coord_t /*@out@*/ /*@null@*/ *px, coord_t /*@out@*/ /*@null@*/ *py);

/**
 * @function GUI_DrawObjects
 * @brief handle all object (user event, refresh)
 * @param none
 * @return none
 */
void GUI_DrawObjects(void);

/**
 * @function GUI_GroupDisable
 * @brief disable or enable a group of object
 * @param group_t g: selected group
 * @param bool p: enable / disable
 * @return none
 */
void GUI_GroupDisable(group_t g, bool p);

/**
 * @function GUI_GroupNotify
 * @brief notify or not a group of object
 * @param group_t g: selected group
 * @param bool p: notified / not notified
 * @return none
 */
void GUI_GroupNotify(group_t g, bool p);

/**
 * @function GUI_GroupRefresh
 * @brief force refresh o group of object
 * @param group_t g: selected group
 * @param bool p
 * @return none
 */
void GUI_GroupRefresh(group_t g, bool p);

/**
 * @function GUI_ObjIsNotified
 * @brief return the flag <Notified> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsNotified(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetNotified
 * @brief set the flag <Notified> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetNotified(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsPressed
 * @brief return the flag <Pressed> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsPressed(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetPressed
 * @brief set the flag <Pressed> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetPressed(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsDisabled
 * @brief return the flag <Disabled> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsDisabled(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetDisabled
 * @brief set the flag <Disabled> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetDisabled(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsFocusable
 * @brief return the flag <Focusable> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsFocusable(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetFocusable
 * @brief set the flag <Focusable> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetFocusable(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsFocused
 * @brief return the flag <Focused> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsFocused(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetBlink
 * @brief set the flag <Blink> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetBlink(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsBlink
 * @brief return the flag <Blink> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsBlink(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetFocused
 * @brief set the flag <Focused> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetFocused(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsNeedRefresh
 * @brief return the flag <NeedRefresh> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsNeedRefresh(const g_obj_st /*@null@*/ *obj);

/**
 * @function GUI_ObjSetNeedRefresh
 * @brief set the flag <NeedRefresh> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetNeedRefresh(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjSetStatic
 * @brief set the flag <Static> of a generic object
 * @param const g_obj_st *obj: generic object
 * @param bool p: new flag value
 * @return none
 */
void GUI_ObjSetStatic(g_obj_st /*@null@*/ *obj, bool p);

/**
 * @function GUI_ObjIsStatic
 * @brief return the flag <Static> of a generic object
 * @param const g_obj_st *obj: generic object
 * @return bool
 */
bool GUI_ObjIsStatic(const g_obj_st /*@null@*/ *obj);


/** INTERNAL
 * @function GUI_AddGenericObject
 * @brief Allocate & initialize a new generic object
 * @param none
 * @return g_obj_st*: pointer to the object if success, NULL otherwise
 */
g_obj_st /*@null@*/ *GUI_AddGenericObject(void);

/**  INTERNAL
 * @function GUI_GetLastAddedObject
 * @brief return (if any) the pointer to the last added generic object
 * @param none
 * @return g_obj_st* : NULL of pointer to the last added generic object
 */
g_obj_st /*@null@*/ *GUI_GetLastAddedObject(void);

#endif
