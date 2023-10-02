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
#ifdef __XC16__  // See comments at the top of this header file
#include <xc.h>
#endif // __XC16__
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <libq.h>  

#include "src/motor_control_noinline.h"

#include "src/general.h"   
#include "src/userparms.h"

#include "src/control.h"   
#include "src/fdweak.h"

#include "src/readadc.h"   
#include "src/meascurr.h" 
#include "src/sccp3_tmr.h"

#include "hal/board_service.h"

#include "diagnostics/diagnostics.h"

volatile UGF_T uGF;

volatile CTRL_PARM_T ctrlParm;
MOTOR_STARTUP_DATA_T motorStartUpData;

MCAPP_DATA_T mcappData;

MEAS_CURR_PARM_T measCurrParm;   
READ_ADC_PARM_T readADCParm;  

volatile int16_t thetaElectrical = 0 ;
uint16_t pwmPeriod;

MC_ALPHABETA_T valphabeta,ialphabeta;
MC_SINCOS_T sincosTheta;
MC_DQ_T vdq,idq;
MC_DUTYCYCLEOUT_T pwmDutycycle;
MC_ABC_T   vabc,iabc;

MC_PIPARMIN_T piInputIq;
MC_PIPARMOUT_T piOutputIq;
MC_PIPARMIN_T piInputId;
MC_PIPARMOUT_T piOutputId;
MC_PIPARMIN_T piInputOmega;
MC_PIPARMOUT_T piOutputOmega;
volatile FAULT_DATA_T faultUndervoltage;
volatile FAULT_DATA_T faultOverTempMCU;
volatile FAULT_DATA_T faultOverTempMOSFET;
volatile FAULT_DATA_T faultOverCurrent;

volatile uint16_t adcDataBuffer;
volatile uint16_t measCurrOffsetFlag = 0;

volatile signed int HallAngle;

bool FindHallStart;
int16_t HallOffset = 5461;  

uint8_t oldHallState = 0;

const int16_t PhaseValues[8] = {0, 0, -21844, -10922, 21844, 10922, 32767, 0}; 

volatile uint32_t PastCapture, ActualCapture;
volatile uint32_t Period, AvgPeriod;
volatile uint16_t hallValue;

volatile uint16_t startUpCounter = 0;
volatile uint32_t idleCounter = 0;

void InitControlParameters(void);
void DoControl(void);
void ResetParmeters(void);
void MeasCurrOffset(int16_t *,int16_t *);

void CalculateParkAngleHall(void);
void InitMovingAvgPeriod(void);
void CalcMovingAvgPeriod(uint16_t instPeriod);
void CalcMovingAvgSpeed(int32_t instSpeed);
void UndervoltageDetect(void);
void OvertemperatureDetectMCU(void);
void OvertemperatureDetectMOSFET(void);

// *****************************************************************************
/* Function:
   main()

  Summary:
    main() function

  Description:
    program entry point, calls the system initialization function group 

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */

int main ( void )
{
    /* Initialize Peripherals */
    Init_Peripherals();
    SCCP3_TMR_Initialize();
    CN_Configure();
    
    OverCurrentEnable();

    /* Initializing Current offsets in structure variable */
    MeasCurrOffset(&measCurrParm.Offseta, &measCurrParm.Offsetb);
    HAL_MC1PhaseStateChangeMaxPeriodSet(PERIOD_CONSTANT);
    
    CORCONbits.SATA = 1;
    CORCONbits.SATB = 1;
    CORCONbits.ACCSAT = 1;

    CORCONbits.SATA = 0;
    LATCbits.LATC11 = TURN_ON;

    while(1)
    {
        /* Initialize PI control parameters */
        InitControlParameters();

        /* Reset parameters used for running motor through Inverter */
        ResetParmeters();
        
        /* Uncomment to enable throttle control*/
        CN_PortCEnable();
        FindHallStart = 1;
        
        while(1)
        {
           
        }//inner while loop

    }//outer while loop
    // should never get here
    while(1){}
}// End of Main loop

