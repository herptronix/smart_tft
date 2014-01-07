#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app/gui/macro/file_browser/gui_m_file_browser.c src/app/gui/macro/keyboard/gui_m_keyboard.c src/app/gui/macro/keyboard/gui_w_key.c src/app/gui/macro/keyboard/keymap.c src/app/gui/macro/list/gui_m_list.c src/app/gui/macro/popup/gui_m_popup.c src/app/gui/widgets/gui_w_button.c src/app/gui/widgets/gui_w_checkBox.c src/app/gui/widgets/gui_w_frame.c src/app/gui/widgets/gui_w_graph.c src/app/gui/widgets/gui_w_led.c src/app/gui/widgets/gui_w_radio.c src/app/gui/widgets/gui_w_slider.c src/app/gui/widgets/gui_w_tab.c src/app/gui/widgets/gui_w_text.c src/app/gui/widgets/gui_w_usr_entry.c src/app/gui/widgets/gui_w_valueBox.c src/app/gui/widgets/gui_w_rot_button.c src/app/gui/widgets/gui_w_rot_value.c src/app/gui/widgets/gui_w_list.c src/app/gui/widgets/gui_w_scroller.c src/app/gui/gui_graphics.c src/app/gui/gui_obj.c src/app/gui/gui_utils.c src/app/gui/gui_debug.c src/app/gui_demo/gui_demo.c src/app/gui_demo/gui_demo_button.c src/app/gui_demo/gui_demo_keyboard.c src/app/gui_demo/gui_demo_rbutton.c src/app/gui_demo/gui_demo_text.c src/app/gui_demo/gui_demo_valuebox.c src/app/gui_demo/gui_demo_graph1.c src/app/gui_demo/gui_demo_graph2.c src/app/gui_demo/gui_demo_list.c src/app/gui_demo/gui_demo_file_browser.c src/app/gui_demo/gui_demo_popup.c src/app/gui_demo/gui_demo_sd.c src/app/gui_demo/p2d_demo.c src/app/p2d/p2d_base.c src/app/p2d/p2d_buffer.c src/app/p2d/p2d_font.c src/app/p2d/p2d_lut.c src/app/p2d/p2d_sprite.c src/app/p2d/p2d_utils.c src/app/p2d/p2d_clip.c src/app/p2d/p2d_internal.c src/app/p2d/p2d_colors.c src/app/p2d/p2d_math.c src/app/p2d/p2d_geo_poly.c src/app/p2d/p2d_geo_circle.c src/app/p2d/p2d_geo_line.c src/app/resources/FontDigit_4bpp.c src/app/resources/FontSerif_4bpp_n.c src/app/resources/FontSerif_4bpp_b.c src/app/resources/FontSerif_4bpp_i.c src/app/resources/FontSymbol.c src/app/resources/sprite00.c src/app/resources/sprite01.c src/app/resources/sprite02.c src/app/resources/sprite03.c src/app/resources/sprite04.c src/app/serial_remote/serial_remote.c src/app/serial_remote/r_p2d.c src/app/serial_remote/opList.c src/app/serial_remote/r_gui.c src/app/serial_remote/ssm.c src/app/serial_remote/serial_tx.c src/app/serial_remote/serial_rx.c src/app/serial_remote/r_mem.c src/app/setup/setup.c src/app/setup/touchCalib.c src/app/setup/gamma.c src/app/user_app/usr_main.c src/drv/bsp/backlight.c src/drv/bsp/ILI9320.c src/drv/bsp/touchscreen.c src/drv/uc/configuration_bits.c src/drv/uc/pmp.c src/drv/uc/tmr.c src/drv/uc/uc.c src/drv/uc/uart.c src/sys/file_system/ff.c src/sys/file_system/mmcPIC32.c src/sys/delay.c src/sys/ticks.c src/sys/timer.c src/sys/salloc.c src/sys/rtc.c src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o ${OBJECTDIR}/src/app/gui/gui_graphics.o ${OBJECTDIR}/src/app/gui/gui_obj.o ${OBJECTDIR}/src/app/gui/gui_utils.o ${OBJECTDIR}/src/app/gui/gui_debug.o ${OBJECTDIR}/src/app/gui_demo/gui_demo.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o ${OBJECTDIR}/src/app/p2d/p2d_base.o ${OBJECTDIR}/src/app/p2d/p2d_buffer.o ${OBJECTDIR}/src/app/p2d/p2d_font.o ${OBJECTDIR}/src/app/p2d/p2d_lut.o ${OBJECTDIR}/src/app/p2d/p2d_sprite.o ${OBJECTDIR}/src/app/p2d/p2d_utils.o ${OBJECTDIR}/src/app/p2d/p2d_clip.o ${OBJECTDIR}/src/app/p2d/p2d_internal.o ${OBJECTDIR}/src/app/p2d/p2d_colors.o ${OBJECTDIR}/src/app/p2d/p2d_math.o ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o ${OBJECTDIR}/src/app/resources/FontSymbol.o ${OBJECTDIR}/src/app/resources/sprite00.o ${OBJECTDIR}/src/app/resources/sprite01.o ${OBJECTDIR}/src/app/resources/sprite02.o ${OBJECTDIR}/src/app/resources/sprite03.o ${OBJECTDIR}/src/app/resources/sprite04.o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o ${OBJECTDIR}/src/app/serial_remote/opList.o ${OBJECTDIR}/src/app/serial_remote/r_gui.o ${OBJECTDIR}/src/app/serial_remote/ssm.o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o ${OBJECTDIR}/src/app/serial_remote/r_mem.o ${OBJECTDIR}/src/app/setup/setup.o ${OBJECTDIR}/src/app/setup/touchCalib.o ${OBJECTDIR}/src/app/setup/gamma.o ${OBJECTDIR}/src/app/user_app/usr_main.o ${OBJECTDIR}/src/drv/bsp/backlight.o ${OBJECTDIR}/src/drv/bsp/ILI9320.o ${OBJECTDIR}/src/drv/bsp/touchscreen.o ${OBJECTDIR}/src/drv/uc/configuration_bits.o ${OBJECTDIR}/src/drv/uc/pmp.o ${OBJECTDIR}/src/drv/uc/tmr.o ${OBJECTDIR}/src/drv/uc/uc.o ${OBJECTDIR}/src/drv/uc/uart.o ${OBJECTDIR}/src/sys/file_system/ff.o ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o ${OBJECTDIR}/src/sys/delay.o ${OBJECTDIR}/src/sys/ticks.o ${OBJECTDIR}/src/sys/timer.o ${OBJECTDIR}/src/sys/salloc.o ${OBJECTDIR}/src/sys/rtc.o ${OBJECTDIR}/src/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d ${OBJECTDIR}/src/app/gui/gui_graphics.o.d ${OBJECTDIR}/src/app/gui/gui_obj.o.d ${OBJECTDIR}/src/app/gui/gui_utils.o.d ${OBJECTDIR}/src/app/gui/gui_debug.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d ${OBJECTDIR}/src/app/p2d/p2d_base.o.d ${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d ${OBJECTDIR}/src/app/p2d/p2d_font.o.d ${OBJECTDIR}/src/app/p2d/p2d_lut.o.d ${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d ${OBJECTDIR}/src/app/p2d/p2d_utils.o.d ${OBJECTDIR}/src/app/p2d/p2d_clip.o.d ${OBJECTDIR}/src/app/p2d/p2d_internal.o.d ${OBJECTDIR}/src/app/p2d/p2d_colors.o.d ${OBJECTDIR}/src/app/p2d/p2d_math.o.d ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d ${OBJECTDIR}/src/app/resources/FontSymbol.o.d ${OBJECTDIR}/src/app/resources/sprite00.o.d ${OBJECTDIR}/src/app/resources/sprite01.o.d ${OBJECTDIR}/src/app/resources/sprite02.o.d ${OBJECTDIR}/src/app/resources/sprite03.o.d ${OBJECTDIR}/src/app/resources/sprite04.o.d ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d ${OBJECTDIR}/src/app/serial_remote/opList.o.d ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d ${OBJECTDIR}/src/app/serial_remote/ssm.o.d ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d ${OBJECTDIR}/src/app/setup/setup.o.d ${OBJECTDIR}/src/app/setup/touchCalib.o.d ${OBJECTDIR}/src/app/setup/gamma.o.d ${OBJECTDIR}/src/app/user_app/usr_main.o.d ${OBJECTDIR}/src/drv/bsp/backlight.o.d ${OBJECTDIR}/src/drv/bsp/ILI9320.o.d ${OBJECTDIR}/src/drv/bsp/touchscreen.o.d ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d ${OBJECTDIR}/src/drv/uc/pmp.o.d ${OBJECTDIR}/src/drv/uc/tmr.o.d ${OBJECTDIR}/src/drv/uc/uc.o.d ${OBJECTDIR}/src/drv/uc/uart.o.d ${OBJECTDIR}/src/sys/file_system/ff.o.d ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d ${OBJECTDIR}/src/sys/delay.o.d ${OBJECTDIR}/src/sys/ticks.o.d ${OBJECTDIR}/src/sys/timer.o.d ${OBJECTDIR}/src/sys/salloc.o.d ${OBJECTDIR}/src/sys/rtc.o.d ${OBJECTDIR}/src/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o ${OBJECTDIR}/src/app/gui/gui_graphics.o ${OBJECTDIR}/src/app/gui/gui_obj.o ${OBJECTDIR}/src/app/gui/gui_utils.o ${OBJECTDIR}/src/app/gui/gui_debug.o ${OBJECTDIR}/src/app/gui_demo/gui_demo.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o ${OBJECTDIR}/src/app/p2d/p2d_base.o ${OBJECTDIR}/src/app/p2d/p2d_buffer.o ${OBJECTDIR}/src/app/p2d/p2d_font.o ${OBJECTDIR}/src/app/p2d/p2d_lut.o ${OBJECTDIR}/src/app/p2d/p2d_sprite.o ${OBJECTDIR}/src/app/p2d/p2d_utils.o ${OBJECTDIR}/src/app/p2d/p2d_clip.o ${OBJECTDIR}/src/app/p2d/p2d_internal.o ${OBJECTDIR}/src/app/p2d/p2d_colors.o ${OBJECTDIR}/src/app/p2d/p2d_math.o ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o ${OBJECTDIR}/src/app/resources/FontSymbol.o ${OBJECTDIR}/src/app/resources/sprite00.o ${OBJECTDIR}/src/app/resources/sprite01.o ${OBJECTDIR}/src/app/resources/sprite02.o ${OBJECTDIR}/src/app/resources/sprite03.o ${OBJECTDIR}/src/app/resources/sprite04.o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o ${OBJECTDIR}/src/app/serial_remote/opList.o ${OBJECTDIR}/src/app/serial_remote/r_gui.o ${OBJECTDIR}/src/app/serial_remote/ssm.o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o ${OBJECTDIR}/src/app/serial_remote/r_mem.o ${OBJECTDIR}/src/app/setup/setup.o ${OBJECTDIR}/src/app/setup/touchCalib.o ${OBJECTDIR}/src/app/setup/gamma.o ${OBJECTDIR}/src/app/user_app/usr_main.o ${OBJECTDIR}/src/drv/bsp/backlight.o ${OBJECTDIR}/src/drv/bsp/ILI9320.o ${OBJECTDIR}/src/drv/bsp/touchscreen.o ${OBJECTDIR}/src/drv/uc/configuration_bits.o ${OBJECTDIR}/src/drv/uc/pmp.o ${OBJECTDIR}/src/drv/uc/tmr.o ${OBJECTDIR}/src/drv/uc/uc.o ${OBJECTDIR}/src/drv/uc/uart.o ${OBJECTDIR}/src/sys/file_system/ff.o ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o ${OBJECTDIR}/src/sys/delay.o ${OBJECTDIR}/src/sys/ticks.o ${OBJECTDIR}/src/sys/timer.o ${OBJECTDIR}/src/sys/salloc.o ${OBJECTDIR}/src/sys/rtc.o ${OBJECTDIR}/src/main.o

