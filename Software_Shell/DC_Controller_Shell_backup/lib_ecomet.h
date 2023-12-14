#ifndef LIB_ECOMET_H
#define	LIB_ECOMET_H

#ifdef	__cplusplus
extern "C" {
#endif

void changeDC_Motor();

void changeDC_Motor_Error(int DC_Motor);

void changeFreq_Motor(int freq_Motor);

void changeDC_Buzzer(int DC_Buzzer);

void changeFreq_Buzzer(int freq_Buzzer);

float measureShunt_1();

float measureShunt_2();

float measureVBUS();

float measureTempMOSFET();

float measureTempPIC();

void init_Ecomet();

#ifdef	__cplusplus
}
#endif

#endif	/* LIB_ECOMET_H */