// *****************************************************************************
/* Function:
    ResetParmeters()

  Summary:
    This routine resets all the parameters required for Motor 

  Description:
    Reinitializes the duty cycle,resets all the counters when restarting motor

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void ResetParmeters(void)
{
    /* Make sure ADC does not generate interrupt while initializing parameters*/
	DisableADCInterrupt();
    
    /* Re initialize the duty cycle to minimum value */
    INVERTERA_PWM_PDC3 = MIN_DUTY;
    INVERTERA_PWM_PDC2 = MIN_DUTY;
    INVERTERA_PWM_PDC1 = MIN_DUTY;
	HAL_MC1PWMDisableOutputs();
    
    /* Stop the motor   */
    uGF.bits.RunMotor = 0;
    /* Set the reference speed value to 0 */
    ctrlParm.qVelRef = 0;
    /* Change speed */
    uGF.bits.ChangeSpeed = 0;
    /* Change mode */
    uGF.bits.ChangeMode = 1;

   /* Initialize PI control parameters */
    InitControlParameters();        
    
    faultUndervoltage.counter = 0;
    faultOverCurrent.counter = 0;
    faultOverTempMCU.counter = 0;
    faultOverTempMOSFET.counter = 0;
    faultOverTempMCU.indicator = 0;

    InitMovingAvgPeriod();
    
    piInputOmega.inReference = 0;
    piInputOmega.inMeasure = 0;
    mcappData.movingAvgFilterSpeed.avg = 0;
    readADCParm.qPrevAnRef = 0;
    pwmDutycycle.dutycycle = 0;
    
    /* Enable ADC interrupt and begin main loop timing */
    ClearADCIF();
	adcDataBuffer = ClearADCIF_ReadADCBUF();
    EnableADCInterrupt();
}

