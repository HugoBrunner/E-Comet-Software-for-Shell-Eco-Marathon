//the main include file for the BLDC driver firmware

#include <xc.h>
#include "UserParms.h"
register int A_reg asm("A");
register int B_reg asm("B"); 

typedef unsigned short WORD;
typedef signed int SFRAC16;
typedef unsigned char  BYTE;
typedef unsigned char  bool;


#define PUSHCORCON()  {__asm__ volatile ("push CORCON");}
#define POPCORCON()   {__asm__ volatile ("pop CORCON");}
#define _PI 3.1416

// This macro is used to convert a float number from -1.0 to 0.99999
// to a fractional number, which is a 16 value from 0x8000 (-1.0) to
// 0x7FFF (0.99999)
#define Q15(Float_Value) ((Float_Value < 0.0) ? (SFRAC16)(32768 * (Float_Value) - 0.5) : (SFRAC16)(32767 * (Float_Value) + 0.5))

// This macro is used to convert a value from amperes to a fractional
// value that depends on the shunt resistor value used, as well as the
// amplification gain.
#define REFINAMPS(Amperes_Value)	(Q15((Amperes_Value)*RSHUNT*DIFFAMPGAIN/(VDD/2)))

#define _0_05DEG 9	// The value for 0.05 degrees is converted to Q15 as follows: .05 * 32768 / 180 = 9.1, approx 9.

//Variables for FOC algorithm 

// Structure for the Clarke/Park transformations
typedef struct {
    short   qAngle;
    short   qSin;
    short   qCos;
    short   qIa;
    short   qIb;
    short   qIc;
    short   qIalpha;
    short   qIbeta;
    short   qId;
    short   qIq;
    short   qVd;
    short   qVq;
    short   qValpha;
    short   qVbeta;
    short   qV1;
    short   qV2;
    short   qV3;
} tParkParm;
 
// Structure for PID controllers   
typedef struct {
    long    qdSum;          // 1.31 format
    short   qKp;
    short   qKi;
    short   qKc;
    short   qOutMax;
    short   qOutMin;
    short   qInRef; 
    short   qInMeas;
    short   qOut;
} tPIParm;

//structure for the control parameters
typedef struct {
    int qVelRef;    // Reference velocity
    int qVdRef;     // Vd flux reference value
    int qVqRef;     // Vq torque reference value
    unsigned int Stall_value;   //stall timer maximum value
    unsigned long Phase_increment_constant; //the constant used to compute the phase increment
    unsigned long Speed_RPM_constant;       // the constant the compute the speed in RPM
    int Angle_offset;
    int Max_phase_error;
    int Min_phase_error;
    unsigned int Correction_speed_threshold;
    unsigned int Correction_speed_threshold_hysteresis;
    unsigned int Minimum_speed;
    int Max_q_axis_value;
    unsigned int Accel_ramp_constant;
    unsigned int Decel_ramp_constant;
    unsigned int Brake_ramp_constant;
    unsigned int Use_regen_brake_current_profile;
    unsigned int Speed_scale_constant;
} tCtrlParm;

// structure for the SVM PWM generator
typedef struct {
    int iPWMPeriod;
    int iPWM_Halfperiod;
    int qVr1;
    int qVr2;
    int qVr3;
    } tSVGenParm;
    

typedef struct {
	unsigned int LockTime;
	long EndSpeed;
    int  MaxTorqueCurrent;
    int  MinTorqueCurrent;
    int  MaxBrakeCurrent;
    unsigned int Speed;
    int  Phase_Zero_D;
    int  Phase_Zero_R;
    int  MaxPowerRef;
} tMotorParm;

typedef struct {
    unsigned int  MedianFilterCounter;  // the counter for the median filter for analog parameters
    unsigned long Flt_Vbus_acc;     // accumulator for the median filter of Vbus
    unsigned long Flt_Vbias_acc;    // accumulator for the median filter of Vbias
    unsigned long Flt_Vtemp_acc;    // accumulator for the median filter of Vtemp
    unsigned int  Flt_Vbus;         // filtered Vbus
    unsigned int  Flt_Vbias;        // filtered Vbias
    unsigned int  Flt_Vtemp;        // filtered Vtemp
} tProtections;

