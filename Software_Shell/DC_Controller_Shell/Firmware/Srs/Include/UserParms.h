// Kick E-Scooter BLDC Motor Driver
// Three-shunt motor phase currents measurement
// To be used with the "High-Performance E-Scooter BLDC Motor Driver Reference Design" board


// *** Section: Options  ***
// Please read the documentation associated to this firmware before modifying these options!

//#define SENSORLESS                   // run in sensorless mode; there are limitations related to the minimum speed, see the AN1078
//#define OPENLOOPONLY                 // run only in open-loop mode; for debugging only!
#define REVERSE_DIRECTION             // reverse the direction of spinning
#define TORQUE_MODE                   // torque mode enable; if this option is disabled the controller will use the speed mode
#define HIGH_SPEED_ANGLE_CORRECTION   // correct the angle at high speeds using the BEMF Observer information
#define REGEN_BRAKE                   // activate the regenerative braking. WARNING: DANGEROUS IF IS TESTED WITHOUT A BATTERY!
#define REGEN_BRAKE_CURRENT_PROFILER  // activate the regenerative brake current profiler: the brake current will be interpolated as a function of speed
#define USE_MINIMUM_SPEED_TO_START    // the driver starts only if the motor has a certain speed. This is a safety feature for e-scooters.
#define CONSTANT_POWER_MODE           // activate the "Constant Power Mode"; the input current is limited to the value defined by MAX_INPUT_CURRENT constant
//#define X2C_SCOPE                     // use X2C Scope
//#define TUNE_PHASE_DIFFERENCE       // tune the phase difference between the angle provided by the estimator and the angle provided by the Halls  

// ***********************

// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************
// OSCILLATOR Related Definitions
// Oscillator frequency (Hz) - 200,000,000 Hz
#define FOSC                    200000000UL
// Oscillator frequency (MHz) - 200MHz
#define FOSC_MHZ                200U     
// Instruction cycle frequency (Hz) - 100,000,000 Hz
#define FCY                     100000000UL
// Instruction cycle frequency (MHz) - 100 MHz
#define FCY_MHZ                 100U  
/* Specify PWM Frequency in Hertz */
#define PWMFREQUENCY_HZ         16000   
/* Specify PWM Period in micro seconds */
#define LOOPTIME_MICROSEC       (unsigned int)(1.0/PWMFREQUENCY_HZ*1000000)  
// loop time in terms of PWM clock period  
#define LOOPTIME_TCY            (uint16_t)((LOOPTIME_MICROSEC*FOSC_MHZ)-1)      

// *** Section: Parameters for protections ***********
#define MIN_VBUS        (unsigned int) (32.0 / TOP_VBUS  * 65535) // in Volts
#define MAX_VBUS        (unsigned int) (45.0 / TOP_VBUS  * 65535) // in Volts, currently 45V
#define VBUS_HYST       (unsigned int) (2.0  / TOP_VBUS  * 65535) // in Volts, currently 2V
#define TYP_VBIAS       (unsigned int) (12.0 / TOP_VBIAS * 65535) // in Volts, currently 12V 
#define VBIAS_HYST      (unsigned int) (1.5  / TOP_VBIAS * 65535) // in Volts; hysteresis for the bias voltage measurement, currently 1.5V
#define MAX_CURRENT              (int) (55.0 / IPEAK     * 32767) // In Amp, peak current, currently 55A
#define MAX_DC_OFFSET            (int) (0.1  / 1.65      * 32767) // in Volts, currently 100mV
#define MAX_TEMP_OFF    2800     // in units. Aprox 115C. This is an unsigned quantity; range is 0 - 65535
#define MAX_TEMP_LIMP   3640     // in units. Aprox 105C. This is an unsigned quantity; range is 0 - 65535
#define TEMP_HYST       400      // in units. This is an unsigned quantity; range is 0 - 65535
//*******************************************

#define STALL_VAL       320   // stall detection timer value, this must be multiplied with the PWM period to find the value in seconds; currently 20ms


