// D�finition de variables globales
#define FCY 8000000UL // defines __delay_ms()
#define CYCLE_DELAY 10

// Nos librairies
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"

// Autres librairies
#include <libpic30.h> //Defines __delay32();
#include <math.h>

// AN17 : potentiom�tre
// AN12 : temp�rature
// AN15 : VBUS
// AN0 : OA1out --> courant moteur
// ANA1 : OA1_in-
// AN9 : OA1_in+
// AN7 : OA2_out = Shunt_norm+ --> courant batterie

int DC_Motor = 0x00;
double Rshunt = 0.002;
float VBUS = 0;
float courantBatt = 0;
float temp = 0;

// Tension de r�f�rence
double Ualim = 3.3;

void changeDC_Motor(){ // Change le DC via la lecture du potentiom�tre

    ADC1_CHANNEL channel = channel_AN17; // lit la pin RC6 o� est connect� le potentiom�tre
            
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
    conversion = ADC1_ConversionResultGet(channel) - 1029; // Corrige le d�callage de tension du potentiom�tre
    ADC1_Disable(); 
    
    DC_Motor = abs(round((float)(conversion/4095.0)*199.0*Ualim/1.725)); // sampling sur 12 bit
     
    PWM_DutyCycleSet(PWM_GENERATOR_1, DC_Motor);
    PG1STAT = 0b01000;
}

void changeFreq_Motor(int freq_Motor){ // Change la fr�quence de mani�re manuelle
    
    PWM_PeriodSet(PWM_GENERATOR_1, freq_Motor);
    PG1STAT = 0b01000;
}

void changeDC_Buzzer(int DC_Buzzer){ // Change le DC de mani�re manuelle
    
    PWM_DutyCycleSet(PWM_GENERATOR_3, DC_Buzzer); 
    PG3STAT = 0b01000;
}

void changeFreq_Buzzer(int freq_Buzzer){ // Change la fr�quence de mani�re manuelle

    PWM_PeriodSet(PWM_GENERATOR_3, freq_Buzzer);
    PG3STAT = 0b01000;
}

void measureShunt_1(){ // Mesure le courant d�livr� par la batterie
    
    ADC1_CHANNEL channel = channel_AN7; // lit la pin RC6 o� est connect� le potentiom�tre
            
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
    conversion = ADC1_ConversionResultGet(channel); // Corrige le d�callage de tension du potentiom�tre
    ADC1_Disable();
    courantBatt = (float)(conversion/4095*Ualim/Rshunt);
}

void measureShunt_2(){ // Mesure le courant absorb� par le moteur
    // Poser question monsieur Alaime
}

void measureVBUS(){
    
    ADC1_CHANNEL channel = channel_AN15; // lit la pin RC6 o� est connect� le potentiom�tre
            
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
    conversion = ADC1_ConversionResultGet(channel); // Corrige le d�callage de tension du potentiom�tre
    ADC1_Disable();
    VBUS = (float)(conversion/4095*Ualim*16); // Ps de mesure alors que je mesure (lorsque j'alimente via l'ICD3) 2V, est-ce trop peu ??
}

void measureTempMOSFET(){
    
    ADC1_CHANNEL channel = channel_AN12; // lit la pin RC6 o� est connect� le potentiom�tre
            
    int conversion = 0;
    int i=0;
    double Uout = 0;
    double Rth = 0;
    
    int R2 = 3300; // R�sitance du pont diviseur de la mesure de temp�rature
    
    ADC1_Initialize();

    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    ADC1_SoftwareTriggerEnable();
    
    for(i=0;i <1000;i++) // laisse le temps au PIC de faire la mesure
    {
    }
    
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion = ADC1_ConversionResultGet(channel); // Corrige le d�callage de tension du potentiom�tre
    ADC1_Disable();
    Uout = (float)(conversion/4095*Ualim);
    Rth = R2*Uout/(Ualim - Uout);
    temp = 1; 
}

void init_Ecomet(){ // Initialise les diff�rents composants (PWM, ADC, ...)
    
    SYSTEM_Initialize(); 
    
    int freq_Buzzer = 0x4E1; // f = 3,2 kHz
    int DC_Buzzer = 0x00; // DC = 00 %
    changeDC_Buzzer(DC_Buzzer);
    changeFreq_Buzzer(freq_Buzzer);
    
    int freq_Motor = 0xC7; // f = 20 kHz
    DC_Motor = 0x00; // DC = 0 %
    changeFreq_Motor(freq_Motor);
    // C'est bizrare de faire comme �a, mais c'est le seul moyen que j'ai trouv� pour avoir un dead time au d�but et � la fin (et pas juste un seul)
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time de 250 ns au d�but
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time de 250 ns � la fin
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
    PG1STAT = 0b01000;
}