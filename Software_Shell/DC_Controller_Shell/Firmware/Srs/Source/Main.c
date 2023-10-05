/*
    (c) 2022 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/* Basic firmware for the "High-Performance E-Scooter BLDC Motor Driver Reference Design" board
   V 1.0 December 2022
   Description: this firmware offers a basic Field Oriented Control functionality for an BLDC/PMSM motor which is part of an electric kick-scooter.
   Compiler : XC16 v1.7 with O1 optimization enabled
   MPLAB    : MPLAB X v6.00
   Silicon  : dsPIC33CK32MP105  
   Author   : Sergiu Oprea, M91359
 */


#include "init_dspic.h"
#include "FOC.h"
#include "libq.h"
#include <libpic30.h>
#include "X2CScope.h"
#include "uart1.h"


SMC smc1 = SMC_DEFAULTS;		/* Variable structure used for the Sliding Mode	observer */

tMotorParm      MotorParm;     // Structure for the motor parameters
tCtrlParm       CtrlParm;      // Structure for the control parameters
tParkParm       ParkParm;      // Structure for the Clarke/Park transforms
tPIParm         PIParmD;       // Structure definition of PI for Flux component of current, or Id
tPIParm         PIParmQ;       // Structure definition of PI for Torque component of current, or Iq
tPIParm         PIParmW;       // Structure definition of PI for Speed or Omega
tSVGenParm      SVGenParm;     // Structure for the Space Vector Modulation PWM
tProtections    Protections;   // Structure for protections
tPIParm         PIParmH;       // Structure for the Hall sensors PLL PI
tPIParm         PIParmP;       // Structure for the Constant Power Mode PI

unsigned long Startup_Ramp = 0; /* Start up ramp in open loop. This variable
								is incremented in CalculateParkAngle()
								subroutine, and it is assigned to 
								ParkParm.qAngle as follows:
								ParkParm.qAngle += (int)(Startup_Ramp >> 16);*/

unsigned int Startup_Lock = 0; /* This is a counter that is incremented in
								CalculateParkAngle() every time it is called. 
								Once this counter has a value of LOCK_TIME, 
								then theta will start increasing moving the 
								motor in open loop. */

 union {
    struct 
    {
        unsigned OpenLoop : 1;          // Indicates if motor is running in open or closed loop
        unsigned RunMotor : 1;          // If motor is running=1, or stopped=0.
        unsigned EnTorqueMod : 1;       // This bit enables Torque mode when running closed loop
        unsigned Sensorless : 1;        // Sensor-less mode
        unsigned ChangeMode : 1;        // This flag indicates that a transition from 
        unsigned Overcurrent : 1;       // An overcurrent condition occurs
        unsigned VBUS_Undervoltage: 1;  // An VBUS under-voltage condition occurs
        unsigned VBUS_Overvoltage: 1;   // An VBUS over-voltage condition occurs
        unsigned V12_Out_of_range: 1;   // +12V bias voltage is out-of-range
        unsigned Overtemp_warning: 1;   // An over-temperature warning condition occurs; LIMP Mode is active
        unsigned Overtemperature: 1;    // An over-temperature condition occurs
        unsigned DC_Offset_error: 1;    // DC offset of current amplifiers is out-of-specs
        unsigned Hall_sensors_error: 1; // Hall sensors error
        unsigned Reverse_direction : 1; // Indicates that the REVERSE_DIRECTION option is active; the motor will spin in the opposite direction
        unsigned Angle_correction : 1;  // Indicates that the high-speed angle correction is active
        unsigned Regen_brake : 1;       // Indicates that the regenerative braking is active
    };
    unsigned : 16;      // number of bits
    unsigned int Word;
} uGF;


int Ia, Ib, Ic; // Measured values for phase currents

unsigned int  trans_counter;
int Theta_error = 0;

volatile unsigned int Torque_demand, Speed, Speed_demand, Speed_Measured, Speed_Measured_Filtered;
int DCbus;  //DC bus voltage
unsigned int Sector_Hall, NextSector;
const unsigned int NextSector_Hall[]    = {0, 2, 3, 4, 5, 6, 1};

// table for brake current interpolation
volatile const int Brake_Current[] = { REFINAMPS(B_CURRENT_0), REFINAMPS(B_CURRENT_1), REFINAMPS(B_CURRENT_2), \
                              REFINAMPS(B_CURRENT_3), REFINAMPS(B_CURRENT_4), REFINAMPS(B_CURRENT_5), \
                              REFINAMPS(B_CURRENT_6), REFINAMPS(B_CURRENT_7) };
