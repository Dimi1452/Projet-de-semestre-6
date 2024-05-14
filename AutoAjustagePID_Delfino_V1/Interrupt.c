/** \file Interrupt.c
* \brief Code of the interrupt routines
* \author Sylvain Decastel
* \date 06.2009
*/
#include "PeripheralHeaderIncludes.h"
#include "Configuration.h"
#include "PWMLib.h"
#include "HMILib.h"
#include "ADCLib.h"
#include "User.h"


interrupt void cpu_timer0_isr(void)
{
	D1_OUT_ON;
	D2_OUT_ON;

	// Start ADC conversion !
	StartConversion;

	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
