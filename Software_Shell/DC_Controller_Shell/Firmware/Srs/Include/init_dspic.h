

#include <xc.h> // include processor files - each processor file is guarded.  

#define FLED   _LATC7   // FAULT LED
#define SW_12V _LATC11  //the signal to activate the 12V_SW line    
    

void PIN_MANAGER_Initialize (void);
void CLOCK_Initialize(void);
void INTERRUPT_Initialize(void);
void ADC1_Initialize (void);
void ADC1_Core0PowerEnable (void);
void ADC1_Core1PowerEnable (void);
void ADC1_SharedCorePowerEnable (void);
void WDT_Setup(void);
void init_DAC_COMP(void);