// table for brake speed interpolation
volatile const unsigned Brake_Speed[] = { B_SPEED_0, B_SPEED_1, B_SPEED_2, B_SPEED_3, B_SPEED_4, B_SPEED_5, B_SPEED_6, B_SPEED_7 }; 

unsigned int Period, ActualCapture, PastCapture, Period_Filtered;

int PhaseInc;

int Hall_Angle;  //angle estimated from Hall sensors
unsigned int Transition_timer;

unsigned int switch_hall=1, electric_turns;
volatile int accel_ramp;
volatile unsigned int Vbus, V12, V_throttle, Vtemperature;
volatile long int DC_Offset_A_tmp, DC_Offset_B_tmp, DC_Offset_C_tmp;
volatile int  DC_Offset_A=0, DC_Offset_B=0, DC_Offset_C=0, DC_Offset_Done = 0, DC_Offset_timer, Do_DC_Offset;

volatile unsigned int Throttle_timer, New_Throttle;
long int Throttle_value_tmp;
int Throttle_value;
long int Throttle_scale_temp;

unsigned int correct_angle=0;
volatile unsigned int brake_in_progress;
volatile int Tmp_Ia, Tmp_Ib, Tmp_Ic;
volatile unsigned int Fatal_error = 0;
volatile unsigned int start_point, throttle_state;

#ifdef  TUNE_PHASE_DIFFERENCE 
volatile int Phase_difference, Phase_difference_filtered;
volatile long LPF_Acc_Phase;
#endif


