#ifndef __UARTB_H
#define __UARTB_H

#include "bool.h"


/**********************************/
/*            TYPES               */
/**********************************/
// PARAMETERS
typedef enum{\
UARTB_BR_115200, \
UARTB_BR_57600, \
UARTB_BR_38400, \
UARTB_BR_19200, \
UARTB_BR_9600 \
}UARTB_BaudRate_T;

typedef enum{\
  UARTB_PAR_None, \
  UARTB_PAR_Even, \
  UARTB_PAR_Odd \
}UARTB_Parity_T;


/**********************************/
/*         PROTOTYPES             */
/**********************************/

void UARTB_Init(UARTB_BaudRate_T baudRate, UARTB_Parity_T parity);
void UARTB_Send(char* string, char length);
void UARTB_Background();
bool UARTB_GetChar(char* c);


#endif

