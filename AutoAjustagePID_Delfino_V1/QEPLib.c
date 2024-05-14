#include "DSP2833x_Device.h"
#include "bool.h"


/********************************************/
/*      		PROTOTYPES			 		*/
/********************************************/
void InitEQepGpio(void);
interrupt void QEP1Interrupt(void);
interrupt void QEP2Interrupt(void);


/********************************************/
/*      		VARIABLES			 		*/
/********************************************/
volatile unsigned long *ptrQEP1PosCounter = &EQep1Regs.QPOSCNT;
volatile unsigned long *ptrQEP2PosCounter = &EQep2Regs.QPOSCNT;

static int QEP1TurnCounter = 0;
static int QEP2TurnCounter = 0;



/* VELOCITY */
//static float QEPCapClockFactor = 128.0/150.0;
//static float QEP1Velocity = 0; // velocity in pos/s
//static float QEP2Velocity = 0; // velocity in pos/s




/********************************************/
/*      		FUNCTIONS			 		*/
/********************************************/

void QEPInit(void)
{
	// init the IOs
	InitEQepGpio();


	// Configure QEP 1

	EQep1Regs.QDECCTL.bit.QSRC = 0; 	// src = encoders with A & B
	EQep1Regs.QDECCTL.bit.SOEN = 0; 	// disable sync output enable
	EQep1Regs.QDECCTL.bit.SPSEL = 0; 	// disable sync output pin selection
	EQep1Regs.QDECCTL.bit.XCR = 0;   	// count falling & rising edges
	EQep1Regs.QDECCTL.bit.SWAP = 0;		// do not swap pins A & B
	EQep1Regs.QDECCTL.bit.IGATE = 1;	// gate the index pin with inputs
	EQep1Regs.QDECCTL.bit.QAP = 0;		// do not reverse input A
	EQep1Regs.QDECCTL.bit.QBP = 0;		// do not reverse input B
	EQep1Regs.QDECCTL.bit.QIP = 0;		// do not reverse index
	EQep1Regs.QDECCTL.bit.QSP = 0;		// do not reverse strobe input

	EQep1Regs.QEPCTL.bit.FREE_SOFT = 3;	// continue run on emulation suspend
	EQep1Regs.QEPCTL.bit.PCRM = 0;		// position counter reset on index
	EQep1Regs.QEPCTL.bit.SEI = 0;		// do not init pos. counter with strobe
	EQep1Regs.QEPCTL.bit.IEI = 0;		// do not init pos. counter with index
	EQep1Regs.QEPCTL.bit.SWI = 0;		// do not use software init
	EQep1Regs.QEPCTL.bit.SEL = 0;		// latch pos counter on rising edge of strobe (useless...)
	EQep1Regs.QEPCTL.bit.IEL = 1;		// latch pos counter on rising edge of index (useless...)
	EQep1Regs.QEPCTL.bit.QPEN = 1;		// enable QEP module
	EQep1Regs.QEPCTL.bit.UTE = 0;	 	// disable unit timer
	EQep1Regs.QEPCTL.bit.WDE = 0;		// disable watchdog tier

	EQep1Regs.QPOSCTL.bit.PCSHDW = 0;	// shadow compare disable
	EQep1Regs.QPOSCTL.bit.PCLOAD = 0;	// load shadow reg when QPOSCNT = 0
	EQep1Regs.QPOSCTL.bit.PCPOL = 0;	// position compare active high
	EQep1Regs.QPOSCTL.bit.PCE = 0;		// position compare disable
	EQep1Regs.QPOSCTL.bit.PCSPW = 0;	// position compare sync pulse with = 4 SYSCLOCK


	EQep1Regs.QCAPCTL.all = 0;			// reset capture unit
//	EQep1Regs.QCAPCTL.bit.UPPS=2;   	// 1/4 for unit position
//	EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
//	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable


	// Reset counters
	EQep1Regs.QPOSCNT = 0;		// position counter
	EQep1Regs.QPOSINIT = 0;		// position counter initialization
	EQep1Regs.QPOSMAX = 0xFFFFFFFF;	// position counter max value
	EQep1Regs.QPOSCMP = 0;		// position counter compare
	EQep1Regs.QUTMR = 0;		// unit timer counter
//	EQep1Regs.QUPRD = 1500000;		// init timer period (100Hz)
	EQep1Regs.QWDTMR = 0;		// QEP watchdog timer counter
	EQep1Regs.QWDPRD = 0;		// QEP watchdog timer period


	EQep1Regs.QEINT.all = 0;	// disable all interrupts
//	EQep1Regs.QEINT.bit.IEL = 1;// enable index interrupt
//	EQep1Regs.QEINT.bit.UTO = 1;// enable unit timer overflow interrupt
	EQep1Regs.QEINT.bit.PCO = 1;//enable interrupt on position counter overflow
	EQep1Regs.QEINT.bit.PCU = 1;//enable interrupt on position counter underflow

	EQep1Regs.QCLR.all = 0x0FFF;// clear all interrupts flags

	



	// Configure QEP 2

	EQep2Regs.QDECCTL.bit.QSRC = 0; 	// src = encoders with A & B
	EQep2Regs.QDECCTL.bit.SOEN = 0; 	// disable sync output enable
	EQep2Regs.QDECCTL.bit.SPSEL = 0; 	// disable sync output pin selection
	EQep2Regs.QDECCTL.bit.XCR = 0;   	// count falling & rising edges
	EQep2Regs.QDECCTL.bit.SWAP = 0;		// do not swap pins A & B
	EQep2Regs.QDECCTL.bit.IGATE = 1;	// gate the index pin with inputs
	EQep2Regs.QDECCTL.bit.QAP = 0;		// do not reverse input A
	EQep2Regs.QDECCTL.bit.QBP = 0;		// do not reverse input B
	EQep2Regs.QDECCTL.bit.QIP = 0;		// do not reverse index
	EQep2Regs.QDECCTL.bit.QSP = 0;		// do not reverse strobe input

	EQep2Regs.QEPCTL.bit.FREE_SOFT = 3;	// continue run on emulation suspend
	EQep2Regs.QEPCTL.bit.PCRM = 0;		// position counter reset on index
	EQep2Regs.QEPCTL.bit.SEI = 0;		// do not init pos. counter with strobe
	EQep2Regs.QEPCTL.bit.IEI = 0;		// do not init pos. counter with index
	EQep2Regs.QEPCTL.bit.SWI = 0;		// do not use software init
	EQep2Regs.QEPCTL.bit.SEL = 0;		// latch pos counter on rising edge of strobe (useless...)
	EQep2Regs.QEPCTL.bit.IEL = 1;		// latch pos counter on rising edge of index (useless...)
	EQep2Regs.QEPCTL.bit.QPEN = 1;		// enable QEP module
	EQep2Regs.QEPCTL.bit.UTE = 0;	 	// disable unit timer
	EQep2Regs.QEPCTL.bit.WDE = 0;		// disable watchdog tier

	EQep2Regs.QPOSCTL.bit.PCSHDW = 0;	// shadow compare disable
	EQep2Regs.QPOSCTL.bit.PCLOAD = 0;	// load shadow reg when QPOSCNT = 0
	EQep2Regs.QPOSCTL.bit.PCPOL = 0;	// position compare active high
	EQep2Regs.QPOSCTL.bit.PCE = 0;		// position compare disable
	EQep2Regs.QPOSCTL.bit.PCSPW = 0;	// position compare sync pulse with = 4 SYSCLOCK


	EQep2Regs.QCAPCTL.all = 0;			// reset capture unit
//	EQep2Regs.QCAPCTL.bit.UPPS=2;   	// 1/4 for unit position
//	EQep2Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
//	EQep2Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable


	// Reset counters
	EQep2Regs.QPOSCNT = 0;		// position counter
	EQep2Regs.QPOSINIT = 0;		// position counter initialization
	EQep2Regs.QPOSMAX = 0xFFFFFFFF;	// position counter max value
	EQep2Regs.QPOSCMP = 0;		// position counter compare
	EQep2Regs.QUTMR = 0;		// unit timer counter
//	EQep2Regs.QUPRD = 1500000;		// init timer period (100Hz)
	EQep2Regs.QWDTMR = 0;		// QEP watchdog timer counter
	EQep2Regs.QWDPRD = 0;		// QEP watchdog timer period


	EQep2Regs.QEINT.all = 0;	// disable all interrupts
//	EQep2Regs.QEINT.bit.IEL = 1;// enable index interrupt
//	EQep2Regs.QEINT.bit.UTO = 1;// enable unit timer overflow interrupt
	EQep2Regs.QEINT.bit.PCO = 1;//enable interrupt on position counter overflow
	EQep2Regs.QEINT.bit.PCU = 1;//enable interrupt on position counter underflow

	EQep2Regs.QCLR.all = 0x0FFF;// clear all interrupts flags




	// enable interrupt
	EALLOW;
	IER |= M_INT5;
	PieCtrlRegs.PIEIER5.bit.INTx1 = 1;	// QEP1 interrupt
	PieVectTable.EQEP1_INT = &QEP1Interrupt;

	PieCtrlRegs.PIEIER5.bit.INTx2 = 1;	// QEP2 interrupt
	PieVectTable.EQEP2_INT = &QEP2Interrupt;

	EDIS;
	
}




