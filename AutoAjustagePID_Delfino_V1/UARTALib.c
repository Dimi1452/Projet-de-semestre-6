//============================================================================
//============================================================================
//
// FILE:	UARTA.c
//
// TITLE:	Librairy to manage & use UARTA port
// 
// Version: 1.0
// Author : Sylvain Décastel
// Date : 14.05.2009
//============================================================================


#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers
#include "Configuration.h"
#include "UARTALib.h"
#include "bool.h"

/******************************************************/
/*                    PROTOTYPES                      */
/******************************************************/
interrupt void UARTA_TXInterrupt(void);
interrupt void UARTA_RXInterrupt(void);


/******************************************************/
/*                    CONSTANTS                       */
/******************************************************/
#define SEND_BUFFER_LENGTH		150
#define RECEIVE_BUFFER_LENGTH	20


/******************************************************/
/*                    VARIABLES                       */
/******************************************************/


// Receive Buffer
static char	UARTA_ReceiveBuffer[RECEIVE_BUFFER_LENGTH];
static char*	UARTA_ReceiveBufferWritePtr = UARTA_ReceiveBuffer;
static char* 	UARTA_ReceiveBufferReadPtr	= UARTA_ReceiveBuffer;
static unsigned int UARTA_ReceiveCharCount = 0;

// Send Buffer
static char	UARTA_SendBuffer[SEND_BUFFER_LENGTH];
static char*	UARTA_SendBufferWritePtr	= UARTA_SendBuffer;
static char*	UARTA_SendBufferReadPtr		= UARTA_SendBuffer;
static unsigned int UARTA_SendCharCount	= 0;


/******************************************************/
/*                      MACROS                        */
/******************************************************/

// is used to check if the buffer ptr is out of the 
// buffer and to reset it to the 1st position 
#define UARTA_LimitReceiveBufferReadPtr()	{ \
											if(UARTA_ReceiveBufferReadPtr >= &UARTA_ReceiveBuffer[RECEIVE_BUFFER_LENGTH]) \
												UARTA_ReceiveBufferReadPtr = UARTA_ReceiveBuffer; \
											}
#define UARTA_LimitReceiveBufferWritePtr()	{ \
											if(UARTA_ReceiveBufferWritePtr >= &UARTA_ReceiveBuffer[RECEIVE_BUFFER_LENGTH]) \
												UARTA_ReceiveBufferWritePtr = UARTA_ReceiveBuffer; \
											}
#define UARTA_LimitSendBufferReadPtr()		{ \
											if(UARTA_SendBufferReadPtr >= &UARTA_SendBuffer[SEND_BUFFER_LENGTH]) \
												UARTA_SendBufferReadPtr = UARTA_SendBuffer; \
											}
#define UARTA_LimitSendBufferWritePtr()		{ \
											if(UARTA_SendBufferWritePtr >= &UARTA_SendBuffer[SEND_BUFFER_LENGTH]) \
												UARTA_SendBufferWritePtr = UARTA_SendBuffer; \
											}

/******************************************************/
/*                    FUNCTIONS                       */
/******************************************************/


