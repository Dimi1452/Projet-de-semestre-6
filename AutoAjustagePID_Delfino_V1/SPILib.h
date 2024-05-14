/* Library to use the SPI connection on the TMS 28f335 */ 
/* The library does not handle chip select signals */
#ifndef __SPILIB_H
#define __SPILIB_H

#include "bool.h"


void SPI_Init(void);

void SPI_Config(unsigned int baudRate, bool clockFallingEdge, bool clockPhaseDelay, bool master, unsigned char dataLength);


void SPI_SendChar(unsigned char* data, unsigned char length);

void SPI_SendInt(unsigned int* data, unsigned char length);



#endif
