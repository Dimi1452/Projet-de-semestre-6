/** \file DACLib.h
* \brief Header file for the DACLib.c file
* \author Sylvain Decastel
* \date 06.2009
*/


#ifndef __DACLIB_H
#define __DACLIB_H

void DAC_Init(void);
void DAC_SetChannel(unsigned char channel, unsigned int data);
void DAC_SetChannelVolt(unsigned char channel, float data);
void DAC_SetAllChannels(unsigned int dataCh1, unsigned int dataCh2, unsigned int dataCh3, unsigned int dataCh4);
void DAC_SetAllChannelsVolt(float dataCh1, float dataCh2, float dataCh3, float dataCh4);
#endif
