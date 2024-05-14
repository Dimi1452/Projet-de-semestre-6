

#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers
#include "SPILib.h"


#define TxNotFinished	(SpiaRegs.SPISTS.bit.INT_FLAG == 0)
#define clearFlag		dummy = SpiaRegs.SPIRXBUF


static unsigned int dummy;

/** Init the SPI with default values */
void SPI_Init(void)
{
	// no software reset
	SpiaRegs.SPICCR.bit.SPISWRESET = 1; 



	// clock polarity falling edge
	SpiaRegs.SPICCR.bit.CLKPOLARITY = 0; 

	// disable loop back mode
	SpiaRegs.SPICCR.bit.SPILBK = 0;

	// data length = 8bit
	SpiaRegs.SPICCR.bit.SPICHAR = 7;


	// disable overrun interrupt
	SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0;

	// normal clock phase
	SpiaRegs.SPICTL.bit.CLK_PHASE = 0;

	// master mode
	SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;

	// enable transmission
	SpiaRegs.SPICTL.bit.TALK = 1;

	// disable interrupt
	SpiaRegs.SPICTL.bit.SPIINTENA = 0;


	// default baud rate = 1Mbit/s
	// BRR  = (LSPCLK / baud rate) - 1 = (150MHz/4) / 1Mhz - 1 = 37
	SpiaRegs.SPIBRR = 37;


	// enable SPI
	SpiaRegs.SPIFFTX.bit.SPIRST = 1;

	// disable fifo enhacements 
	SpiaRegs.SPIFFTX.bit.SPIFFENA = 0;

	// disable tx fifo
	SpiaRegs.SPIFFTX.bit.TXFIFO = 0;

	// disable fifo interrupt
	SpiaRegs.SPIFFTX.bit.TXFFIENA = 0;



}

void SPI_Config(unsigned int baudRatekHz, bool clockFallingEdge, bool clockPhaseDelay, bool master, unsigned char dataLength)
{
	unsigned int tmpBRR;

	// compute baud rate
	tmpBRR = (150/4/(baudRatekHz/1000)) - 1;

	if(tmpBRR > 64)
		tmpBRR = 64;

	SpiaRegs.SPIBRR = tmpBRR;


	if(clockFallingEdge == true)
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
	else
		SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;

	if(clockPhaseDelay == true)
		SpiaRegs.SPICTL.bit.CLK_PHASE = 1;
	else
		SpiaRegs.SPICTL.bit.CLK_PHASE = 0;

	if(master == true)
		SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
	else
		SpiaRegs.SPICTL.bit.MASTER_SLAVE = 0;

	if(dataLength > 0 && dataLength <= 16)

		SpiaRegs.SPICCR.bit.SPICHAR = dataLength - 1 ;



}


void SPI_SendChar(unsigned char* data, unsigned char length)
{

	while(length-- > 0)
	{

		clearFlag;

		// send next char from MSB to LSB
		SpiaRegs.SPIDAT = (data[length]<<8) & 0xFF00;

		// wait for free buffer
		while(TxNotFinished);

		data++;
	}
}



void SPI_SendInt(unsigned int* data, unsigned char length)
{

	while(length-- > 0)
	{

		clearFlag;

		// send next char, from MSB to LSB
		SpiaRegs.SPIDAT = data[length];

		// wait for free buffer
		while(TxNotFinished);

		data++;
	}

}