int main(void) 
{  
    PIN_MANAGER_Initialize();
    FLED = 1; //initialization in progress
    CLOCK_Initialize();
    Set_Clock_High();    //go to 100 MIPS

    init_DAC_COMP(); //init comparators for the overcurrent/short-circuit protection
 
    //if the X2C Scope is used
#ifdef  X2C_SCOPE
    UART1_Initialize();
    X2CScope_Init();
#endif
    
    uGF.Word = 0; // clear flags
    
// Options /////////////////////////
#ifdef TORQUE_MODE
    uGF.EnTorqueMod = 1;
#endif
    
#ifdef SENSORLESS
    uGF.Sensorless = 1;
#endif

#ifdef REVERSE_DIRECTION
    uGF.Reverse_direction = 1;
#endif

#ifdef HIGH_SPEED_ANGLE_CORRECTION
    uGF.Angle_correction = 1;
#endif

#ifdef REGEN_BRAKE
    uGF.Regen_brake = 1;
#endif

#ifdef REGEN_BRAKE_CURRENT_PROFILER
    CtrlParm.Use_regen_brake_current_profile = 1;
#else
    CtrlParm.Use_regen_brake_current_profile = 0;
#endif      
//////////////////////////////////    
    
    SetupParm();    // initialize the ADC and PWM
    SW_12V = 1;     //activate the 12V bias switch
    Config_CCP1();  //CCP1 is used for the speed measurement
    __delay_ms(20); //wait for all bias voltages become stable
    SetupControlParameters(); // control parameters
    StopMotor();              // disable the PWM interface
    INTERRUPT_Initialize();
    __builtin_enable_interrupts();  //activate the interrupts
    WDT_Setup();      //enable WDT
    Get_Current_Sector();           //read the current sector
    NextSector = NextSector_Hall[Sector_Hall];
    FLED = 0; //initialization complete
        
    while (1)   // main loop
    {   
#ifdef  X2C_SCOPE
        X2CScope_Communicate();
#endif
        
 //FAULT LED is on if a fatal error occurs
        if(Fatal_error == 0) FLED = 0;
        else FLED = 1;
        
// if LIMP Mode is active reduce the maximum torque current        
        if(uGF.Overtemp_warning == 1)
        {
            MotorParm.MaxTorqueCurrent = REFINAMPS(MAX_TORQUE_CURRENT_LIMP); // maximum torque current
            PIParmW.qOutMax = REFINAMPS(MAX_TORQUE_CURRENT_LIMP);            //for speed mode
        }
        else
        {
#ifdef CONSTANT_POWER_MODE
            Limit_power();   // limit the input power           
            PIParmW.qOutMax = MotorParm.MaxTorqueCurrent;   //for speed mode
#else
            MotorParm.MaxTorqueCurrent = REFINAMPS(MAX_TORQUE_CURRENT); // maximum torque current
            PIParmW.qOutMax = MotorParm.MaxTorqueCurrent;               //for speed mode
#endif
        }
        
        
#ifdef  USE_MINIMUM_SPEED_TO_START
        if(uGF.Sensorless == 0)  //use a minimum starting speed only in sensored mode
        {
            if((throttle_state == 0)&&(Speed_Measured > MINIMUM_START_SPEED)) start_point = 1;
            else start_point = 0;
        }
        else start_point = 1;         
#else  
        start_point = 1;
#endif
        
           
        if(New_Throttle)
        {
           if(Throttle_value >= THROTTLE_LOW + THROTTLE_HYSTERESIS)
            {
               throttle_state = 1;
               if((uGF.RunMotor == 0)) 
               { 
                   if((Fatal_error == 0) && (uGF.Overcurrent == 0) && (start_point == 1))    
                   {
                       SetupControlParameters();    // reset all parameters
                       RunMotor();                  //start the driver
                   }
               }
               
               if(brake_in_progress == 1) brake_in_progress = 0; 
            }
            else if(Throttle_value < THROTTLE_LOW - THROTTLE_HYSTERESIS)
            {     
                throttle_state = 0;
                if(uGF.Sensorless == 0)
                {
                    if((uGF.RunMotor == 1)&&(Speed_Measured_Filtered > BRAKE_MIN_SPEED)&&(switch_hall == 0))

                    {
                        Brake(); //brake motor
                        brake_in_progress = 1; 
                    }
                    else
                    {
                        StopMotor();    //stop motor
                    }
                }
                else    //stop motor in sensorless mode
                {
                    StopMotor();
                }
            }
          
            if(uGF.RunMotor)
            {                    
               if(uGF.EnTorqueMod == 1)
               {
                   Throttle_handle();   // handle the throttle value
                //scale the ADC value
                   Torque_demand = (__builtin_mulss(Throttle_value, Q15((float)(MotorParm.MaxTorqueCurrent - MotorParm.MinTorqueCurrent)/32767))>>15) + MotorParm.MinTorqueCurrent;
                   
                   if(brake_in_progress == 0) 
                   Motoring(); //ramp up/down the torque current
               }
               else
               {
                   Throttle_handle();
                   if(uGF.Sensorless == 0)
                   {
                    //scale the value
                        Speed = (__builtin_mulss(Throttle_value, (MAX_SPEED_RPM - MIN_SPEED_RPM))>>15) + MIN_SPEED_RPM;
                        if(Speed < MIN_SPEED_RPM) Speed = MIN_SPEED_RPM;    //clamp the speed
                        if(Speed > MAX_SPEED_RPM) Speed = MAX_SPEED_RPM;
                   }
                   else
                   {
                       //scale the value
                        Speed = (__builtin_mulss(Throttle_value, (Q15(OMEGANOMINAL) - Q15(OMEGA0)))>>15) + Q15(OMEGA0);
                        if(Speed < Q15(OMEGA0)) Speed = Q15(OMEGA0);            //clamp the speed
                        if(Speed > Q15(OMEGANOMINAL)) Speed = Q15(OMEGANOMINAL);
                   }

                   if(brake_in_progress == 0)
                   {
                       Motoring();  // ramp up/down the speed or torque 
                   }
                   else 
                   {
                       Speed_demand = 1;  //set the speed demand to minimum
                   }
               }
            }
            New_Throttle = 0;
        }      
    }
}

