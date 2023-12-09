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
             
    init_Ecomet();
    
    float Imax = 10;              // Ampères
    float Umin = 0;             // Volts
    float Umax = 25;             // Volts
    float TempMOSmax = 75;       // °C
    float TempPICmax = 125;      // °C
    
    // Valeurs initiales (lecture des ADCs)
    float VBUS = measureVBUS();
    float courantBatt = measureShunt_1();
    float courantMoteur = measureShunt_2();
    float tempMOS = measureTempMOSFET();
    float tempPIC = 25;//measureTempPIC();
    
    // Indique que la carte a fini son initialisation
    changeDC_Buzzer(0x4E1); // DC = 0 %
    __delay_ms(250);
    changeDC_Buzzer(0x271); // DC = 50 %
    __delay_ms(250);
    changeDC_Buzzer(0x4E1); // DC = 0 %
    __delay_ms(250);
    changeDC_Buzzer(0x271); // DC = 50 %
    __delay_ms(250);
    changeDC_Buzzer(0x4E1); // DC = 0 %
    __delay_ms(250);
     
    while (1){
        
        LATCbits.LATC7 = 0;
        LATCbits.LATC12 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD8 = 0;
        
        while (courantBatt <= Imax && courantMoteur <= Imax && VBUS >= Umin && VBUS <= Umax && tempPIC <= TempPICmax && tempMOS <= TempMOSmax){

            changeDC_Motor();

            VBUS = measureVBUS();
            tempMOS = measureTempMOSFET();
            courantBatt = measureShunt_1();
            courantMoteur = measureShunt_2();
        } 
        
        // Allume la LED rouge FAULT
        LATCbits.LATC7 = 1;
        
        // Coupe le moteur
        changeDC_Motor_Error(0);
        
        // Allume la LED correspondante afin de prévenir le pilote du problème
        if(courantBatt >= Imax){
            LATCbits.LATC12 = 1;
        }
        else if(courantMoteur >= Imax){
            LATCbits.LATC12 = 1;
        }
        else if(VBUS <= Umin || VBUS >= Umax){
            LATDbits.LATD1 = 1;
        }
        else if(tempMOS >= TempMOSmax){
            LATDbits.LATD8 = 1;
        }
                
        // Boucle Reset
        int a = 1;
        while(a == 1){          
            
            // Test le bouton lors de l'attente du Reset
            a = PORTDbits.RD13; 
        }
        
        VBUS = measureVBUS();
        tempMOS = measureTempMOSFET();
        courantBatt = measureShunt_1();
        courantMoteur = measureShunt_2();
    }
    return 1; 
}