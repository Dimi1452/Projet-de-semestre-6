/** \file main.c
* \brief Main file of DelfinoExe 
* \author Sylvain Décastel & Florian Berset
* \Edited by Kneuss André
* \date 11.2009
*/
/** \def Allow to declare global variables */
#define __MAIN

#include "PeripheralHeaderIncludes.h"
#include "DSP2833x_EPWM_defines.h"
#include "DSP2833x_Adc.h"
#include "DSP2833x_ECan.h"
#include "Configuration.h"
#include "UARTBLib.h"
#include "bool.h"
#include "HMILib.h"
#include "ADCLib.h"
#include "PWMLib.h"
#include "user.h"
#include "QEPLib.h"
#include "SPILib.h"
#include "DACLib.h"
#include "TimeoutLib.h"
#include "CANLib.h"

/*-----------------------------------------------------------+
|                           PROTOTYPES                       |
+-----------------------------------------------------------*/
void MemCopy(Uint16* SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);
void InitFlash(void);
void DeviceInit(void);
void InitTimer0(void);

/*-----------------------------------------------------------+
|                       RAM  VARIABLES                       |
+-----------------------------------------------------------*/
/** Used in MemCopy to init flash */
extern Uint16 RamfuncsLoadStart;
/**  Used in MemCopy to init flash */
extern Uint16 RamfuncsLoadEnd;
/** Used in MemCopy to init flash. */
extern Uint16 RamfuncsRunStart;


/*-----------------------------------------------------------+
|                     MAIN   FUNCTIONS                       |
+-----------------------------------------------------------*/
/** Main function of the program*/
void main(void)

{

/*-----------------------------------------------------------+
|                    Flash Initialisation                    |
+-----------------------------------------------------------*/
#ifdef FLASH		
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	InitFlash();	// Call the flash wrapper init function
#endif

/*-----------------------------------------------------------+
|                  Global initialisation                     |
+-----------------------------------------------------------*/

// Initialisation des différents périphériques
//---------------------------------------------
	DeviceInit();
	GpioDataRegs.GPACLEAR.bit.GPIO28 = 1;		// Error Led ON
	GpioDataRegs.GPACLEAR.bit.GPIO29 = 1;		// Run Led ON
	ConfigAdc();
//	UARTB_Init(UARTB_BR_19200,UARTB_PAR_Even);
	UARTB_Init(UARTB_BR_19200,UARTB_PAR_None);
	ConfigPwm();
	HMILib_Init();
	SPI_Init();
	SPI_Config(10000, false, true, true, 16);
	DAC_Init();
	QEPInit();
	InitTimer0();
	Timeout_Init();
	InitECana();
	UserInit();
	GpioDataRegs.GPASET.bit.GPIO28 = 1;			// Error Led OFF


/*-----------------------------------------------------------+
|                        Main Loop !                        |
+-----------------------------------------------------------*/

	for(;;)
	{
		HMILib_Background();
		UARTB_Background();
		UserIdle();	

	}
}



