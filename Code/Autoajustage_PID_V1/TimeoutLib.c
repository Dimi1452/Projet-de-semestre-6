
#include "PeripheralHeaderIncludes.h"
#include "TimeoutLib.h"
#include "User.h"

// CONSTANTS
#define MAX_NB_TIMEOUTS		10

// PROTOTYPES
interrupt void cpu_timer1_isr(void);


// VARIABLES
typedef struct
{
	unsigned int counter;
	unsigned int period;
	unsigned int active:1;
}Timeout_T;


static Timeout_T timeouts[MAX_NB_TIMEOUTS];


void Timeout_Init(void)
{
	int i=0;
	EALLOW;
	// enable Xnmi interrupt and select timer 1 for source
//	XIntruptRegs.XNMICR.bit.SELECT = 0;
//	XIntruptRegs.XNMICR.bit.ENABLE = 1;
	PieVectTable.XINT13 = &cpu_timer1_isr;
	EDIS;

	// init timer 1 with system clock 150MHz and period 1000us
	ConfigCpuTimer(&CpuTimer1, 150, 1000);
	CpuTimer1Regs.TCR.bit.TIE = 1; // enable timer1 interrupt
	IER |= M_INT13;

	StartCpuTimer1();


	//Reset active timeouts
	for(i=0;i<MAX_NB_TIMEOUTS;i++)
	{
	timeouts[i].active = 0;
	}

}

int Timeout_Open(unsigned int period)
{
	int timeoutID = 0;


	// find next free timeout
	while(timeoutID < MAX_NB_TIMEOUTS)
	{
		if(timeouts[timeoutID].active == 0)
		{
			break;
		}
		else
			timeoutID++;
	}

	// check if no timeouts found
	if(timeoutID >= MAX_NB_TIMEOUTS)
		return -1;

	// init values
	timeouts[timeoutID].period = period;
	timeouts[timeoutID].counter = period;
	timeouts[timeoutID].active = 1;	// timeout is reserved

	// return this ID
	return timeoutID;

}

int Timeout_Expired(int timeoutID)
{
	// check if timeout does not exist or not active or not expired
	if(timeoutID < 0 || \
	timeoutID >= MAX_NB_TIMEOUTS || \
	timeouts[timeoutID].active == 0 || \
	timeouts[timeoutID].counter > 0)
		return 0;
	else
		return 1;
}

void Timeout_Refresh(int timeoutID)
{
	// check if timeout exists and is active
	if(timeoutID < 0 || \
	timeoutID >= MAX_NB_TIMEOUTS || \
	timeouts[timeoutID].active == 0)
		return;

	// reset counter
	timeouts[timeoutID].counter = timeouts[timeoutID].period;
}

void Timeout_Close(int timeoutID)
{
	// check if timeout exists and is active
	if(timeoutID < 0 || \
	timeoutID >= MAX_NB_TIMEOUTS)
		return;

	// deactivate timeout
	timeouts[timeoutID].active = 0;
}

interrupt void cpu_timer1_isr(void)
{
	
	int timeoutID = 0;
	Timeout_T *ptrTimeouts = timeouts;
	// decrement each active timeouts
	D3_OUT_ON;
	for(timeoutID = 0; timeoutID < MAX_NB_TIMEOUTS; timeoutID++)
	{
		D5_OUT_TOGGLE;
		if(ptrTimeouts->active != 0 && ptrTimeouts->counter > 0)
			ptrTimeouts->counter--;

		*ptrTimeouts++;
	}
	D3_OUT_OFF;
}
