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
#ifndef USERPARMS_H
#define USERPARMS_H

#ifdef __cplusplus
extern "C" {
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "../hal/clock.h"

#ifdef __XC16__  // See comments at the top of this header file
    #include <xc.h>
#endif // __XC16__

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************
#define TURN_ON      1
#define TURN_OFF     0
#define ONE_MIN      1200000UL
/*************** PWM and Control Timing Parameters ****************************/
/* Specify PWM Frequency in Hertz */
#define PWMFREQUENCY_HZ         20000
/* Specify dead time in micro seconds */
/* Specify PWM Period in seconds, (1/ PWMFREQUENCY_HZ) */
#define LOOPTIME_SEC            0.00005


/*********************************** ADC Scaling ******************************/
/* Scaling constants: Determined by calibration or hardware design. */

/* scaling factor for pot */
#define KPOT        Q15(0.5)
/* scaling factor for current phase A */
#define KCURRA      Q15(0.5)
/* scaling factor for current phase B */
#define KCURRB      Q15(0.5) 
#define SCALER      10
/****************************** Motor Parameters ******************************/
/********************  support xls file definitions begin *********************/
/* The following values are given in the xls attached file */

/* Motor's number of pole pairs */
#define NOPOLESPAIRS         15
/* Open loop speed ramp up end value Value in RPM*/
#define MINIMUM_SPEED_RPM    150    //2250 elec speed, 160=2400
/* Maximum speed of the motor in RPM - given by the motor's manufacturer */
#define MAXIMUM_SPEED_RPM    600
    
#define MINIMUM_SPEED_ELECTR   (MINIMUM_SPEED_RPM * NOPOLESPAIRS)
#define MAXIMUM_SPEED_ELECTR   (MAXIMUM_SPEED_RPM * NOPOLESPAIRS)
#define SPEED_MULTIPLIER_1      10500
#define SPEED_MULTIPLIER_2      12500
    
    
#define FW_NOMINAL_SPEED_RPM    2700

/* The following values are given in the xls attached file */
#define NORM_CURRENT_CONST  0.000214

#define TIMER_PRESCALER     64
// Period Calculation
// Period = (FCY / TIMER_PRESCALE) / (RPM * NO_POLEPAIRS )/10
#define MAXPERIOD	(unsigned long)(((float)FCY / (float)TIMER_PRESCALER) / (float)((MINIMUM_SPEED_RPM * NOPOLESPAIRS)/10))	
#define MINPERIOD	(unsigned long)(((float)FCY / (float)TIMER_PRESCALER) / (float)((MAXIMUM_SPEED_RPM * NOPOLESPAIRS)/10))
//Maximum number of ticks in lowest speed for the counter used
#define PERIOD_CONSTANT  (unsigned long)((float)MAXPERIOD *(float)MINIMUM_SPEED_RPM) 
    
//(FCY/(TIMER_PRESCALER*FPWM)*(65536/6))
#define PHASE_INC_CALC  (unsigned long)((float)FCY/((float)(TIMER_PRESCALER)*(float)(PWMFREQUENCY_HZ))*(float)(65536/6))  //(unsigned long)(269040)//  
/**  SPEED MULTIPLIER CALCULATION = ((FCY*60)/(TIMER_PRESCALER*POLEPAIRS)) ---FOR RPM  */
#define SPEED_MULTI_PER     (unsigned long)(((float)FCY/(float)(TIMER_PRESCALER))*(float)10) //per sector *60
#define SPEED_MULTI_ELEC    (unsigned long)(((float)FCY/(float)(TIMER_PRESCALER))*(float)60)

/**********************  support xls file definitions end *********************/

/* current transformation macro, used below */
#define NORM_CURRENT(current_real) (Q15(current_real/NORM_CURRENT_CONST/32768))

/* Open loop q current setup - */
#define Q_CURRENT_REF_OPENLOOP   NORM_CURRENT(0.1373) 

/* In case of the potentiometer speed reference, a reference ramp
is needed for assuring the motor can follow the reference imposed /
minimum value accepted */
#define SPEEDREFRAMP   Q15(0.00006)

/* The Speed Control Loop Executes every  SPEEDREFRAMP_COUNT */
#define SPEEDREFRAMP_COUNT   2
/* PI controllers tuning values - */

/* D Control Loop Coefficients */
#define D_CURRCNTR_PTERM       Q15(0.02)
#define D_CURRCNTR_ITERM       Q15(0.001)
#define D_CURRCNTR_CTERM       Q15(0.999)
#define D_CURRCNTR_OUTMAX      0x7FFF

/* Q Control Loop Coefficients */
#define Q_CURRCNTR_PTERM       Q15(0.02)
#define Q_CURRCNTR_ITERM       Q15(0.001)
#define Q_CURRCNTR_CTERM       Q15(0.999)
#define Q_CURRCNTR_OUTMAX      0x7FFF        

/* Velocity Control Loop Coefficients */
#define SPEEDCNTR_PTERM        Q15(0.4)
#define SPEEDCNTR_ITERM        Q15(0.009) 
#define SPEEDCNTR_CTERM        Q15(0.999)
#define SPEEDCNTR_OUTMAX       0x3500   

#define OVERCURRENT_COUNTER    10000
#define VOLTAGE_LIMITER        562
#define UNDERVOLTAGE_COUNTER   20000
#define OVERTEMP_LIMITER_57    225
#define OVERTEMP_LIMITER_45    230
#define OVERTEMP_LIMITER_35    235
#define OVERTEMP_MOSFET_60     128
#define OVERTEMP_COUNTER       20
#define UNDERVOLTAGE_INDICATOR 200
#define BRAKE_COUNTER          20

//***********************SMC Params*********************************************//
#define LOOPTIMEINSEC (1.0/PWMFREQUENCY_HZ) // PWM Period = 1.0 / PWMFREQUENCY
#define MAX_VOLTAGE_VECTOR                      0.98
        
/******************************** Field Weakening *****************************/
/* Field Weakening constant for constant torque range 
   Flux reference value */
#define IDREF_BASESPEED         NORM_CURRENT(0.0)

/*-------------------------------------------------------------
   IMPORTANT:--------------------------------------------------
  -------------------------------------------------------------
   In flux weakening of the surface mounted permanent magnets
   PMSMs the mechanical damage of the rotor and the
   demagnetization of the permanent magnets is possible if
   cautions measures are not taken or the motor’s producer
   specifications are not respected.
  -------------------------------------------------------------
   IMPORTANT:--------------------------------------------------
  -------------------------------------------------------------
   In flux weakening regime implementation, if the FOC is lost
   at high speed above the nominal value, the possibility of
   damaging the inverter is eminent. The reason is that the
   BEMF will have a greater value than the one that would be
   obtained for the nominal speed exceeding the DC bus voltage
   value and though the inverter’s power semiconductors and DC
   link capacitors would have to support it. Since the tuning
   proposed implies iterative coefficient corrections until
   the optimum functioning is achieved, the protection of the
   inverter with corresponding circuitry should be assured in
   case of stalling at high speeds.                            */

/* speed index is increase */
#define SPEED_INDEX_CONST 10

#define FWONSPEED FW_NOMINAL_SPEED_RPM*NOPOLESPAIRS

/* the following values indicate the d-current variation with speed 
 please consult app note for details on tuning */
#define	IDREF_SPEED0	NORM_CURRENT(0)     /* up to 2800 RPM */
#define	IDREF_SPEED1	NORM_CURRENT(-0.7)  /* ~2950 RPM */
#define	IDREF_SPEED2	NORM_CURRENT(-0.9)  /* ~3110 RPM */
#define	IDREF_SPEED3	NORM_CURRENT(-1.0)  /* ~3270 RPM */
#define	IDREF_SPEED4	NORM_CURRENT(-1.4)  /* ~3430 RPM */
#define	IDREF_SPEED5	NORM_CURRENT(-1.7)  /* ~3600 RPM */
#define	IDREF_SPEED6	NORM_CURRENT(-2.0)  /* ~3750 RPM */
#define	IDREF_SPEED7	NORM_CURRENT(-2.1)  /* ~3910 RPM */
#define	IDREF_SPEED8	NORM_CURRENT(-2.2)  /* ~4070 RPM */
#define	IDREF_SPEED9	NORM_CURRENT(-2.25) /* ~4230 RPM */
#define	IDREF_SPEED10	NORM_CURRENT(-2.3)  /* ~4380 RPM */
#define	IDREF_SPEED11	NORM_CURRENT(-2.35) /* ~4550 RPM */
#define	IDREF_SPEED12	NORM_CURRENT(-2.4)  /* ~4700 RPM */
#define	IDREF_SPEED13	NORM_CURRENT(-2.45) /* ~4860 RPM */
#define	IDREF_SPEED14	NORM_CURRENT(-2.5)  /* ~5020 RPM */
#define	IDREF_SPEED15	NORM_CURRENT(-2.5)  /* ~5180 RPM */
#define	IDREF_SPEED16	NORM_CURRENT(-2.5)  /* ~5340 RPM */
#define	IDREF_SPEED17	NORM_CURRENT(-2.5)  /* ~5500 RPM */

void OverCurrentEnable(void);
void CMP1_ISR(void);
// This pre-processor condition will generate an error if maximum speed is out of
// range on Q15 when calculating Omega.
//#if (FW_NOMINAL_SPEED_RPM < NOMINAL_SPEED_RPM)
//	#error FIELDWEAKSPEEDRPM must be greater than NOMINALSPEEDINRPM for field weakening.
//	#error if application does not require Field Weakening, set FIELDWEAKSPEEDRPM value
//	#error equal to NOMINALSPEEDINRPM
//#elif (((FW_NOMINAL_SPEED_RPM*NOPOLESPAIRS*2)/(60*SPEEDLOOPFREQ)) >= 1)
//		#error FIELDWEAKSPEEDRPM will generate an Omega value greater than 1 which is the
//		#error maximum in Q15 format. Reduce FIELDWEAKSPEEDRPM value, or increase speed
//		#error control loop frequency, SPEEDLOOPFREQ
//#endif
/******************** End of Field Weakening Params ***************************/

#ifdef __cplusplus
}
#endif

#endif /* USERPARMS_H */
