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

// DSPIC33CK32MP105 Configuration Bit Settings

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config FCKSM = CSECME           //Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are enabled
#pragma config PLLKEN = ON              // PLL Lock Enable (PLL clock output will be disabled if LOCK is lost)
#pragma config XTCFG = G3               // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE           // XT Boost (Boost the kick-start)

// FWDT
#pragma config RWDTPS = PS1             // Run Mode Watchdog Timer Post Scaler select bits (1:1)
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config SWDTPS = PS1             // Sleep Mode Watchdog Timer Post Scaler select bits (1:1)
#pragma config FWDTEN = ON_SW           // Watchdog Timer Enable bit (WDT controlled via SW, use WDTCON.ON bit)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGC3 and PGD3)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF         // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF         // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF         // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF         // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
#pragma config SMB3EN = SMBUS3          // SM Bus Enable (SMBus 3.0 input levels)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

#include "init_dspic.h"
#include "UserParms.h"
#include <libpic30.h>

void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0100;
    LATD = 0x0000;

//  RA0/AN0     OP1Amp Out
//  RA1/ANA1    OP1Amp -
//  RA2/AN1     OP2Amp +
    
//  AN1/AN7     OA2_OUT
//  RB3/AN8     OA2_IN-
//  RB4         OA2_IN+

//  RA4/AN4     OA3_OUT
//  RC1/AN13    OA3_IN-
//  RC2/AN14    OA3_IN+
        
//  RC6/AN17    Throttle
//  RC3/AN15    VBUS/16
//  RB7/AN2     V12    

//  RB0/AN5     BEMF A
//  RB1/AN6     BEMF B
//  RD10/AN18   BEMF C
    
//  RC4         HALL1
//  RC5         HALL2    
//  RC10        HALL3    
    
//  RC0/AN12    TEMPERATURE
//  RC11        SW_12V
//  RC12        AUX3
//  RC13        AUX4
//  RD1         AUX5
//  RD8         AUX6
//  RD13        AUX13
    
//  RC7         FAULT LED
    
//  RB8         SCL   
//  RB9         SDA
    
//  RC8         UART_TX
//  RC9         UART_RX    
    
    

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0xFFFF;
    TRISB = 0x03FF; //all inputs, except PWMs
    TRISC = 0xF67F;
    TRISD = 0xFFFF;
    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x001F;
    ANSELB = 0x009F;
    ANSELC = 0x004F;
    ANSELD = 0x0400;
    
// enable the OPAMP 1, 2, 3
    AMPCON1L = 0x8007;
    AMPCON1H = 0x0000;
	
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_RPCON(0x0000); // unlock PPS
    RPOR12bits.RP56R = 0x0001;    //RC8->UART1:U1TX
    RPINR18bits.U1RXR = 0x0039;    //RC9->UART1:U1RX
    __builtin_write_RPCON(0x0800); // lock PPS
    
    return;
}
//////////////////////////////////////////////////////////////////////
void CLOCK_Initialize(void)
{
    // FRCDIV FRC/1; PLLPRE 1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3001;
    // PLLFBDIV 100; 
    PLLFBD = 0x64;
    // TUN Center frequency; 
    OSCTUN = 0x00;
    // POST1DIV 1:2; VCODIV FVCO/2; POST2DIV 1:1; 
    PLLDIV = 0x221;
    // APLLEN disabled; FRCSEL FRC; APLLPRE 1:1; 
    ACLKCON1 = 0x101;
    // APLLFBDIV 150; 
    APLLFBD1 = 0x96;
    // APOST1DIV 1:4; APOST2DIV 1:1; AVCODIV FVCO/4; 
    APLLDIV1 = 0x41;
    // CANCLKEN disabled; CANCLKSEL No Clock Selected; CANCLKDIV Divide by 1; 
//    CANCLKCON = 0x00;
    // ROEN disabled; ROSWEN disabled; ROSLP disabled; ROSEL FOSC; ROOUT disabled; ROSIDL disabled; 
    REFOCONL = 0x00;
    // RODIV 0; 
    REFOCONH = 0x00;
    // IOLOCK disabled; 
    RPCON = 0x00;
    // PMDLOCK disabled; 
    PMDCON = 0x00;
    // ADC1MD enabled; T1MD enabled; U2MD enabled; U1MD enabled; SPI2MD enabled; SPI1MD enabled; QEIMD enabled; C1MD enabled; PWMMD enabled; I2C1MD enabled; 
    PMD1 = 0x00;
    // CCP2MD enabled; CCP1MD enabled; CCP4MD enabled; CCP3MD enabled; CCP7MD enabled; CCP8MD enabled; CCP5MD enabled; CCP6MD enabled; CCP9MD enabled; 
    PMD2 = 0x00;
    // I2C3MD enabled; U3MD enabled; QEI2MD enabled; CRCMD enabled; I2C2MD enabled; 
    PMD3 = 0x00;
    // REFOMD enabled; 
    PMD4 = 0x00;
    // DMA1MD enabled; SPI3MD enabled; DMA2MD enabled; DMA3MD enabled; DMA0MD enabled; 
    PMD6 = 0x00;
    // CMP3MD enabled; PTGMD enabled; CMP1MD enabled; CMP2MD enabled; 
    PMD7 = 0x00;
    // DMTMD enabled; CLC3MD enabled; OPAMPMD enabled; BIASMD enabled; CLC4MD enabled; SENT2MD enabled; SENT1MD enabled; CLC1MD enabled; CLC2MD enabled; 
    PMD8 = 0x00;
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x01));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}