void UARTA_Init(UARTA_BaudRate_T baudRate, UARTA_Parity_T parity)
{
	// see example Example_2833xSci_Echoback


	/* Init GPIO for SCIA */

	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled disabled by the user.  
	// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)

	/* Set qualification for selected pins to asynch only */
	// Inputs are synchronized to SYSCLKOUT by default.  
	// This will select asynch (no qualification) for the selected pins.

	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)

	/* Configure SCI-A pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation

	EDIS;


	/* Configure SCIA */

	// reset SCICCR
	SciaRegs.SCICCR.all = 0x0000;
	// loopback disable
	// IDLE mode selected

	// 8bit char mode
	SciaRegs.SCICCR.bit.SCICHAR = 7;

	// 2 stop bits
	SciaRegs.SCICCR.bit.STOPBITS = 1;

	switch(parity)
	{
		default:
		case UARTA_PAR_None:
		{
			// already set to 0 at reset
			//SciaRegs.SCICCR.bit.PARITYENA = 0;
		}break;

		case UARTA_PAR_Even:
		{
			SciaRegs.SCICCR.bit.PARITYENA = 1;
			SciaRegs.SCICCR.bit.PARITY = 1;
		}break;

		case UARTA_PAR_Odd:
		{
			SciaRegs.SCICCR.bit.PARITYENA = 1;
			// already set to 0 at reset
			//SciaRegs.SCICCR.bit.PARITY = 0;
		}break;
	}

	// baudrate (LSPCLK = 37.5MHz)
	// BRR = (LSPCLK/(Baud rate * 8)) - 1
	switch(baudRate)
	{
		case UARTA_BR_115200:
		{
			// BRR = 39.69 => 40 => 0x0028
			SciaRegs.SCIHBAUD = 0x00;
			SciaRegs.SCILBAUD = 0x28;
		}break;

		case UARTA_BR_57600:
		{
			// BRR = 80.38 => 80 => 0x0050
			SciaRegs.SCIHBAUD = 0x00;
			SciaRegs.SCILBAUD = 0x50;
		}break;

		case UARTA_BR_38400:
		{
			// BRR = 121.07 => 121 => 0x0079
			SciaRegs.SCIHBAUD = 0x00;
			SciaRegs.SCILBAUD = 0x79;
		}break;

		case UARTA_BR_19200:
		{
			// BRR = 243.141 => 243 => 0x00F3
			SciaRegs.SCIHBAUD = 0x00;
			SciaRegs.SCILBAUD = 0xF3;
		}break;

		default:
		case UARTA_BR_9600:
		{
			// BRR = 487.281 => 487 => 0x01E7
			SciaRegs.SCIHBAUD = 0x01;
			SciaRegs.SCILBAUD = 0xE7;
		}break;
	}


	// enable RX interrupt
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
	// disable TX interrupt
	SciaRegs.SCICTL2.bit.TXINTENA = 0;

	// enable RX & TX
	SciaRegs.SCICTL1.bit.RXENA = 1;
	SciaRegs.SCICTL1.bit.TXENA = 1;

	// software reset the scia
	SciaRegs.SCICTL1.bit.SWRESET = 0;
	asm(" RPT #5 || NOP");
	SciaRegs.SCICTL1.bit.SWRESET = 1;

	EALLOW;

	// Rx interrupt...
	PieVectTable.SCIRXINTA = &UARTA_RXInterrupt;


    PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, int1

	IER |= M_INT9;

	EDIS;
}

// this function can be used to send data to UARTA port. The content is copied into
// the send buffer, values are send to the port in the background function
void UARTA_Send(char* string, char length)
{
	
	while(length-- > 0)
	{
		if(UARTA_SendCharCount >= SEND_BUFFER_LENGTH)
			return; // not enough place !!
		else
			UARTA_SendCharCount++;

		*UARTA_SendBufferWritePtr++ = *string++;

		UARTA_LimitSendBufferWritePtr()

	}

}


// this function has to be called periodically to send the content of the send buffer
void UARTA_Background()
{

	// check the error flags
	if(SciaRegs.SCIRXST.bit.RXERROR == 1)
	{
		// don't care type of error... just reset
		SciaRegs.SCICTL1.bit.SWRESET = 0;

		asm(" RPT #5 || NOP");

		SciaRegs.SCICTL1.bit.SWRESET = 1;
	}

	
	// Send Next Char

	// check if tx buffer is ready
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
	{

		// check if the send buffer is not empty
		if(UARTA_SendCharCount  > 0)
		{
			// send the next char
			SciaRegs.SCITXBUF = *UARTA_SendBufferReadPtr++;

			if(UARTA_SendCharCount > 0)
				UARTA_SendCharCount--;
			else
			{
				// just to be sure... 
				// check if ptrs are equals
				if(UARTA_SendBufferReadPtr != UARTA_SendBufferWritePtr)
				UARTA_SendBufferReadPtr = UARTA_SendBufferWritePtr;

			}

			UARTA_LimitSendBufferReadPtr()
		}

	}




}

// this function return a char from the receive buffer
// the char is return using the pointer c
// the function return true if a char was returned or false
// if the receive buffer was empty.
bool UARTA_GetChar(char* c)
{
	if(UARTA_ReceiveBufferReadPtr != UARTA_ReceiveBufferWritePtr)
	{
		*c = *UARTA_ReceiveBufferReadPtr++;

		if(UARTA_ReceiveCharCount > 0)
			UARTA_ReceiveCharCount--;

		UARTA_LimitReceiveBufferReadPtr()

		return true;

	}

	return false;
}


// interrupt function for the UARTA RX interrupt
// reset the UARTA RX system if an error occurred
// store the received char in the receive buffer if no error
interrupt void UARTA_RXInterrupt(void)
{

	// check if no error
	if((SciaRegs.SCIRXST.bit.RXERROR == 0) && (UARTA_ReceiveCharCount < RECEIVE_BUFFER_LENGTH))
	{
		// get the char

		UARTA_ReceiveCharCount++;

		*UARTA_ReceiveBufferWritePtr++ = SciaRegs.SCIRXBUF.bit.RXDT;

		UARTA_LimitReceiveBufferWritePtr()

	}
	else
	{
		// don't care type of error... just reset
		SciaRegs.SCICTL1.bit.SWRESET = 0;

		asm(" RPT #5 || NOP");

		SciaRegs.SCICTL1.bit.SWRESET = 1;

	}

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;

}







