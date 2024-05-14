/** \file PWMLib.c
* \brief Code to control the PWM modules of the tms 28335
* \author Kneuss André
* \date 03.2010
*/

//============================================================================
//============================================================================
//
//
//	Fonction Set_Pwm_Freq :
//	-----------------------
//
//	Cette fonction permet de configurer la fréquence de commutation
//	de la branche choisie. Pour l'utiliser il faut donner en "int"
//	la branche à paramétrer (de 1 à 6) puis en "int" la valeur de
//	fréquence de commutation en [kHz]. Par exemple pour 25 [kHz],
//	il faut écrire 25. La fréquence est comprise entre 2 et 200 [kHz].
//
//	Cette fonction prend environ 0.6 [us] à être exécutée
//
//
//
//	Fonction Set_Pwm_Duty :
//	-----------------------
//
//	Cette fonction permet de configurer le duty cycle de la branche choisie.
//	Pour l'utiliser il faut donner en "int" la branche à paramétrer (de 1 à 6)
//	puis en "int" la valeur du duty. Cette valeur est à donner en %.
//	Par exemple pour 72% il faut écrire 72. Le duty cycle est compris
//	entre 0 et 100 [%].
//
//	Cette fonction prend environ 0.6 [us] à être exécutée
//
//
//
//	Fonction Set_Pwm_Phase :
//	-----------------------
//
//	Cette fonction permet de configurer la phase de la branche choisie.
//	Pour l'utiliser il faut donner en "int" la branche à paramétrer (de 1 à 6)
//	puis en "int" l'angle de déphase de la branche par rapport à la branche 1.
//	La valeur de l'angle est comprise entre 0 et 360 degré. Par exemple pour
//	avoir un déphasage de 120 degré il faut écrire 120.
//
//	Cette fonction prend environ 0.6 [us] à être exécutée
//
//
//
//	Fonction Set_Pwm_DeadTime :
//	---------------------------
//
//	Cette fonction permet de configurer le temps mort  de la branche choisie.
//	Pour l'utiliser il faut donner en "int" la branche à paramétrer (de 1 à 6)
//	puis en "int" la valeur en [us] du "deadTime". Cette valeur est comprise
//	entre 0 et 1000. La valeur 1 correspond à 0.01 [us] et
//	la valeur 1000 correspond à 10 [us].
//
//	Cette fonction prend environ 0.5 [us] à être exécutée
//
//
//============================================================================
//============================================================================
#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "PeripheralHeaderIncludes.h"	// Include all Peripheral Headers
#include "DSP2833x_EPwm_defines.h"
#include "Configuration.h"

/*-----------------------------------------------------------+
|                       VARIABLES                            |
+-----------------------------------------------------------*/
/** \brief Local backup of PWM period 
* \author asdfasdf
*/
static double Period_PWM;   
static double Duty_PWM;     /**< \brief Local backup of PWM duty cycle */
static double Phase_PWM;    /**< \brief Local backup of PWM phase */
static double DeadBand_PWM; /**< \brief Local backup of PWM dead band */


/*-----------------------------------------------------------+
|                       FUNCTIONS                            |
+-----------------------------------------------------------*/


void Set_Pwm_Freq(int Branch, int Value)
{
	Period_PWM = (75e3 / Value);

	switch(Branch)
	{
	case 1:
		EPwm1Regs.TBPRD = Period_PWM;
	break;

	case 2:
		EPwm2Regs.TBPRD = Period_PWM;
	break;

	case 3:
		EPwm3Regs.TBPRD = Period_PWM;
	break;

	case 4:
		EPwm4Regs.TBPRD = Period_PWM;
	break;

	case 5:
		EPwm5Regs.TBPRD = Period_PWM;
	break;

	case 6:
		EPwm6Regs.TBPRD = Period_PWM;
	break;

	default:
	break;
	}
}


void Set_Pwm_Duty(int Branch, int Value)
{
	Duty_PWM = Period_PWM-((Period_PWM/100) * Value);

	switch(Branch)
	{
	case 1:
		EPwm1Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	case 2:
		EPwm2Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	case 3:
		EPwm3Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	case 4:
		EPwm4Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	case 5:
		EPwm5Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	case 6:
		EPwm6Regs.CMPA.half.CMPA = Duty_PWM;
	break;

	default:
	break;
	}
}