//////////////////////////////////////////////////////////
void INTERRUPT_Initialize (void)
{   
    // config the ADC17 interrupt
    IPC27bits.ADCAN17IP = 5;  // priority level is 5
    
    IFS6bits.ADCAN17IF = 0; //clear flag
    IEC6bits.ADCAN17IE = 1; //enable CH17 interrupt
    
    // config comparators interrupts
    // priority must be higher than the priority of ADC17 interrupt
    IFS4bits.CMP1IF = 0;    // clear the flag
    IFS4bits.CMP2IF = 0;
    IFS4bits.CMP3IF = 0;
    
    IPC19bits.CMP1IP = 6;   // priority level is 6
    IPC19bits.CMP2IP = 6;
    IPC19bits.CMP3IP = 6;

    IEC4bits.CMP1IE = 1;    // enable the interrupt
    IEC4bits.CMP2IE = 1;
    IEC4bits.CMP3IE = 1;
}



////////////////////////////////////////////////////////////////////////
void ADC1_Initialize (void)
{   
 // ADC config
    
    ADCON1L = 0x0000;   //ADC off
    ADCON1H = 0x00E0;   //12 bits, fractional
    ADCON2L = 0x0000;   //SHRADCS = 2
    ADCON2H = 0x0001;   //
    ADCON3L = 0x0000;
    ADCON3H = 0xC200;    //CLKSEL = Peripheral Clock (100 MHz) CLKDIV = 2 Source Clock Period       
    ADCON4L = 0x0000;   //
    ADCON4H = 0x0000;   //AN0, AN1 = inputs to dedicated ADC cores
    ADCON5L = 0x0000;   //all dedicated cores OFF
    ADCON5H = 0x0000;    
    ADCORE0L = 0x0000;
    ADCORE0H = 0x0300;  //12 bits  
    ADCORE1L = 0x0000;
    ADCORE1H = 0x0300;   //12 bits
    
    
//  CH0 - OA1 - signed
//  CH1 - OA2 - signed
//  CH7 - OA2 - signed    
//  CH2 - V12 - unsigned
//  CH4 - OA3 - signed
//  CH12 - VTemp - unsigned    
//  CH15 - VBUS - unsigned
//  CH17 - Throttle - unsigned    
    ADMOD0L = 0x4105;   //  0x0105; 
    ADMOD0H = 0x0000;
    ADMOD1L = 0x0000;
    
    ADIEL = 0x00;
    ADIEH = 0x02;
    
    ADFL0CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL1CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL2CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL3CON = 0x400;
       
    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();
    // Enabling Power for Core 0
    ADC1_Core0PowerEnable();
    // Enabling Power for Core 1
//    ADC1_Core1PowerEnable();

    //ADC0, ADC1, ADC2, ADC4, ADC15, ADC17
    
    ADTRIG0L = 0x0004; //CH0 triggered by PWM1, CH1 N/A
    ADTRIG0H = 0x0004; //CH2 triggered by PWM1, CH3 N/A
    ADTRIG1L = 0x0004; //CH4 triggered by PWM1, CH5 N/A
    ADTRIG1H = 0x0400; //CH6 N/A, CH7 triggered by PWM1
    ADTRIG2L = 0x0000; //CH8 N/A, CH9 N/A
    ADTRIG2H = 0x0000; //CH10 N/A, CH11 N/A
    ADTRIG3L = 0x0004; //CH12 triggered by PWM1, CH13 N/A
    ADTRIG3H = 0x0400; //CH14 N/A, CH15 triggered by PWM1
    ADTRIG4L = 0x0400; //CH16 N/A, CH17 triggered by PWM1
}