//Sliding Mode BEMF Observer
typedef volatile struct	{  
    SFRAC16  Valpha;   		// Input: Stationary alfa-axis stator voltage 
    SFRAC16  Ealpha;   		// Variable: Stationary alfa-axis back EMF 
    SFRAC16  EalphaFinal;	// Variable: Filtered EMF for Angle calculation
    SFRAC16  Zalpha;      	// Output: Stationary alfa-axis sliding control 
    SFRAC16  Gsmopos;    	// Parameter: Motor dependent control gain 
    SFRAC16  EstIalpha;   	// Variable: Estimated stationary alfa-axis stator current 
    SFRAC16  Fsmopos;    	// Parameter: Motor dependent plant matrix 
    SFRAC16  Vbeta;   		// Input: Stationary beta-axis stator voltage 
    SFRAC16  Ebeta;  		// Variable: Stationary beta-axis back EMF 
    SFRAC16  EbetaFinal;	// Variable: Filtered EMF for Angle calculation
    SFRAC16  Zbeta;      	// Output: Stationary beta-axis sliding control 
    SFRAC16  EstIbeta;    	// Variable: Estimated stationary beta-axis stator current 
    SFRAC16  Ialpha;  		// Input: Stationary alfa-axis stator current 
    SFRAC16  IalphaError; 	// Variable: Stationary alfa-axis current error                 
    SFRAC16  Kslide;     	// Parameter: Sliding control gain 
    SFRAC16  MaxSMCError;  	// Parameter: Maximum current error for linear SMC 
    SFRAC16  Ibeta;  		// Input: Stationary beta-axis stator current 
    SFRAC16  IbetaError;  	// Variable: Stationary beta-axis current error                 
    SFRAC16  Kslf;       	// Parameter: Sliding control filter gain 
    SFRAC16  KslfFinal;    	// Parameter: BEMF Filter for angle calculation
    SFRAC16  FiltOmCoef;   	// Parameter: Filter Coef for Omega filtered calc
    SFRAC16  ThetaOffset;	// Output: Offset used to compensate rotor angle
    SFRAC16  Theta;			// Output: Compensated rotor angle 
    SFRAC16  Omega;     	// Output: Rotor speed
    SFRAC16  OmegaFltred;  	// Output: Filtered Rotor speed for speed PI
    int      IrpPerCalc;    // PWM loops per velocity calculation
    int      TransSteps;    // PWM loops necessary for transition from open loop to closed loop
    int      MinKslf;       // Minimum value for the Sliding control filter gain
    int      PI_over_IrpPerCalc;    //PI / IrpPerCalc
    } SMC;
	            
#define SMC_DEFAULTS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define THETA_AT_ALL_SPEED FILTERDELAY
#define THETA_ALL (int)(THETA_AT_ALL_SPEED / 180.0 * 32768.0)
#define OMEGA0 (float)(SPEED0 * LOOPTIMEINSEC * IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
#define OMEGANOMINAL	(float)(NOMINALSPEEDINRPM * LOOPTIMEINSEC * IRP_PERCALC * POLEPAIRS * 2.0 / 60.0)
typedef SMC *SMC_handle;
void SMC_Position_Estimation(SMC_handle);
void SMCInit(SMC_handle);

extern tMotorParm   MotorParm;    // Structure for the motor's parameters
extern tCtrlParm    CtrlParm;     // Structure for the control parameters
extern tParkParm    ParkParm;     // Structure for the Clarke/Park transformations
extern tPIParm      PIParmD;      // Structure definition for Flux component of current, or Id
extern tPIParm      PIParmQ;      // Structure definition for Torque component of current, or Iq
extern tPIParm      PIParmW;      // Structure definition for Speed, or Omega
extern tSVGenParm   SVGenParm;    // Structure for the Space Vector PWM generator
extern tProtections Protections;  // Structure for protections parameters
extern tPIParm      PIParmH;      // Structure for the Hall sensors PLL
extern tPIParm      PIParmP;      // Structure for the constant power PI

//prototypes
void InitPI( tPIParm *pParm); // Initializes Proportional-Integral controller
void CalcPI( tPIParm *pParm); // Executes a Proportional-Integral controller

void CalculateParkAngle_Inline(void);
void SetupParm(void);
void SetupControlParameters(void);
void RunMotor(void);
void StopMotor(void);
void Disable_PWM(void);
void Config_CCP1(void);
void Get_DC_Offset(void);
void Set_Clock_Low(void);
void Set_Clock_High(void);
void Motoring (void);
void Brake(void);
void Throttle_handle(void);
void Check_Protections(void);

//library functions
void FOC_loop(void); 
void Calculate_currents(void);
void Angle_correction(void);
void CalculateParkAngle_Hall(void);
void Get_Current_Sector(void);
void SMC_Position_Estimation_Inline(void);
void Limit_power(void);


