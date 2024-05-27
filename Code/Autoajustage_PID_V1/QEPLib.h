#ifndef __QEPLIB_H
#define __QEPLIB_H

#include "bool.h"

void QEPInit(void);
unsigned long getQEP1Pos(void);
unsigned long getQEP2Pos(void);

void configQEP1(bool indexEnable, unsigned int maxCount, bool speedCalsEnable, bool swapAB);
void configQEP2(bool indexEnable, unsigned int maxCount, bool speedCalsEnable, bool swapAB);

void setQEO1Pos(unsigned long value);
void setQEO2Pos(unsigned long value);

int getQEP1Turn(void);
int getQEP2Turn(void);

void setQEP1Turn(int value);
void setQEP2Turn(int value);

#endif
