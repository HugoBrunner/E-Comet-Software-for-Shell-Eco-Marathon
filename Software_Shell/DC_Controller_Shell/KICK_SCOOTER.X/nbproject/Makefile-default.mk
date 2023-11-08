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
${OBJECTDIR}/_ext/410712389/Main.o: ../Firmware/Srs/Source/Main.c  .generated_files/flags/default/956fcf4cb4fe0d482a7f712f094dd7f5f43527c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/Main.c  -o ${OBJECTDIR}/_ext/410712389/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/Main.o.d"      -g -D__DEBUG   -mno-eds-warn  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScope.o: ../Firmware/Srs/Source/X2CScope.c  .generated_files/flags/default/47cbaaf0deb9a672700297db4649cdbb0dfc15c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScope.c  -o ${OBJECTDIR}/_ext/410712389/X2CScope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScope.o.d"      -g -D__DEBUG   -mno-eds-warn  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScopeComm.o: ../Firmware/Srs/Source/X2CScopeComm.c  .generated_files/flags/default/676b59d4413cc6c014ce89f530556cf986613c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScopeComm.c  -o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d"      -g -D__DEBUG   -mno-eds-warn  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/init_dspic.o: ../Firmware/Srs/Source/init_dspic.c  .generated_files/flags/default/728574192efe8ed36ea58316cb627b9bba198c13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/init_dspic.c  -o ${OBJECTDIR}/_ext/410712389/init_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/init_dspic.o.d"      -g -D__DEBUG   -mno-eds-warn  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/uart1.o: ../Firmware/Srs/Source/uart1.c  .generated_files/flags/default/aafd2c4adcaccc7ca3fdf2db69682661fae87435 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/uart1.c  -o ${OBJECTDIR}/_ext/410712389/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/uart1.o.d"      -g -D__DEBUG   -mno-eds-warn  -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
else
${OBJECTDIR}/_ext/410712389/Main.o: ../Firmware/Srs/Source/Main.c  .generated_files/flags/default/288b664ab728c5fc9fb9d8d21da8767c4e68a06d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/Main.c  -o ${OBJECTDIR}/_ext/410712389/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/Main.o.d"      -mno-eds-warn  -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScope.o: ../Firmware/Srs/Source/X2CScope.c  .generated_files/flags/default/5f732ed098eedd46f6cf5e03f514112a164d541b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScope.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScope.c  -o ${OBJECTDIR}/_ext/410712389/X2CScope.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScope.o.d"      -mno-eds-warn  -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/X2CScopeComm.o: ../Firmware/Srs/Source/X2CScopeComm.c  .generated_files/flags/default/6b7d3cbe34525d6965283916fd254e459c5d874f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/X2CScopeComm.c  -o ${OBJECTDIR}/_ext/410712389/X2CScopeComm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/X2CScopeComm.o.d"      -mno-eds-warn  -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/init_dspic.o: ../Firmware/Srs/Source/init_dspic.c  .generated_files/flags/default/20d85130684a1d6557dc074c66b060d642b4d67a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/init_dspic.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/init_dspic.c  -o ${OBJECTDIR}/_ext/410712389/init_dspic.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/init_dspic.o.d"      -mno-eds-warn  -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
${OBJECTDIR}/_ext/410712389/uart1.o: ../Firmware/Srs/Source/uart1.c  .generated_files/flags/default/e46913d1e07f3424a33894e6aba00357d73d8c4d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/410712389" 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o.d 
	@${RM} ${OBJECTDIR}/_ext/410712389/uart1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Firmware/Srs/Source/uart1.c  -o ${OBJECTDIR}/_ext/410712389/uart1.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/410712389/uart1.o.d"      -mno-eds-warn  -g -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O1 -I"../Firmware/Srs/Source" -msmart-io=1 -Wall -msfr-warn=off   
	
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

