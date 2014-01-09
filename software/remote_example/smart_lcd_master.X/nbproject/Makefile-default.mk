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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app/serial_remote/pages/gui_demo.c src/app/serial_remote/pages/gui_demo_button.c src/app/serial_remote/pages/gui_demo_file_browser.c src/app/serial_remote/pages/gui_demo_graph2.c src/app/serial_remote/pages/gui_demo_keyboard.c src/app/serial_remote/pages/gui_demo_list.c src/app/serial_remote/pages/gui_demo_rbutton.c src/app/serial_remote/pages/gui_demo_text.c src/app/serial_remote/pages/gui_demo_valuebox.c src/app/serial_remote/serial_remote.c src/app/serial_remote/r_p2d.c src/app/serial_remote/r_gui.c src/app/serial_remote/serial_tx.c src/app/serial_remote/serial_rx.c src/app/serial_remote/r_mem.c src/app/serial_remote/local_functions.c src/drv/uc/configuration_bits.c src/drv/uc/tmr.c src/drv/uc/uc.c src/drv/uc/uart.c src/sys/delay.c src/sys/ticks.c src/sys/timer.c src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o ${OBJECTDIR}/src/app/serial_remote/r_gui.o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o ${OBJECTDIR}/src/app/serial_remote/r_mem.o ${OBJECTDIR}/src/app/serial_remote/local_functions.o ${OBJECTDIR}/src/drv/uc/configuration_bits.o ${OBJECTDIR}/src/drv/uc/tmr.o ${OBJECTDIR}/src/drv/uc/uc.o ${OBJECTDIR}/src/drv/uc/uart.o ${OBJECTDIR}/src/sys/delay.o ${OBJECTDIR}/src/sys/ticks.o ${OBJECTDIR}/src/sys/timer.o ${OBJECTDIR}/src/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d ${OBJECTDIR}/src/app/serial_remote/local_functions.o.d ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d ${OBJECTDIR}/src/drv/uc/tmr.o.d ${OBJECTDIR}/src/drv/uc/uc.o.d ${OBJECTDIR}/src/drv/uc/uart.o.d ${OBJECTDIR}/src/sys/delay.o.d ${OBJECTDIR}/src/sys/ticks.o.d ${OBJECTDIR}/src/sys/timer.o.d ${OBJECTDIR}/src/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o ${OBJECTDIR}/src/app/serial_remote/r_gui.o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o ${OBJECTDIR}/src/app/serial_remote/r_mem.o ${OBJECTDIR}/src/app/serial_remote/local_functions.o ${OBJECTDIR}/src/drv/uc/configuration_bits.o ${OBJECTDIR}/src/drv/uc/tmr.o ${OBJECTDIR}/src/drv/uc/uc.o ${OBJECTDIR}/src/drv/uc/uart.o ${OBJECTDIR}/src/sys/delay.o ${OBJECTDIR}/src/sys/ticks.o ${OBJECTDIR}/src/sys/timer.o ${OBJECTDIR}/src/main.o

# Source Files
SOURCEFILES=src/app/serial_remote/pages/gui_demo.c src/app/serial_remote/pages/gui_demo_button.c src/app/serial_remote/pages/gui_demo_file_browser.c src/app/serial_remote/pages/gui_demo_graph2.c src/app/serial_remote/pages/gui_demo_keyboard.c src/app/serial_remote/pages/gui_demo_list.c src/app/serial_remote/pages/gui_demo_rbutton.c src/app/serial_remote/pages/gui_demo_text.c src/app/serial_remote/pages/gui_demo_valuebox.c src/app/serial_remote/serial_remote.c src/app/serial_remote/r_p2d.c src/app/serial_remote/r_gui.c src/app/serial_remote/serial_tx.c src/app/serial_remote/serial_rx.c src/app/serial_remote/r_mem.c src/app/serial_remote/local_functions.c src/drv/uc/configuration_bits.c src/drv/uc/tmr.c src/drv/uc/uc.c src/drv/uc/uart.c src/sys/delay.c src/sys/ticks.c src/sys/timer.c src/main.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o: src/app/serial_remote/pages/gui_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o src/app/serial_remote/pages/gui_demo.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o: src/app/serial_remote/pages/gui_demo_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o src/app/serial_remote/pages/gui_demo_button.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o: src/app/serial_remote/pages/gui_demo_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o src/app/serial_remote/pages/gui_demo_file_browser.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o: src/app/serial_remote/pages/gui_demo_graph2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o src/app/serial_remote/pages/gui_demo_graph2.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o: src/app/serial_remote/pages/gui_demo_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o src/app/serial_remote/pages/gui_demo_keyboard.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o: src/app/serial_remote/pages/gui_demo_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o src/app/serial_remote/pages/gui_demo_list.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o: src/app/serial_remote/pages/gui_demo_rbutton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o src/app/serial_remote/pages/gui_demo_rbutton.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o: src/app/serial_remote/pages/gui_demo_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o src/app/serial_remote/pages/gui_demo_text.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o: src/app/serial_remote/pages/gui_demo_valuebox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o src/app/serial_remote/pages/gui_demo_valuebox.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_remote.o: src/app/serial_remote/serial_remote.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o src/app/serial_remote/serial_remote.c  
	
