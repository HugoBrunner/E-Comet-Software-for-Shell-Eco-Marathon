/*
 * Projet Shell Eco-Marathon 2024
 * 
 * Ecole d'Ingénieurs de Pierrard-Virton
 * 
 *  01 mai 2024
 * 
 */

// Définition de variables globales
#define FCY 8000000UL        // défini la fonction : __delay_ms()
#define CYCLE_DELAY 10

// Nos librairies
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/adc1.h"
#include "lib_ecomet.h"

// Autres librairies
#include <libpic30.h>       //Defines __delay32();
#include <math.h>

// Programme
void init_Timer( void ){
    T1CONbits.TON = 1;       //Activate the timer module
    T1CONbits.TCKPS = 1;     //Select input clock prescaler as 1:8
    
    T1CONbits.TGATE = 0;     //Disable Gate Time Accumulation Mode
    T1CONbits.TCS = 0;       //Select internal clock as the timer clock source
    
    PR1 = 50000;              // 100 ms de delay
}

void Interrupt_Init( void ){
    IEC0bits.T1IE = 1;
    IPC0bits.T1IP = 6;
}

// Paramètres ipmortants
float Imax = 12;             // Ampères
float Umin = 42;             // Volts
float Umax = 52;             // Volts
float TempMOSmax = 75;       // °C
float TempPICmax = 125;      // °C

float DeltaT = 0.1;         // temps d'échantillonage régulation
int test = 0;
int consigne = 0;

float K_p = 5;               // coefficient proportionnel : 0.004497
float K_i = 1;              // coefficient intégral : 10.39
 
float erreur = 0;
float u = 0;                 // commande du Buck
float integral = 0;

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void ){
    
    int sat = 0;
    
    float VBUS1 = measureVBUS();    
    consigne = consigneCourant();
    float courantMoteur1 = measureShunt_2();

    sat = (int)(36/VBUS1*199 - 1);
    erreur = consigne - courantMoteur1;

    if (consigne != 0) {

        integral = integral + erreur*DeltaT;
    }else{

        integral = 0;
    }

    u = K_p*erreur + K_i*integral;

    if (u/36*sat >= sat){

        u = 36;  
        integral = 36;
    } 

    if(u/36*sat < 0){

        u = 0;
        integral = 0;
    }

    u = (int)(u*sat/36);

    PWM_DutyCycleSet(PWM_GENERATOR_1, u);

    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
    PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
    PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
    PG1STAT = 0b01000;
    
    IFS0bits.T1IF = 0;
}

int main(void){
             
    init_Ecomet();
    
    // Valeurs initiales (lecture des ADCs)
    float VBUS = measureVBUS();
    float courantBatt = 1;
    float courantMoteur = measureShunt_2();
    float tempMOS = measureTempMOSFET();
    float tempPIC = 25;
    
    // Indique que la carte a fini son initialisation
    Buzzer_ON();
    __delay_ms(250);
    Buzzer_OFF();
    __delay_ms(250);
    Buzzer_ON();
    __delay_ms(250);
    Buzzer_OFF();
    
    init_Timer();
    Interrupt_Init();
     
    while (1){
        
        LATCbits.LATC7 = 0;
        LATCbits.LATC12 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD8 = 0;
                
        while (courantBatt <= Imax && courantMoteur <= Imax && VBUS >= Umin && VBUS <= Umax && tempPIC <= TempPICmax && tempMOS <= TempMOSmax){
            
            tempMOS = measureTempMOSFET();
            VBUS = measureVBUS();
            courantMoteur = measureShunt_2();
            
            test = test + 1;
        } 
        
        // Allume la LED rouge FAULT
        LATCbits.LATC7 = 1;
        T1CONbits.TON = 0;
        integral = 0;
        erreur = 0;
        
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
        T1CONbits.TON = 1;
    }
    return 1; 
}