/** \file ADCLib.c
* \brief Set of functions to init, configure and use the ADC on the TMS320F28335
* \author Sylvain Decastel & Florian Berset
* \date 06.2009
*/

#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers
#include "Configuration.h"
#include "ADCLib.h"
#include "User.h"


/*-----------------------------------------------------------+
|                           PROTOTYPES                       |
+-----------------------------------------------------------*/
interrupt void AdcInterrupt(void);


/*-----------------------------------------------------------+
|                            FUNCTIONS                       |
+-----------------------------------------------------------*/

/** \brief Return the value of an ADC channel
* 
* This function return the last converted value of the ADC channel 
* set by parameter Channel .
* \param[in] Channel No of the ADC Channel, 0 to 15
* \return Value of the converted value on 12 bits
* \author Sylvain Decastel
* \date 06.2009
*/
int GetAdc(int Channel)
{
	// check channel
	if(Channel >=1 && Channel <= 16)
	{
		return *(&AdcRegs.ADCRESULT0+(Channel-1)) >> 4;
	}
	else
	{
		return 0;
	}
}


/** \brief Return the value of an analog input in voltage
* 
* This function return the last converted value of the analog input 
* set by parameter Channel and convert it in a voltage value.
* \param[in] Channel No of the ADC Channel, 0 to 15
* \return Value of the voltage mesured
* \author Florian Berset
* \date 10.2009
*/
float GetVoltage(int Channel)
{
	// check channel
	if(Channel >=1 && Channel <= 16)
	{
		return ((*(&AdcRegs.ADCRESULT0+(Channel-1)) >> 4)/204.8)-10.0;
	}
	else
	{
		return 0.0;
	}
}


/** \brief Return the value of an input of the Mesu Card
* 
* This function return the last converted value of the Mesu channel 
* set by parameter Channel and convert it in a voltage value.
* This fonction is only usable with the "mesu" card.
* \param[in] Channel No of the ADC Channel, 0 to 11
* \return Value of the voltage mesured
* \author Florian Berset
* \date 10.2009
*/
float GetMesu(int Channel)
{
	// check channel
	if(Channel >=1 && Channel <= 12)
	{
		return (((*(&AdcRegs.ADCRESULT0+(Channel-1)) >> 4)*0.3413)-699.0);
	}
	else
	{
		return 0.0;
	}
}


/** \brief Return the value of an input of the Mesi Card
* 
* This function return the last converted value of the Mesi channel 
* set by parameter Channel and convert it in a current value.
* This fonction is only usable with the "mesi" card.
* \param[in] Channel No of the ADC Channel, 0 to 11
* \return Value of the current mesured
* \author Florian Berset
* \date 10.2009
*/
float GetMesi(int Channel)
{
	// check channel
	if(Channel >=1 && Channel <= 12)
	{
		return (((*(&AdcRegs.ADCRESULT0+(Channel-1)) >> 4)/102.4)-20.0);
	}
	else
	{
		return 0.0;
	}
}


/** \brief Init the Analog to digital converter
*
* Init the ADC converter with a configuration to use with DelfinoCard application
* This function init also the interrupt routine.
* \author Sylvain Decastel
* \date 06.2009
*/
void ConfigAdc(void)
{
	/* Calibration of the converter ! */
	InitAdc();

	// ADC CONTROL REGISTER 1
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1 Cascaded mode SEQ1 and SEQ2 
   											// operate as a single 16 state sequencer
	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;		// Sequencer override
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;       // 1 Setup continuous run
	AdcRegs.ADCTRL1.bit.CPS = 0;       		// ADC core clock pre-scalar
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0xf;		// Acquisition window size
	AdcRegs.ADCTRL1.bit.SUSMOD = 0;			// Emulation suspend mode
	AdcRegs.ADCTRL1.bit.RESET = 0;			// ADC reset

	// ADC CONTROL REGISTER 2
	AdcRegs.ADCTRL2.all = 0x0000;

	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;	// enable ADC interrupt



	// ADC CONTROL REGISTER 3
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x1;		// Core clock divider

	// Set up ADC to perform 15 conversions for the SOC
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 15;


	/* Enable Seq2 Interrupt */
	EALLOW;
	IER |= M_INT1;
	PieCtrlRegs.PIEIER1.bit.INTx1 = 1;	// enable interrupt for SEQ 1
	
	
	PieVectTable.SEQ1INT = &AdcInterrupt;
	

	EDIS;

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
	AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
	AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
	AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
	AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;
}


/** \brief Interrupt routine at the end of the ADC conversion
*
* This interrupt occured after the ADC conversion is completed. 
* The conversion is started periodically by the timer interrupt routine 
* (default every 100us). The UserTe() function is called here, so thate the last 
* analog values are up to date.
*
* \author Sylvain Decastel
* \date 06.2009
*/
interrupt void AdcInterrupt(void)
{
D2_OUT_OFF;
	UserTe();

	// clear the interrupt flag
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;

	// Acknowledge the interrupt group
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
D1_OUT_OFF;
}
