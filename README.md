Smart TFT module
================

Open source (hardware & software) smart TFT module, based on:
 - Microchip PIC32MX795F512L microcontroller
 - 3.2" TFT 320x240, ILI9320/9325 controller
 - optional µSD card, for extra storage

This module has three operational modes:
 - slave: an other microcontroller sends commands to the TFT through UART (1M bauds, 8N1)
 - embedded app: the user includes its application directly into the PIC32
 - setup: setup menu, for touchscreen callibration, gamma adjustement & software demo; enter this mode by keeping the touchscreen pressed while powering on the 5V PSU.

Small video: https://www.youtube.com/watch?v=Nt97tPhJtdA
Some explanations (french only): http://herptronix.blogspot.fr/

## Pins & wirepads description ##
![pin_desription](https://raw.github.com/herptronix/smart_tft/master/documentation/pin_description.jpg)

## Software modules ##
![software_arch](https://raw.github.com/herptronix/smart_tft/master/documentation/software_arch.jpg)

## Screenshots ##
![screenshots](https://raw.github.com/herptronix/smart_tft/master/documentation/screenshots.jpg)

## Pickit3 ##
![pickit](https://raw.github.com/herptronix/smart_tft/master/documentation/pickit.jpg)

Status
======

Maintained

 - 2014/02/27 Add display orientation support (limited to BSP) & Minor bug fixes
 - 2014/02/01 Minor bug fixes (p2d_font.c / touchCalib.c / gui_w_usr_entry.c)
 - 2014/01/15 Add a quick & dirty (... and not yet completed) dev. guide
 - 2014/01/09 Add a serial remote example
 - 2013/12/29 Rev. A (improved P2D/GUI, FAT-FS support, setup menu, serial comm support)
 - 2013/08/11 First GUI version (not on git)
 - 2013/07/13 First P2D version (not on git)
