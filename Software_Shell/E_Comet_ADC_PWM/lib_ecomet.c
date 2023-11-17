#define FCY 8000000UL // defines __delay_ms()
#define CYCLE_DELAY 10

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"
#include <libpic30.h> //Defines __delay32();
#include <math.h>

int DC_Motor = 0x00;

void changeDC_Motor(){ // Change le DC via la lecture du potentiomètre

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
    conversion = ADC1_ConversionResultGet(channel) - 1029; // Corrige le décallage de tension du potentiomètre
    ADC1_Disable(); 
    
    DC_Motor = abs(round((float)(conversion/4095.0)*199.0*3.3/1.725)); // sampling sur 12 bit
     
    PWM_DutyCycleSet(PWM_GENERATOR_1, DC_Motor);
    PG1STAT = 0b01000;
}

void changeFreq_Motor(int freq_Motor){ // Change la fréquence de manière manuelle
    
    PWM_PeriodSet(PWM_GENERATOR_1, freq_Motor);
    PG1STAT = 0b01000;
}

void changeDC_Buzzer(int DC_Buzzer){ // Change le DC de manière manuelle
    
    PWM_DutyCycleSet(PWM_GENERATOR_3, DC_Buzzer); 
    PG3STAT = 0b01000;
}

void changeFreq_Buzzer(int freq_Buzzer){ // Change la fréquence de manière manuelle

    PWM_PeriodSet(PWM_GENERATOR_3, freq_Buzzer);
    PG3STAT = 0b01000;
}

void measureShunt_1(){
    
}

void measureShunt_2(){
    
}

void measureVBUS(){
    
}

void measureTempMOSFET(){
    
}

void init_Ecomet(){ // Initialise les différents composants (PWM, ADC, ...)
    
    SYSTEM_Initialize(); 
    
    int freq_Buzzer = 0x4E1; // f = 3,2 kHz
    int DC_Buzzer = 0x00; // DC = 00 %
    changeDC_Buzzer(DC_Buzzer);
    changeFreq_Buzzer(freq_Buzzer);
    
    int freq_Motor = 0xC7; // f = 20 kHz
    DC_Motor = 0x00; // DC = 0 %
    changeFreq_Motor(freq_Motor);
    // C'est bizrare de faire comme ça, mais c'est le seul moyen que j'ai trouvé pour avoir un dead time au début et à la fin (et pas juste un seul)
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time de 250 ns au début
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time de 250 ns à la fin
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
    PG1STAT = 0b01000;
}