// *****************************************************************************
/* Function:
    DoControl()

  Summary:
    Executes one PI iteration for each of the three loops Id,Iq,Speed

  Description:
    This routine executes one PI iteration for each of the three loops
    Id,Iq,Speed

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void DoControl( void )
{
    /* Temporary variables for sqrt calculation of q reference */
    volatile int16_t temp_qref_pow_q15;

    if(FindHallStart)
    {
        /* Speed reference */
        ctrlParm.qVelRef = Q_CURRENT_REF_OPENLOOP;
        /* q current reference is equal to the velocity reference 
         while d current reference is equal to 0
        for maximum startup torque, set the q current to maximum acceptable 
        value represents the maximum peak value */
        ctrlParm.qVqRef = ctrlParm.qVelRef;

        /* PI control for Q */
        piInputIq.inMeasure = idq.q;
        piInputIq.inReference = ctrlParm.qVqRef;
        MC_ControllerPIUpdate_Assembly(piInputIq.inReference,
                                       piInputIq.inMeasure,
                                       &piInputIq.piState,
                                       &piOutputIq.out);
        vdq.q = piOutputIq.out;

        /* PI control for D */
        piInputId.inMeasure = idq.d;
        piInputId.inReference  = ctrlParm.qVdRef;
        MC_ControllerPIUpdate_Assembly(piInputId.inReference,
                                       piInputId.inMeasure,
                                       &piInputId.piState,
                                       &piOutputId.out);
        vdq.d = piOutputId.out;
        
        FindHallStart = 0;
    }
    else
    {            
        ReadADC0(ADCBUF_SPEED_REF_A, &readADCParm);
        if(readADCParm.qADValue < Q15(0.4364))
        {
            ReadADC0(ADCBUF_SPEED_REF_A, &readADCParm);
            readADCParm.qAnRef = (uint16_t)(__builtin_muluu(readADCParm.qADValue,
                                    MAXIMUM_SPEED_ELECTR) >> 15);
        }
        else if((readADCParm.qADValue > Q15(0.4364)) && 
                (readADCParm.qADValue < Q15(0.6097)))
        {
            ReadADC0(ADCBUF_SPEED_REF_A, &readADCParm);
            readADCParm.qAnRef = (uint16_t)(__builtin_muluu(readADCParm.qADValue,
                                    SPEED_MULTIPLIER_1) >> 15);
        }
        else if((readADCParm.qADValue > Q15(0.6097)) && 
                (readADCParm.qADValue < Q15(0.7935)))
        {
            ReadADC0(ADCBUF_SPEED_REF_A, &readADCParm);
            readADCParm.qAnRef = (uint16_t)(__builtin_muluu(readADCParm.qADValue,
                                    SPEED_MULTIPLIER_2) >> 15);
        }
        
        /* Commented for speed step response measurement*/
        if(ctrlParm.speedRampCount < SPEEDREFRAMP_COUNT)
        {
           ctrlParm.speedRampCount++; 
        }
        else
        {
            /* Ramp generator to limit the change of the speed reference
              the rate of change is defined by CtrlParm.qRefRamp */
            ctrlParm.qDiff = ctrlParm.qVelRef - readADCParm.qAnRef;
            
            /* Speed Ref Ramp */
            if (ctrlParm.qDiff < 0)
            {
                /* Set this cycle reference as the sum of
                previously calculated one plus the reference ramp value */
                ctrlParm.qVelRef = ctrlParm.qVelRef + ctrlParm.qRefRamp;
            }
            else
            {
                /* Same as above for speed decrease */
                ctrlParm.qVelRef = ctrlParm.qVelRef - ctrlParm.qRefRamp;
            }
            /* If difference less than half of ref ramp, set reference
            directly from the pot */
            if (_Q15abs(ctrlParm.qDiff) < (ctrlParm.qRefRamp << 1))
            {
                ctrlParm.qVelRef = readADCParm.qAnRef;
            }
            ctrlParm.speedRampCount = 0;
        }

        if(uGF.bits.ChangeMode)
        {
            /* Just changed from open loop */
            uGF.bits.ChangeMode = 0;
            piInputOmega.piState.integrator = (int32_t)ctrlParm.qVqRef << 13;
        }
        
        /* Execute the velocity control loop */
        piInputOmega.inMeasure = mcappData.movingAvgFilterSpeed.avg;
        piInputOmega.inReference = ctrlParm.qVelRef;
        
        if(ctrlParm.qVelRef < 5000)
        {
            piInputOmega.piState.kp = Q15(0.4);
            piInputOmega.piState.ki = Q15(0.009);
        }
        else if((ctrlParm.qVelRef > 5001) && (ctrlParm.qVelRef < 7000))
        {
            piInputOmega.piState.kp = Q15(0.2);
            piInputOmega.piState.ki = Q15(0.009); 
        }
        else if(ctrlParm.qVelRef > 7001)
        {
            piInputOmega.piState.kp = Q15(0.1);
            piInputOmega.piState.ki = Q15(0.009); 
        }
        MC_ControllerPIUpdate_Assembly(piInputOmega.inReference,
                                       piInputOmega.inMeasure,
                                       &piInputOmega.piState,
                                       &piOutputOmega.out);
        ctrlParm.qVqRef = piOutputOmega.out;

        /* Flux weakening control - the actual speed is replaced 
        with the reference speed for stability 
        reference for d current component 
        adapt the estimator parameters in concordance with the speed */
        ctrlParm.qVdRef = FieldWeakening(_Q15abs(ctrlParm.qVelRef));

        /* PI control for D */
        piInputId.inMeasure = idq.d;
        piInputId.inReference  = ctrlParm.qVdRef;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        MC_ControllerPIUpdate_Assembly(piInputId.inReference,
                                       piInputId.inMeasure,
                                       &piInputId.piState,
                                       &piOutputId.out);
        vdq.d    = piOutputId.out;

         /* Dynamic d-q adjustment with d component priority*/
		// Vector limitation
		// Vd is not limited
		// Vq is limited so the vector Vs is less than a maximum of 95%.
		// Vs = SQRT(Vd^2 + Vq^2) < 0.98
		// Vq = SQRT(0.98^2 - Vd^2)
        temp_qref_pow_q15 = (int16_t)(__builtin_mulss(piOutputId.out ,
                                                      piOutputId.out) >> 15);
        temp_qref_pow_q15 = Q15(MAX_VOLTAGE_VECTOR) - temp_qref_pow_q15;
        piInputIq.piState.outMax = Q15SQRT(temp_qref_pow_q15);
        piInputIq.piState.outMin = -piInputIq.piState.outMax;

        /* PI control for Q */
        piInputIq.inMeasure  = idq.q;
        piInputIq.inReference  = ctrlParm.qVqRef;
        MC_ControllerPIUpdate_Assembly(piInputIq.inReference,
                                       piInputIq.inMeasure,
                                       &piInputIq.piState,
                                       &piOutputIq.out);
        vdq.q = piOutputIq.out;
    }
}