void ADC1_Core0PowerEnable ( ) 
{
    ADCON5Lbits.C0PWR = 1; 
    while(ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN = 1;     
}

void ADC1_Core1PowerEnable ( ) 
{
    ADCON5Lbits.C1PWR = 1; 
    while(ADCON5Lbits.C1RDY == 0);
    ADCON3Hbits.C1EN = 1;     
}

void ADC1_SharedCorePowerEnable ( ) 
{
    ADCON5Lbits.SHRPWR = 1;   
    while(ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN = 1;   
}

void T1_Init(void)
{
    T1CON = 0x120;  //Clock is Fcy, prescaler is 1:64, timer off
    PR1 = 10000;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC0bits.T1IP = 1;
}

void Config_CCP1(void)
{
    REFOCONL = 0x8000;  //Reference Clock Enable, System clock (FOSC) as source - 200 MHz    
    REFOCONH = 8;       //divide by 16, 12.5MHz
    CCP1CON1L = 0x81C0; //16 bit timer, REFOCLK, 1:64 prescaler
    CCP1CON1H = 0;
    CCP1CON2H = 0;  
}

// init Comparators+DACs for overcurrent/short-circuit detection
// one comparator per phase; the threshold is set to the maximum value
void init_DAC_COMP(void)
{
    DACCTRL1L = 0x00C0; //CLKSEL = FPLLO, CLKDIV = 1 => 400MHz   
    DAC1CONH  = 0;
    DAC2CONH  = 0;
    DAC3CONH  = 0;
    
    // center 2130
    DAC1DATH = 3890;   //TH high, maximum value according with the data-sheet
    DAC2DATH = 3890;
    DAC3DATH = 3890;
    
    //CMP1A - IA
    //CMP3B - IB
    //CMP2D - IC
    DAC1CONL  = 0xA101; // digital filter "on", CMP1A - input, interrupt on rising edge
    DAC2CONL  = 0xA119; // digital filter "on", CMP2D - input, interrupt on rising edge
    DAC3CONL  = 0xA109; // digital filter "on", CMP3B - input, interrupt on rising edge
    
    DACCTRL1Lbits.DACON = 1;
}


void WDT_Setup(void)
{
    WDTCONL = 0x80C0; //WDT on, LPRC oscillator is used as the clock source, RUNDIV=0
}

//set clock to 100MIPS
void Set_Clock_High(void)
{
    //set clock to 100MIPS
    // CF no clock failure; NOSC FRCPLL; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x01));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
    while (OSCCONbits.LOCK != 1);
}

void Set_Clock_Low(void)
{
    //set clock to low MIPS
    // CF no clock failure; NOSC FRC; CLKLOCK unlocked; OSWEN Switch is Complete; 
    __builtin_write_OSCCONH((uint8_t) (0x00));
    __builtin_write_OSCCONL((uint8_t) (0x01));
    // Wait for Clock switch to occur
    while (OSCCONbits.OSWEN != 0);
}

