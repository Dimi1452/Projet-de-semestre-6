/* Library to define and use timeout */

#ifndef __TIMEOUTLIB_H
#define __TIMEOUTLIB_H


void Timeout_Init(void);

int Timeout_Open(unsigned int period);

int Timeout_Expired(int timeout_ID);

void Timeout_Refresh(int timeout_ID);

void Timeout_Close(int timeout_ID);


#endif