void Set_Pwm_Phase(int Branch, int Value)
{
	if(Value>360){Value=360;}

	switch(Branch)
	{

	case 1:
	break;

	case 2:
		if(Value<=180){
		Phase_PWM = (Period_PWM /180) * Value;
		EPwm2Regs.TBCTL.bit.PHSDIR=TB_DOWN;
	
	}else {
	    Phase_PWM = Period_PWM-(((Period_PWM /180) * ((Value)-180)));
	    EPwm2Regs.TBCTL.bit.PHSDIR=TB_UP;
	}
	break;
	case 3:
		if(Value<=180){
		Phase_PWM = (Period_PWM /180) * Value;
		EPwm3Regs.TBCTL.bit.PHSDIR=TB_DOWN;

	}else {
	    Phase_PWM = Period_PWM-(((Period_PWM /180) * ((Value)-180)));
		EPwm3Regs.TBCTL.bit.PHSDIR=TB_UP;
	}
	break;
	case 4:
		if(Value<=180){
		Phase_PWM = (Period_PWM /180) * Value;
		EPwm4Regs.TBCTL.bit.PHSDIR=TB_DOWN;
	
	}else {
	    Phase_PWM = Period_PWM-(((Period_PWM /180) * ((Value)-180)));
		EPwm4Regs.TBCTL.bit.PHSDIR=TB_UP;
	}
	break;
	case 5:
		if(Value<=180){
		Phase_PWM = (Period_PWM /180) * Value;
		EPwm5Regs.TBCTL.bit.PHSDIR=TB_DOWN;
	
	}else {
	    Phase_PWM = Period_PWM-(((Period_PWM /180) * ((Value)-180)));
		EPwm5Regs.TBCTL.bit.PHSDIR=TB_UP;
	}
	break;
	case 6:
		if(Value<=180){
		Phase_PWM = (Period_PWM /180) * Value;
		EPwm6Regs.TBCTL.bit.PHSDIR=TB_DOWN;
	
	}else {
	    Phase_PWM = Period_PWM-(((Period_PWM /180) * ((Value)-180)));
		EPwm6Regs.TBCTL.bit.PHSDIR=TB_UP;
	}
	break;
	default:
	break;
 }

	switch(Branch)
	{
	case 1:
		EPwm1Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	case 2:
		EPwm2Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	case 3:
		EPwm3Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	case 4:
		EPwm4Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	case 5:
		EPwm5Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	case 6:
		EPwm6Regs.TBPHS.half.TBPHS = Phase_PWM;
	break;

	default:
	break;
	}
}


void Set_Pwm_DeadTime(int Branch, int Value)
{
	DeadBand_PWM = Value;

	switch(Branch)
	{
	case 1:
		EPwm1Regs.DBRED = DeadBand_PWM;
		EPwm1Regs.DBFED = DeadBand_PWM;
	break;

	case 2:
		EPwm2Regs.DBRED = DeadBand_PWM;
		EPwm2Regs.DBFED = DeadBand_PWM;
	break;

	case 3:
		EPwm3Regs.DBRED = DeadBand_PWM;
		EPwm3Regs.DBFED = DeadBand_PWM;
	break;

	case 4:
		EPwm4Regs.DBRED = DeadBand_PWM;
		EPwm4Regs.DBFED = DeadBand_PWM;
	break;

	case 5:
		EPwm5Regs.DBRED = DeadBand_PWM;
		EPwm5Regs.DBFED = DeadBand_PWM;
	break;

	case 6:
		EPwm6Regs.DBRED = DeadBand_PWM;
		EPwm6Regs.DBFED = DeadBand_PWM;
	break;

	default:
	break;
	}
}