void InitEQepGpio()
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (EQEP1B)
//    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pull-up on GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (EQEP1I)

//    GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   // Enable pull-up on GPIO50 (EQEP1A)
//    GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;   // Enable pull-up on GPIO51 (EQEP1B)
//    GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;   // Enable pull-up on GPIO52 (EQEP1S)
//    GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;   // Enable pull-up on GPIO53 (EQEP1I)


// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;   // Sync to SYSCLKOUT GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0;   // Sync to SYSCLKOUT GPIO21 (EQEP1B)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0;   // Sync to SYSCLKOUT GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;   // Sync to SYSCLKOUT GPIO23 (EQEP1I)

//    GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 0;   // Sync to SYSCLKOUT GPIO50 (EQEP1A)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 0;   // Sync to SYSCLKOUT GPIO51 (EQEP1B)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 0;   // Sync to SYSCLKOUT GPIO52 (EQEP1S)
//    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 0;   // Sync to SYSCLKOUT GPIO53 (EQEP1I)

/* Configure eQEP-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eQEP1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   // Configure GPIO20 as EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   // Configure GPIO21 as EQEP1B
//    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;   // Configure GPIO22 as EQEP1S
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO23 as EQEP1I

//    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;   // Configure GPIO50 as EQEP1A
//    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;   // Configure GPIO51 as EQEP1B
//    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 1;   // Configure GPIO52 as EQEP1S
//    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 1;   // Configure GPIO53 as EQEP1I


 	// INIT QEP 2

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;    // Enable pull-up on GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (EQEP2B)
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO26 (EQEP2I)
//    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;    // Enable pull-up on GPIO27 (EQEP2S)

// Inputs are synchronized to SYSCLKOUT by default.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;  // Sync to SYSCLKOUT GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;  // Sync to SYSCLKOUT GPIO25 (EQEP2B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;  // Sync to SYSCLKOUT GPIO26 (EQEP2I)
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0;  // Sync to SYSCLKOUT GPIO27 (EQEP2S)

/* Configure eQEP-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be eQEP2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2;   // Configure GPIO24 as EQEP2A
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2;   // Configure GPIO25 as EQEP2B
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 2;   // Configure GPIO26 as EQEP2I
//    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 2;   // Configure GPIO27 as EQEP2S


    EDIS;
}


void configQEP1(bool indexEnable, unsigned int maxCount, bool speedCalsEnable, bool swapAB)
{
	if(indexEnable == true)
	{
		// reset pos counter on index event
		EQep1Regs.QEPCTL.bit.PCRM = 0;
	}
	else
	{
		EQep1Regs.QEPCTL.bit.PCRM = 1;
	}

	// set max count
	if(maxCount > 0)
		EQep1Regs.QPOSMAX = maxCount-1;
	else
		EQep1Regs.QPOSMAX = 0;

	// speed calc toto !!

	// swap AB
	if(swapAB == true)
	{
		EQep1Regs.QDECCTL.bit.SWAP = 1;
	}
	else
	{
		EQep1Regs.QDECCTL.bit.SWAP = 0;
	}


}


void configQEP2(bool indexEnable, unsigned int maxCount, bool speedCalsEnable, bool swapAB)
{

	if(indexEnable == true)
	{
		// reset pos counter on index event
		EQep2Regs.QEPCTL.bit.PCRM = 0;
	}
	else
	{
		EQep2Regs.QEPCTL.bit.PCRM = 1;
	}

	// set max count
	EQep2Regs.QPOSMAX = maxCount;

	// speed calc todo !!

	// swap AB
	if(swapAB == true)
	{
		EQep2Regs.QDECCTL.bit.SWAP = 1;
	}
	else
	{
		EQep2Regs.QDECCTL.bit.SWAP = 0;
	}

}


/*
void QEP1Background(void)
{
	
	// compute Velocity
	
	TODO : fonctionne en basse vitesse mais attention : 
	 - dépend de la fréquence du processeur, du nombre de position par tour
	 - ne revient pas automatiquement à 0 lors de l'arrêt du moteur...


	if(EQep1Regs.QFLG.bit.UTO==1)                    // If unit timeout (one 100Hz period)
	{ 
		
				
		EQep1Regs.QCLR.bit.UTO=1;					// Clear interrupt flag
	}	

	if(EQep1Regs.QEPSTS.bit.UPEVNT == 1)
	{

		GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;


		// compute velocity


		// check if no error 
		if(EQep1Regs.QEPSTS.bit.CDEF == 1)
		{
			// set velocity to 0
			QEP1Velocity = 0;

			// clear flag
			EQep1Regs.QEPSTS.bit.CDEF = 1;

		}
		else if(EQep1Regs.QEPSTS.bit.COEF == 1)
		{

			// set velocity to 0
			QEP1Velocity = 0;

			// clear flag
			EQep1Regs.QEPSTS.bit.COEF = 1;
		}
		else
		{
			// LOW SPEED METHOD

			// no error compute velocity

			unsigned int temp = EQep1Regs.QCPRD;	// time between 2 events
			unsigned int presc =  4;//EQep1Regs.QCAPCTL.bit.UPPS; // nb pos for each event
			unsigned int prd = 2000;//EQep1Regs.QPOSMAX;	// nb pos per revolution

			// check direction
			if(EQep1Regs.QEPSTS.bit.QDF == 0) // reverse
			{
				QEP1Velocity = -(presc/(temp*QEPCapClockFactor)*1e6/prd*60);
			}
			else 
			{
				QEP1Velocity = presc/(temp*QEPCapClockFactor)*1e6/prd*60;
			}
		}

		EQep1Regs.QEPSTS.bit.UPEVNT = 1; // clear event flag (write 1)
		EQep1Regs.QEPSTS.bit.COEF = 1;   // clear overflow error flag
	}

	


	if(EQep1Regs.QFLG.bit.IEL == 1)
	{

		// clear flag
		EQep1Regs.QCLR.bit.IEL = 1;
	}

} // end QEP1Background()

*/ 