// *** Definitions for the input throttle key or potentiometer******************************************
//**** Linear Hall sensor throttle key
#define THROTTLE_LOW    (int)((0.99/3.3)*32767)     // (low level voltage / scale)* 32767, currently 0.99V
#define THROTTLE_HIGH   (int)((2.5/3.3)*32767)      // (high level voltage / scale)* 32767, currently 2.5V
#define THROTTLE_HYSTERESIS (int)((0.05/3.3)*32767) // (hysteresis voltage / scale)* 32767, , currently 50mV

//**** Potentiometer
//#define THROTTLE_LOW    (int)((0.1/3.3)*32767)       // (low level voltage / scale) 32767
//#define THROTTLE_HIGH   (int)((3.25/3.3)*32767)      // (high level voltage / scale) 32767
//#define THROTTLE_HYSTERESIS (int)((0.05/3.3)*32767)  // (hysteresis voltage / scale)* 32767


//*** Section: Acceleration/deceleration/brake ramp parameters
#define ACCEL_RAMP_CONST    30  // acceleration ramp constant; a higher value provides a steeper ramp for the acceleration
#define DECEL_RAMP_CONST    70  // deceleration ramp constant; a higher value provides a steeper ramp for the deceleration
#define BRAKE_RAMP_CONST    80  // regenerative brake ramp constant; a higher value provides a steeper ramp for the regenerative brake
//*** 


//*** Section: Regenerative brake current profile
#define B_CURRENT_7     27.5      // in Amps
#define B_CURRENT_6     26
#define B_CURRENT_5     24.5
#define B_CURRENT_4     23.5
#define B_CURRENT_3     22
#define B_CURRENT_2     18
#define B_CURRENT_1     12
#define B_CURRENT_0      8

#define B_SPEED_7       800     // in RPM
#define B_SPEED_6       700
#define B_SPEED_5       600
#define B_SPEED_4       500
#define B_SPEED_3       400
#define B_SPEED_2       300
#define B_SPEED_1       200
#define B_SPEED_0       100
//*************************************************


//*** Section: Motor parameters
//************************************************ 
/* 250W, 15 pole pairs BLDC hub motor
 Keep the maximum peak current below 35A to avoid the motor overload!
 */
#define POLEPAIRS               15                  
#define PHASERES                0.260     // in Ohms
#define PHASEIND                0.000395  // in Henry
#define PHASE_ZERO_D            21100     // initial phase for Hall angle interpolator in "Forward Mode"
#define PHASE_ZERO_R            9700      // initial phase for Hall angle interpolator in "Reverse Mode"
#define INITIALTORQUE_ALLIGN    15        // in Amps, this is the peak current
#define INITIALTORQUE           15        // in Amps, this is the peak current
#define PHASE_ADVANCE_6_STEP    0         // in units, 182 units for 1 degree, 0 degrees now
#define MAX_TORQUE_CURRENT      35        // in Amps, this is the peak current
#define MAX_TORQUE_CURRENT_LIMP 20        // in Amps, this is the peak current
#define MIN_TORQUE_CURRENT      0         // in Amps, this is the peak current
#define BRAKE_CURRENT           22.0      // in Amps, peak current
#define MAX_INPUT_CURRENT       16.0      // Maximum input (battery) current, in Amps
#define LOCKTIMEINSEC           0.3       // Initial rotor lock time in seconds. Make sure LOCKTIMEINSEC*(1.0/LOOPTIMEINSEC) is less than 65535.
#define MAX_SPEED_RPM           650       // in RPM, used only in closed loop speed control
#define MIN_SPEED_RPM           40        // in RPM, used only in closed loop speed control
#define CORRECTION_SPEED_THR    80        // in RPM, this is the threshold where the correction of angle starts to operate
#define CORRECTION_SPEED_HYST   10        // in RPM
#define ANGLE_OFFSET            0         // 182 units per degree
#define BRAKE_MIN_SPEED         70        // in RPM, if the speed is lower than this threshold the regenerative brake will be disabled