/*****************************************************************************/
void SetupControlParameters(void) 
{
    // ============= PI D Term ===============
    PIParmD.qKp = DKP;
    PIParmD.qKi = DKI;
    PIParmD.qKc = DKC;
    PIParmD.qOutMax = DOUTMAX;
    PIParmD.qOutMin = -PIParmD.qOutMax;
    PIParmD.qdSum = 0;
    PIParmD.qInMeas = 0;
    PIParmD.qInRef  = 0;
    PIParmD.qOut    = 0;
    InitPI(&PIParmD);

    // ============= PI Q Term ===============
    PIParmQ.qKp = QKP;
    PIParmQ.qKi = QKI;
    PIParmQ.qKc = QKC;
    PIParmQ.qOutMax = QOUTMAX;
    PIParmQ.qOutMin = -PIParmQ.qOutMax;
    PIParmQ.qdSum = 0;
    PIParmQ.qInMeas = 0;
    PIParmQ.qInRef  = 0;
    PIParmQ.qOut    = 0;
    InitPI(&PIParmQ);

    // ============= PI W Term ===============
    PIParmW.qKp = WKP;
    PIParmW.qKi = WKI;
    PIParmW.qKc = WKC;
    PIParmW.qOutMax = WOUTMAX;
    PIParmW.qOutMin = 0;
    PIParmW.qdSum = 0;
    PIParmW.qInMeas = 0;
    PIParmW.qInRef  = 0;
    PIParmW.qOut    = 0;
    InitPI(&PIParmW);
    
    // ============= PI PLL Hall Term ===============
    PIParmH.qKp = HKP;
    PIParmH.qKi = HKI;
    PIParmH.qKc = HKC;
    PIParmH.qOutMax = HOUTMAX;
    PIParmH.qOutMin = -HOUTMAX;
    PIParmH.qdSum = 0;
    PIParmH.qInMeas = 0;
    PIParmH.qInRef  = 0;
    PIParmH.qOut    = 0;
    InitPI(&PIParmH);
    
    // ============= PI Constant Power Term ===============
    PIParmP.qKp = PKP;
    PIParmP.qKi = PKI;
    PIParmP.qKc = PKC;
    PIParmP.qOutMax = POUTMAX;
    PIParmP.qOutMin = POUTMIN;
    PIParmP.qdSum = (long)2^31;   // load the maximum value to ensure no limitation of the torque current during the start-up
    PIParmP.qInMeas = 0;
    PIParmP.qInRef  = 0;
    PIParmP.qOut    = 0;
    InitPI(&PIParmP);
    
    SMCInit(&smc1);
      					
    // Initialize SMC
    smc1.Valpha = 0;
    smc1.Ealpha = 0;
    smc1.EalphaFinal = 0;
    smc1.Zalpha = 0;
    smc1.EstIalpha = 0;
    smc1.Vbeta = 0;
    smc1.Ebeta = 0;
    smc1.EbetaFinal = 0;
    smc1.Zbeta = 0;
    smc1.EstIbeta = 0;
    smc1.Ialpha = 0;
    smc1.IalphaError = 0;
    smc1.Ibeta = 0;
    smc1.IbetaError = 0;
    smc1.Theta = 0;
    smc1.Omega = 0;
    smc1.IrpPerCalc = IRP_PERCALC;
    smc1.TransSteps = TRANSITION_STEPS;
    smc1.PI_over_IrpPerCalc = Q15(_PI / IRP_PERCALC);
    smc1.MinKslf = Q15(OMEGA0 * _PI / IRP_PERCALC);
    
    ParkParm.qAngle = 0;
    CtrlParm.qVdRef = 0;
    CtrlParm.qVelRef = 0;
    
    CtrlParm.Stall_value = STALL_VAL;
    CtrlParm.Phase_increment_constant = PHASE_INC_CALC;
    CtrlParm.Speed_RPM_constant = SPEED_RPM_CALC;
    CtrlParm.Angle_offset = ANGLE_OFFSET;
    CtrlParm.Max_phase_error = MAX_PHASE_ERROR;
    CtrlParm.Min_phase_error = MIN_PHASE_ERROR;
    CtrlParm.Correction_speed_threshold = CORRECTION_SPEED_THR;
    CtrlParm.Correction_speed_threshold = CORRECTION_SPEED_HYST;
    CtrlParm.Minimum_speed = MINSPEEDINRPM;
    CtrlParm.Max_q_axis_value = Q15(0.99);  //99%
    
    CtrlParm.Accel_ramp_constant = ACCEL_RAMP_CONST;    // acceleration ramp constant
    CtrlParm.Decel_ramp_constant = DECEL_RAMP_CONST;    // deceleration ramp constant
    CtrlParm.Brake_ramp_constant = BRAKE_RAMP_CONST;    // brake ramp constant
    MotorParm.Phase_Zero_D       = PHASE_ZERO_D;        // initial phase for "Forward Mode"
    MotorParm.Phase_Zero_R       = PHASE_ZERO_R;        // initial phase for "Reverse Mode"
    MotorParm.MaxPowerRef        = MAX_POWER_REFERENCE; // maximum delivered power
    
    CtrlParm.Speed_scale_constant = SPEED_SCALE_CONSTANT;
     
    Startup_Lock = 0;
    Startup_Ramp = 0;
    Theta_error = 0;
    
    accel_ramp = REFINAMPS(MIN_TORQUE_CURRENT);
    MotorParm.MaxTorqueCurrent = REFINAMPS(MAX_TORQUE_CURRENT); // maximum torque current
    MotorParm.MinTorqueCurrent = REFINAMPS(MIN_TORQUE_CURRENT); // minimum torque current
    MotorParm.MaxBrakeCurrent  = REFINAMPS(BRAKE_CURRENT);      // maximum brake current
    
    if(uGF.Sensorless == 1) Speed_demand = Q15(OMEGA0);     // set the minimum speed in sensorless mode  
    else                    Speed_demand = 1;
}