// *****************************************************************************
/* Function:
    _ADCAN17Interrupt()
  Summary:
    _ADCAN17Interrupt() ISR routine

  Description:
    Does speed calculation and executes the vector update loop
    The ADC sample and conversion is triggered by the PWM period.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void __attribute__((__interrupt__,no_auto_psv)) _ADCAN17Interrupt()
{
	/* Read ADC Buffet to Clear Flag */
	adcDataBuffer = ClearADCIF_ReadADCBUF();
            
    /* Uncomment to enable the throttle control */
    /* Read unsigned values */
    ReadADC0(ADCBUF_SPEED_REF_A, &readADCParm);
    if(readADCParm.qADValue > Q15(0.2746))
    {
        LATCbits.LATC11 = TURN_ON;
    }
    
    if (uGF.bits.RunMotor)
    {
        /* Calculate qIa,qIb */
        MeasCompCurr(ADCBUF_INV_A_IPHASE1, ADCBUF_INV_A_IPHASE2, &measCurrParm);

        iabc.a = measCurrParm.qIa;
        iabc.b = measCurrParm.qIb;

        /* Calculate qIalpha,qIbeta from qIa,qIb */
        MC_TransformClarke_Assembly(&iabc, &ialphabeta);

        /* Calculate qId,qIq from qSin,qCos,qIalpha,qIbeta */
        MC_TransformPark_Assembly(&ialphabeta, &sincosTheta, &idq);

        /* Calculate control values */
        DoControl();

        CalculateParkAngleHall();

		/* Calculate qSin,qCos from the thetaElectrical */
        MC_CalculateSineCosine_Assembly_Ram(thetaElectrical, &sincosTheta);

		/* Calculate qValpha,qVbeta from qSin,qCos,qVd,qVq */
        MC_TransformParkInverse_Assembly(&vdq, &sincosTheta, &valphabeta);

		/* Calculate qVa,qVb,qVc vectors from qValpha,qVbeta */
        MC_TransformClarkeInverseSwappedInput_Assembly(&valphabeta, &vabc);

		/* Generate SV-PWM from the voltage vectors and PWM frequency */
        MC_CalculateSpaceVectorPhaseShifted_Assembly(&vabc, pwmPeriod,
                                                    &pwmDutycycle);

        if (pwmDutycycle.dutycycle1 < MIN_DUTY)
        {
            pwmDutycycle.dutycycle1 = MIN_DUTY;
        }
        if (pwmDutycycle.dutycycle2 < MIN_DUTY)
        {
            pwmDutycycle.dutycycle2 = MIN_DUTY;
        }
        if (pwmDutycycle.dutycycle3 < MIN_DUTY)
        {
            pwmDutycycle.dutycycle3 = MIN_DUTY;
        }

        INVERTERA_PWM_PDC3 = pwmDutycycle.dutycycle1; //Phase A
        INVERTERA_PWM_PDC2 = pwmDutycycle.dutycycle3; //Phase C 
        INVERTERA_PWM_PDC1 = pwmDutycycle.dutycycle2; //Phase B 
       
    }
    else
    {
        measCurrOffsetFlag = 1;
        
        PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
        PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
        PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

        PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
        PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
        PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H
        
        INVERTERA_PWM_PDC3 = pwmDutycycle.dutycycle;
        INVERTERA_PWM_PDC2 = pwmDutycycle.dutycycle;
        INVERTERA_PWM_PDC1 = pwmDutycycle.dutycycle;      
    }
    
    if(PORTCbits.RC12 == 0)
    {  
            uGF.bits.RunMotor = 0;
            pwmDutycycle.dutycycle = 3500;

        if(mcappData.movingAvgFilterSpeed.avg <= 0)
        {
            pwmDutycycle.dutycycle = MIN_DUTY;
            ResetParmeters();
        }
        
    }
    
    /*For turning off the MOSFET driver during IDLE Time.*/
    idleCounter++;
    if(idleCounter > ONE_MIN){
        LATCbits.LATC11 = TURN_OFF;
    }
    
    startUpCounter++;
    if(startUpCounter > 1000)
        UndervoltageDetect();
    OvertemperatureDetectMCU();
    OvertemperatureDetectMOSFET();
    
    /* Clear Interrupt Flag */
    ClearADCIF();
}

