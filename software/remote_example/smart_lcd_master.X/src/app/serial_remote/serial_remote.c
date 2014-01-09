/**
 * @file serial_remote.c
 * @brief communication with the smart TFT (master side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-17
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

#include "serial_remote.h"
#include "timer.h"


#include "gui_demo.h"

/**
 * local variables
 */
typedef enum {TFT_INIT, TFT_WAIT_INIT, TFT_RUN_HANDLER, TFT_SEND_DATA, TFT_WAIT_ANSWER, TFT_ERROR} tft_fsm_e;
static tft_fsm_e fsm = TFT_INIT;
static uint8_t seqId = 0;
static timer_t msgTimeout;
static void (*pUsrHandler) (void) = NULL;
static void (*pUsrErrorHandler) (void) = NULL;


/**
 * local functions
 */
static void R_GUI_MsgStart(void);
static void R_GUI_MsgStop(void);


/**
 * @function SerialRemoteTask
 * @brief remote task; shall be called at each software cycle
 * @param none
 * @return none
 */
void SerialRemoteTask(void) {

  static bool bInitialized = false;

  if(bInitialized == false) {
    bInitialized = true;
    R_GUI_SetTask(Gui_Demo);
  }
  else {
    RemoteTask();
  }
}


/**
 * @function R_GUI_SetTask
 * @brief set the current user handler
 * @param void (*pFunc)(void): pointer to the user handler
 * @return none
 */
void R_GUI_SetTask(void (*pFunc)(void)) {
  pUsrHandler = pFunc;
  if(pUsrErrorHandler == NULL) R_GUI_SetErrorTask(pFunc);
}


/**
 * @function R_GUI_SetErrorTask
 * @brief set the user error handler
 * @param void (*pFunc)(void): pointer to the user error handler
 * @return none
 */
void R_GUI_SetErrorTask( void (*pFunc)(void)) {
  pUsrErrorHandler = pFunc;
}


/**
 * @function RemoteTask
 * @brief remote task; shall be called in main loop
 * @param none
 * @return none
 */
void RemoteTask(void) {

  switch(fsm) {

    /*init*/
    case TFT_INIT:
      UartConfigure(UART_SPEED);
      RxInit();
      fsm = TFT_WAIT_INIT;
      msgTimeout = GetTimeout(500);
      break;

    /*wait ~500ms for the TFT setup*/
    case TFT_WAIT_INIT:
      if(IsTimerElapsed(msgTimeout)) fsm = TFT_RUN_HANDLER;
      break;

    /*run the user handler*/
    case TFT_RUN_HANDLER:
      if(pUsrHandler != NULL) {
        R_GUI_MsgStart();
        pUsrHandler();
        R_GUI_MsgStop();
      }
      break;

    /*user handler has sent something to the TFT*/
    case TFT_SEND_DATA:
      msgTimeout = GetTimeout(500);
      fsm = TFT_WAIT_ANSWER;
      break;

    /*waiting answer from the previous request*/
    case TFT_WAIT_ANSWER:

      /*message received? launch the pUsrHandler & update te sequence number*/
      if(RxIsMsgReceived()) {
        if(RxGetU8() != seqId) fsm = TFT_ERROR;
        else fsm = TFT_RUN_HANDLER;
        seqId++;
      }
      /*timeout? launch the pUsrErrorHandler*/
      else if(IsTimerElapsed(msgTimeout)) {
        fsm = TFT_ERROR;
      }
      /*none, just wait*/
      else { }
      break;

    /*timeout error*/
    case TFT_ERROR:
      pUsrHandler = pUsrErrorHandler;
      fsm = TFT_RUN_HANDLER;
      break;

    default:
      fsm = TFT_INIT;
      break;
  }
}


/**
 * @function R_GUI_MsgStart
 * @brief starts a serial message; will send the start sequence ONLY if there if someting to send to the TFT
 * @param none
 * @return none
 */
static void R_GUI_MsgStart(void) {
  TxMsgStart(seqId);
}


/**
 * @function R_GUI_MsgStop
 * @brief stop a serial message, only if someting has been sent to the TFT
 * @param none
 * @return none
 */
static void R_GUI_MsgStop(void) {
  if(TxMsgStop() == true) {
    fsm = TFT_SEND_DATA;
    RxAck();  /*enable RX*/
  }
}