void RunMotor(void) 
{
       if(uGF.Sensorless == 1)
       {
            CtrlParm.qVqRef = REFINAMPS(INITIALTORQUE_ALLIGN); //align current
            CtrlParm.qVdRef = 0;
            CtrlParm.qVelRef = 0;
            ParkParm.qAngle = 0;
            trans_counter = 0;
            uGF.OpenLoop = 1; // start in open-loop
       }
      else
      {
          CtrlParm.qVqRef    =   accel_ramp;      // apply the minimum torque current
      }

        PIParmD.qdSum = 0;
        PIParmQ.qdSum = 0;
        CtrlParm.qVdRef =  0;
        CtrlParm.qVelRef = 0;
        
        if(Do_DC_Offset)
        {
            Get_DC_Offset();
            Do_DC_Offset = 0;
        }

        Get_Current_Sector();   //read the current sector
        NextSector = NextSector_Hall[Sector_Hall];

        PG1IOCONH = 0x000C;   //complementary mode PWWM
        PG2IOCONH = 0x000C;
        PG3IOCONH = 0x000C;

        accel_ramp = REFINAMPS(MIN_TORQUE_CURRENT); // apply the minimum torque current   
        uGF.RunMotor = 1;
}

void StopMotor(void) 
{
    uGF.RunMotor = 0;    // stop motor 
    Disable_PWM();       // no PWM on pins
    Speed_demand = 1;    // set the lowest value for speed demand
    uGF.Overcurrent = 0; // reset the overcurrent flag here
    Do_DC_Offset = 1;    // run a DC offset measurement at the next start
}


void __attribute__((__interrupt__, auto_psv)) _ADCAN17Interrupt (void)
{
//    FLED = 1; //to check the speed of the state machine 
    
// Ia - AN0 ->  PWM3
// Ib - AN4 ->  PWM2
// Ic - AN1 ->  PWM1 
    
#ifdef  X2C_SCOPE
    X2CScope_Update();
#endif 
    PUSHCORCON();       // save the CORCON 

    // read the analog quantities
    Tmp_Ia       =  ADCBUF0;
    V12          =  ADCBUF2;
    Tmp_Ib       =  ADCBUF4;
    Tmp_Ic       =  ADCBUF7;
    Vtemperature =  ADCBUF12;
    Vbus         =  ADCBUF15;
    V_throttle   =  ADCBUF17;
    
    if(DC_Offset_Done == 1)
    {   
       Ia = Tmp_Ia - DC_Offset_A;   //compensate the offsets
       Ib = Tmp_Ib - DC_Offset_B;
       Ic = Tmp_Ic - DC_Offset_C;    
    }
      
    Check_Protections();
    
    if(DC_Offset_Done == 0)
    {
        DC_Offset_timer++;
        DC_Offset_A_tmp += Tmp_Ia;  //ADCBUF0;
        DC_Offset_B_tmp += Tmp_Ib;  //ADCBUF4;
        DC_Offset_C_tmp += Tmp_Ic;  //ADCBUF7;
        if(DC_Offset_timer == 128)
           DC_Offset_Done = 1;      //measurement done
    }
    
// the throttle value is low-pass filtered using a simple median filter   
    Throttle_timer++;
    Throttle_value_tmp += V_throttle;
    if(Throttle_timer == 4)
    {
        Throttle_timer = 0;
        Throttle_value = (int)(Throttle_value_tmp>>3); //divided by 2
        Throttle_value_tmp = 0;
        New_Throttle = 1;
    }
     
    Calculate_currents();  //scale the currents, the result is placed directly to ParkParm.Ix
    
    //run this here even if uGF.RunMotor is 0
    CalculateParkAngle_Hall(); //estimate angle using the Hall sensors
    
    if (uGF.RunMotor)    
    {        
        if(uGF.Sensorless == 1)     //sensorless mode
        {
            CalculateParkAngle_Inline();    //get the angle and the speed
            switch_hall = 0;                //Halls not used in sensorless mode
            Speed_Measured_Filtered = smc1.OmegaFltred; //get the speed from the estimator
        }
        else    //Hall sensors provide the angle
        {            
            // Four inputs to estimator are updated
            smc1.Ialpha = ParkParm.qIalpha>>1;
            smc1.Ibeta  = ParkParm.qIbeta>>1;
            smc1.Valpha = ParkParm.qValpha;
            smc1.Vbeta  = ParkParm.qVbeta;
            
            // An iteration of the position and speed estimator is run
            SMC_Position_Estimation_Inline();

            if(switch_hall)
            { 
                ParkParm.qAngle = Hall_Angle + PHASE_ADVANCE_6_STEP;
                correct_angle = 0; //do not attempt to correct the angle at low speeds
            }
            else
            {
                Angle_correction();  //correct the angle using the Observer information          
            }
        }
        
        FOC_loop();  //this is the FOC state machine; all specific computations are done here
        
#ifdef  TUNE_PHASE_DIFFERENCE        
        Phase_difference = ParkParm.qAngle - Hall_Angle;     // difference between the angle provided by the estimator and the angle provided by Halls
        //low-pass filter for phase difference
        LPF_Acc_Phase = (LPF_Acc_Phase - (LPF_Acc_Phase >> 8)) + Phase_difference;
        Phase_difference_filtered = (LPF_Acc_Phase >> 8);
#endif
    }
    
    POPCORCON();        //restore the CORCON 
    WDTCONH = 0x5743;   //reset WDT
    IFS6bits.ADCAN17IF = 0; //reset the interrupt flag
//    FLED = 0;
}