// *****************************************************************************
/* Function:
    InitControlParameters()

  Summary:
    Function initializes control parameters

  Description:
    Initialize control parameters: PI coefficients, scaling constants etc.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void InitControlParameters(void)
{
    /* ADC - Measure Current & Pot */
    /* Scaling constants: Determined by calibration or hardware design.*/
    readADCParm.qK = KPOT;
    measCurrParm.qKa = KCURRA;
    measCurrParm.qKb = KCURRB;

    ctrlParm.qRefRamp = SPEEDREFRAMP;
    ctrlParm.speedRampCount = SPEEDREFRAMP_COUNT;

    /* Set PWM period to Loop Time */
    pwmPeriod = LOOPTIME_TCY;

    /* PI - Id Current Control */
    piInputId.piState.kp = D_CURRCNTR_PTERM;
    piInputId.piState.ki = D_CURRCNTR_ITERM;
    piInputId.piState.kc = D_CURRCNTR_CTERM;
    piInputId.piState.outMax = D_CURRCNTR_OUTMAX;
    piInputId.piState.outMin = -piInputId.piState.outMax;
    piInputId.piState.integrator = 0;
    piOutputId.out = 0;

    /* PI - Iq Current Control */
    piInputIq.piState.kp = Q_CURRCNTR_PTERM;
    piInputIq.piState.ki = Q_CURRCNTR_ITERM;
    piInputIq.piState.kc = Q_CURRCNTR_CTERM;
    piInputIq.piState.outMax = Q_CURRCNTR_OUTMAX;
    piInputIq.piState.outMin = -piInputIq.piState.outMax;
    piInputIq.piState.integrator = 0;
    piOutputIq.out = 0;

    /* PI - Speed Control */
    piInputOmega.piState.kp = SPEEDCNTR_PTERM;
    piInputOmega.piState.ki = SPEEDCNTR_ITERM;
    piInputOmega.piState.kc = SPEEDCNTR_CTERM;
    piInputOmega.piState.outMax = SPEEDCNTR_OUTMAX;
    piInputOmega.piState.outMin = Q15(0.0);
    piInputOmega.piState.integrator = 0;
    piOutputOmega.out = 0;
}

// ******************************************8652/******************************
/* Function:
    measCurrOffset()

  Summary:
    Routine initializes Offset values of current
  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
void MeasCurrOffset(int16_t *pOffseta,int16_t *pOffsetb)
{
    int32_t adcOffsetIa = 0, adcOffsetIb = 0;
    uint16_t i = 0;

    /* Enable ADC interrupt and begin main loop timing */
    ClearADCIF();
    adcDataBuffer = ClearADCIF_ReadADCBUF();
    EnableADCInterrupt();

    /* Taking multiple sample to measure voltage offset in all the channels */
    for (i = 0; i < (1<<CURRENT_OFFSET_SAMPLE_SCALER); i++)
    {
        measCurrOffsetFlag = 0;
        /* Wait for the conversion to complete */
        while (measCurrOffsetFlag == 0);
        /* Sum up the converted results */
        adcOffsetIa += (int16_t) ADCBUF_INV_A_IPHASE1;
        adcOffsetIb += (int16_t) ADCBUF_INV_A_IPHASE2;
    }
    /* Averaging to find current Ia offset */
    *pOffseta = (int16_t)(adcOffsetIa >> CURRENT_OFFSET_SAMPLE_SCALER);
    /* Averaging to find current Ib offset*/
    *pOffsetb = (int16_t)(adcOffsetIb >> CURRENT_OFFSET_SAMPLE_SCALER);
    measCurrOffsetFlag = 0;

    /* Make sure ADC does not generate interrupt while initializing parameters*/
    DisableADCInterrupt();
}