#define OPENLOOPTIMEINSEC 0.8   // Open loop time in seconds. This is the time that
                                // will take from stand still to closed loop.
#define NOMINALSPEEDINRPM 800	// Make sure NOMINALSPEEDINRPM generates a MAXOMEGA < 1.0
								// Use this formula:
								// MAXOMEGA = NOMINALSPEEDINRPM*SPEEDLOOPTIME*POLEPAIRS*2/60
								// If MAXOMEGA > 1.0, reduce NOMINALSPEEDINRPM or execute
								// speed loop faster by reducing SpeedLoopTime.
								// Maximum position of POT will set a reference of 
								// NOMINALSPEEDINRPM.
#define MINSPEEDINRPM	80     // Minimum speed in RPM. Closed loop (in sensorless mode) will operate at this
								// speed. Open loop will transition to closed loop at
								// this minimum speed. Minimum POT position (CCW) will set
								// a speed reference of MINSPEEDINRPM
#define MINIMUM_START_SPEED 70  // in RPM. The driver will start only if the speed of the motor is over this value.
                                // Used only if USE_MINIMUM_SPEED_TO_START option is active

//***************************************************


#define ENDSPEEDOPENLOOP    MINSPEEDINRPM   //this is the speed at the end of open-loop; valid only in sensorless mode
#define MAX_PHASE_ERROR     2730            //182 units per degree, 15 degrees
#define MIN_PHASE_ERROR     -2730           //182 units per degree, -15 degrees
         
// definitions for the Hall sensors angle interpolator/speed measurement
//DO NOT ALTER!
#define PHASE_INC_CALC   (unsigned long int)(106667*(20000.0/PWMFREQUENCY_HZ))
#define SPEED_RPM_CALC  ((FOSC/16)/(64*POLEPAIRS*2))*20

//************** Sliding Mode Controller Parameters **********
#define SMCGAIN			0.75    // Sliding Mode Controller Gain (0.0 to 0.9999)
#define MAXLINEARSMC    0.25	// If measured current - estimated current
								// is less than MAXLINEARSMC, the slide mode
								// Controller will have a linear behavior
								// instead of ON/OFF. Value from (0.0 to 0.9999)
#define SMO_OFFSET     21840    // constant offset; the angle observer introduces a constant phase delay of 120 degrees; 120*182 = 21840

//************** Section: PI Coefficients **************

//******** D Control Loop Coefficients *******
#define     DKP        Q15(0.35)
#define     DKI        Q15(0.00825)
#define     DKC        Q15(1)
#define     DOUTMAX    Q15(1)

//******** Q Control Loop Coefficients *******
#define     QKP        Q15(0.35)
#define     QKI        Q15(0.00825)
#define     QKC        Q15(1)
#define     QOUTMAX    Q15(1)   

//*** Velocity Control Loop Coefficients *****
#define     WKP        Q15(0.65)
#define     WKI        Q15(0.004)
#define     WKC        Q15(1)
#define     WOUTMAX    REFINAMPS(MAX_TORQUE_CURRENT)   // limit the current
#define     SPEED_SCALE_CONSTANT    1                  // the measured speed and the reference speed will be multiplied by 
                                                       // 2^SPEED_SCALE_CONSTANT before running the speed loop PI
                                                       // Make sure that MAX_SPEED * 2^SPEED_SCALE_CONSTANT < 32767

//*** Hall sensors angle PLL Coefficients *****
// currently optimized for a 250W, 15-pole pairs hub motor
#define     HKP        100
#define     HKI        2
#define     HKC        Q15(1)
#define     HOUTMAX    2500    //limit the output

//*** Constant power PI Coefficients *****
// currently optimized for a 7.5Ah/36V battery and a kick e-scooter equipped with a 250W BLDC motor
#define     PKP        7000
#define     PKI        50
#define     PKC        Q15(1)
#define     POUTMAX    REFINAMPS(MAX_TORQUE_CURRENT);    //limit the output
#define     POUTMIN    REFINAMPS(MIN_TORQUE_CURRENT);    //limit the output

