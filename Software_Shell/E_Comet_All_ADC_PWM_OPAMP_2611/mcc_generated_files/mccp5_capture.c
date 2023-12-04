/**
  MCCP5 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    mccp5.c

  @Summary
    This is the generated driver implementation file for the MCCP5 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for MCCP5. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33CK32MP105
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB             :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
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

/**
  Section: Included Files
*/

#include "mccp5_capture.h"


void MCCP5_CAPTURE_Initialize(void)
{
    // CCPON enabled; MOD Every rising edge; CCSEL enabled; CCPSIDL disabled; T32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP5CON1L = (0x8011 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; OPS Each IC Event; SYNC None; OPSSRC Timer Interrupt Event; 
    CCP5CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP5CON2L = 0x00;
    //OCCEN disabled; OCDEN disabled; OCEEN disabled; ICGSM Level-Sensitive mode; OCFEN disabled; ICSEL IC5; AUXOUT Disabled; OCAEN disabled; OCBEN disabled; OENSYNC disabled; 
    CCP5CON2H = 0x00;
    //DT 0; 
    CCP5CON3L = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; POLBDF disabled; PSSBDF Tri-state; OUTM Steerable single output; PSSACE Tri-state; 
    CCP5CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; ICGARM disabled; TRCLR disabled; 
    CCP5STATL = 0x00;
    //TMR 0; 
    CCP5TMRL = 0x00;
    //TMR 0; 
    CCP5TMRH = 0x00;
    //PR 0; 
    CCP5PRL = 0x00;
    //PR 0; 
    CCP5PRH = 0x00;
    //CMP 0; 
    CCP5RA = 0x00;
    //CMP 0; 
    CCP5RB = 0x00;
    //BUF 0; 
    CCP5BUFL = 0x00;
    //BUF 0; 
    CCP5BUFH = 0x00;

    CCP5CON1Lbits.CCPON = 0x1; //Enabling CCP


}

void MCCP5_CAPTURE_Start( void )
{
    /* Start the Timer */
    CCP5CON1Lbits.CCPON = true;
}

void MCCP5_CAPTURE_Stop( void )
{
    /* Stop the Timer */
    CCP5CON1Lbits.CCPON = false;
}

void __attribute__ ((weak)) MCCP5_CAPTURE_CallBack(void)
{
    // Add your custom callback code here
}


void MCCP5_CAPTURE_Tasks( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS2bits.CCP5IF)
    {
		// MCCP5 CAPTURE callback function 
		MCCP5_CAPTURE_CallBack();
        
        IFS2bits.CCP5IF = 0;
    }
}

void __attribute__ ((weak)) MCCP5_CAPTURE_TimerCallBack(void)
{
    // Add your custom callback code here
}


void MCCP5_CAPTURE_TimerTasks( void )
{
    if(IFS2bits.CCT5IF)
    {
		// MCCP5 CAPTURE Timer callback function 
		MCCP5_CAPTURE_TimerCallBack();

        IFS2bits.CCT5IF = 0;
    }
}

uint16_t MCCP5_CAPTURE_Data16Read( void )
{
    /* Return the captured timer data */
    return(CCP5BUFL);

}


bool MCCP5_CAPTURE_HasBufferOverflowed( void )
{
    return( CCP5STATLbits.ICOV );
}

bool MCCP5_CAPTURE_IsBufferEmpty( void )
{
    return( ! CCP5STATLbits.ICBNE );
}

void MCCP5_CAPTURE_OverflowFlagReset( void )
{
    CCP5STATLbits.ICOV = 0;
}
/**
 End of File
*/