inline void CalculateParkAngle_Inline(void)
{
	// Four inputs to estimator are updated
 	smc1.Ialpha = ParkParm.qIalpha>>1;
  	smc1.Ibeta  = ParkParm.qIbeta>>1;
    smc1.Valpha = ParkParm.qValpha;
    smc1.Vbeta  = ParkParm.qVbeta;
    
	// An iteration of the position and speed estimator is run
	SMC_Position_Estimation_Inline();

	// If in open loop, lock rotor or go through forced angle ramp
	if(uGF.OpenLoop)	
	{
		// If motor is locked in an initial position, run a timeout
		if (Startup_Lock < MotorParm.LockTime)
		{
			Startup_Lock += 1;	// This variable is incremented until
								// lock time expires, them the open loop
								// ramp begins
		}
		// After locking rotor in initial position, then go through forced
		// commutated angle to get motor spinning. Notice that in forced
		// commutation, Id and Iq are being controller.
		else if (Startup_Ramp < MotorParm.EndSpeed)
		{	
			CtrlParm.qVqRef = REFINAMPS(INITIALTORQUE);
			Startup_Ramp += (DELTA_STARTUP_RAMP); 
		}
		// After the ramp, close the loop and start using the angle for
		// running the motor.
		else
		{
			// This section enables closed loop, right after open loop ramp.
		#ifndef OPENLOOPONLY
            uGF.OpenLoop = 0;
            accel_ramp = REFINAMPS(INITIALTORQUE);
		#endif

			// Difference between force angle and estimated theta is saved,
			// so a soft transition is made when entering closed loop.
			Theta_error = ParkParm.qAngle - smc1.Theta;
		}
		// This operation is done to force a new angle with the open loop ramp
		ParkParm.qAngle += (int)(Startup_Ramp >> 16);
	}
	else
	{
		// This value is used to transition from open loop to closed looop. 
		// At the end of open loop ramp, there is a difference between 
		// forced angle and estimated angle. This difference is stored in 
		// Theta_error, and added to estimated theta (smc1.Theta) so the 
		// effective angle used for commutating the motor is the same at 
		// the end of open loop, and at the beginning of closed loop. 
		// This Theta_error is then subtracted from estimated theta 
		// gradually in increments of 0.05 degrees until the error is less
		// than 0.05 degrees.
		ParkParm.qAngle = smc1.Theta + Theta_error;    
		if( (_Q15abs(Theta_error) > _0_05DEG)&&(trans_counter == 0))
		{
			if (Theta_error < 0)
				Theta_error += _0_05DEG;
			else
				Theta_error -= _0_05DEG;
		}
	}
}

//measure and compute the DC offset for all currents measurement channels
void Get_DC_Offset(void)
{
    DC_Offset_A_tmp = 0;
    DC_Offset_B_tmp = 0;
    DC_Offset_C_tmp = 0;    //temp offsets values clear
    DC_Offset_A = 0;
    DC_Offset_B = 0;
    DC_Offset_C = 0;
        
    Disable_PWM(); //no PWM on pins
    
    DC_Offset_timer = 0;
    DC_Offset_Done = 0;

    while(DC_Offset_Done == 0); //wait for DC offset measurement BLOCKING CODE!!!!
        
    DC_Offset_A = (int)(DC_Offset_A_tmp >> 7);  //compute the DC offsets for currents measurement channels
    DC_Offset_B = (int)(DC_Offset_B_tmp >> 7);
    DC_Offset_C = (int)(DC_Offset_C_tmp >> 7);
    
    // check offsets
    if((_Q15abs(DC_Offset_A) > MAX_DC_OFFSET)||(_Q15abs(DC_Offset_B) > MAX_DC_OFFSET)||(_Q15abs(DC_Offset_C) > MAX_DC_OFFSET))
    {
        uGF.DC_Offset_error = 1;
    }
    else
    {
        uGF.DC_Offset_error = 0;
    }
}


