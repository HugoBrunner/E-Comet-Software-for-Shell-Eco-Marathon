/*******************************************************************************
* Copyright (c) 2020 released Microchip Technology Inc.  All rights reserved.
*
* SOFTWARE LICENSE AGREEMENT:
* 
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in all
* derivatives hereto.  You may use this code, and any derivatives created by
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE,
* WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
* STATUTORY DUTY),STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE,
* FOR ANY INDIRECT, SPECIAL,PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE,
* HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR
* THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW,
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS CODE,
* SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/

#ifndef __CONTROL_H
#define __CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sccp3_tmr.h"

#define PERIOD_MOVING_AVG_FILTER_SCALE     4
#define PERIOD_MOVING_AVG_FILTER_SIZE       (uint16_t)(1 << PERIOD_MOVING_AVG_FILTER_SCALE) 
#define SPEED_MOVING_AVG_FILTER_SCALE      6
#define SPEED_MOVING_AVG_FILTER_SIZE       (uint16_t)(1 << SPEED_MOVING_AVG_FILTER_SCALE) 
    
#define HAL_MC1PhaseStateChangeMaxPeriodSet          SCCP3_TMR_Period32BitSet
    
/* Control Parameter data type

  Description:
    This structure will host parameters related to application control
    parameters.
 */
typedef struct
{
    /* Reference velocity */
    int16_t   qVelRef;
    /* Vd flux reference value */
    int16_t   qVdRef;
    /* Vq torque reference value */
    int16_t   qVqRef;
    /* Ramp for speed reference value */
    int16_t   qRefRamp;
    /* Speed of the ramp */
    int16_t   qDiff;
    /* The Speed Control Loop will be executed only every speedRampCount*/
    int16_t   speedRampCount; 
} CTRL_PARM_T;
/* Motor Parameter data type

  Description:
    This structure will host parameters related to motor parameters.
*/
typedef struct
{
    /* Start up ramp in open loop. */
    uint32_t startupRamp;
    /* counter that is incremented in CalculateParkAngle() up to LOCK_TIME,*/
    uint16_t startupLock;
    /* Start up ramp increment */
    uint16_t tuningAddRampup;	
    uint16_t tuningDelayRampup;
} MOTOR_STARTUP_DATA_T;

/* General system flag data type

  Description:
    This structure will host parameters related to application system flags.
 */
typedef union
{
    struct
    {
        /* Run motor indication */
        unsigned RunMotor:1;
        /* Open loop/closed loop indication */
        unsigned OpenLoop:1;
        /* Mode changed indication - from open to closed loop */
        unsigned ChangeMode:1;
        /* Speed doubled indication */
        unsigned ChangeSpeed:1;
       /* Unused bits */
        unsigned    :12;
    } bits;
    uint16_t Word;
} UGF_T;

typedef struct 
{
    uint32_t calculatedSpeed;  
    uint16_t index;
    int16_t buffer[6];
    int32_t sum;
    int16_t avg;    //changed
} MCAPP_SPEED_SUMMATION;

typedef struct 
{
    uint16_t index;
    int16_t buffer[PERIOD_MOVING_AVG_FILTER_SIZE];
    int32_t sum;
    uint16_t avg;
} MCAPP_PERIOD_MOVING_AVG_T;

typedef struct
{
    uint16_t calculatedSpeed;

    uint16_t index;
    int16_t buffer[SPEED_MOVING_AVG_FILTER_SIZE];
    int32_t sum;
    int16_t avg;
} MCAPP_SPEED_MOVING_AVG_T;

typedef struct 
{
    uint16_t state;
    uint16_t avgPeriod;
    uint16_t phaseInc;     

    volatile uint8_t sector;

    MCAPP_SPEED_MOVING_AVG_T movingAvgFilterSpeed;
    MCAPP_PERIOD_MOVING_AVG_T movingAvgFilterPeriod;
    MCAPP_SPEED_SUMMATION movingbuffer;
} MCAPP_DATA_T;

typedef struct 
{
    volatile uint16_t counter;
    volatile uint16_t indicator;
    volatile uint16_t monitor;    
    volatile uint16_t measure;
} FAULT_DATA_T;

extern volatile CTRL_PARM_T ctrlParm;
extern MOTOR_STARTUP_DATA_T motorStartUpData;
extern MC_ALPHABETA_T valphabeta,ialphabeta;
extern MC_ALPHABETA_T valphabeta,ialphabeta;
extern MC_SINCOS_T sincosTheta;
extern MC_DQ_T vdq,idq;
extern MC_DUTYCYCLEOUT_T pwmDutycycle;
extern MC_ABC_T   vabc,iabc;
extern volatile FAULT_DATA_T fault;

inline static uint16_t PWM_MasterPeriodRead(void)
{
    return MPER;
}

inline static void CN_PortCEnable(void){CNCONCbits.ON = 1;}

inline static void CN_PortCDisable(void){CNCONCbits.ON = 0;}

#ifdef __cplusplus
}
#endif

#endif /* __CONTORL_H */
