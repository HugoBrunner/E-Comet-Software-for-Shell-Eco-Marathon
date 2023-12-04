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

// AN17 : potentiomètre             --> accélérateur
// AN12 : température               --> température MOSFET Q2
// AN15 : VBUS                      --> tension batterie
// AN0 : OA1out                     --> courant moteur
// AN7 : OA2_out = Shunt_norm+      --> courant batterie

int DC_Motor = 0x00;
double Rshunt = 0.002;
float VBUS = 0;
float courantBatt = 0;
float courantMoteur = 0;
float tempMOS = 0;
float tempPIC = 0;

// Tension de référence
float Ualim = 3.3;

// Tous les ADCs sont en 12 bit

void changeDC_Motor(){                                                          // Change le DC du Buck de puissance via la lecture du potentiomètre

    ADC1_CHANNEL channel = channel_AN17; // lit la pin RC6 où est connecté le potentiomètre
            
    int conversion = 0;
    int i=0;
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    //while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel) - 1050; // Corrige le décallage 
                                                           // de tension du potentiomètre
    ADC1_Disable(); 
    
    DC_Motor = abs(round((float)(conversion/4095.0)*150.0*Ualim/1.725));
     
    PWM_DutyCycleSet(PWM_GENERATOR_1, DC_Motor);
    PG1STAT = 0b01000;
}

void changeDC_Motor_Error(int DC_Motor){
    
    PWM_DutyCycleSet(PWM_GENERATOR_1, DC_Motor);
    PG1STAT = 0b01000;
}

void changeFreq_Motor(int freq_Motor){                                          // Change la fréquence du Buck de puissance de manière manuelle
    
    PWM_PeriodSet(PWM_GENERATOR_1, freq_Motor);
    PG1STAT = 0b01000;
}

void changeDC_Buzzer(int DC_Buzzer){                                            // Change le DC du buzzer de manière manuelle
    
    PWM_DutyCycleSet(PWM_GENERATOR_3, DC_Buzzer); 
    PG3STAT = 0b01000;
}

void changeFreq_Buzzer(int freq_Buzzer){                                        // Change la fréquence de l'alimentation du buzzer de manière manuelle

    PWM_PeriodSet(PWM_GENERATOR_3, freq_Buzzer);
    PG3STAT = 0b01000;
}

float measureShunt_1(){                                                          // Mesure le courant fourni par la batterie
    
    ADC1_CHANNEL channel = channel_AN7; 
            
    int conversion = 0;
    int i=0;
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); 
    ADC1_Disable();
    courantBatt = (float)(conversion/4095*Ualim/Rshunt);
    return courantBatt;
}

float measureShunt_2(){                                                          // Mesure le courant absorbé par le moteur
    
    ADC1_CHANNEL channel = channel_AN0; 
            
    int conversion = 0;
    int i=0;
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); 
    ADC1_Disable();
    courantMoteur = (float)(conversion*0.0275 + 0.0432);
    return courantMoteur;
}

float measureVBUS(){                                                             // Mesure la tension de la batterie (les 3 4S en série)
    
    ADC1_CHANNEL channel = channel_AN15; 
            
    int conversion = 0;
    int i=0;
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); 
    ADC1_Disable();
    VBUS = (float)(conversion/4095.0*Ualim*16.0); 
    return VBUS;
}

float measureTempMOSFET(){                                                       // Mesure la température de la surface du MOSFET Q2
    
    ADC1_CHANNEL channel = channel_AN12;  
                                         
    int conversion = 0;
    int i=0;
    double Uout = 0;
    double Rth = 0;
    
    int R2 = 3300; // Résitance du pont diviseur de la mesure de température
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); 
    ADC1_Disable();
    Uout = (float)(conversion/4095.0*Ualim);
    Rth = R2*Uout/(Ualim - Uout);
    tempMOS = 82.313*pow(Rth/10000.0,-0.235) - 56.0; // Utilisation de la fonction de régression 
                                                  // permettant de calculer la température
    return tempMOS;
}

float measureTempPIC(){                                                          // Mesure la température du dsPIC33CK32MP105
    
    ADC1_CHANNEL channel = channel_AN19; 
            
    int conversion = 0;
    int i=0;
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); 
    ADC1_Disable();
    tempPIC = (float)(conversion/4095*Ualim);
    return tempPIC;
}

void init_Ecomet(){                                                             // Initialise les différents composants (PWM, ADC, ...)
    
    SYSTEM_Initialize(); 
    
    TRISCbits.TRISC7 = 0;
    LATCbits.LATC7 = 0;
    
    TRISCbits.TRISC12 = 0;
    LATCbits.LATC12 = 0;
    
    TRISDbits.TRISD1 = 0;
    LATDbits.LATD1 = 0;
    
    TRISDbits.TRISD8 = 0;
    LATDbits.LATD8 = 0;
    
    TRISDbits.TRISD13 = 0;
    LATDbits.LATD13 = 0;
        
    int freq_Buzzer = 0x4E1; // f = 3,2 kHz
    int DC_Buzzer = 0x00; // DC = 0 %
    changeDC_Buzzer(DC_Buzzer);
    changeFreq_Buzzer(freq_Buzzer);
    
    int freq_Motor = 0xC7; // f = 20 kHz
    DC_Motor = 0x00; // DC = 0 %
    changeFreq_Motor(freq_Motor);
    
    /* C'est bizrare de faire comme ça, mais c'est le seul moyen que 
       j'ai trouvé pour avoir un dead time au début 
       et à la fin (et pas juste un seul)
    */
    
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
    PG1STAT = 0b01000; // Met à jour les registres du PWM
}