/*****************************************************************************/
void SetupParm(void) 
{
    ADC1_Initialize();  //init the ADC
    
    // Set PWM period to Loop Time 
    SVGenParm.iPWMPeriod      = SVMPWM_TOP;
    SVGenParm.iPWM_Halfperiod = SVMPWM_HALF;
    
    MotorParm.EndSpeed = ENDSPEEDOPENLOOP * POLEPAIRS * LOOPTIMEINSEC * 65536 * 65536 / 60.0;
	MotorParm.LockTime = LOCKTIME;

    PCLKCON = 0x02;
    MPER    = PWM_TOP;
    MPHASE  = 0;
    MDC     = 0;
    PG1DC   = 0;
    PG2DC   = 0;
    PG3DC   = 0;
        
    PG1CONH = 0x6100;
    PG2CONH = 0x6100;
    PG3CONH = 0x6100;
    
    PG1EVTL = 0x0108; //PG1TRIGA is the ADC trigger 1 source    
    PG2EVTL = 0x0008;
    PG3EVTL = 0x0008;
    
    PG1TRIGA = 0;   //ADC trigger point
    PG2TRIGA = 0;
    PG3TRIGA = 0;
    
    PG1DTL = PG2DTL = PG3DTL = DDEADTIME;   //dead times
    PG1DTH = PG2DTH = PG3DTH = DDEADTIME;
       
    PG1CONL = PG2CONL =  PG3CONL = 0x800D; //center aligned, double update
}


void Throttle_handle(void)
{
   if(Throttle_value > THROTTLE_HIGH) Throttle_value = THROTTLE_HIGH; //clamp

   Throttle_scale_temp = (long int)Throttle_value * THROTTLE_SCALE_A_COEFFICIENT - THROTTLE_SCALE_B_COEFFICIENT; //interpolate

   Throttle_value = (int)(Throttle_scale_temp >> 10); //compute the value
   if(Throttle_value < 0) Throttle_value = 0;
}

// these are the comparators interrupt handlers used for overcurrent/short-circuit protection *****
void __attribute__ ( ( __interrupt__ , no_auto_psv ) ) _CMP1Interrupt ( void )
{
  Disable_PWM();        // disable the PWM
  uGF.Overcurrent = 1;  // set overcurrent flag
  IFS4bits.CMP1IF = 0;
}

void __attribute__ ( ( __interrupt__ , no_auto_psv ) ) _CMP2Interrupt ( void )
{
   Disable_PWM();       // disable the PWM
   uGF.Overcurrent = 1; // set overcurrent flag
   IFS4bits.CMP2IF = 0;
}

void __attribute__ ( ( __interrupt__ , no_auto_psv ) ) _CMP3Interrupt ( void )
{
   Disable_PWM();       // disable the PWM
   uGF.Overcurrent = 1; // set overcurrent flag
   IFS4bits.CMP3IF = 0;
}
// ***********************

