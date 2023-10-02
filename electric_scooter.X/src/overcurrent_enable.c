/*
 * File:   OC_enable.c
 * Author: A20692
 *
 * Created on July 19, 2020, 6:36 PM
 */


#include <xc.h>
#include "userparms.h"
#include "../hal/cmp1.h"

void OverCurrentEnable(void) {
      // Clearing IF flag before enabling the interrupt.
    DAC1CONLbits.DACEN = 1;
    
    IFS4bits.CMP1IF = 0;
    // Enabling CMP1 interrupt.
    IEC4bits.CMP1IE = 1;
    
    _CMP1IP = 4; 
    
    CMP1_Enable();
}
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CMP1Interrupt(void)
{

	CMP1_ISR();
    // clear the CMP1 interrupt flag
    IFS4bits.CMP1IF = 0;
}