# Source Files
SOURCEFILES=src/app/gui/macro/file_browser/gui_m_file_browser.c src/app/gui/macro/keyboard/gui_m_keyboard.c src/app/gui/macro/keyboard/gui_w_key.c src/app/gui/macro/keyboard/keymap.c src/app/gui/macro/list/gui_m_list.c src/app/gui/macro/popup/gui_m_popup.c src/app/gui/widgets/gui_w_button.c src/app/gui/widgets/gui_w_checkBox.c src/app/gui/widgets/gui_w_frame.c src/app/gui/widgets/gui_w_graph.c src/app/gui/widgets/gui_w_led.c src/app/gui/widgets/gui_w_radio.c src/app/gui/widgets/gui_w_slider.c src/app/gui/widgets/gui_w_tab.c src/app/gui/widgets/gui_w_text.c src/app/gui/widgets/gui_w_usr_entry.c src/app/gui/widgets/gui_w_valueBox.c src/app/gui/widgets/gui_w_rot_button.c src/app/gui/widgets/gui_w_rot_value.c src/app/gui/widgets/gui_w_list.c src/app/gui/widgets/gui_w_scroller.c src/app/gui/gui_graphics.c src/app/gui/gui_obj.c src/app/gui/gui_utils.c src/app/gui/gui_debug.c src/app/gui_demo/gui_demo.c src/app/gui_demo/gui_demo_button.c src/app/gui_demo/gui_demo_keyboard.c src/app/gui_demo/gui_demo_rbutton.c src/app/gui_demo/gui_demo_text.c src/app/gui_demo/gui_demo_valuebox.c src/app/gui_demo/gui_demo_graph1.c src/app/gui_demo/gui_demo_graph2.c src/app/gui_demo/gui_demo_list.c src/app/gui_demo/gui_demo_file_browser.c src/app/gui_demo/gui_demo_popup.c src/app/gui_demo/gui_demo_sd.c src/app/gui_demo/p2d_demo.c src/app/p2d/p2d_base.c src/app/p2d/p2d_buffer.c src/app/p2d/p2d_font.c src/app/p2d/p2d_lut.c src/app/p2d/p2d_sprite.c src/app/p2d/p2d_utils.c src/app/p2d/p2d_clip.c src/app/p2d/p2d_internal.c src/app/p2d/p2d_colors.c src/app/p2d/p2d_math.c src/app/p2d/p2d_geo_poly.c src/app/p2d/p2d_geo_circle.c src/app/p2d/p2d_geo_line.c src/app/resources/FontDigit_4bpp.c src/app/resources/FontSerif_4bpp_n.c src/app/resources/FontSerif_4bpp_b.c src/app/resources/FontSerif_4bpp_i.c src/app/resources/FontSymbol.c src/app/resources/sprite00.c src/app/resources/sprite01.c src/app/resources/sprite02.c src/app/resources/sprite03.c src/app/resources/sprite04.c src/app/serial_remote/serial_remote.c src/app/serial_remote/r_p2d.c src/app/serial_remote/opList.c src/app/serial_remote/r_gui.c src/app/serial_remote/ssm.c src/app/serial_remote/serial_tx.c src/app/serial_remote/serial_rx.c src/app/serial_remote/r_mem.c src/app/setup/setup.c src/app/setup/touchCalib.c src/app/setup/gamma.c src/app/user_app/usr_main.c src/drv/bsp/backlight.c src/drv/bsp/ILI9320.c src/drv/bsp/touchscreen.c src/drv/uc/configuration_bits.c src/drv/uc/pmp.c src/drv/uc/tmr.c src/drv/uc/uc.c src/drv/uc/uart.c src/sys/file_system/ff.c src/sys/file_system/mmcPIC32.c src/sys/delay.c src/sys/ticks.c src/sys/timer.c src/sys/salloc.c src/sys/rtc.c src/main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o: src/app/gui/macro/file_browser/gui_m_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/file_browser 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d" -o ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o src/app/gui/macro/file_browser/gui_m_file_browser.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o: src/app/gui/macro/keyboard/gui_m_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o src/app/gui/macro/keyboard/gui_m_keyboard.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o: src/app/gui/macro/keyboard/gui_w_key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o src/app/gui/macro/keyboard/gui_w_key.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o: src/app/gui/macro/keyboard/keymap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o src/app/gui/macro/keyboard/keymap.c  
	