void Check_Protections(void)
{
    //Software overcurrent protection. WARNING: is SLOW!!! But precise...
    if(uGF.RunMotor)
    {
        if((Ia > MAX_CURRENT)||(Ib > MAX_CURRENT)||(Ic > MAX_CURRENT)) 
        {        
            uGF.Overcurrent = 1; // overcurrent detected
        }
    }
    
    // median filter for VBUS, VBias and Vtemperature
    Protections.MedianFilterCounter++;
    Protections.Flt_Vbus_acc    += Vbus;
    Protections.Flt_Vbias_acc   += V12;
    Protections.Flt_Vtemp_acc   += Vtemperature;
    if(Protections.MedianFilterCounter == 8)
    {
        Protections.MedianFilterCounter = 0;
        Protections.Flt_Vbias = (unsigned int)(Protections.Flt_Vbias_acc >> 3); //8 samples
        Protections.Flt_Vbus  = (unsigned int)(Protections.Flt_Vbus_acc  >> 3); //8 samples
        Protections.Flt_Vtemp = (unsigned int)(Protections.Flt_Vtemp_acc >> 3); //8 samples
        
        //reset accumulators
        Protections.Flt_Vbias_acc = 0;
        Protections.Flt_Vbus_acc = 0;
        Protections.Flt_Vtemp_acc = 0;
    }
    
    // check for VBUS under-voltage
    if ( Protections.Flt_Vbus < MIN_VBUS ) 
    {
        uGF.VBUS_Undervoltage = 1;  //under-voltage detected
    }
    else if (Protections.Flt_Vbus > MIN_VBUS + VBUS_HYST)
    {
        uGF.VBUS_Undervoltage = 0;  //under-voltage reset
    }
    
    //check for VBUS over-voltage
    if ( Protections.Flt_Vbus > MAX_VBUS )   //Danger! VBUS over-voltage detected
    {
        uGF.VBUS_Overvoltage = 1;
    }
    else if ( Protections.Flt_Vbus < MAX_VBUS -  VBUS_HYST) 
        uGF.VBUS_Overvoltage = 0; //reset the over-voltage condition
    
    // check the +12V bias voltage limits
    if (( Protections.Flt_Vbias < TYP_VBIAS - VBIAS_HYST ) || ( Protections.Flt_Vbias > TYP_VBIAS + VBIAS_HYST )) 
    {
        uGF.V12_Out_of_range = 1;   // under-voltage or over-voltage detected               
    }
    else uGF.V12_Out_of_range = 0; // +12V bias is OK
    
    // check the temperature
    // a NTC thermistor is used to measure the temperature
    // the measured voltage decreases with temperature
    if ( Protections.Flt_Vtemp < MAX_TEMP_OFF ) //maximum temperature on the MOSFETs is reached
    {
        uGF.Overtemperature = 1;
    }
    else if (Protections.Flt_Vtemp > (MAX_TEMP_OFF + TEMP_HYST))
    {
        uGF.Overtemperature = 0;
    }
    
    if (Protections.Flt_Vtemp < MAX_TEMP_LIMP)    //LIMP mode, reduce the torque current
    {
        uGF.Overtemp_warning = 1;
    }
    else if (Protections.Flt_Vtemp > MAX_TEMP_LIMP + TEMP_HYST)
    {
        uGF.Overtemp_warning = 0;
    }
    
    // Fatal errors
    if((uGF.VBUS_Undervoltage == 1) || (uGF.V12_Out_of_range   == 1) || \
       (uGF.VBUS_Overvoltage  == 1) || (uGF.Hall_sensors_error == 1) || \
       (uGF.DC_Offset_error   == 1) || (uGF.Overtemperature == 1)    || (uGF.Overcurrent == 1))
    {
        Disable_PWM();  // disable the PWM
        Fatal_error = 1;
    }
    else Fatal_error = 0;
}

void SMCInit(SMC *s)
{
    //                R * Ts
    // Fsmopos = 1 - --------
    //                  L
    //            Ts
    // Gsmopos = ----
    //            L
    // Ts = Sampling Period. If sampling at PWM, Ts = 50 us
    // R = Phase Resistance. If not provided by motor datasheet,
    //     measure phase to phase resistance with multimeter, and
    //     divide over two to get phase resistance. If 4 Ohms are
    //     measured from phase to phase, then R = 2 Ohms
    // L = Phase inductance. If not provided by motor datasheet,
    //     measure phase to phase inductance with multimeter, and
    //     divide over two to get phase inductance. If 2 mH are
    //     measured from phase to phase, then L = 1 mH

	if (Q15(PHASERES * LOOPTIMEINSEC) > Q15(PHASEIND))
		s->Fsmopos = Q15(0.0);
	else
		s->Fsmopos = Q15(1 - PHASERES * LOOPTIMEINSEC / PHASEIND);

	if (Q15(LOOPTIMEINSEC) > Q15(PHASEIND))
		s->Gsmopos = Q15(0.99999);
	else
		s->Gsmopos = Q15(LOOPTIMEINSEC / PHASEIND);

	s->Kslide       = Q15(SMCGAIN);                     // SMC gain
	s->MaxSMCError  = Q15(MAXLINEARSMC);                // Max error
	s->FiltOmCoef   = Q15(OMEGA0 * _PI / IRP_PERCALC);  // Cutoff frequency for omega filter is the minimum omega, or OMEGA0
	s->ThetaOffset  = SMO_OFFSET;  //120 degrees   THETA_ALL;                        // This offset is fixed due to the use of adaptive low-pass filters

	return;
}

void Disable_PWM(void)
{
    PG1IOCONH = 0x00;   //no PWM on pins
    PG2IOCONH = 0x00;
    PG3IOCONH = 0x00;
}