${OBJECTDIR}/src/app/serial_remote/r_p2d.o: src/app/serial_remote/r_p2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o src/app/serial_remote/r_p2d.c  
	
${OBJECTDIR}/src/app/serial_remote/r_gui.o: src/app/serial_remote/r_gui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_gui.o src/app/serial_remote/r_gui.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_tx.o: src/app/serial_remote/serial_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o src/app/serial_remote/serial_tx.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_rx.o: src/app/serial_remote/serial_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o src/app/serial_remote/serial_rx.c  
	
${OBJECTDIR}/src/app/serial_remote/r_mem.o: src/app/serial_remote/r_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_mem.o src/app/serial_remote/r_mem.c  
	
${OBJECTDIR}/src/app/serial_remote/local_functions.o: src/app/serial_remote/local_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/local_functions.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/local_functions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/local_functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/local_functions.o.d" -o ${OBJECTDIR}/src/app/serial_remote/local_functions.o src/app/serial_remote/local_functions.c  
	
${OBJECTDIR}/src/drv/uc/configuration_bits.o: src/drv/uc/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" -o ${OBJECTDIR}/src/drv/uc/configuration_bits.o src/drv/uc/configuration_bits.c  
	
${OBJECTDIR}/src/drv/uc/tmr.o: src/drv/uc/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/tmr.o.d" -o ${OBJECTDIR}/src/drv/uc/tmr.o src/drv/uc/tmr.c  
	
${OBJECTDIR}/src/drv/uc/uc.o: src/drv/uc/uc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uc.o.d" -o ${OBJECTDIR}/src/drv/uc/uc.o src/drv/uc/uc.c  
	
${OBJECTDIR}/src/drv/uc/uart.o: src/drv/uc/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uart.o.d" -o ${OBJECTDIR}/src/drv/uc/uart.o src/drv/uc/uart.c  
	
${OBJECTDIR}/src/sys/delay.o: src/sys/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/delay.o.d 
	@${RM} ${OBJECTDIR}/src/sys/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/delay.o.d" -o ${OBJECTDIR}/src/sys/delay.o src/sys/delay.c  
	
${OBJECTDIR}/src/sys/ticks.o: src/sys/ticks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o.d 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/ticks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/ticks.o.d" -o ${OBJECTDIR}/src/sys/ticks.o src/sys/ticks.c  
	
${OBJECTDIR}/src/sys/timer.o: src/sys/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sys/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/timer.o.d" -o ${OBJECTDIR}/src/sys/timer.o src/sys/timer.c  
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  
	
else
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o: src/app/serial_remote/pages/gui_demo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo.o src/app/serial_remote/pages/gui_demo.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o: src/app/serial_remote/pages/gui_demo_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_button.o src/app/serial_remote/pages/gui_demo_button.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o: src/app/serial_remote/pages/gui_demo_file_browser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_file_browser.o src/app/serial_remote/pages/gui_demo_file_browser.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o: src/app/serial_remote/pages/gui_demo_graph2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_graph2.o src/app/serial_remote/pages/gui_demo_graph2.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o: src/app/serial_remote/pages/gui_demo_keyboard.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_keyboard.o src/app/serial_remote/pages/gui_demo_keyboard.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o: src/app/serial_remote/pages/gui_demo_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_list.o src/app/serial_remote/pages/gui_demo_list.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o: src/app/serial_remote/pages/gui_demo_rbutton.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_rbutton.o src/app/serial_remote/pages/gui_demo_rbutton.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o: src/app/serial_remote/pages/gui_demo_text.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_text.o src/app/serial_remote/pages/gui_demo_text.c  
	