// *** Parameters for the sensorless operating mode
#define SPEEDLOOPFREQ	1000		// Speed loop Frequency in Hertz. This value must
									// be an integer to avoid pre-compiler error
    
						// PWM Period = 1.0 / PWMFREQUENCY
#define LOOPTIMEINSEC 	(1.0/PWMFREQUENCY_HZ )  //50us for 20 kHz PWM

						// Speed Control Period
#define SPEEDLOOPTIME 	(float)(1.0/SPEEDLOOPFREQ)          
						
                        // PWM loops per velocity calculation
#define IRP_PERCALC 	(unsigned int)(SPEEDLOOPTIME/LOOPTIMEINSEC)        
    
// PWM loops necessary for transition from open-loop to closed-loop
#define TRANSITION_STEPS   IRP_PERCALC/2
   
// Basic loop period in units of Tcy
#define LOOPINTCY		(LOOPTIMEINSEC/DTCY)
#define LOCKTIME		(unsigned int)(LOCKTIMEINSEC*(1.0/LOOPTIMEINSEC))

// Time it takes to ramp from zero to MINSPEEDINRPM. 
// Time represented in seconds
#define DELTA_STARTUP_RAMP	(unsigned int)(MINSPEEDINRPM*POLEPAIRS*LOOPTIMEINSEC* LOOPTIMEINSEC*65536*65536/(60*OPENLOOPTIMEINSEC))
#define SPEED0 MINSPEEDINRPM
#define OMEGA0 (float)(SPEED0 * LOOPTIMEINSEC * IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)   //100*50us*20*15*2/60   0.05  
#define OMEGANOMINAL	(float)(NOMINALSPEEDINRPM * LOOPTIMEINSEC * IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
    
// This pre-processor condition will generate an error if maximum speed is out of
// range on Q15 when calculating Omega.
#if ((NOMINALSPEEDINRPM*POLEPAIRS*2/(60*SPEEDLOOPFREQ)) >= 1)
		#error NOMINALSPEEDINRPM will generate an Omega value greater than 1 which is the
		#error maximum in Q15 format. Reduce NOMINALSPEEDINRPM value, or increase speed
		#error control loop frequency, SPEEDLOOPFREQ
#endif

// *****************************************************************************
// PWM generator and SVM PWM parameters
// DO NOT ALTER!
#define PWM_TOP         (uint16_t)((LOOPTIME_MICROSEC*FOSC_MHZ)-1)
#define SVMPWM_TOP      (int)(PWM_TOP/2/0.866)
#define SVMPWM_HALF     (int)(PWM_TOP/2)
#define DEADTIMESEC		0.0000005	// Deadtime in seconds, 500ns, DO NOT ALTER!
#define DDEADTIME   	(unsigned int)(DEADTIMESEC*FOSC*2)

//************** Hardware Parameters ****************
#define RSHUNT		 0.002 // Value in Ohms of shunt resistors used. DO NOT ALTER!
#define DIFFAMPGAIN	 12.6  // Gain of the differential amplifier.    DO NOT ALTER!
#define VDD			 3.3   // VDD voltage, only used to convert torque reference from Amps to internal variables. DO NOT ALTER!   
#define UMAX         52.0  // in Volts, DO NOT ALTER!
#define IPEAK        60.0  // in Amp, DO NOT ALTER!
#define TOP_VBUS     52.8  // in Volts, DO NOT ALTER!
#define TOP_VBIAS    19.1  // in Volts, DO NOT ALTER!

#define MAX_POWER_REFERENCE Q15((MAX_INPUT_CURRENT/0.83)*RSHUNT*DIFFAMPGAIN/(VDD/2))

//linear interpolation coefficients
//DO NOT ALTER!
#define THROTTLE_SCALE_A_COEFFICIENT (int)((33553408/(THROTTLE_HIGH - THROTTLE_LOW)))
#define THROTTLE_SCALE_B_COEFFICIENT (long int)((33553408/(THROTTLE_HIGH - THROTTLE_LOW))*THROTTLE_LOW)
// *******************************************************************************************************