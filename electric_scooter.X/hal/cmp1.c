/*******************************************************************************
  CMP1 Configuration Routine source File
 
  File Name:
    cmp1.c

  Summary:
    This file includes subroutine for initializing ADC Cores of Controller

  Description:
    Definitions in the file are for dsPIC33CK256MP508 MC PIM plugged onto
    Motor Control Development board from Microchip

*******************************************************************************/
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


/**
  Section: Included Files
*/

#include "cmp1.h"

/**
  Section: CMP1 APIs
*****************************************************************************************/
/******************************************************************************
*                                                                             
*    Function:			CMP1_Initialize
*    Description:       Initialization of the Comparator with Slope Compensation module                                                                         
*                                             
*    Return Value:      None
******************************************************************************/

void CMP1_Initialize(void)
{           

    // Disable the CMP module before the initialization
    CMP1_Disable();
	
	// Comparator Register settings
	DACCTRL1L = 0xC0; //CLKDIV 1:1; DACON disabled; DACSIDL disabled; FCLKDIV 1:1; CLKSEL FPLLO - System Clock with PLL Enabled; 
	DACCTRL2L = 0x55; //TMODTIME 85; 
	DACCTRL2H = 0x8A; //SSTIME 138; 
	DAC1CONH = 0x00; //TMCB 0; 
	DAC1CONL = 0x2200; //CMPPOL Non Inverted; HYSPOL Rising Edge; HYSSEL None; DACEN disabled; FLTREN disabled; CBE disabled; IRQM Rising edge detect; INSEL CMP1A; DACOEN enabled; 

	//Slope Settings
	SLP1CONH = 0x00; //HME disabled; PSE Negative; SLOPEN disabled; TWME disabled; 
	SLP1CONL = 0x00; //HCFSEL None; SLPSTRT None; SLPSTOPB None; SLPSTOPA None; 
	SLP1DAT = 0x00; //SLPDAT 0; 
	DAC1DATL = 0x00; //DACDATL 0; 
	DAC1DATH = 0xe74; //DACDATH 3498; 0xA2E;
    
	
    CMP1_Enable();

}

/******************************************************************************
*                                                                             
*    Function:			CMP1_ComparatorOuputStatusGet
*    Description:       Returns the status of the Comparator including the 
*						polarity                                                                       
*                                             
*    Return Value:      True if the Comparator Status is 1 and False if it is 0
******************************************************************************/
bool CMP1_ComparatorOuputStatusGet(void)
{
    return (DAC1CONLbits.CMPSTAT);
}

/******************************************************************************
*                                                                             
*    Function:			CMP1_Enable
*    Description:       Enables the common DAC module                                     
*      
*	 Parameters:		None                                       
*    Return Value:      None
******************************************************************************/
void CMP1_Enable(void)
{
    DACCTRL1Lbits.DACON = 1;
}

/******************************************************************************
*                                                                             
*    Function:			CMP1_Disable
*    Description:       Disables the common DAC module                                     
*      
*	 Parameters:		None                                       
*    Return Value:      None
******************************************************************************/
void CMP1_Disable(void)
{
    DACCTRL1Lbits.DACON = 0;
}

/******************************************************************************
*                                                                             
*    Function:			CMP1_SetInputSource
*    Description:       Set the source to the non-inverting input of the 
*						Comparator module                                                                     
*      
*	 Parameters:		Enumeration specifying the input source                                      
*    Return Value:      None
******************************************************************************/
void CMP1_SetInputSource(CMP1_INPUT inpSrc)
{
    DAC1CONLbits.INSEL = inpSrc;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetDACDataHighValue
*    Description:       Sets the DAC Data High Value                                     
*      
*    Parameters:        Value to be set as DAC Data High                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetDACDataHighValue(uint16_t dacVal)
{
    DAC1DATH = dacVal;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetDACDataLowValue
*    Description:       Sets the DAC Data Low Value                                     
*      
*    Parameters:        Value to be set as DAC Data Low                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetDACDataLowValue(uint16_t dacVal)
{
    DAC1DATL = dacVal;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_EnableDACOutput
*    Description:       Enables the DAC Output                                    
*      
*    Parameters:        None                                       
*    Return Value:      None
******************************************************************************/
void CMP1_EnableDACOutput(void)
{
    DAC1CONLbits.DACOEN = 1;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_DisableDACOutput
*    Description:       Disables the DAC Output                                    
*      
*    Parameters:        None                                       
*    Return Value:      None
******************************************************************************/
void CMP1_DisableDACOutput(void)
{
    DAC1CONLbits.DACOEN = 0;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetStartTrigger
*    Description:       Trigger set for the Start Signal of the Slope                                    
*      
*    Parameters:        Value indicating the trigger to be set                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetStartTrigger(CMP1_START_TRIGGER trigger)
{
    SLP1CONLbits.SLPSTRT = trigger;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetStopATrigger
*    Description:       Trigger set for the Stop A Signal of the Slope                                    
*      
*    Parameters:        Value indicating the trigger to be set                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetStopATrigger(CMP1_STOPA_TRIGGER trigger)
{
    SLP1CONLbits.SLPSTOPA = trigger;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetStopBTrigger
*    Description:       Trigger set for the Stop B Signal of the Slope                                    
*      
*    Parameters:        Value indicating the trigger to be set                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetStopBTrigger(CMP1_STOPB_TRIGGER trigger)
{
    SLP1CONLbits.SLPSTOPB = trigger;
}

/******************************************************************************
*                                                                             
*    Function:		CMP1_SetHystereticTrigger
*    Description:       Trigger set for the Hysteretic mode                                    
*      
*    Parameters:        Value indicating the trigger to be set                                       
*    Return Value:      None
******************************************************************************/
void CMP1_SetHystereticTrigger(CMP1_HYSTERETIC_FUNCTION trigger)
{
    SLP1CONLbits.HCFSEL = trigger;
}

/* Callback function for the CMP1 module */
void __attribute__ ((weak)) CMP1_CallBack(void)
{
    // Add your custom callback code here
}

/******************************************************************************
*    Function:			CMP1_Tasks
*    Description:       The Task function can be called in the main application 
*						using the High Speed Comparator, when interrupts are not 
*						used.  This would thus introduce the polling mode feature 
*						of the Analog Comparator.                                                                     
*      
*	 Parameters:		None                                      
*    Return Value:      None 
******************************************************************************/
void CMP1_Tasks(void)
{
	if(IFS4bits.CMP1IF)
	{
		// CMP1 callback function 
		CMP1_CallBack();
	
		// clear the CMP1 interrupt flag
		IFS4bits.CMP1IF = 0;
	}
}

/**
 End of File
*/