${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o: src/app/serial_remote/pages/gui_demo_valuebox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote/pages 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o.d" -o ${OBJECTDIR}/src/app/serial_remote/pages/gui_demo_valuebox.o src/app/serial_remote/pages/gui_demo_valuebox.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_remote.o: src/app/serial_remote/serial_remote.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_remote.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_remote.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_remote.o src/app/serial_remote/serial_remote.c  
	
${OBJECTDIR}/src/app/serial_remote/r_p2d.o: src/app/serial_remote/r_p2d.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_p2d.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_p2d.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_p2d.o src/app/serial_remote/r_p2d.c  
	
${OBJECTDIR}/src/app/serial_remote/r_gui.o: src/app/serial_remote/r_gui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_gui.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_gui.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_gui.o src/app/serial_remote/r_gui.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_tx.o: src/app/serial_remote/serial_tx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_tx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_tx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_tx.o src/app/serial_remote/serial_tx.c  
	
${OBJECTDIR}/src/app/serial_remote/serial_rx.o: src/app/serial_remote/serial_rx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/serial_rx.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/serial_rx.o.d" -o ${OBJECTDIR}/src/app/serial_remote/serial_rx.o src/app/serial_remote/serial_rx.c  
	
${OBJECTDIR}/src/app/serial_remote/r_mem.o: src/app/serial_remote/r_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/r_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/r_mem.o.d" -o ${OBJECTDIR}/src/app/serial_remote/r_mem.o src/app/serial_remote/r_mem.c  
	
${OBJECTDIR}/src/app/serial_remote/local_functions.o: src/app/serial_remote/local_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/app/serial_remote 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/local_functions.o.d 
	@${RM} ${OBJECTDIR}/src/app/serial_remote/local_functions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/app/serial_remote/local_functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/app/serial_remote/local_functions.o.d" -o ${OBJECTDIR}/src/app/serial_remote/local_functions.o src/app/serial_remote/local_functions.c  
	
${OBJECTDIR}/src/drv/uc/configuration_bits.o: src/drv/uc/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/configuration_bits.o.d" -o ${OBJECTDIR}/src/drv/uc/configuration_bits.o src/drv/uc/configuration_bits.c  
	
${OBJECTDIR}/src/drv/uc/tmr.o: src/drv/uc/tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/tmr.o.d" -o ${OBJECTDIR}/src/drv/uc/tmr.o src/drv/uc/tmr.c  
	
${OBJECTDIR}/src/drv/uc/uc.o: src/drv/uc/uc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uc.o.d" -o ${OBJECTDIR}/src/drv/uc/uc.o src/drv/uc/uc.c  
	
${OBJECTDIR}/src/drv/uc/uart.o: src/drv/uc/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/drv/uc 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o.d 
	@${RM} ${OBJECTDIR}/src/drv/uc/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drv/uc/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/drv/uc/uart.o.d" -o ${OBJECTDIR}/src/drv/uc/uart.o src/drv/uc/uart.c  
	
${OBJECTDIR}/src/sys/delay.o: src/sys/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/delay.o.d 
	@${RM} ${OBJECTDIR}/src/sys/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/delay.o.d" -o ${OBJECTDIR}/src/sys/delay.o src/sys/delay.c  
	
${OBJECTDIR}/src/sys/ticks.o: src/sys/ticks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o.d 
	@${RM} ${OBJECTDIR}/src/sys/ticks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/ticks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/ticks.o.d" -o ${OBJECTDIR}/src/sys/ticks.o src/sys/ticks.c  
	
${OBJECTDIR}/src/sys/timer.o: src/sys/timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/sys 
	@${RM} ${OBJECTDIR}/src/sys/timer.o.d 
	@${RM} ${OBJECTDIR}/src/sys/timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/sys/timer.o.d" -o ${OBJECTDIR}/src/sys/timer.o src/sys/timer.c  
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mno-float -I"src/" -I"src/drv/uc" -I"src/sys" -I"src/app" -I"src/app/serial_remote" -I"src/app/serial_remote/pages" -I"src/app/serial_remote/inc" -O3 -Wall -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1 
else
dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O3 -o dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/smart_lcd_master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
