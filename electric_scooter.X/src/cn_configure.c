/*
 * File:   interrupt.c
 * Author: A20692
 *
 * Created on June 23, 2020, 10:35 AM
 */


#include <xc.h>
#include "userparms.h"

void CN_Configure(void) {
    CNCONC = 0;
    /*  ON: Change Notification (CN) Control for PORTx On bit
        1 = CN is enabled
        0 = CN is disabled   */
    CNCONCbits.ON = 0;
    /*    CNSTYLE: Change Notification Style Selection bit
        1 = Edge style (detects edge transitions, bits are used for a CNE)
        0 = Mismatch style (detects change from last port read event)       */
    CNCONCbits.CNSTYLE = 0;

    CNEN0C = 0;
    CNEN0Cbits.CNEN0C4 = 1;
    CNEN0Cbits.CNEN0C5 = 1;
    CNEN0Cbits.CNEN0C10 = 1;

    _CNCIF = 0;
    _CNCIE = 1;
    _CNCIP = 5;
}

