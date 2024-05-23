/*
 * Projet Shell Eco-Marathon 2024
 * 
 * Ecole d'Ingénieurs de Pierrard-Virton
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

float courantMoteur = 0;
// Programme

void init_Timer(void) {
    T1CONbits.TON = 1; //Activate the timer module
    T1CONbits.TCKPS = 1; //Select input clock prescaler as 1:8

    T1CONbits.TGATE = 0; //Disable Gate Time Accumulation Mode
    T1CONbits.TCS = 0; //Select internal clock as the timer clock source
    T1CONbits.TSYNC = 0; //External clock source is left unsynchronized

    PR1 = 50000; // 1 ms de delay
}

void Interrupt_Init(void) {
    IEC0bits.T1IE = 1;
    IPC0bits.T1IP = 6;
}

// Paramètres ipmortants
//float Imax = 15; // Ampères
//float Umin = 38; // Volts
//float Umax = 52; // Volts
//float TempMOSmax = 75; // °C
//float TempPICmax = 125; // °C

float DeltaT = 0.1; // temps d'échantillonage régulation
int consigne = 0;

float K_p = 0.1; // coefficient proportionnel : 0.004497
float K_i = 10; // coefficient intégral : 10.39

float erreur = 0;
float u = 0; // commande du Buck
float ValueStepMax=0; 
float integral = 0;
int currentState = 2;

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {

//    float VBUS = measureVBUS();
//    float courantBatt = measureShunt_1();
//    float courantMoteur = measureShunt_2();
//    float tempMOS = measureTempMOSFET();
//    float tempPIC = 25;
//
//    int sat = 1;
//
//    LATDbits.LATD8 = ~LATDbits.LATD8;
//
//
//    if (courantBatt <= Imax && courantMoteur <= Imax && VBUS >= Umin && VBUS <= Umax && tempPIC <= TempPICmax && tempMOS <= TempMOSmax) {
//
//        consigne = consigneCourant();
//
//        erreur = consigne - courantMoteur;
//
//        if (consigne != 0) {
//
//            integral = integral + erreur*DeltaT;
//            sat = 1;
//        } else {
//
//            integral = 0;
//        }
//
//        u = K_p * erreur + K_i*integral;
//
//        if (u / 36 * 150 >= 150) {
//
//            u = 36;
//            integral = 36;
//        }
//
//        if (u / 36 * 150 < 0) {
//
//            u = 0;
//            //integral = 0;
//        }
//
//        u = (int) (u * 150 / 36);
//
//        PWM_DutyCycleSet(PWM_GENERATOR_1, u);
//
//        PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
//        PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
//        PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
//        PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
//        PG1STAT = 0b01000;
//    } else {
//
//        PWM_DutyCycleSet(PWM_GENERATOR_1, 0);
//
//        PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
//        PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
//        PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
//        PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
//        PG1STAT = 0b01000;
//    }
//    IFS0bits.T1IF = 0;

}

int main(void) {

    init_Ecomet();

    float Imax = 25; // Ampères
    float Umin = 38; // Volts
    float Umax = 52; // Volts
    float TempMOSmax = 75; // °C
    float TempPICmax = 125; // °C
    int Step=0;

    // Valeurs initiales (lecture des ADCs)
    float VBUS = measureVBUS();
    float courantBatt = measureShunt_1();
    courantMoteur = measureShunt_2();
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

    PWM_DutyCycleSet(PWM_GENERATOR_1, 25);

    while (1) {
        T1CONbits.TON = 0;

        courantMoteur = measureShunt_2();
        if (courantMoteur >= Imax)  {

                    changeDC_Motor_Error(0);
                    currentState = 1;
        }
        
        switch (currentState) {
            case 0:
                // do something in the idle state
                //        LATCbits.LATC7 = 0;
                //        LATCbits.LATC12 = 0;
                //        LATDbits.LATD1 = 0;
                //        LATDbits.LATD8 = 0;
                // LATCbits.LATC12 =~ LATCbits.LATC12  ;
                LATCbits.LATC7 = 0;
                
                
                LATCbits.LATC12 = 1;
                VBUS = measureVBUS();

                // tempMOS = measureTempMOSFET();
                // courantBatt = measureShunt_1();
                courantMoteur = measureShunt_2();


                consigne = consigneCourant();

                LATCbits.LATC12 = 0;
                erreur = consigne - courantMoteur;

                if (consigne != 0) {

                    integral = integral + erreur*DeltaT;
                    //sat = 1;
                } else {

                    integral = 0;
                }

                u = K_p * erreur + K_i*integral;

                if (u / 36 * 150 >= 150) {

                    u = 36;
                    integral = 36/K_i;
                }

                if (u / 36 * 150 < 0) {

                    u = 0;
                    //integral = 0;
                }

                u = (int) (u * 150 / 36);

                PWM_DutyCycleSet(PWM_GENERATOR_1, u);
                PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
                PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
                PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
                PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
                PG1STAT = 0b01000;

                if ((courantMoteur >= Imax) || (VBUS <= Umin || VBUS>= Umax)) {

                    changeDC_Motor_Error(0);
                    currentState = 2;

                }

                break;

            case 1:
                // do something in the stop state
                changeDC_Motor_Error(0);
                 LATCbits.LATC7  = 1;
                if (PORTDbits.RD13 == 0)
                { currentState = 2;
                LATCbits.LATC7  = 0;
                }

                break;
            case 2:
                // do something in the stop state
                
                consigne = consigneCourant();                
                
                if (consigne >=1 && consigne <3)
                    ValueStepMax=35;
                if (consigne >=3 && consigne <5)
                    ValueStepMax=55;
                else if (consigne >=5 && consigne <7)
                    ValueStepMax=90;
                else if (consigne >=7 && consigne <9 )
                  ValueStepMax=120;
                else if (consigne >=9 )
                  ValueStepMax=150;
                else
                    ValueStepMax=0;
                 
                
                
                PWM_DutyCycleSet(PWM_GENERATOR_1, u);
                PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1); // Dead time H : 250 ns 
                PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1);
                PWM_DeadTimeLowSet(PWM_GENERATOR_1, 1); // Dead time L : 250 ns 
                PWM_DeadTimeHighSet(PWM_GENERATOR_1, 1);
                PG1STAT = 0b01000;                        
                
                    
//                changeDC_Motor_Error(0);
//                 LATCbits.LATC7  = 1;
//                if (PORTDbits.RD13 == 0)
//                    currentState = 0;

                break;
        }







        //        while (courantBatt <= Imax && courantMoteur <= Imax && VBUS >= Umin && VBUS <= Umax && tempPIC <= TempPICmax && tempMOS <= TempMOSmax) {
        //
        //            VBUS = measureVBUS();
        //            tempMOS = measureTempMOSFET();
        //            courantBatt = measureShunt_1();
        //            courantMoteur = measureShunt_2();
        //        }
        //
        //        // Allume la LED rouge FAULT
        //        LATCbits.LATC7 = 1;
        //        T1CONbits.TON = 0;
        //        integral = 0;
        //        erreur = 0;
        //
        //        // Coupe le moteur
        //        changeDC_Motor_Error(0);
        //
        //        // Allume la LED correspondante afin de prévenir le pilote du problème
        //        if (courantBatt >= Imax) {
        //            LATCbits.LATC12 = 1;
        //        } else if (courantMoteur >= Imax) {
        //            LATCbits.LATC12 = 1;
        //        } else if (VBUS <= Umin || VBUS >= Umax) {
        //            LATDbits.LATD1 = 1;
        //        } else if (tempMOS >= TempMOSmax) {
        //            LATDbits.LATD8 = 1;
        //        }
        //
        //        // Boucle Reset
        //        int a = 1;
        //        while (a == 1) {
        //
        //            // Test le bouton lors de l'attente du Reset
        //            a = PORTDbits.RD13;
        //        }
        //
        //        VBUS = measureVBUS();
        //        tempMOS = measureTempMOSFET();
        //        courantBatt = measureShunt_1();
        //        courantMoteur = measureShunt_2();
        //        T1CONbits.TON = 1;
    }
    return 1;
}