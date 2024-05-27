#ifndef __UARTA_H
#define __UARTA_H

#include "bool.h"


/**********************************/
/*            TYPES               */
/**********************************/
// PARAMETERS
typedef enum{\
UARTA_BR_115200, \
UARTA_BR_57600, \
UARTA_BR_38400, \
UARTA_BR_19200, \
UARTA_BR_9600 \
}UARTA_BaudRate_T;

typedef enum{\
  UARTA_PAR_None, \
  UARTA_PAR_Even, \
  UARTA_PAR_Odd \
}UARTA_Parity_T;


/**********************************/
/*         PROTOTYPES             */
/**********************************/

void UARTA_Init(UARTA_BaudRate_T baudRate, UARTA_Parity_T parity);
void UARTA_Send(char* string, char length);
void UARTA_Background();
bool UARTA_GetChar(char* c);


#endif