${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o: src/app/gui/macro/list/gui_m_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/list 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d" -o ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o src/app/gui/macro/list/gui_m_list.c  
	
${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o: src/app/gui/macro/popup/gui_m_popup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/popup 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d" -o ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o src/app/gui/macro/popup/gui_m_popup.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o: src/app/gui/widgets/gui_w_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o src/app/gui/widgets/gui_w_button.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o: src/app/gui/widgets/gui_w_checkBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o src/app/gui/widgets/gui_w_checkBox.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o: src/app/gui/widgets/gui_w_frame.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o src/app/gui/widgets/gui_w_frame.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o: src/app/gui/widgets/gui_w_graph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o src/app/gui/widgets/gui_w_graph.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o: src/app/gui/widgets/gui_w_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o src/app/gui/widgets/gui_w_led.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o: src/app/gui/widgets/gui_w_radio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o src/app/gui/widgets/gui_w_radio.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o: src/app/gui/widgets/gui_w_slider.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o src/app/gui/widgets/gui_w_slider.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o: src/app/gui/widgets/gui_w_tab.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o src/app/gui/widgets/gui_w_tab.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o: src/app/gui/widgets/gui_w_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o src/app/gui/widgets/gui_w_text.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o: src/app/gui/widgets/gui_w_usr_entry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o src/app/gui/widgets/gui_w_usr_entry.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o: src/app/gui/widgets/gui_w_valueBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o src/app/gui/widgets/gui_w_valueBox.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o: src/app/gui/widgets/gui_w_rot_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o src/app/gui/widgets/gui_w_rot_button.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o: src/app/gui/widgets/gui_w_rot_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o src/app/gui/widgets/gui_w_rot_value.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o: src/app/gui/widgets/gui_w_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o src/app/gui/widgets/gui_w_list.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o: src/app/gui/widgets/gui_w_scroller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o src/app/gui/widgets/gui_w_scroller.c  
	
${OBJECTDIR}/src/app/gui/gui_graphics.o: src/app/gui/gui_graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_graphics.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_graphics.o.d" -o ${OBJECTDIR}/src/app/gui/gui_graphics.o src/app/gui/gui_graphics.c  
	
${OBJECTDIR}/src/app/gui/gui_obj.o: src/app/gui/gui_obj.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_obj.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_obj.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_obj.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_obj.o.d" -o ${OBJECTDIR}/src/app/gui/gui_obj.o src/app/gui/gui_obj.c  
	
${OBJECTDIR}/src/app/gui/gui_utils.o: src/app/gui/gui_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_utils.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_utils.o.d" -o ${OBJECTDIR}/src/app/gui/gui_utils.o src/app/gui/gui_utils.c  
	
${OBJECTDIR}/src/app/gui/gui_debug.o: src/app/gui/gui_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_debug.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_debug.o.d" -o ${OBJECTDIR}/src/app/gui/gui_debug.o src/app/gui/gui_debug.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo.o: src/app/gui_demo/gui_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo.o src/app/gui_demo/gui_demo.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o: src/app/gui_demo/gui_demo_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o src/app/gui_demo/gui_demo_button.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o: src/app/gui_demo/gui_demo_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o src/app/gui_demo/gui_demo_keyboard.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o: src/app/gui_demo/gui_demo_rbutton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o src/app/gui_demo/gui_demo_rbutton.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o: src/app/gui_demo/gui_demo_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o src/app/gui_demo/gui_demo_text.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o: src/app/gui_demo/gui_demo_valuebox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o src/app/gui_demo/gui_demo_valuebox.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o: src/app/gui_demo/gui_demo_graph1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o src/app/gui_demo/gui_demo_graph1.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o: src/app/gui_demo/gui_demo_graph2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o src/app/gui_demo/gui_demo_graph2.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o: src/app/gui_demo/gui_demo_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o src/app/gui_demo/gui_demo_list.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o: src/app/gui_demo/gui_demo_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o src/app/gui_demo/gui_demo_file_browser.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o: src/app/gui_demo/gui_demo_popup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o src/app/gui_demo/gui_demo_popup.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o: src/app/gui_demo/gui_demo_sd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o src/app/gui_demo/gui_demo_sd.c  
	
${OBJECTDIR}/src/app/gui_demo/p2d_demo.o: src/app/gui_demo/p2d_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d" -o ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o src/app/gui_demo/p2d_demo.c  
	
${OBJECTDIR}/src/app/p2d/p2d_base.o: src/app/p2d/p2d_base.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_base.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_base.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_base.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_base.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_base.o src/app/p2d/p2d_base.c  
	
${OBJECTDIR}/src/app/p2d/p2d_buffer.o: src/app/p2d/p2d_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_buffer.o src/app/p2d/p2d_buffer.c  
	
${OBJECTDIR}/src/app/p2d/p2d_font.o: src/app/p2d/p2d_font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_font.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_font.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_font.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_font.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_font.o src/app/p2d/p2d_font.c  
	
${OBJECTDIR}/src/app/p2d/p2d_lut.o: src/app/p2d/p2d_lut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_lut.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_lut.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_lut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_lut.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_lut.o src/app/p2d/p2d_lut.c  
	
${OBJECTDIR}/src/app/p2d/p2d_sprite.o: src/app/p2d/p2d_sprite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_sprite.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_sprite.o src/app/p2d/p2d_sprite.c  
	
${OBJECTDIR}/src/app/p2d/p2d_utils.o: src/app/p2d/p2d_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_utils.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_utils.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_utils.o src/app/p2d/p2d_utils.c  
	
${OBJECTDIR}/src/app/p2d/p2d_clip.o: src/app/p2d/p2d_clip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_clip.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_clip.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_clip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_clip.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_clip.o src/app/p2d/p2d_clip.c  
	
${OBJECTDIR}/src/app/p2d/p2d_internal.o: src/app/p2d/p2d_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_internal.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_internal.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_internal.o src/app/p2d/p2d_internal.c  
	
${OBJECTDIR}/src/app/p2d/p2d_colors.o: src/app/p2d/p2d_colors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_colors.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_colors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_colors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_colors.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_colors.o src/app/p2d/p2d_colors.c  
	
${OBJECTDIR}/src/app/p2d/p2d_math.o: src/app/p2d/p2d_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_math.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_math.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_math.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_math.o src/app/p2d/p2d_math.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o: src/app/p2d/p2d_geo_poly.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o src/app/p2d/p2d_geo_poly.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o: src/app/p2d/p2d_geo_circle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o src/app/p2d/p2d_geo_circle.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_line.o: src/app/p2d/p2d_geo_line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o src/app/p2d/p2d_geo_line.c  
	
${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o: src/app/resources/FontDigit_4bpp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d" -o ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o src/app/resources/FontDigit_4bpp.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o: src/app/resources/FontSerif_4bpp_n.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o src/app/resources/FontSerif_4bpp_n.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o: src/app/resources/FontSerif_4bpp_b.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o src/app/resources/FontSerif_4bpp_b.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o: src/app/resources/FontSerif_4bpp_i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o src/app/resources/FontSerif_4bpp_i.c  
	
${OBJECTDIR}/src/app/resources/FontSymbol.o: src/app/resources/FontSymbol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSymbol.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSymbol.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSymbol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSymbol.o.d" -o ${OBJECTDIR}/src/app/resources/FontSymbol.o src/app/resources/FontSymbol.c  
	
${OBJECTDIR}/src/app/resources/sprite00.o: src/app/resources/sprite00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite00.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite00.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite00.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite00.o.d" -o ${OBJECTDIR}/src/app/resources/sprite00.o src/app/resources/sprite00.c  
	
${OBJECTDIR}/src/app/resources/sprite01.o: src/app/resources/sprite01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite01.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite01.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite01.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite01.o.d" -o ${OBJECTDIR}/src/app/resources/sprite01.o src/app/resources/sprite01.c  
	
${OBJECTDIR}/src/app/resources/sprite02.o: src/app/resources/sprite02.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite02.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite02.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite02.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite02.o.d" -o ${OBJECTDIR}/src/app/resources/sprite02.o src/app/resources/sprite02.c  
	
${OBJECTDIR}/src/app/resources/sprite03.o: src/app/resources/sprite03.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite03.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite03.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite03.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite03.o.d" -o ${OBJECTDIR}/src/app/resources/sprite03.o src/app/resources/sprite03.c  
	
${OBJECTDIR}/src/app/resources/sprite04.o: src/app/resources/sprite04.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite04.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite04.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite04.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite04.o.d" -o ${OBJECTDIR}/src/app/resources/sprite04.o src/app/resources/sprite04.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_remote.o: src/app/serial_remote/serial_remote.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o src/app/serial_remote/serial_remote.c  
	
${OBJECTDIR}/src/app/serial_remote/r_p2d.o: src/app/serial_remote/r_p2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o src/app/serial_remote/r_p2d.c  
	
${OBJECTDIR}/src/app/serial_remote/opList.o: src/app/serial_remote/opList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/opList.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/opList.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/opList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/opList.o.d" -o ${OBJECTDIR}/src/app/serial_remote/opList.o src/app/serial_remote/opList.c  
	
${OBJECTDIR}/src/app/serial_remote/r_gui.o: src/app/serial_remote/r_gui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_gui.o src/app/serial_remote/r_gui.c  
	
${OBJECTDIR}/src/app/serial_remote/ssm.o: src/app/serial_remote/ssm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/ssm.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/ssm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/ssm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/ssm.o.d" -o ${OBJECTDIR}/src/app/serial_remote/ssm.o src/app/serial_remote/ssm.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_tx.o: src/app/serial_remote/serial_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o src/app/serial_remote/serial_tx.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_rx.o: src/app/serial_remote/serial_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o src/app/serial_remote/serial_rx.c  
	
${OBJECTDIR}/src/app/serial_remote/r_mem.o: src/app/serial_remote/r_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_mem.o src/app/serial_remote/r_mem.c  
	
${OBJECTDIR}/src/app/setup/setup.o: src/app/setup/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/setup.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/setup.o.d" -o ${OBJECTDIR}/src/app/setup/setup.o src/app/setup/setup.c  
	
${OBJECTDIR}/src/app/setup/touchCalib.o: src/app/setup/touchCalib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/touchCalib.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/touchCalib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/touchCalib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/touchCalib.o.d" -o ${OBJECTDIR}/src/app/setup/touchCalib.o src/app/setup/touchCalib.c  
	
${OBJECTDIR}/src/app/setup/gamma.o: src/app/setup/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/gamma.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/gamma.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/gamma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/gamma.o.d" -o ${OBJECTDIR}/src/app/setup/gamma.o src/app/setup/gamma.c  
	
${OBJECTDIR}/src/app/user_app/usr_main.o: src/app/user_app/usr_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/user_app 
	@${RM} ${OBJECTDIR}/src/app/user_app/usr_main.o.d 
	@${RM} ${OBJECTDIR}/src/app/user_app/usr_main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/user_app/usr_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/user_app/usr_main.o.d" -o ${OBJECTDIR}/src/app/user_app/usr_main.o src/app/user_app/usr_main.c  
	
${OBJECTDIR}/src/drv/bsp/backlight.o: src/drv/bsp/backlight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/backlight.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/backlight.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/backlight.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/backlight.o.d" -o ${OBJECTDIR}/src/drv/bsp/backlight.o src/drv/bsp/backlight.c  
	
${OBJECTDIR}/src/drv/bsp/ILI9320.o: src/drv/bsp/ILI9320.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/ILI9320.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/ILI9320.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/ILI9320.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/ILI9320.o.d" -o ${OBJECTDIR}/src/drv/bsp/ILI9320.o src/drv/bsp/ILI9320.c  
	
${OBJECTDIR}/src/drv/bsp/touchscreen.o: src/drv/bsp/touchscreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/touchscreen.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/touchscreen.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/touchscreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/touchscreen.o.d" -o ${OBJECTDIR}/src/drv/bsp/touchscreen.o src/drv/bsp/touchscreen.c  
	
${OBJECTDIR}/src/drv/uc/configuration_bits.o: src/drv/uc/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" -o ${OBJECTDIR}/src/drv/uc/configuration_bits.o src/drv/uc/configuration_bits.c  
	
${OBJECTDIR}/src/drv/uc/pmp.o: src/drv/uc/pmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/pmp.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/pmp.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/pmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/pmp.o.d" -o ${OBJECTDIR}/src/drv/uc/pmp.o src/drv/uc/pmp.c  
	
${OBJECTDIR}/src/drv/uc/tmr.o: src/drv/uc/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/tmr.o.d" -o ${OBJECTDIR}/src/drv/uc/tmr.o src/drv/uc/tmr.c  
	
${OBJECTDIR}/src/drv/uc/uc.o: src/drv/uc/uc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uc.o.d" -o ${OBJECTDIR}/src/drv/uc/uc.o src/drv/uc/uc.c  
	
${OBJECTDIR}/src/drv/uc/uart.o: src/drv/uc/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uart.o.d" -o ${OBJECTDIR}/src/drv/uc/uart.o src/drv/uc/uart.c  
	
${OBJECTDIR}/src/sys/file_system/ff.o: src/sys/file_system/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys/file_system 
	@${RM} ${OBJECTDIR}/src/sys/file_system/ff.o.d 
	@${RM} ${OBJECTDIR}/src/sys/file_system/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/file_system/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/file_system/ff.o.d" -o ${OBJECTDIR}/src/sys/file_system/ff.o src/sys/file_system/ff.c  
	
${OBJECTDIR}/src/sys/file_system/mmcPIC32.o: src/sys/file_system/mmcPIC32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys/file_system 
	@${RM} ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d 
	@${RM} ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d" -o ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o src/sys/file_system/mmcPIC32.c  
	
${OBJECTDIR}/src/sys/delay.o: src/sys/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/delay.o.d 
	@${RM} ${OBJECTDIR}/src/sys/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/delay.o.d" -o ${OBJECTDIR}/src/sys/delay.o src/sys/delay.c  
	
${OBJECTDIR}/src/sys/ticks.o: src/sys/ticks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o.d 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/ticks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/ticks.o.d" -o ${OBJECTDIR}/src/sys/ticks.o src/sys/ticks.c  
	
${OBJECTDIR}/src/sys/timer.o: src/sys/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sys/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/timer.o.d" -o ${OBJECTDIR}/src/sys/timer.o src/sys/timer.c  
	
${OBJECTDIR}/src/sys/salloc.o: src/sys/salloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/salloc.o.d 
	@${RM} ${OBJECTDIR}/src/sys/salloc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/salloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/salloc.o.d" -o ${OBJECTDIR}/src/sys/salloc.o src/sys/salloc.c  
	
${OBJECTDIR}/src/sys/rtc.o: src/sys/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sys/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/rtc.o.d" -o ${OBJECTDIR}/src/sys/rtc.o src/sys/rtc.c  
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  
	
else
${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o: src/app/gui/macro/file_browser/gui_m_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/file_browser 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o.d" -o ${OBJECTDIR}/src/app/gui/macro/file_browser/gui_m_file_browser.o src/app/gui/macro/file_browser/gui_m_file_browser.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o: src/app/gui/macro/keyboard/gui_m_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_m_keyboard.o src/app/gui/macro/keyboard/gui_m_keyboard.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o: src/app/gui/macro/keyboard/gui_w_key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/gui_w_key.o src/app/gui/macro/keyboard/gui_w_key.c  
	
${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o: src/app/gui/macro/keyboard/keymap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/keyboard 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o.d" -o ${OBJECTDIR}/src/app/gui/macro/keyboard/keymap.o src/app/gui/macro/keyboard/keymap.c  
	
${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o: src/app/gui/macro/list/gui_m_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/list 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o.d" -o ${OBJECTDIR}/src/app/gui/macro/list/gui_m_list.o src/app/gui/macro/list/gui_m_list.c  
	
${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o: src/app/gui/macro/popup/gui_m_popup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/macro/popup 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o.d" -o ${OBJECTDIR}/src/app/gui/macro/popup/gui_m_popup.o src/app/gui/macro/popup/gui_m_popup.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o: src/app/gui/widgets/gui_w_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_button.o src/app/gui/widgets/gui_w_button.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o: src/app/gui/widgets/gui_w_checkBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_checkBox.o src/app/gui/widgets/gui_w_checkBox.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o: src/app/gui/widgets/gui_w_frame.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_frame.o src/app/gui/widgets/gui_w_frame.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o: src/app/gui/widgets/gui_w_graph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_graph.o src/app/gui/widgets/gui_w_graph.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o: src/app/gui/widgets/gui_w_led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_led.o src/app/gui/widgets/gui_w_led.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o: src/app/gui/widgets/gui_w_radio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_radio.o src/app/gui/widgets/gui_w_radio.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o: src/app/gui/widgets/gui_w_slider.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_slider.o src/app/gui/widgets/gui_w_slider.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o: src/app/gui/widgets/gui_w_tab.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_tab.o src/app/gui/widgets/gui_w_tab.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o: src/app/gui/widgets/gui_w_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_text.o src/app/gui/widgets/gui_w_text.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o: src/app/gui/widgets/gui_w_usr_entry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_usr_entry.o src/app/gui/widgets/gui_w_usr_entry.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o: src/app/gui/widgets/gui_w_valueBox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_valueBox.o src/app/gui/widgets/gui_w_valueBox.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o: src/app/gui/widgets/gui_w_rot_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_button.o src/app/gui/widgets/gui_w_rot_button.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o: src/app/gui/widgets/gui_w_rot_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_rot_value.o src/app/gui/widgets/gui_w_rot_value.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o: src/app/gui/widgets/gui_w_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_list.o src/app/gui/widgets/gui_w_list.c  
	
${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o: src/app/gui/widgets/gui_w_scroller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui/widgets 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o.d" -o ${OBJECTDIR}/src/app/gui/widgets/gui_w_scroller.o src/app/gui/widgets/gui_w_scroller.c  
	
${OBJECTDIR}/src/app/gui/gui_graphics.o: src/app/gui/gui_graphics.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_graphics.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_graphics.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_graphics.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_graphics.o.d" -o ${OBJECTDIR}/src/app/gui/gui_graphics.o src/app/gui/gui_graphics.c  
	
${OBJECTDIR}/src/app/gui/gui_obj.o: src/app/gui/gui_obj.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_obj.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_obj.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_obj.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_obj.o.d" -o ${OBJECTDIR}/src/app/gui/gui_obj.o src/app/gui/gui_obj.c  
	
${OBJECTDIR}/src/app/gui/gui_utils.o: src/app/gui/gui_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_utils.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_utils.o.d" -o ${OBJECTDIR}/src/app/gui/gui_utils.o src/app/gui/gui_utils.c  
	
${OBJECTDIR}/src/app/gui/gui_debug.o: src/app/gui/gui_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_debug.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui/gui_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui/gui_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui/gui_debug.o.d" -o ${OBJECTDIR}/src/app/gui/gui_debug.o src/app/gui/gui_debug.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo.o: src/app/gui_demo/gui_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo.o src/app/gui_demo/gui_demo.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o: src/app/gui_demo/gui_demo_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_button.o src/app/gui_demo/gui_demo_button.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o: src/app/gui_demo/gui_demo_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_keyboard.o src/app/gui_demo/gui_demo_keyboard.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o: src/app/gui_demo/gui_demo_rbutton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_rbutton.o src/app/gui_demo/gui_demo_rbutton.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o: src/app/gui_demo/gui_demo_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_text.o src/app/gui_demo/gui_demo_text.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o: src/app/gui_demo/gui_demo_valuebox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_valuebox.o src/app/gui_demo/gui_demo_valuebox.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o: src/app/gui_demo/gui_demo_graph1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph1.o src/app/gui_demo/gui_demo_graph1.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o: src/app/gui_demo/gui_demo_graph2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_graph2.o src/app/gui_demo/gui_demo_graph2.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o: src/app/gui_demo/gui_demo_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_list.o src/app/gui_demo/gui_demo_list.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o: src/app/gui_demo/gui_demo_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_file_browser.o src/app/gui_demo/gui_demo_file_browser.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o: src/app/gui_demo/gui_demo_popup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_popup.o src/app/gui_demo/gui_demo_popup.c  
	
${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o: src/app/gui_demo/gui_demo_sd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o.d" -o ${OBJECTDIR}/src/app/gui_demo/gui_demo_sd.o src/app/gui_demo/gui_demo_sd.c  
	
${OBJECTDIR}/src/app/gui_demo/p2d_demo.o: src/app/gui_demo/p2d_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/gui_demo 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/gui_demo/p2d_demo.o.d" -o ${OBJECTDIR}/src/app/gui_demo/p2d_demo.o src/app/gui_demo/p2d_demo.c  
	
${OBJECTDIR}/src/app/p2d/p2d_base.o: src/app/p2d/p2d_base.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_base.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_base.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_base.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_base.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_base.o src/app/p2d/p2d_base.c  
	
${OBJECTDIR}/src/app/p2d/p2d_buffer.o: src/app/p2d/p2d_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_buffer.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_buffer.o src/app/p2d/p2d_buffer.c  
	
${OBJECTDIR}/src/app/p2d/p2d_font.o: src/app/p2d/p2d_font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_font.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_font.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_font.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_font.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_font.o src/app/p2d/p2d_font.c  
	
${OBJECTDIR}/src/app/p2d/p2d_lut.o: src/app/p2d/p2d_lut.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_lut.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_lut.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_lut.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_lut.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_lut.o src/app/p2d/p2d_lut.c  
	
${OBJECTDIR}/src/app/p2d/p2d_sprite.o: src/app/p2d/p2d_sprite.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_sprite.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_sprite.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_sprite.o src/app/p2d/p2d_sprite.c  
	
${OBJECTDIR}/src/app/p2d/p2d_utils.o: src/app/p2d/p2d_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_utils.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_utils.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_utils.o src/app/p2d/p2d_utils.c  
	
${OBJECTDIR}/src/app/p2d/p2d_clip.o: src/app/p2d/p2d_clip.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_clip.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_clip.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_clip.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_clip.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_clip.o src/app/p2d/p2d_clip.c  
	
${OBJECTDIR}/src/app/p2d/p2d_internal.o: src/app/p2d/p2d_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_internal.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_internal.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_internal.o src/app/p2d/p2d_internal.c  
	
${OBJECTDIR}/src/app/p2d/p2d_colors.o: src/app/p2d/p2d_colors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_colors.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_colors.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_colors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_colors.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_colors.o src/app/p2d/p2d_colors.c  
	
${OBJECTDIR}/src/app/p2d/p2d_math.o: src/app/p2d/p2d_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_math.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_math.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_math.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_math.o src/app/p2d/p2d_math.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o: src/app/p2d/p2d_geo_poly.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_poly.o src/app/p2d/p2d_geo_poly.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o: src/app/p2d/p2d_geo_circle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_circle.o src/app/p2d/p2d_geo_circle.c  
	
${OBJECTDIR}/src/app/p2d/p2d_geo_line.o: src/app/p2d/p2d_geo_line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/p2d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d 
	@${RM} ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/p2d/p2d_geo_line.o.d" -o ${OBJECTDIR}/src/app/p2d/p2d_geo_line.o src/app/p2d/p2d_geo_line.c  
	
${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o: src/app/resources/FontDigit_4bpp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o.d" -o ${OBJECTDIR}/src/app/resources/FontDigit_4bpp.o src/app/resources/FontDigit_4bpp.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o: src/app/resources/FontSerif_4bpp_n.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_n.o src/app/resources/FontSerif_4bpp_n.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o: src/app/resources/FontSerif_4bpp_b.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_b.o src/app/resources/FontSerif_4bpp_b.c  
	
${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o: src/app/resources/FontSerif_4bpp_i.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o.d" -o ${OBJECTDIR}/src/app/resources/FontSerif_4bpp_i.o src/app/resources/FontSerif_4bpp_i.c  
	
${OBJECTDIR}/src/app/resources/FontSymbol.o: src/app/resources/FontSymbol.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSymbol.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/FontSymbol.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/FontSymbol.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/FontSymbol.o.d" -o ${OBJECTDIR}/src/app/resources/FontSymbol.o src/app/resources/FontSymbol.c  
	
${OBJECTDIR}/src/app/resources/sprite00.o: src/app/resources/sprite00.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite00.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite00.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite00.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite00.o.d" -o ${OBJECTDIR}/src/app/resources/sprite00.o src/app/resources/sprite00.c  
	
${OBJECTDIR}/src/app/resources/sprite01.o: src/app/resources/sprite01.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite01.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite01.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite01.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite01.o.d" -o ${OBJECTDIR}/src/app/resources/sprite01.o src/app/resources/sprite01.c  
	
${OBJECTDIR}/src/app/resources/sprite02.o: src/app/resources/sprite02.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite02.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite02.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite02.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite02.o.d" -o ${OBJECTDIR}/src/app/resources/sprite02.o src/app/resources/sprite02.c  
	
${OBJECTDIR}/src/app/resources/sprite03.o: src/app/resources/sprite03.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite03.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite03.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite03.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite03.o.d" -o ${OBJECTDIR}/src/app/resources/sprite03.o src/app/resources/sprite03.c  
	
${OBJECTDIR}/src/app/resources/sprite04.o: src/app/resources/sprite04.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/resources 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite04.o.d 
	@${RM} ${OBJECTDIR}/src/app/resources/sprite04.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/resources/sprite04.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/resources/sprite04.o.d" -o ${OBJECTDIR}/src/app/resources/sprite04.o src/app/resources/sprite04.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_remote.o: src/app/serial_remote/serial_remote.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o src/app/serial_remote/serial_remote.c  
	
${OBJECTDIR}/src/app/serial_remote/r_p2d.o: src/app/serial_remote/r_p2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o src/app/serial_remote/r_p2d.c  
	
${OBJECTDIR}/src/app/serial_remote/opList.o: src/app/serial_remote/opList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/opList.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/opList.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/opList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/opList.o.d" -o ${OBJECTDIR}/src/app/serial_remote/opList.o src/app/serial_remote/opList.c  
	
${OBJECTDIR}/src/app/serial_remote/r_gui.o: src/app/serial_remote/r_gui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_gui.o src/app/serial_remote/r_gui.c  
	
${OBJECTDIR}/src/app/serial_remote/ssm.o: src/app/serial_remote/ssm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/ssm.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/ssm.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/ssm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/ssm.o.d" -o ${OBJECTDIR}/src/app/serial_remote/ssm.o src/app/serial_remote/ssm.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_tx.o: src/app/serial_remote/serial_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o src/app/serial_remote/serial_tx.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_rx.o: src/app/serial_remote/serial_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o src/app/serial_remote/serial_rx.c  
	
${OBJECTDIR}/src/app/serial_remote/r_mem.o: src/app/serial_remote/r_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_mem.o src/app/serial_remote/r_mem.c  
	
${OBJECTDIR}/src/app/setup/setup.o: src/app/setup/setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/setup.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/setup.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/setup.o.d" -o ${OBJECTDIR}/src/app/setup/setup.o src/app/setup/setup.c  
	
${OBJECTDIR}/src/app/setup/touchCalib.o: src/app/setup/touchCalib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/touchCalib.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/touchCalib.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/touchCalib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/touchCalib.o.d" -o ${OBJECTDIR}/src/app/setup/touchCalib.o src/app/setup/touchCalib.c  
	
${OBJECTDIR}/src/app/setup/gamma.o: src/app/setup/gamma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/setup 
	@${RM} ${OBJECTDIR}/src/app/setup/gamma.o.d 
	@${RM} ${OBJECTDIR}/src/app/setup/gamma.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/setup/gamma.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/setup/gamma.o.d" -o ${OBJECTDIR}/src/app/setup/gamma.o src/app/setup/gamma.c  
	
${OBJECTDIR}/src/app/user_app/usr_main.o: src/app/user_app/usr_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/user_app 
	@${RM} ${OBJECTDIR}/src/app/user_app/usr_main.o.d 
	@${RM} ${OBJECTDIR}/src/app/user_app/usr_main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/user_app/usr_main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/user_app/usr_main.o.d" -o ${OBJECTDIR}/src/app/user_app/usr_main.o src/app/user_app/usr_main.c  
	
${OBJECTDIR}/src/drv/bsp/backlight.o: src/drv/bsp/backlight.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/backlight.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/backlight.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/backlight.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/backlight.o.d" -o ${OBJECTDIR}/src/drv/bsp/backlight.o src/drv/bsp/backlight.c  
	
${OBJECTDIR}/src/drv/bsp/ILI9320.o: src/drv/bsp/ILI9320.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/ILI9320.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/ILI9320.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/ILI9320.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/ILI9320.o.d" -o ${OBJECTDIR}/src/drv/bsp/ILI9320.o src/drv/bsp/ILI9320.c  
	
${OBJECTDIR}/src/drv/bsp/touchscreen.o: src/drv/bsp/touchscreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/bsp 
	@${RM} ${OBJECTDIR}/src/drv/bsp/touchscreen.o.d 
	@${RM} ${OBJECTDIR}/src/drv/bsp/touchscreen.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/bsp/touchscreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/bsp/touchscreen.o.d" -o ${OBJECTDIR}/src/drv/bsp/touchscreen.o src/drv/bsp/touchscreen.c  
	
${OBJECTDIR}/src/drv/uc/configuration_bits.o: src/drv/uc/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" -o ${OBJECTDIR}/src/drv/uc/configuration_bits.o src/drv/uc/configuration_bits.c  
	
${OBJECTDIR}/src/drv/uc/pmp.o: src/drv/uc/pmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/pmp.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/pmp.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/pmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/pmp.o.d" -o ${OBJECTDIR}/src/drv/uc/pmp.o src/drv/uc/pmp.c  
	
${OBJECTDIR}/src/drv/uc/tmr.o: src/drv/uc/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/tmr.o.d" -o ${OBJECTDIR}/src/drv/uc/tmr.o src/drv/uc/tmr.c  
	
${OBJECTDIR}/src/drv/uc/uc.o: src/drv/uc/uc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uc.o.d" -o ${OBJECTDIR}/src/drv/uc/uc.o src/drv/uc/uc.c  
	
${OBJECTDIR}/src/drv/uc/uart.o: src/drv/uc/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uart.o.d" -o ${OBJECTDIR}/src/drv/uc/uart.o src/drv/uc/uart.c  
	
${OBJECTDIR}/src/sys/file_system/ff.o: src/sys/file_system/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys/file_system 
	@${RM} ${OBJECTDIR}/src/sys/file_system/ff.o.d 
	@${RM} ${OBJECTDIR}/src/sys/file_system/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/file_system/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/file_system/ff.o.d" -o ${OBJECTDIR}/src/sys/file_system/ff.o src/sys/file_system/ff.c  
	
${OBJECTDIR}/src/sys/file_system/mmcPIC32.o: src/sys/file_system/mmcPIC32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys/file_system 
	@${RM} ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d 
	@${RM} ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/file_system/mmcPIC32.o.d" -o ${OBJECTDIR}/src/sys/file_system/mmcPIC32.o src/sys/file_system/mmcPIC32.c  
	
${OBJECTDIR}/src/sys/delay.o: src/sys/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/delay.o.d 
	@${RM} ${OBJECTDIR}/src/sys/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/delay.o.d" -o ${OBJECTDIR}/src/sys/delay.o src/sys/delay.c  
	
${OBJECTDIR}/src/sys/ticks.o: src/sys/ticks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o.d 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/ticks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/ticks.o.d" -o ${OBJECTDIR}/src/sys/ticks.o src/sys/ticks.c  
	
${OBJECTDIR}/src/sys/timer.o: src/sys/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sys/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/timer.o.d" -o ${OBJECTDIR}/src/sys/timer.o src/sys/timer.c  
	
${OBJECTDIR}/src/sys/salloc.o: src/sys/salloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/salloc.o.d 
	@${RM} ${OBJECTDIR}/src/sys/salloc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/salloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/salloc.o.d" -o ${OBJECTDIR}/src/sys/salloc.o src/sys/salloc.c  
	
${OBJECTDIR}/src/sys/rtc.o: src/sys/rtc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/rtc.o.d 
	@${RM} ${OBJECTDIR}/src/sys/rtc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/rtc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/rtc.o.d" -o ${OBJECTDIR}/src/sys/rtc.o src/sys/rtc.c  
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/app/resources" -I"src/drv/bsp" -I"src/drv/uc" -I"src/sys" -I"src/app/p2d" -I"src/app" -I"src/app/gui" -I"src/sys/file_system" -I"src/app/gui/macro/keyboard" -I"src/app/gui/widgets" -I"src/app/gui_demo" -I"src/app/gui/macro/list" -I"src/app/gui/macro/popup" -I"src/app/gui/macro/file_browser" -I"src/app/setup" -I"src/app/user_app" -I"src/app/serial_remote" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 
else
dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