// ----------------------- Init PWM  ---------------------------
//--------------------------------------------------------------
void ConfigPwm(void)
{

	if(Onduleur_1 == 1)
	{
// ---------------------- Init PWM 1 ---------------------------
//--------------------------------------------------------------
   InitEPwm1Gpio();
   Set_Pwm_Freq(1,PWM_freq);
   Set_Pwm_Duty(1,PWM_duty);
   Set_Pwm_Phase(1,PWM_phase);
   Set_Pwm_DeadTime(1,PWM_deadtime);

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active High PWMs - Setup Deadband
   EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 2 ---------------------------
//--------------------------------------------------------------
   InitEPwm2Gpio();
   Set_Pwm_Freq(2,PWM_freq);
   Set_Pwm_Duty(2,PWM_duty);
   Set_Pwm_Phase(2,PWM_phase);
   Set_Pwm_DeadTime(2,PWM_deadtime);

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active Low PWMs - Setup Deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 3 ---------------------------
//--------------------------------------------------------------
   InitEPwm3Gpio();
   Set_Pwm_Freq(3,PWM_freq);
   Set_Pwm_Duty(3,PWM_duty);
   Set_Pwm_Phase(3,PWM_phase);
   Set_Pwm_DeadTime(3,PWM_deadtime);

   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm3Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   // Active Low PWMs - Setup Deadband
   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
									

// --------------------- Clear PWM Counter --------------------------
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm3Regs.TBCTR = 0x0000;                      // Clear counter
	}

	

	if(Onduleur_2 == 1)
	{
// ---------------------- Init PWM 4 ---------------------------
//--------------------------------------------------------------
   InitEPwm4Gpio();
   Set_Pwm_Freq(4,PWM_freq);
   Set_Pwm_Duty(4,PWM_duty);
   Set_Pwm_Phase(4,PWM_phase);
   Set_Pwm_DeadTime(4,PWM_deadtime);

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm4Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   // Active Low PWMs - Setup Deadband
   EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 5 ---------------------------
//--------------------------------------------------------------
   InitEPwm5Gpio();
   Set_Pwm_Freq(5,PWM_freq);
   Set_Pwm_Duty(5,PWM_duty);
   Set_Pwm_Phase(5,PWM_phase);
   Set_Pwm_DeadTime(5,PWM_deadtime);

   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm5Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   // Active Low PWMs - Setup Deadband
   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm5Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm5Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 6 ---------------------------
//--------------------------------------------------------------
   InitEPwm6Gpio();
   Set_Pwm_Freq(6,PWM_freq);
   Set_Pwm_Duty(6,PWM_duty);
   Set_Pwm_Phase(6,PWM_phase);
   Set_Pwm_DeadTime(6,PWM_deadtime);

   // Setup TBCLK
   EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm6Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;


   // Active Low PWMs - Setup Deadband
   EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm6Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm6Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
																																																																				

// --------------------- Clear PWM Counter --------------------------
   EPwm4Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm5Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm6Regs.TBCTR = 0x0000;                      // Clear counter
	}



	if(PontH_ELMERE_1 == 1)
	{
// ---------------------- Init PWM 1 ---------------------------
//--------------------------------------------------------------
   InitEPwm1Gpio();
   Set_Pwm_Freq(1,PWM_freq);
   Set_Pwm_Duty(1,PWM_duty);
   Set_Pwm_Phase(1,PWM_phase);
   Set_Pwm_DeadTime(1,PWM_deadtime);

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active High PWMs - Setup Deadband
   EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 2 ---------------------------
//--------------------------------------------------------------
   InitEPwm2Gpio();
   Set_Pwm_Freq(2,PWM_freq);
   Set_Pwm_Duty(2,PWM_duty);
   Set_Pwm_Phase(2,PWM_phase);
   Set_Pwm_DeadTime(2,PWM_deadtime);

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             
   EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
																																																								

// --------------------- Clear PWM Counter --------------------------
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter
	}



	if(PontH_ELMERE_2 == 1)
	{
// ---------------------- Init PWM 4 ---------------------------
//--------------------------------------------------------------
   InitEPwm4Gpio();
   Set_Pwm_Freq(4,PWM_freq);
   Set_Pwm_Duty(4,PWM_duty);
   Set_Pwm_Phase(4,PWM_phase);
   Set_Pwm_DeadTime(4,PWM_deadtime);

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm4Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active Low PWMs - Setup Deadband
   EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 5 ---------------------------
//--------------------------------------------------------------
   InitEPwm5Gpio();
   Set_Pwm_Freq(5,PWM_freq);
   Set_Pwm_Duty(5,PWM_duty);
   Set_Pwm_Phase(5,PWM_phase);
   Set_Pwm_DeadTime(5,PWM_deadtime);

   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm5Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;             
   EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm5Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm5Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

																																																																

// --------------------- Clear PWM Counter --------------------------
   EPwm4Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm5Regs.TBCTR = 0x0000;                      // Clear counter
	}




	if(PontH_ELMERE_3 == 1)
	{
// ---------------------- Init PWM 3 ---------------------------
//--------------------------------------------------------------
   InitEPwm3Gpio();
   Set_Pwm_Freq(3,PWM_freq);
   Set_Pwm_Duty(3,PWM_duty);
   Set_Pwm_Phase(3,PWM_phase);
   Set_Pwm_DeadTime(3,PWM_deadtime);

   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm3Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active Low PWMs - Setup Deadband
   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 6 ---------------------------
//--------------------------------------------------------------
   InitEPwm6Gpio();
   Set_Pwm_Freq(6,PWM_freq);
   Set_Pwm_Duty(6,PWM_duty);
   Set_Pwm_Phase(6,PWM_phase);
   Set_Pwm_DeadTime(6,PWM_deadtime);

   EPwm6Regs.TBCTR = 0x0000;                      // Clear counter

   // Setup TBCLK
   EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm6Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;             
   EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;

   // Active Low PWMs - Setup Deadband
   EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm6Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm6Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event

																																																																													

// --------------------- Clear PWM Counter --------------------------
   EPwm3Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm6Regs.TBCTR = 0x0000;                      // Clear counter
	}


	if(PontH_OND_1 == 1)
	{
// ---------------------- Init PWM 1 ---------------------------
//--------------------------------------------------------------
   InitEPwm1Gpio();
   Set_Pwm_Freq(1,PWM_freq);
   Set_Pwm_Duty(1,PWM_duty);
   Set_Pwm_Phase(1,PWM_phase);
   Set_Pwm_DeadTime(1,PWM_deadtime);

   // Setup TBCLK
   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active High PWMs - Setup Deadband
   EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 2 ---------------------------
//--------------------------------------------------------------
   InitEPwm2Gpio();
   Set_Pwm_Freq(2,PWM_freq);
   Set_Pwm_Duty(2,PWM_duty);
   Set_Pwm_Phase(2,PWM_phase);
   Set_Pwm_DeadTime(2,PWM_deadtime);

   // Setup TBCLK
   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             
   EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;


   // Active Low PWMs - Setup Deadband
   EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 3 ---------------------------
//--------------------------------------------------------------
   InitEPwm3Gpio();
   Set_Pwm_Freq(3,PWM_freq);
   Set_Pwm_Duty(3,PWM_duty);
   Set_Pwm_Phase(3,PWM_phase);
   Set_Pwm_DeadTime(3,PWM_deadtime);

   // Setup TBCLK
   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm3Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm3Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;             
   EPwm3Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;


   EPwm3Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;          
   EPwm3Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;

   // Active Low PWMs - Setup Deadband
   EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
   EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
									

// --------------------- Clear PWM Counter --------------------------
   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm3Regs.TBCTR = 0x0000;                      // Clear counter
	}







	if(PontH_OND_2 == 1)
	{
// ---------------------- Init PWM 4 ---------------------------
//--------------------------------------------------------------
   InitEPwm4Gpio();
   Set_Pwm_Freq(4,PWM_freq);
   Set_Pwm_Duty(4,PWM_duty);
   Set_Pwm_Phase(4,PWM_phase);
   Set_Pwm_DeadTime(4,PWM_deadtime);

   // Setup TBCLK
   EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
   EPwm4Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;             
   EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;

   // Active Low PWMs - Setup Deadband
   EPwm4Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 5 ---------------------------
//--------------------------------------------------------------
   InitEPwm5Gpio();
   Set_Pwm_Freq(5,PWM_freq);
   Set_Pwm_Duty(5,PWM_duty);
   Set_Pwm_Phase(5,PWM_phase);
   Set_Pwm_DeadTime(5,PWM_deadtime);

   // Setup TBCLK
   EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm5Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;             
   EPwm5Regs.AQCTLA.bit.CAD = AQ_SET;


   // Active Low PWMs - Setup Deadband
   EPwm5Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
   EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm5Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm5Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event



// ---------------------- Init PWM 6 ---------------------------
//--------------------------------------------------------------
   InitEPwm6Gpio();
   Set_Pwm_Freq(6,PWM_freq);
   Set_Pwm_Duty(6,PWM_duty);
   Set_Pwm_Phase(6,PWM_phase);
   Set_Pwm_DeadTime(6,PWM_deadtime);

   // Setup TBCLK
   EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
   EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
   EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
   EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;
   EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
   EPwm6Regs.TBCTL.bit.FREE_SOFT = 3;			// run free

   EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
   EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
   EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
   EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

   // Set actions
   EPwm6Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;             
   EPwm6Regs.AQCTLA.bit.CAD = AQ_NO_ACTION;


   EPwm6Regs.AQCTLB.bit.CAU = AQ_NO_ACTION;          
   EPwm6Regs.AQCTLB.bit.CAD = AQ_NO_ACTION;

   // Active Low PWMs - Setup Deadband
   EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
   EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;
   EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;

   // Interrupt where we will change the Deadband
   EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
   EPwm6Regs.ETSEL.bit.INTEN = 1;                // Enable INT
   EPwm6Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
																																																																				

// --------------------- Clear PWM Counter --------------------------
   EPwm4Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm5Regs.TBCTR = 0x0000;                      // Clear counter
   EPwm6Regs.TBCTR = 0x0000;                      // Clear counter
	}


}

