#ifndef __USER_H
#define __USER_H

#define	LED1_GREEN_ON		GpioDataRegs.GPBCLEAR.bit.GPIO55 = 1; 
#define	LED1_GREEN_OFF		GpioDataRegs.GPBSET.bit.GPIO55 = 1; 
#define	LED1_GREEN_TOGGLE	GpioDataRegs.GPBTOGGLE.bit.GPIO55 = 1;

#define	LED1_RED_ON			GpioDataRegs.GPBCLEAR.bit.GPIO54 = 1; 
#define	LED1_RED_OFF		GpioDataRegs.GPBSET.bit.GPIO54 = 1; 
#define	LED1_RED_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO54 = 1;

#define	LED2_GREEN_ON		GpioDataRegs.GPBCLEAR.bit.GPIO53 = 1; 
#define	LED2_GREEN_OFF		GpioDataRegs.GPBSET.bit.GPIO53 = 1; 
#define	LED2_GREEN_TOGGLE	GpioDataRegs.GPBTOGGLE.bit.GPIO53 = 1;

#define	LED2_RED_ON			GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1; 
#define	LED2_RED_OFF		GpioDataRegs.GPBSET.bit.GPIO52 = 1; 
#define	LED2_RED_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO52 = 1;

#define	LED3_GREEN_ON		GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1; 
#define	LED3_GREEN_OFF		GpioDataRegs.GPBSET.bit.GPIO51 = 1; 
#define	LED3_GREEN_TOGGLE	GpioDataRegs.GPBTOGGLE.bit.GPIO51 = 1;

#define	LED3_RED_ON			GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1; 
#define	LED3_RED_OFF		GpioDataRegs.GPBSET.bit.GPIO50 = 1; 
#define	LED3_RED_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO50 = 1;

#define	LED4_GREEN_ON		GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1; 
#define	LED4_GREEN_OFF		GpioDataRegs.GPBSET.bit.GPIO49 = 1; 
#define	LED4_GREEN_TOGGLE	GpioDataRegs.GPBTOGGLE.bit.GPIO49 = 1;

#define	LED4_RED_ON			GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1; 
#define	LED4_RED_OFF		GpioDataRegs.GPBSET.bit.GPIO48 = 1; 
#define	LED4_RED_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO48 = 1;


#define	D1_OUT_ON			GpioDataRegs.GPCSET.bit.GPIO76 = 1;
#define	D1_OUT_OFF			GpioDataRegs.GPCCLEAR.bit.GPIO76 = 1; 
#define	D1_OUT_TOGGLE		GpioDataRegs.GPCTOGGLE.bit.GPIO76 = 1;

#define	D2_OUT_ON			GpioDataRegs.GPCSET.bit.GPIO77 = 1; 
#define	D2_OUT_OFF			GpioDataRegs.GPCCLEAR.bit.GPIO77 = 1; 
#define	D2_OUT_TOGGLE		GpioDataRegs.GPCTOGGLE.bit.GPIO77 = 1;

#define	D3_OUT_ON			GpioDataRegs.GPCSET.bit.GPIO78 = 1; 
#define	D3_OUT_OFF			GpioDataRegs.GPCCLEAR.bit.GPIO78 = 1; 
#define	D3_OUT_TOGGLE		GpioDataRegs.GPCTOGGLE.bit.GPIO78 = 1;

#define	D4_OUT_ON			GpioDataRegs.GPCSET.bit.GPIO79 = 1;
#define	D4_OUT_OFF			GpioDataRegs.GPCCLEAR.bit.GPIO79 = 1;
#define	D4_OUT_TOGGLE		GpioDataRegs.GPCTOGGLE.bit.GPIO79 = 1;

#define	D5_OUT_ON			GpioDataRegs.GPBSET.bit.GPIO38 = 1; 
#define	D5_OUT_OFF			GpioDataRegs.GPBCLEAR.bit.GPIO38 = 1; 
#define	D5_OUT_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO38 = 1;

#define	D6_OUT_ON			GpioDataRegs.GPBSET.bit.GPIO36 = 1; 
#define	D6_OUT_OFF			GpioDataRegs.GPBCLEAR.bit.GPIO36 = 1; 
#define	D6_OUT_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO36 = 1;

#define	D7_OUT_ON			GpioDataRegs.GPBSET.bit.GPIO35 = 1; 
#define	D7_OUT_OFF			GpioDataRegs.GPBCLEAR.bit.GPIO35 = 1; 
#define	D7_OUT_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO35 = 1;

#define	D8_OUT_ON			GpioDataRegs.GPBSET.bit.GPIO37 = 1; 
#define	D8_OUT_OFF			GpioDataRegs.GPBCLEAR.bit.GPIO37 = 1; 
#define	D8_OUT_TOGGLE		GpioDataRegs.GPBTOGGLE.bit.GPIO37 = 1;


#define D1_IN				GpioDataRegs.GPBDAT.bit.GPIO63;
#define D2_IN				GpioDataRegs.GPBDAT.bit.GPIO62;
#define D3_IN				GpioDataRegs.GPBDAT.bit.GPIO61;
#define D4_IN				GpioDataRegs.GPBDAT.bit.GPIO60;
#define D5_IN				GpioDataRegs.GPBDAT.bit.GPIO59;
#define D6_IN				GpioDataRegs.GPBDAT.bit.GPIO58;
#define D7_IN				GpioDataRegs.GPBDAT.bit.GPIO57;
#define D8_IN				GpioDataRegs.GPBDAT.bit.GPIO56;

void UserInit(void);
void UserIdle(void);
void UserTe(void);
void RegRelais(void);
void RegPID(void);
void CalcParam(void);


#endif