void __attribute__((interrupt, no_auto_psv)) _CNCInterrupt()
{
    idleCounter = 0;
    oldHallState = hallValue;
    hallValue = HAL_HallValueRead();
    
    if(oldHallState != hallValue)
    {
        switch(oldHallState)
        {
            case 1:  hallValue = 5; break;
            case 5:  hallValue = 4; break;
            case 4:  hallValue = 6; break;
            case 6:  hallValue = 2; break;
            case 2:  hallValue = 3; break;
            case 3:  hallValue = 1; break;
        }
    }
    
    ActualCapture = SCCP3_TMR_Counter32BitGet();
    Period = ActualCapture - PastCapture;
    
    if (ActualCapture < PastCapture)
    {
        Period = PERIOD_CONSTANT - (PastCapture - ActualCapture);
    }
    PastCapture = ActualCapture;
    
    CalcMovingAvgSpeed(Period);
    
    if (Period < MINPERIOD) 
    {
        Period = MINPERIOD; 
    }
    else if (Period > MAXPERIOD) 
    {
        Period = MAXPERIOD; 
    }
    
    /* Uncomment to enable throttle control */
    if((mcappData.movingAvgFilterSpeed.avg > 2000) &&
            (readADCParm.qADValue > Q15(0.2746)))
    {
        uGF.bits.RunMotor = 1;
        HAL_MC1PWMEnableOutputs();
    }
    else if((readADCParm.qADValue < Q15(0.2808)) &&
            (mcappData.movingAvgFilterSpeed.avg < 2600))
    {
        ResetParmeters();
    }
    
    HallAngle = PhaseValues[(hallValue)] + 16384 + HallOffset; 
    thetaElectrical = HallAngle;
                
    IFS1bits.CNCIF = 0;
}

void CMP1_ISR(void)
{
    if (faultOverCurrent.counter > OVERCURRENT_COUNTER)
    {
        ResetParmeters();
        faultOverCurrent.counter = 0;
    }
    faultOverCurrent.counter++;
}

void UndervoltageDetect(void)
{
    
    faultUndervoltage.measure = ADCBUF_VOLTAGE;
    faultUndervoltage.monitor = (faultUndervoltage.measure >> 6);
    
    if(faultUndervoltage.monitor < VOLTAGE_LIMITER)
    {
        faultUndervoltage.counter++;
        
        if(faultUndervoltage.counter > UNDERVOLTAGE_COUNTER)
        {
            ResetParmeters();
            faultUndervoltage.counter  = 0;
        }
    }
}

void OvertemperatureDetectMCU(void)
{
    faultOverTempMCU.measure = ADCBUF_TEMPERATURE_MCU;
    faultOverTempMCU.monitor = (faultOverTempMCU.measure >> 6);
    
    if(faultOverTempMCU.monitor < OVERTEMP_LIMITER_57)
    {
        faultOverTempMCU.counter++;
        
        if(faultOverTempMCU.counter > OVERTEMP_COUNTER)
        {
            ResetParmeters();
            faultOverTempMCU.counter = 0;
        }
    }
      
    if(faultOverTempMCU.monitor < OVERTEMP_LIMITER_35)
    {
        faultOverTempMCU.counter++;
        
        if(faultOverTempMCU.counter> OVERTEMP_COUNTER)
        {
            faultOverTempMCU.indicator = (faultOverTempMCU.monitor >> 1);
        }
    }
}

void OvertemperatureDetectMOSFET(void)
{

    faultOverTempMOSFET.measure = ADCBUF_TEMPERATURE_MOSFET;
    faultOverTempMOSFET.monitor = (faultOverTempMOSFET.measure >> 6);
    
    if(faultOverTempMOSFET.monitor < OVERTEMP_MOSFET_60)
    {
        faultOverTempMOSFET.counter++;
        
        if(faultOverTempMOSFET.counter > OVERTEMP_COUNTER)
        {
            ResetParmeters();
            faultOverTempMOSFET.counter = 0;
        }
    }
}

/******************************************************************************
 * Description: The InitMovingAvgPeriod function initializes the current 
 *              array table that is being used to calculate the moving average,
 *              thereby eliminate the undesired response and variations during
 *              reset and restart of motor.
 *****************************************************************************/
