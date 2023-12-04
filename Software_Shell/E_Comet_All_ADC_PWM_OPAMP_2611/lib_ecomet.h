#ifndef LIB_ECOMET_H
#define	LIB_ECOMET_H

#ifdef	__cplusplus
extern "C" {
#endif

void changeDC_Motor();

void changeFreq_Motor(int freq_Motor);

void changeDC_Buzzer(int DC_Buzzer);

void changeFreq_Buzzer(int freq_Buzzer);

void measureShunt_1();

void measureShunt_2();

void measureVBUS();

void measureTempMOSFET();

void init_Ecomet();

#ifdef	__cplusplus
}
#endif

#endif	/* LIB_ECOMET_H */

