/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* Refer to 'C32 Configuration Settings' under the Help > Contents            */
/* > C32 Toolchain in MPLAB X IDE for available PIC32 Configurations.  For    */
/* additional information about what the hardware configurations mean in      */
/* terms of device operation, refer to the device datasheet 'Special Features'*/
/* chapter.                                                                   */
/*                                                                            */
/******************************************************************************/

/* Fill in your configuration bits here.  The general style is shown below.
The Debug Configuration bit is handline by MPLAB and should not be embedded
in the configuration macro.*/

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */

/* TODO Fill in your configuration bits here.  The general style is below:    */
#pragma config FSRSSEL = PRIORITY_7     /*SRS Select (SRS Priority 7) */
#pragma config FMIIEN = OFF             /*Ethernet RMII/MII Enable (MII Enabled)*/
#pragma config FETHIO = OFF             /*Ethernet I/O Pin Select (Default Ethernet I/O)*/
#pragma config FCANIO = OFF             /*CAN I/O Pin Select (Default CAN I/O)*/
#pragma config FUSBIDIO = OFF           /*USB USID Selection (Controlled by Port Function)*/
#pragma config FVBUSONIO = OFF          /*USB VBUS ON Selection (Controlled by Port Function)*/
// DEVCFG2
#pragma config FPLLIDIV = DIV_2         /*PLL Input Divider (2x Divider)*/
#pragma config FPLLMUL = MUL_20         /*PLL Multiplier (20x Multiplier)*/
#pragma config FPLLODIV = DIV_1         /*System PLL Output Clock Divider (PLL Divide by 1)*/
#pragma config UPLLIDIV = DIV_2         /*USB PLL Input Divider (2x Divider)*/
#pragma config UPLLEN = OFF             /*USB PLL Enable (Disabled and Bypassed)*/
// DEVCFG1
#pragma config FNOSC = FRCPLL           /*Oscillator Selection Bits (Fast RC Osc with PLL)*/
#pragma config FSOSCEN = OFF            /*Secondary Oscillator Enable (Disabled)*/
#pragma config IESO = OFF               /*Internal/External Switch Over (Disabled)*/
#pragma config POSCMOD = OFF            /*Primary Oscillator Configuration (crystal) HS*/
#pragma config OSCIOFNC = OFF           /*CLKO Output Signal Active on the OSCO Pin (Disabled)*/
#pragma config FPBDIV = DIV_1           /*Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)*/
#pragma config FCKSM = CSDCMD           /*Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)*/
#pragma config WDTPS = PS1048576        /*Watchdog Timer Postscaler (1:1048576)*/
#pragma config FWDTEN = OFF             /*Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))*/
// DEVCFG0
#pragma config DEBUG = OFF              /*Background Debugger Enable (Debugger is disabled)*/
#pragma config ICESEL = ICS_PGx1        /*ICE/ICD Comm Channel Select (ICE EMUC1/EMUD1 pins shared with PGC1/PGD1)*/
#pragma config PWP = OFF                /*Program Flash Write Protect (Disable)*/
#pragma config BWP = OFF                /*Boot Flash Write Protect bit (Protection Disabled)*/
#pragma config CP = OFF                 /*Code Protect (Protection Disabled)*/
