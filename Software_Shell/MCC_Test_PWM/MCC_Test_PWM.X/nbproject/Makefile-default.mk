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
FINAL_IMAGE=${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../main.c ../mcc_generated_files/clock.c ../mcc_generated_files/interrupt_manager.c ../mcc_generated_files/mcc.c ../mcc_generated_files/pin_manager.c ../mcc_generated_files/pwm.c ../mcc_generated_files/reset.c ../mcc_generated_files/system.c ../mcc_generated_files/traps.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1769188794/clock.o ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o ${OBJECTDIR}/_ext/1769188794/mcc.o ${OBJECTDIR}/_ext/1769188794/pin_manager.o ${OBJECTDIR}/_ext/1769188794/pwm.o ${OBJECTDIR}/_ext/1769188794/reset.o ${OBJECTDIR}/_ext/1769188794/system.o ${OBJECTDIR}/_ext/1769188794/traps.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1769188794/clock.o.d ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o.d ${OBJECTDIR}/_ext/1769188794/mcc.o.d ${OBJECTDIR}/_ext/1769188794/pin_manager.o.d ${OBJECTDIR}/_ext/1769188794/pwm.o.d ${OBJECTDIR}/_ext/1769188794/reset.o.d ${OBJECTDIR}/_ext/1769188794/system.o.d ${OBJECTDIR}/_ext/1769188794/traps.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1769188794/clock.o ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o ${OBJECTDIR}/_ext/1769188794/mcc.o ${OBJECTDIR}/_ext/1769188794/pin_manager.o ${OBJECTDIR}/_ext/1769188794/pwm.o ${OBJECTDIR}/_ext/1769188794/reset.o ${OBJECTDIR}/_ext/1769188794/system.o ${OBJECTDIR}/_ext/1769188794/traps.o

# Source Files
SOURCEFILES=../main.c ../mcc_generated_files/clock.c ../mcc_generated_files/interrupt_manager.c ../mcc_generated_files/mcc.c ../mcc_generated_files/pin_manager.c ../mcc_generated_files/pwm.c ../mcc_generated_files/reset.c ../mcc_generated_files/system.c ../mcc_generated_files/traps.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK32MP105
MP_LINKER_FILE_OPTION=,--script=p33CK32MP105.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/935b58a8952d41b107e502b5a7c2872f36420dca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/clock.o: ../mcc_generated_files/clock.c  .generated_files/flags/default/c98d3eab49077d4f25aed388842fc29101de2630 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/1769188794/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/clock.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/interrupt_manager.o: ../mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/43256b874f13b1a4653a398baa6125d46522931b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/interrupt_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/mcc.o: ../mcc_generated_files/mcc.c  .generated_files/flags/default/3f988f4aa6812919ba2284da3d9af958f7496cbb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/1769188794/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/mcc.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/pin_manager.o: ../mcc_generated_files/pin_manager.c  .generated_files/flags/default/8c9fc6331b1164952d4927a821df486720e177c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/1769188794/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/pin_manager.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/pwm.o: ../mcc_generated_files/pwm.c  .generated_files/flags/default/3526681dafd7f58800eb7092dcf5b24d198dafd2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/pwm.c  -o ${OBJECTDIR}/_ext/1769188794/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/pwm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/reset.o: ../mcc_generated_files/reset.c  .generated_files/flags/default/2eedb87938e25774a8685330eec07c1a538f6651 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/reset.c  -o ${OBJECTDIR}/_ext/1769188794/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/reset.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/system.o: ../mcc_generated_files/system.c  .generated_files/flags/default/106916d87f9f5a8a9c0dbf78811dca7b20ab3971 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/1769188794/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/system.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/traps.o: ../mcc_generated_files/traps.c  .generated_files/flags/default/53848421f8e12c14d90c2d3a327134fb566aed0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/1769188794/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/traps.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  .generated_files/flags/default/c242f67a9c313500c77ba17a31bdd1f44dbc3c93 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../main.c  -o ${OBJECTDIR}/_ext/1472/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/clock.o: ../mcc_generated_files/clock.c  .generated_files/flags/default/ebcdb0f2d7fa2e39f72e0a501afc8f444d243383 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/clock.c  -o ${OBJECTDIR}/_ext/1769188794/clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/clock.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/interrupt_manager.o: ../mcc_generated_files/interrupt_manager.c  .generated_files/flags/default/2484662c1527b2d2bb3f29f0f30abbc3c6627714 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/interrupt_manager.c  -o ${OBJECTDIR}/_ext/1769188794/interrupt_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/interrupt_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/mcc.o: ../mcc_generated_files/mcc.c  .generated_files/flags/default/d1ac9b55e6ff814fe803b46e50bf78f7dd35ccfb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/mcc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/mcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/mcc.c  -o ${OBJECTDIR}/_ext/1769188794/mcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/mcc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/pin_manager.o: ../mcc_generated_files/pin_manager.c  .generated_files/flags/default/51ae73514712a5a944ee0290fd1206e26feb404f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pin_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pin_manager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/pin_manager.c  -o ${OBJECTDIR}/_ext/1769188794/pin_manager.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/pin_manager.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/pwm.o: ../mcc_generated_files/pwm.c  .generated_files/flags/default/cd086fe571359d3a48f75cc33c7cef2a5faf0260 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/pwm.c  -o ${OBJECTDIR}/_ext/1769188794/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/pwm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/reset.o: ../mcc_generated_files/reset.c  .generated_files/flags/default/c7b37314083f2a354e35ab7bcd1d268918981a91 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/reset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/reset.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/reset.c  -o ${OBJECTDIR}/_ext/1769188794/reset.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/reset.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/system.o: ../mcc_generated_files/system.c  .generated_files/flags/default/ee494c116bb36d40b659bf77b2a2fd552a3bde63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/system.c  -o ${OBJECTDIR}/_ext/1769188794/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1769188794/traps.o: ../mcc_generated_files/traps.c  .generated_files/flags/default/94d580eea86041230a40444579e5c7ac0580d998 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1769188794" 
	@${RM} ${OBJECTDIR}/_ext/1769188794/traps.o.d 
	@${RM} ${OBJECTDIR}/_ext/1769188794/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mcc_generated_files/traps.c  -o ${OBJECTDIR}/_ext/1769188794/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1769188794/traps.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/MCC_Test_PWM.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
