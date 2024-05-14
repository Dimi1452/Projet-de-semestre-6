/** \file DACLib.c
* \brief Library for the digital-to-analog converter TLV5614
* \author Sylvain Decastel
* \date 06.2009
*/

#include "PeripheralHeaderIncludes.h"
#include "SPILib.h"
#include "DACLib.h"

#define DAC_Select		GpioDataRegs.GPACLEAR.bit.GPIO13 = 1    /**< \brief Set the chip select low to enable the chip */
#define DAC_UnSelect	GpioDataRegs.GPASET.bit.GPIO13 = 1      /**< \brief Set the chip select high to disable the chip */

// control LDAC signal, no update when high
#define DAC_NoOutputUpdate	GpioDataRegs.GPASET.bit.GPIO12 = 1      /**< \brief Set the LDAC signal high to hold the outputs */
#define DAC_OutputUpdate	GpioDataRegs.GPACLEAR.bit.GPIO12 = 1    /**< \brief Set the LDAC signal low to update the outputs */

/** \brief SPI frame for the TLV5614 
* \author Sylvain Decastel
* \date 06.2009
*/
typedef union
{
	unsigned int word;  /**< \brief Used to access all the 16 bits */

    /** \brief Struct to access the bitfields */
	struct
	{
		unsigned int data:12;   /**< \brief Data field on 12 bits */
		unsigned int speed:1;   /**< \brief Speed flag, 1: fast mode, 0: slow mode */
		unsigned int power:1;   /**< \brief Power flag, 1: power down, 0: power up */
		unsigned int address:2; /**< \brief Channel address 00: ch1, 11: ch4 */

	}fields;

}DAC_Frame_T;

/** \brief static buffer for the SPI frames */
static DAC_Frame_T DAC_Frame;


/** \brief Function to init the DAC and set all the channels to 0V
* \author Sylvain Decastel
* \date 06.2009
*/
void DAC_Init(void)
{
	// set IO as output
	EALLOW;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;
	EDIS;

	// init frame
	DAC_Frame.fields.speed = 0;
	DAC_Frame.fields.power = 0;

	// set all channel to 0
	DAC_SetAllChannels(0,0,0,0);

}

/** \brief Send data to the DAC through the SPI bus
*
* \param[in] channel    Nb of the channel to set (1 to 4), if the nb is out of bounds, it's limited to the min/max
* \param[in] data       Value to set on 12 bits, if value is out of bounds, it's limited to the min/max
* \author Sylvain Decastel
* \date 06.2009
*
*/
void DAC_WriteData(unsigned char channel, unsigned int data)
{
	// check values
	if(channel < 1)
		channel = 1;
	else if(channel > 4)
		channel = 4;

	// limit data
	if(data > 4096)
		data = 4096;

	DAC_Frame.fields.address = channel - 1;
	DAC_Frame.fields.data = data;


	// select device
	DAC_Select;

	SPI_SendInt(&DAC_Frame.word, 1);

	// unselect device
	DAC_UnSelect;

}

/** \brief Set the value of the channel
* \author Sylvain Decastel
* \date 06.2009
* \todo In future, could be meged with the DAC_WriteData()
* \param[in] channel Nb of the channel to set
* \param[in] data Value of the desired output on 12 bits
*/
void DAC_SetChannel(unsigned char channel, unsigned int data)
{
	// write data
	DAC_WriteData(channel, data);

	// update output
	DAC_OutputUpdate;
}

/** \brief Directly set the 4 output channels of the device. The ouputs are update synchronously.
* \author Sylvain Decastel
* \date 06.2009
* \param[in] dataCh1 Value of the channel 1
* \param[in] dataCh2 Value of the channel 2
* \param[in] dataCh3 Value of the channel 3
* \param[in] dataCh4 Value of the channel 4
*/
void DAC_SetAllChannels(unsigned int dataCh1, unsigned int dataCh2, unsigned int dataCh3, unsigned int dataCh4)
{
	// block output
	DAC_NoOutputUpdate;

	// ch1
	DAC_WriteData(1, dataCh1);

	// ch2
	DAC_WriteData(2, dataCh2);

	// ch3
	DAC_WriteData(3, dataCh3);

	// ch4
	DAC_WriteData(4, dataCh4);


	// update output
	DAC_OutputUpdate;
}

/** \brief Set the 4 output channels with values in volts between -10.0V and +10.0V
*
* The function automatically convert values in float to set the correct output voltage.
*
* \author Sylvain Decastel
* \date 06.2009
* \param[in] dataCh1 Value for the channel 1
* \param[in] dataCh2 Value for the channel 2
* \param[in] dataCh3 Value for the channel 3
* \param[in] dataCh4 Value for the channel 4
*/
void DAC_SetAllChannelsVolt(float dataCh1, float dataCh2, float dataCh3, float dataCh4)
{
	// block output
	DAC_NoOutputUpdate;

	// ch1
	DAC_WriteData(1, (unsigned int)((dataCh1 * 2048.0 / 10.0)+2048.0));

	// ch2
	DAC_WriteData(2, (unsigned int)((dataCh2 * 2048.0 / 10.0)+2048.0));

	// ch3
	DAC_WriteData(3, (unsigned int)((dataCh3 * 2048.0 / 10.0)+2048.0));

	// ch4
	DAC_WriteData(4, (unsigned int)((dataCh4 * 2048.0 / 10.0)+2048.0));

	// update output
	DAC_OutputUpdate;
}


/** \brief Set the value of the channel
* \author Sylvain Decastel
* \date 06.2009
* \todo In future, could be meged with the DAC_WriteData()
* \param[in] channel Nb of the channel to set
* \param[in] data Value of the desired output on 12 bits
*/
void DAC_SetChannelVolt(unsigned char channel, float data)
{
	// write data
	DAC_WriteData(channel, (unsigned int)((data * 2048.0 / 10.0)+2048.0));

	// update output
	DAC_OutputUpdate;
}
