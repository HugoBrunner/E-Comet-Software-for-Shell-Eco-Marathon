/**
  MCCP5 Generated Driver API Header File 

  @Company
    Microchip Technology Inc.

  @File Name
    mccp5.h

  @Summary
    This is the generated header file for the MCCP5 driver using PIC24 / dsPIC33 / PIC32MM MCUs

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

#ifndef _MCCP5_CAPTURE_H
#define _MCCP5_CAPTURE_H

/**
  Section: Included Files
*/

#include <xc.h> 
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes MCCP/SCCP instance : 5

  @Description
    This routine initializes the MCCP/SCCP driver for instance : 5
    index, making it ready for clients to open and use it. It also initializes any
    internal data structures.

  @Param
    None.

  @Returns
    None.
  
  @Comment
   
*/
void MCCP5_CAPTURE_Initialize(void);

/**
  @Summary
    Starts the MCCP5

  @Description
    This routine starts the MCCP5

  @Param
    None.

  @Returns
    None
*/

void MCCP5_CAPTURE_Start( void );
/**
  @Summary
    Stops the MCCP5

  @Description
    This routine stops the MCCP5

  @Param
    None.

  @Returns
    None
*/

void MCCP5_CAPTURE_Stop( void );

/**
  @Summary
    Callback for MCCP5 CAPTURE.

  @Description
    This routine is callback for MCCP5 CAPTURE

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to MCCP5_Initialize(); for an example
*/
void MCCP5_CAPTURE_CallBack(void);

/**
  @Summary
    Maintains the driver's capture mode state machine in a polled manner

  @Description
    This routine is used to maintain the driver's capture mode state
    machine.This routine is called when the state of the capture mode needs to be
    maintained in a polled manner.

  @Param
    None.

  @Returns
    None
*/

void MCCP5_CAPTURE_Tasks( void );

/**
  @Summary
    Callback for MCCP5 CAPTURE Timer.

  @Description
    This routine is callback for MCCP5 CAPTURE Timer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to MCCP5_Initialize(); for an example
*/
void MCCP5_CAPTURE_TimerCallBack(void);

/**
  @Summary
    Maintains the driver's capture mode state machine in a polled manner

  @Description
    This routine is used to maintain the driver's capture mode state
    machine.This routine is called when the state of the capture mode needs to be
    maintained in a polled manner.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    while (true)
    {
        MCCP5_CAPTURE_TimerTasks();

        // Do other tasks
    }
    </code>
    
*/
void MCCP5_CAPTURE_TimerTasks( void );

/**
  @Summary
    Reads the 16 bit capture value. 

  @Description
    This routine reads the 16 bit capture value. 

  @Param
    None.

  @Returns
    Returns 16 bit captured value
*/

uint16_t MCCP5_CAPTURE_Data16Read( void );

/**
  @Summary
    Gets the buffer overflow status.

  @Description
    This routine gets the buffer overflow status.

  @Param
    None.

  @Returns
    Returns true if the input capture buffer has overflowed. 
    Returns false if the input capture buffer has not overflowed. 
*/

bool MCCP5_CAPTURE_HasBufferOverflowed( void );
/**
  @Summary
    Gets the buffer empty status.

  @Description
    This routine gets the buffer empty status.

  @Param
    None.

  @Returns
    Returns true if the input capture buffer is empty . 
    Returns false if the input capture buffer is not empty. 
*/

bool MCCP5_CAPTURE_IsBufferEmpty( void );
/**
  @Summary
    Resets the buffer overflow status flag.

  @Description
    This routine resets the buffer overflow status flag.

  @Param
    None.

  @Returns
    None. 
*/

void MCCP5_CAPTURE_OverflowFlagReset( void );
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_MCCP5_H
/**
 End of File
*/