unsigned long getQEP1Pos(void)
{

	return *ptrQEP1PosCounter;
}


unsigned long getQEP2Pos(void)
{

	return *ptrQEP2PosCounter;
}

void setQEO1Pos(unsigned long value)
{
	*ptrQEP1PosCounter = value;
}

void setQEO2Pos(unsigned long value)
{
	*ptrQEP2PosCounter = value;
}


int getQEP1Turn(void)
{
	return QEP1TurnCounter;
}

int getQEP2Turn(void)
{
	return QEP2TurnCounter;
}

void setQEP1Turn(int value)
{
	QEP1TurnCounter = value;
}

void setQEP2Turn(int value)
{
	QEP2TurnCounter = value;
}


interrupt void QEP1Interrupt(void)
{
	// check for overflow interrupt
	if(EQep1Regs.QFLG.bit.PCO == 1)
	{
		// increment turn counter
		QEP1TurnCounter++;
	}

	// check for underflow interrupt
	if(EQep1Regs.QFLG.bit.PCU == 1)
	{
		// decrement turn counter
		QEP1TurnCounter--;
	}

	// clear all interrupt flags
	EQep1Regs.QCLR.all = 0x0FFF;

	// Acknowledge the interrupt group
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

}

interrupt void QEP2Interrupt(void)
{
	// check for overflow interrupt
	if(EQep2Regs.QFLG.bit.PCO == 1)
	{
		// increment turn counter
		QEP2TurnCounter++;
	}

	// check for underflow interrupt
	if(EQep2Regs.QFLG.bit.PCU == 1)
	{
		// decrement turn counter
		QEP2TurnCounter--;
	}

	// clear all interrupt flags
	EQep2Regs.QCLR.all = 0x0FFF;

	// Acknowledge the interrupt group
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;

}

