/*
 * Projet Shell Eco-Marathon 2024
 * 
 * Ecole d'Ingénieurs de Pierrard-Virton
 * 
 */

// Définition de variables globales
#define FCY 8000000UL // défini la fonction : __delay_ms()
#define CYCLE_DELAY 10

// Nos librairies
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/mccp5_capture.h"
#include "lib_ecomet.h"

// Autres librairies
#include <libpic30.h> //Defines __delay32();
#include <math.h>

// Programme
int main(void){
    
    uint16_t test = 0;
    
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
     
    while (1){
        changeDC_Motor();
        
        measureVBUS();
        measureTempMOSFET();
        measureShunt_1();
        measureShunt_2();
    }
    return 1; 
}