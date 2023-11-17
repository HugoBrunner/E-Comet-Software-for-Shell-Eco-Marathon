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

// Définition de variables globales
#define FCY 8000000UL // défini la fonction : __delay_ms()
#define CYCLE_DELAY 10

// Nos librairies
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"
#include "lib_ecomet.h"

// Autres librairies
#include <libpic30.h> //Defines __delay32();
#include <math.h>

// Programme
int main(void){
    
    init_Ecomet();
    
    // Indique que la carte a fini son initialisation
    
    changeDC_Buzzer(0x00); // DC = 0 %
    __delay_ms(1000);
    changeDC_Buzzer(0x271); // DC = 50 %
    __delay_ms(1000);
    changeDC_Buzzer(0x00); // DC = 0 %
    __delay_ms(1000);
    changeDC_Buzzer(0x271); // DC = 50 %
    __delay_ms(1000);
    changeDC_Buzzer(0x00); // DC = 0 %
     
    int DC_num = 0;
    while (1){
        changeDC_Motor();
        DC_num = DC_num + 1;
    }
    return 1; 
}