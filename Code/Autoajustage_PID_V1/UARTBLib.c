//============================================================================
//============================================================================
//
// FILE:	UARTB.c
//
// TITLE:	Librairy to manage & use UARTB port
// 
// Version: 1.0
// Author : Sylvain Décastel
// Date : 14.05.2009
//============================================================================


#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers
#include "Configuration.h"
#include "UARTBLib.h"
#include "bool.h"

/******************************************************/
/*                    PROTOTYPES                      */
/******************************************************/
interrupt void UARTB_TXInterrupt(void);
interrupt void UARTB_RXInterrupt(void);


/******************************************************/
/*                    CONSTANTS                       */
/******************************************************/
#define SEND_BUFFER_LENGTH		150	// 100 min to send the 80 char of LCD
#define RECEIVE_BUFFER_LENGTH	20


/******************************************************/
/*                    VARIABLES                       */
/******************************************************/


// Receive Buffer
static char	UARTB_ReceiveBuffer[RECEIVE_BUFFER_LENGTH];
static char*	UARTB_ReceiveBufferWritePtr = UARTB_ReceiveBuffer;
static char* 	UARTB_ReceiveBufferReadPtr	= UARTB_ReceiveBuffer;
static unsigned int UARTB_ReceiveCharCount = 0;

// Send Buffer
static char	UARTB_SendBuffer[SEND_BUFFER_LENGTH];
static char*	UARTB_SendBufferWritePtr	= UARTB_SendBuffer;
static char*	UARTB_SendBufferReadPtr		= UARTB_SendBuffer;
static unsigned int UARTB_SendCharCount	= 0;


/******************************************************/
/*                      MACROS                        */
/******************************************************/

// is used to check if the buffer ptr is out of the 
// buffer and to reset it to the 1st position 
#define UARTB_LimitReceiveBufferReadPtr()	{ \
											if(UARTB_ReceiveBufferReadPtr >= &UARTB_ReceiveBuffer[RECEIVE_BUFFER_LENGTH]) \
												UARTB_ReceiveBufferReadPtr = UARTB_ReceiveBuffer; \
											}
#define UARTB_LimitReceiveBufferWritePtr()	{ \
											if(UARTB_ReceiveBufferWritePtr >= &UARTB_ReceiveBuffer[RECEIVE_BUFFER_LENGTH]) \
												UARTB_ReceiveBufferWritePtr = UARTB_ReceiveBuffer; \
											}
#define UARTB_LimitSendBufferReadPtr()		{ \
											if(UARTB_SendBufferReadPtr >= &UARTB_SendBuffer[SEND_BUFFER_LENGTH]) \
												UARTB_SendBufferReadPtr = UARTB_SendBuffer; \
											}
#define UARTB_LimitSendBufferWritePtr()		{ \
											if(UARTB_SendBufferWritePtr >= &UARTB_SendBuffer[SEND_BUFFER_LENGTH]) \
												UARTB_SendBufferWritePtr = UARTB_SendBuffer; \
											}

/******************************************************/
/*                    FUNCTIONS                       */
/******************************************************/


void UARTB_Init(UARTB_BaudRate_T baudRate, UARTB_Parity_T parity)
{
	// see example Example_2833xSci_Echoback


	/* Init GPIO for SCIB */

	EALLOW;

	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled disabled by the user.  
	// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;    // Enable pull-up for GPIO28 (SCIRXDB)
	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;	   // Enable pull-up for GPIO29 (SCITXDB)

	/* Set qualification for selected pins to asynch only */
	// Inputs are synchronized to SYSCLKOUT by default.  
	// This will select asynch (no qualification) for the selected pins.

//	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3;

	/* Configure SCI-A pins using GPIO regs*/
	// This specifies which of the possible GPIO pins will be SCI functional pins.

	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;   // Configure GPIO28 for SCIRXDB operation
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO29 for SCITXDB operation

	EDIS;


	/* Configure SCIB */

	// reset SCICCR
	ScibRegs.SCICCR.all = 0x0000;
	// loopback disable
	// IDLE mode selected

	// 8bit char mode
	ScibRegs.SCICCR.bit.SCICHAR = 7;

	// 2 stop bits
	ScibRegs.SCICCR.bit.STOPBITS = 1;

	switch(parity)
	{
		default:
		case UARTB_PAR_None:
		{
			// already set to 0 at reset
			//ScibRegs.SCICCR.bit.PARITYENA = 0;
		}break;

		case UARTB_PAR_Even:
		{
			ScibRegs.SCICCR.bit.PARITYENA = 1;
			ScibRegs.SCICCR.bit.PARITY = 1;
		}break;

		case UARTB_PAR_Odd:
		{
			ScibRegs.SCICCR.bit.PARITYENA = 1;
			// already set to 0 at reset
			//ScibRegs.SCICCR.bit.PARITY = 0;
		}break;
	}

	// baudrate (LSPCLK = 37.5MHz)
	// BRR = (LSPCLK/(Baud rate * 8)) - 1
	switch(baudRate)
	{
		case UARTB_BR_115200:
		{
			// BRR = 39.69 => 40 => 0x0028
			ScibRegs.SCIHBAUD = 0x00;
			ScibRegs.SCILBAUD = 0x28;
		}break;

		case UARTB_BR_57600:
		{
			// BRR = 80.38 => 80 => 0x0050
			ScibRegs.SCIHBAUD = 0x00;
			ScibRegs.SCILBAUD = 0x50;
		}break;

		case UARTB_BR_38400:
		{
			// BRR = 121.07 => 121 => 0x0079
			ScibRegs.SCIHBAUD = 0x00;
			ScibRegs.SCILBAUD = 0x79;
		}break;

		case UARTB_BR_19200:
		{
			// BRR = 243.141 => 243 => 0x00F3
			ScibRegs.SCIHBAUD = 0x00;
			ScibRegs.SCILBAUD = 0xF3;
		}break;

		default:
		case UARTB_BR_9600:
		{
			// BRR = 487.281 => 487 => 0x01E7
			ScibRegs.SCIHBAUD = 0x01;
			ScibRegs.SCILBAUD = 0xE7;
		}break;
	}


	// enable RX interrupt
	ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
	// disable TX interrupt
	ScibRegs.SCICTL2.bit.TXINTENA = 0;

	// enable RX & TX
	ScibRegs.SCICTL1.bit.RXENA = 1;
	ScibRegs.SCICTL1.bit.TXENA = 1;

	// software reset the scia
	ScibRegs.SCICTL1.bit.SWRESET = 0;
	asm(" RPT #5 || NOP");
	ScibRegs.SCICTL1.bit.SWRESET = 1;

	EALLOW;

	// Rx interrupt...
	PieVectTable.SCIRXINTB = &UARTB_RXInterrupt;


    PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, int3 : SCIB RX

	IER |= M_INT9;

	EDIS;


	// call background funct after init
	UARTB_Background();

}

