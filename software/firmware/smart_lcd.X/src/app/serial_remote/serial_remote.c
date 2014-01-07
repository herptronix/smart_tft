/**
 * @file serial_remote.c
 * @brief serial remote (slave side)
 * @author Duboisset Philippe
 * @version 0.1b
 * @date (yyyy-mm-dd) 2013-11-23
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
#include "serial_common.h"
#include "opList.h"
#include "p2d.h"
#include "gui_obj.h"
#include "gui_w.h"


#ifdef SMART_TFT_SLAVE_MODE

/**
 * global variable
 */
const char *EXTRACT_ERROR_MSG = "RXGet error; this error appears with very long messages (>5KB) or inconsistant messages";

/**
 * Local functions
 */
static void DisplayWaitMsg(void);


/**
 * @function SerialRemoteTask
 * @brief serial remote task; called at each software cycles, from main() through pCurrentTask pointer
 * @param none
 * @return none
 */
void SerialRemoteTask(void) {

  static bool bInitialized = false;
  static uint8_t seqId = 0;
  char str[50];
  int8_t res;
  uint8_t opCode;

  /*init*/
  if(bInitialized == false) {
    UartConfigure(UART_SPEED);
    RxInit();
    seqId = 0;
    DisplayWaitMsg();
    bInitialized = true;
  }

  /*runtime*/
  else {

    /*message from master?*/
    if(RxIsMsgReceived()) {

      /*extract the sequence number*/
      seqId = RxGetU8();

      /*create an answer message & echo the sequence number*/
      TxMsgStart();
      TxMsgPut(seqId);

      /*parse received message*/
      res = 0;
      while(RxIsEmpty() == false && res == 0) {

        /*get the op code*/
        opCode = RxGetU8();

        /*execute the function corresponding to the op code*/
        if(RxStatus() == 0 && opCode < _S_NB_OP) {
          if(opList[opCode] != NULL) res = opList[opCode]();
        }
        else {
          sprintf(str, "unknown op code: %d", opCode);
          Error(str);
          res = -1;
        }

      }

      /*return result to the master*/
      if(res < 0) {
        TxMsgPutByte(0xFF);   /*error*/
        pCurrentTask = NULL;  /*self kill*/
      }
      else {
        TxMsgPutByte(0);      /*success*/
      }

      /*send the answer*/
      TxMsgStop();

      /*acq RX & wait for a new message*/
      RxAck();
    }
  }
}


/**
 * @function ErrorMsg
 * @brief Display an error message, called by R_P2D / R_GUI / R_MEM
 * @param const char *file: file name
 * @param const char *function: function name
 * @param uint16_t line: current line
 * @param const char *msg: error message
 * @return none
 */
void ErrorMsg(const char *file, const char *function, uint16_t line, const char *msg) {

  rect_st rec;
  #define STR_BUFF 200
  char str[STR_BUFF];

  GUI_ClearAll();

  SetFont(G_FONT_BOLD);
  SetColor(G_COL_TEXT, COLOR_RED);
  rec = GUI_Rect(10, 10, 300, 20);
  GUI_W_TextAdd(&rec, "Critical error");
  SetFont(G_FONT_DEFAULT);
  SetColor(G_COL_TEXT, COLOR_BLACK);

  rec = GUI_Rect(10, 30, 300, 50);
  snprintf(str, STR_BUFF, "In function <%s> in file <%s> at line <%d>", file, function, line);
  GUI_W_TextAdd(&rec, str);

  rec = GUI_Rect(10, 90, 300, 80);
  GUI_W_TextAdd(&rec, msg);

  /*no widgets will be added after calling this function; R_P2D_xxx or whatever
  will return -1, breaking the parsing loop of SerialRemoteTask()*/
}


/**
 * @function DisplayWaitMsg
 * @brief Display the waiting msg, at startup
 * @param none
 * @return none
 */
static void DisplayWaitMsg(void) {
  rect_st rec = {10, 10, 300, 220};
  GUI_ClearAll();
  #if UART_SPEED != 1000000
    #warning "plz correct string"
  #endif
  GUI_W_TextAdd(&rec, "Waiting message from UART (1Mbaud, 8N1)...");
}

#endif
