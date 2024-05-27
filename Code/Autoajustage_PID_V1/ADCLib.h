/** \file ADCLib.h
* \brief Header of the file ADCLib.c
* \author Sylvain Decastel & Florian Berset
* \date 06.2009
*/


#ifndef __ADCLib_H
#define __ADCLib_H

/*-----------------------------------------------------------+
|                        MACROS                              |
+-----------------------------------------------------------*/

/** \brief Macro to start the ADC conversion */
#define StartConversion		AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;


/*-----------------------------------------------------------+
|                      PROTOTYPES                            |
+-----------------------------------------------------------*/

void InitAdc(void);

void ConfigAdc(void);
void SelectAdc(void);

int GetAdc(int Channel);
float GetVoltage(int Channel);
float GetMesu(int Channel);
float GetMesi(int Channel);
#endif