// this function can be used to send data to UARTB port. The content is copied into
// the send buffer, values are send to the port in the background function
void UARTB_Send(char* string, char length)
{
	
	while(length-- > 0)
	{
		if(UARTB_SendCharCount >= SEND_BUFFER_LENGTH)
			return; // not enough place !!
		else
			UARTB_SendCharCount++;

		*UARTB_SendBufferWritePtr++ = *string++;

		UARTB_LimitSendBufferWritePtr()

	}

}


// this function has to be called periodically to send the content of the send buffer
void UARTB_Background()
{

	// check the error flags
	if(ScibRegs.SCIRXST.bit.RXERROR == 1)
	{
		// don't care type of error... just reset
		ScibRegs.SCICTL1.bit.SWRESET = 0;

		asm(" RPT #5 || NOP");

		ScibRegs.SCICTL1.bit.SWRESET = 1;
	}

	
	// Send Next Char

	// check if tx buffer is ready
	if(ScibRegs.SCICTL2.bit.TXRDY == 1)
	{

		// check if the send buffer is not empty
		if(UARTB_SendCharCount  > 0)
		{
			// send the next char
			ScibRegs.SCITXBUF = *UARTB_SendBufferReadPtr++;

			if(UARTB_SendCharCount > 0)
				UARTB_SendCharCount--;
			else
			{
				// just to be sure... 
				// check if ptrs are equals
				if(UARTB_SendBufferReadPtr != UARTB_SendBufferWritePtr)
				UARTB_SendBufferReadPtr = UARTB_SendBufferWritePtr;

			}

			UARTB_LimitSendBufferReadPtr()
		}

	}




}

// this function return a char from the receive buffer
// the char is return using the pointer c
// the function return true if a char was returned or false
// if the receive buffer was empty.
bool UARTB_GetChar(char* c)
{
	if(UARTB_ReceiveBufferReadPtr != UARTB_ReceiveBufferWritePtr)
	{
		*c = *UARTB_ReceiveBufferReadPtr++;

		if(UARTB_ReceiveCharCount > 0)
			UARTB_ReceiveCharCount--;

		UARTB_LimitReceiveBufferReadPtr()

		return true;

	}

	return false;
}


// interrupt function for the UARTB RX interrupt
// reset the UARTB RX system if an error occurred
// store the received char in the receive buffer if no error
interrupt void UARTB_RXInterrupt(void)
{

	// check if no error
	if((ScibRegs.SCIRXST.bit.RXERROR == 0) && (UARTB_ReceiveCharCount < RECEIVE_BUFFER_LENGTH))
	{
		// get the char

		UARTB_ReceiveCharCount++;

		*UARTB_ReceiveBufferWritePtr++ = ScibRegs.SCIRXBUF.bit.RXDT;

		UARTB_LimitReceiveBufferWritePtr()

	}
	else
	{
		// don't care type of error... just reset
		ScibRegs.SCICTL1.bit.SWRESET = 0;

		asm(" RPT #5 || NOP");

		ScibRegs.SCICTL1.bit.SWRESET = 1;

	}

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP9;

}