void InitMovingAvgPeriod(void)
{
    uint16_t i;

    for (i = 0; i < PERIOD_MOVING_AVG_FILTER_SIZE; i++)
    {
        mcappData.movingAvgFilterPeriod.buffer[i] = 0;
    }

    mcappData.movingAvgFilterPeriod.index = 0;
    mcappData.movingAvgFilterPeriod.sum = 0;
    mcappData.movingAvgFilterPeriod.avg = 0;


    for (i = 0; i < SPEED_MOVING_AVG_FILTER_SIZE; i++)
    {
        mcappData.movingAvgFilterSpeed.buffer[i] = 0;
    }

    mcappData.movingAvgFilterSpeed.index = 0;
    mcappData.movingAvgFilterSpeed.sum = 0;
    mcappData.movingAvgFilterSpeed.avg = 0;
}

/******************************************************************************
 * Description: The CalcMovingAvgPeriod function calculates the moving
 *              average period.
 *****************************************************************************/
void CalcMovingAvgPeriod(uint16_t instPeriod)
{
    uint16_t i;
    
    mcappData.movingAvgFilterPeriod.buffer[mcappData.movingAvgFilterPeriod.index] 
        = instPeriod;
    mcappData.movingAvgFilterPeriod.index++;
    if (mcappData.movingAvgFilterPeriod.index >= PERIOD_MOVING_AVG_FILTER_SIZE)
        mcappData.movingAvgFilterPeriod.index = 0;

    mcappData.movingAvgFilterPeriod.sum = 0;
    for (i = 0; i < PERIOD_MOVING_AVG_FILTER_SIZE; i++)
    {
        mcappData.movingAvgFilterPeriod.sum = mcappData.movingAvgFilterPeriod.sum 
                + mcappData.movingAvgFilterPeriod.buffer[i];
        mcappData.movingAvgFilterPeriod.avg = mcappData.movingAvgFilterPeriod.sum 
                >> PERIOD_MOVING_AVG_FILTER_SCALE;
    }
}

void CalculateParkAngleHall(void)
{
    if(FindHallStart)
    {
        HallAngle = PhaseValues[(hallValue)] + 16384 + HallOffset;
        thetaElectrical = HallAngle;
    }
    else
    {         
        CalcMovingAvgPeriod(Period);
        AvgPeriod = mcappData.movingAvgFilterPeriod.avg;

        if(AvgPeriod != 0)
            mcappData.phaseInc = __builtin_divud((long unsigned int)PHASE_INC_CALC,
                                    (unsigned int) AvgPeriod);                
        thetaElectrical += mcappData.phaseInc;  

        if((thetaElectrical - HallAngle) > 10922)
            thetaElectrical = HallAngle + 10922;          
    }            
}

/******************************************************************************
 * Description: The CalcMovingAvgSpeed function calculates the moving
 *              average of speed.
 *****************************************************************************/
void CalcMovingAvgSpeed(int32_t instSpeed)
{
    uint16_t i;
    mcappData.movingbuffer.buffer[mcappData.movingbuffer.index] = instSpeed;
    mcappData.movingbuffer.index++;
    
    if (mcappData.movingbuffer.index >= 6)
        mcappData.movingbuffer.index = 0;
    
    mcappData.movingbuffer.sum = 0;
    for (i = 0; i < 6; i++)
    {
        mcappData.movingbuffer.sum = mcappData.movingbuffer.sum + 
                                        mcappData.movingbuffer.buffer[i];
    }

    mcappData.movingbuffer.calculatedSpeed = 
        (uint32_t) (__builtin_divud(SPEED_MULTI_ELEC,
             mcappData.movingbuffer.sum));
    mcappData.movingAvgFilterSpeed.buffer[mcappData.movingAvgFilterSpeed.index] 
        = mcappData.movingbuffer.calculatedSpeed;
    mcappData.movingAvgFilterSpeed.index++;
    if (mcappData.movingAvgFilterSpeed.index >= SPEED_MOVING_AVG_FILTER_SIZE)
        mcappData.movingAvgFilterSpeed.index = 0;

    mcappData.movingAvgFilterSpeed.sum = 0;
    for (i = 0; i < SPEED_MOVING_AVG_FILTER_SIZE; i++)
    {
        mcappData.movingAvgFilterSpeed.sum = mcappData.movingAvgFilterSpeed.sum 
            + mcappData.movingAvgFilterSpeed.buffer[i];
        mcappData.movingAvgFilterSpeed.avg = mcappData.movingAvgFilterSpeed.sum 
            >> SPEED_MOVING_AVG_FILTER_SCALE;
    }
}
/*
 End of File
 */