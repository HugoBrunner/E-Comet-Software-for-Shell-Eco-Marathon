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
FINAL_IMAGE=${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../Firmware/Srs/Source/Main.c ../Firmware/Srs/Source/X2CScope.c ../Firmware/Srs/Source/X2CScopeComm.c ../Firmware/Srs/Source/init_dspic.c ../Firmware/Srs/Source/uart1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/410712389/Main.o ${OBJECTDIR}/_ext/410712389/X2CScope.o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o ${OBJECTDIR}/_ext/410712389/init_dspic.o ${OBJECTDIR}/_ext/410712389/uart1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/410712389/Main.o.d ${OBJECTDIR}/_ext/410712389/X2CScope.o.d ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d ${OBJECTDIR}/_ext/410712389/init_dspic.o.d ${OBJECTDIR}/_ext/410712389/uart1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/410712389/Main.o ${OBJECTDIR}/_ext/410712389/X2CScope.o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o ${OBJECTDIR}/_ext/410712389/init_dspic.o ${OBJECTDIR}/_ext/410712389/uart1.o

# Source Files
SOURCEFILES=../Firmware/Srs/Source/Main.c ../Firmware/Srs/Source/X2CScope.c ../Firmware/Srs/Source/X2CScopeComm.c ../Firmware/Srs/Source/init_dspic.c ../Firmware/Srs/Source/uart1.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33CK32MP105
MP_LINKER_FILE_OPTION=,--script=p33CK32MP105.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/410712389/Main.o: ../Firmware/Srs/Source/Main.c  .generated_files/flags/default/d7573228549c0a45667b348ee5865b6de626d04f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/Main.c  -o ${OBJECTDIR}/_ext/410712389/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/Main.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScope.o: ../Firmware/Srs/Source/X2CScope.c  .generated_files/flags/default/389af801eab56ec823a7fd8f3771d7319d9eb976 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScope.c  -o ${OBJECTDIR}/_ext/410712389/X2CScope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScope.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScopeComm.o: ../Firmware/Srs/Source/X2CScopeComm.c  .generated_files/flags/default/fab8ee2afbe0d6039f07d018ea25bf925e2484d6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScopeComm.c  -o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/init_dspic.o: ../Firmware/Srs/Source/init_dspic.c  .generated_files/flags/default/1777db831f38e2d5b7e8539397529b399ad3bf0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/init_dspic.c  -o ${OBJECTDIR}/_ext/410712389/init_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/init_dspic.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/uart1.o: ../Firmware/Srs/Source/uart1.c  .generated_files/flags/default/fcd404c23fc587fecbb0192cc9b4ae3384bf06fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/uart1.c  -o ${OBJECTDIR}/_ext/410712389/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/_ext/410712389/Main.o: ../Firmware/Srs/Source/Main.c  .generated_files/flags/default/cfb1812ccbb7731bccd38f3fc8d20745c317ae0d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/Main.c  -o ${OBJECTDIR}/_ext/410712389/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/Main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScope.o: ../Firmware/Srs/Source/X2CScope.c  .generated_files/flags/default/1e619fb724cc076c98d6a335a4f56157b04d2966 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScope.c  -o ${OBJECTDIR}/_ext/410712389/X2CScope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScope.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScopeComm.o: ../Firmware/Srs/Source/X2CScopeComm.c  .generated_files/flags/default/1df5e7b0a7cce17f02d7c52becb6ef87234f3090 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScopeComm.c  -o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/init_dspic.o: ../Firmware/Srs/Source/init_dspic.c  .generated_files/flags/default/bbbfdcca17778bdae718bc187ac670ef00050427 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/init_dspic.c  -o ${OBJECTDIR}/_ext/410712389/init_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/init_dspic.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/uart1.o: ../Firmware/Srs/Source/uart1.c  .generated_files/flags/default/7463e9c8c64de599043734b39e6a5d4afb83e2d8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/uart1.c  -o ${OBJECTDIR}/_ext/410712389/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/uart1.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
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
${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Firmware/Srs/Lib/libx2cscope-33ck-elf.a ../Firmware/Srs/Lib/Kick_scooter.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ..\Firmware\Srs\Lib\libx2cscope-33ck-elf.a ..\Firmware\Srs\Lib\Kick_scooter.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include"  -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library="q",--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	
else
${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Firmware/Srs/Lib/libx2cscope-33ck-elf.a ../Firmware/Srs/Lib/Kick_scooter.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}    ..\Firmware\Srs\Lib\libx2cscope-33ck-elf.a ..\Firmware\Srs\Lib\Kick_scooter.X.a  -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -I"../Firmware/Srs/Include" -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--library="q",--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/KICK_SCOOTER.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}
