/** \file CANlib.c
* \brief Library to use the Delfino CAN interface
* \author André Kneuss
* \date 04.2010
*/

#include "PeripheralHeaderIncludes.h"
#include "CANlib.h"

/*-----------------------------------------------------------+
|                         VARIABLES                          |
+-----------------------------------------------------------*/
 struct ECAN_REGS ECanaShadow;

/*-----------------------------------------------------------+
|                         PROTOTYPES                         |
+-----------------------------------------------------------*/
/*
void Config_CAN_Mailbox(unsigned char Mbx, int ID, unsigned char, unsigned char Data_lenght, unsigned char Remote, unsigned char Auto_Ans);
void Enable_CAN_Mailbox(unsigned char Mbx);
void Disable_CAN_Mailbox(unsigned char Mbx);
void Wait_Send_Ack(unsigned char Mbx);
void Send_Mailbox(unsigned char Mbx);
int Check_Receive_Mailbox(unsigned char Mbx);
long Read_Mailbox(unsigned char Mbx, unsigned char ByteX);
void Set_RTRbit_Mailbox(unsigned char Mbx);
void Set_Data_Mailbox(unsigned char Mbx, char Byte0, char Byte1, char Byte2, char Byte3, char Byte4, char Byte5, char Byte6, char Byte7);
*/
/*-----------------------------------------------------------+
|                         FUNCTIONS                          |
+-----------------------------------------------------------*/

/*
* This function configure the CAN Mailbox:
* 
* \author André Kneuss // pourrait etre simplifié en utilisant l'adresse+incrément, prendrait moins de place !!
* \date 04.2010
*/


void Config_CAN_Mailbox(unsigned char Mbx, int ID, unsigned char Dir, unsigned char Data_lenght, unsigned char Remote, unsigned char Auto_Ans)
{

switch(Mbx){
	case 1:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD0 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX0.MSGCTRL.bit.DLC = Data_lenght; 
	ECanaMboxes.MBOX0.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX0.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX0.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX0.MSGID.bit.AME=0;
	ECanaMboxes.MBOX0.MSGID.bit.STDMSGID=ID;
	}break;
	case 2:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD1 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX1.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX1.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX1.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX1.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX1.MSGID.bit.AME=0;
	ECanaMboxes.MBOX1.MSGID.bit.STDMSGID=ID;
	}break;
	case 3:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD2 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX2.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX2.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX2.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX2.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX2.MSGID.bit.AME=0;
	ECanaMboxes.MBOX2.MSGID.bit.STDMSGID=ID;
	}break;
	case 4:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD3 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX3.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX3.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX3.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX3.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX3.MSGID.bit.AME=0;
	ECanaMboxes.MBOX3.MSGID.bit.STDMSGID=ID;
	}break;
	case 5:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD4 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX4.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX4.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX4.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX4.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX4.MSGID.bit.AME=0;
	ECanaMboxes.MBOX4.MSGID.bit.STDMSGID=ID;
	}break;
	case 6:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD5 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX5.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX5.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX5.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX5.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX5.MSGID.bit.AME=0;
	ECanaMboxes.MBOX5.MSGID.bit.STDMSGID=ID;
	}break;
	case 7:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD6 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX6.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX6.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX6.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX6.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX6.MSGID.bit.AME=0;
	ECanaMboxes.MBOX6.MSGID.bit.STDMSGID=ID;
	}break;
	case 8:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD7 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX7.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX7.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX7.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX7.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX7.MSGID.bit.AME=0;
	ECanaMboxes.MBOX7.MSGID.bit.STDMSGID=ID;
	}break;
	case 9:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD8 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX8.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX8.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX8.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX8.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX8.MSGID.bit.AME=0;
	ECanaMboxes.MBOX8.MSGID.bit.STDMSGID=ID;
	}break;
	case 10:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD9 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX9.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX9.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX9.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX9.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX9.MSGID.bit.AME=0;
	ECanaMboxes.MBOX9.MSGID.bit.STDMSGID=ID;
	}break;
	case 11:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD10 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX10.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX10.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX10.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX10.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX10.MSGID.bit.AME=0;
	ECanaMboxes.MBOX10.MSGID.bit.STDMSGID=ID;
	}break;
	case 12:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD11 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX11.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX11.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX11.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX11.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX11.MSGID.bit.AME=0;
	ECanaMboxes.MBOX11.MSGID.bit.STDMSGID=ID;
	}break;
	case 13:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD12 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX12.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX12.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX12.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX12.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX12.MSGID.bit.AME=0;
	ECanaMboxes.MBOX12.MSGID.bit.STDMSGID=ID;
	}break;
	case 14:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD13 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX13.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX13.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX13.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX13.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX13.MSGID.bit.AME=0;
	ECanaMboxes.MBOX13.MSGID.bit.STDMSGID=ID;
	}break;
	case 15:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD14 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX14.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX14.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX14.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX14.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX14.MSGID.bit.AME=0;
	ECanaMboxes.MBOX14.MSGID.bit.STDMSGID=ID;
	}break;
	case 16:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD15 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX15.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX15.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX15.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX15.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX15.MSGID.bit.AME=0;
	ECanaMboxes.MBOX15.MSGID.bit.STDMSGID=ID;
	}break;
	case 17:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD16 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX16.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX16.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX16.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX16.MSGID.bit.AME=0;
	ECanaMboxes.MBOX16.MSGID.bit.STDMSGID=ID;
	}break;
	case 18:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD17 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX17.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX17.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX17.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX17.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX17.MSGID.bit.AME=0;
	ECanaMboxes.MBOX17.MSGID.bit.STDMSGID=ID;
	}break;
	case 19:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD18 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX18.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX18.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX18.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX18.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX18.MSGID.bit.AME=0;
	ECanaMboxes.MBOX18.MSGID.bit.STDMSGID=ID;
	}break;
	case 20:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD19 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX19.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX19.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX19.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX19.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX19.MSGID.bit.AME=0;
	ECanaMboxes.MBOX19.MSGID.bit.STDMSGID=ID;
	}break;
	case 21:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD20 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX20.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX0.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX20.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX20.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX20.MSGID.bit.AME=0;
	ECanaMboxes.MBOX20.MSGID.bit.STDMSGID=ID;
	}break;
	case 22:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD21 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX21.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX21.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX21.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX21.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX21.MSGID.bit.AME=0;
	ECanaMboxes.MBOX21.MSGID.bit.STDMSGID=ID;
	}break;
	case 23:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD22 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX22.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX22.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX22.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX22.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX22.MSGID.bit.AME=0;
	ECanaMboxes.MBOX22.MSGID.bit.STDMSGID=ID;
	}break;
	case 24:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD23 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX23.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX23.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX23.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX23.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX23.MSGID.bit.AME=0;
	ECanaMboxes.MBOX23.MSGID.bit.STDMSGID=ID;
	}break;
	case 25:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD24 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX24.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX24.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX24.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX24.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX24.MSGID.bit.AME=0;
	ECanaMboxes.MBOX24.MSGID.bit.STDMSGID=ID;
	}break;
	case 26:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD25 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX25.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX25.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX25.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX25.MSGID.bit.AME=0;
	ECanaMboxes.MBOX25.MSGID.bit.STDMSGID=ID;
	}break;
	case 27:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD26 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX26.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX26.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX26.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX26.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX26.MSGID.bit.AME=0;
	ECanaMboxes.MBOX26.MSGID.bit.STDMSGID=ID;
	}break;
	case 28:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD27 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX27.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX27.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX27.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX27.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX27.MSGID.bit.AME=0;
	ECanaMboxes.MBOX27.MSGID.bit.STDMSGID=ID;
	}break;
	case 29:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD28 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX28.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX28.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX28.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX28.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX28.MSGID.bit.AME=0;
	ECanaMboxes.MBOX28.MSGID.bit.STDMSGID=ID;
	}break; 
	case 30:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD29 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX29.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX29.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX29.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX29.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX29.MSGID.bit.AME=0;
	ECanaMboxes.MBOX29.MSGID.bit.STDMSGID=ID;
	}break; 
	case 31:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD30 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX30.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX30.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX30.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX30.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX30.MSGID.bit.AME=0;
	ECanaMboxes.MBOX30.MSGID.bit.STDMSGID=ID;
	}break; 
	case 32:
	{
	ECanaShadow.CANMD.all = ECanaRegs.CANMD.all; // Lecture-écriture uniquement en 32bit
	ECanaShadow.CANMD.bit.MD31 = Dir;
	ECanaRegs.CANMD.all = ECanaShadow.CANMD.all; // Lecture-écriture uniquement en 32bit

	ECanaMboxes.MBOX31.MSGCTRL.bit.DLC = Data_lenght;
	ECanaMboxes.MBOX31.MSGCTRL.bit.RTR=Remote;

	ECanaMboxes.MBOX31.MSGID.bit.AAM=Auto_Ans; 
	ECanaMboxes.MBOX31.MSGID.bit.IDE=0;
	ECanaMboxes.MBOX31.MSGID.bit.AME=0;
	ECanaMboxes.MBOX31.MSGID.bit.STDMSGID=ID;
	}break;

 }

}


void Enable_CAN_Mailbox(unsigned char Mbx)
{
 switch(Mbx)
 {
	case 1:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME0 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 2:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME1 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 3:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME2 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 4:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME3 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 5:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME4 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 6:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME5 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 7:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME6 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 8:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME7 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 9:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME8 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 10:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME9 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 11:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME10 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 12:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME11 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 13:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME12 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 14:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME13 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 15:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME14 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 16:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME15 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 17:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME16 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 18:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME17 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 19:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME18 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 20:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME19 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 21:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME20 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 22:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME21 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 23:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME22 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 24:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME23 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 25:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME24 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 26:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME25 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 27:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME26 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 28:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME27 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 29:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME28 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 30:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME29 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 31:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME30 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 32:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME31 = 1;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;



 }
}


void Disable_CAN_Mailbox(unsigned char Mbx)
{
 switch(Mbx)
 {
	case 1:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME0 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 2:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME1 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 3:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME2 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 4:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME3 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 5:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME4 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 6:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME5 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 7:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME6 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 8:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME7 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 9:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME8 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 10:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME9 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 11:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME10 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 12:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME11 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 13:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME12 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 14:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME13 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 15:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME14 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 16:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME15 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 17:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME16 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 18:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME17 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 19:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME18 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 20:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME19 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 21:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME20 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 22:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME21 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 23:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME22 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 24:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME23 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 25:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME24 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 26:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME25 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 27:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME26 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 28:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME27 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 29:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME28 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 30:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME29 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 31:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME30 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;

	case 32:
	{
   		ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   		ECanaShadow.CANME.bit.ME31 = 0;
   		ECanaRegs.CANME.all = ECanaShadow.CANME.all;
	}break;
 }
}


void Send_Mailbox(unsigned char Mbx)
{

 switch(Mbx)
 {
	case 1:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS0 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 2:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS1 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 3:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS2 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 4:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS3 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 5:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS4 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 6:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS5 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 7:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS6 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 8:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS7 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 9:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS8 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 10:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS9 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 11:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS10 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 12:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS11 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 13:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS12 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 14:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS13 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 15:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS14 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 16:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS15 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 17:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS16 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 18:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS17 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 19:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS18 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 20:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS19 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 21:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS20 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 22:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS21 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 23:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS22 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 24:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS23 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 25:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS24 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 26:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS25 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 27:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS26 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 28:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS27 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 29:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS28 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 30:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS29 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 31:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS30 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;

	case 32:
	{
   	   ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS31 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

	}break;
 }
}

int Check_Receive_Mailbox(unsigned char Mbx)
{
 int Mailbox_Receive_Flag=0;
 ECanaShadow.CANRMP.all= ECanaRegs.CANRMP.all;
 

 switch(Mbx)
 {
	case 1:
	{
		if(ECanaShadow.CANRMP.bit.RMP0==1)
		{
		ECanaShadow.CANRMP.bit.RMP0=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
		Mailbox_Receive_Flag=1;
		}

	}break;

	case 2:
	{
		if(ECanaShadow.CANRMP.bit.RMP1==1)
		{
		ECanaShadow.CANRMP.bit.RMP1=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}
		
	}break;

	case 3:
	{
		if(ECanaShadow.CANRMP.bit.RMP2==1)
		{
		ECanaShadow.CANRMP.bit.RMP2=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}
		
	}break;

	case 4:
	{
		if(ECanaShadow.CANRMP.bit.RMP3==1)
		{
		ECanaShadow.CANRMP.bit.RMP3=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 5:
	{
		if(ECanaShadow.CANRMP.bit.RMP4==1)
		{
		ECanaShadow.CANRMP.bit.RMP4=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 6:
	{
		if(ECanaShadow.CANRMP.bit.RMP5==1)
		{
		ECanaShadow.CANRMP.bit.RMP5=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 7:
	{
		if(ECanaShadow.CANRMP.bit.RMP6==1)
		{
		ECanaShadow.CANRMP.bit.RMP6=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 8:
	{
		if(ECanaShadow.CANRMP.bit.RMP7==1)
		{
		ECanaShadow.CANRMP.bit.RMP7=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 9:
	{
		if(ECanaShadow.CANRMP.bit.RMP8==1)
		{
		ECanaShadow.CANRMP.bit.RMP8=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 10:
	{
		if(ECanaShadow.CANRMP.bit.RMP9==1)
		{
		ECanaShadow.CANRMP.bit.RMP9=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 11:
	{
		if(ECanaShadow.CANRMP.bit.RMP10==1)
		{
		ECanaShadow.CANRMP.bit.RMP10=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 12:
	{
		if(ECanaShadow.CANRMP.bit.RMP11==1)
		{
		ECanaShadow.CANRMP.bit.RMP11=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 13:
	{
		if(ECanaShadow.CANRMP.bit.RMP12==1)
		{
		ECanaShadow.CANRMP.bit.RMP12=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 14:
	{
		if(ECanaShadow.CANRMP.bit.RMP13==1)
		{
		ECanaShadow.CANRMP.bit.RMP13=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 15:
	{
		if(ECanaShadow.CANRMP.bit.RMP14==1)
		{
		ECanaShadow.CANRMP.bit.RMP14=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 16:
	{
		if(ECanaShadow.CANRMP.bit.RMP15==1)
		{
		ECanaShadow.CANRMP.bit.RMP15=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 17:
	{
		if(ECanaShadow.CANRMP.bit.RMP16==1)
		{
		ECanaShadow.CANRMP.bit.RMP16=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 18:
	{
		if(ECanaShadow.CANRMP.bit.RMP17==1)
		{
		ECanaShadow.CANRMP.bit.RMP17=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 19:
	{
		if(ECanaShadow.CANRMP.bit.RMP18==1)
		{
		ECanaShadow.CANRMP.bit.RMP18=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 20:
	{
		if(ECanaShadow.CANRMP.bit.RMP19==1)
		{
		ECanaShadow.CANRMP.bit.RMP19=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 21:
	{
		if(ECanaShadow.CANRMP.bit.RMP20==1)
		{
		ECanaShadow.CANRMP.bit.RMP20=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 22:
	{
		if(ECanaShadow.CANRMP.bit.RMP21==1)
		{
		ECanaShadow.CANRMP.bit.RMP21=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 23:
	{
		if(ECanaShadow.CANRMP.bit.RMP22==1)
		{
		ECanaShadow.CANRMP.bit.RMP22=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 24:
	{
		if(ECanaShadow.CANRMP.bit.RMP23==1)
		{
		ECanaShadow.CANRMP.bit.RMP23=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 25:
	{
		if(ECanaShadow.CANRMP.bit.RMP24==1)
		{
		ECanaShadow.CANRMP.bit.RMP24=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 26:
	{
		if(ECanaShadow.CANRMP.bit.RMP25==1)
		{
		ECanaShadow.CANRMP.bit.RMP25=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 27:
	{
		if(ECanaShadow.CANRMP.bit.RMP26==1)
		{
		ECanaShadow.CANRMP.bit.RMP26=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 28:
	{
		if(ECanaShadow.CANRMP.bit.RMP27==1)
		{
		ECanaShadow.CANRMP.bit.RMP27=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 29:
	{
		if(ECanaShadow.CANRMP.bit.RMP28==1)
		{
		ECanaShadow.CANRMP.bit.RMP28=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 30:
	{
		if(ECanaShadow.CANRMP.bit.RMP29==1)
		{
		ECanaShadow.CANRMP.bit.RMP29=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 31:
	{
		if(ECanaShadow.CANRMP.bit.RMP30==1)
		{
		ECanaShadow.CANRMP.bit.RMP30=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	case 32:
	{
		if(ECanaShadow.CANRMP.bit.RMP31==1)
		{
		ECanaShadow.CANRMP.bit.RMP31=1;
		ECanaRegs.CANRMP.all=ECanaShadow.CANRMP.all;
        Mailbox_Receive_Flag=1;
		}

	}break;

	default :
        Mailbox_Receive_Flag=0;
 }

  return Mailbox_Receive_Flag;
}


void Set_Data_Mailbox(unsigned char Mbx, char Byte0, char Byte1, char Byte2, char Byte3, char Byte4, char Byte5, char Byte6, char Byte7)
{

 switch(Mbx)
 {
	case 1:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=0;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX0.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX0.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX0.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX0.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX0.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX0.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX0.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX0.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=0;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 2:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=1;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX1.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX1.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX1.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX1.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX1.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX1.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX1.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX1.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=1;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
		
	}break;

	case 3:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=2;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX2.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX2.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX2.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX2.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX2.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX2.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX2.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX2.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=2;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;
		
	}break;

	case 4:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=3;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX3.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX3.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX3.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX3.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX3.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX3.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX3.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX3.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=3;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 5:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=4;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX4.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX4.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX4.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX4.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX4.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX4.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX4.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX4.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=4;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 6:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=5;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX5.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX5.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX5.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX5.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX5.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX5.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX5.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX5.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=5;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 7:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=6;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX6.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX6.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX6.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX6.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX6.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX6.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX6.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX6.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=6;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 8:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=7;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX7.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX7.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX7.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX7.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX7.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX7.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX7.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX7.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=7;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 9:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=8;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX8.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX8.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX8.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX8.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX8.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX8.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX8.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX8.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=8;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 10:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=9;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX9.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX9.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX9.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX9.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX9.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX9.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX9.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX9.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=9;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 11:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=10;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX10.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX10.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX10.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX10.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX10.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX10.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX10.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX10.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=10;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 12:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=11;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX11.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX11.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX11.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX11.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX11.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX11.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX11.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX11.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=11;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 13:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=12;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX12.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX12.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX12.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX12.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX12.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX12.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX12.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX12.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=12;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 14:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=13;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX13.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX13.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX13.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX13.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX13.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX13.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX13.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX13.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=13;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 15:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=14;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX14.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX14.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX14.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX14.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX14.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX14.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX14.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX14.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=14;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 16:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=15;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX15.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX15.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX15.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX15.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX15.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX15.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX15.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX15.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=15;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 17:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=16;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX16.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX16.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX16.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX16.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX16.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX16.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX16.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX16.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=16;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 18:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=17;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX17.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX17.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX17.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX17.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX17.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX17.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX17.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX17.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=17;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 19:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=18;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX18.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX18.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX18.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX18.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX18.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX18.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX18.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX18.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=18;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 20:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=19;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX19.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX19.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX19.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX19.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX19.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX19.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX19.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX19.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=19;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 21:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=20;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX20.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX20.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX20.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX20.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX20.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX20.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX20.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX20.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=20;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 22:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=21;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX21.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX21.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX21.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX21.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX21.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX21.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX21.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX21.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=21;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 23:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=22;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX22.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX22.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX22.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX22.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX22.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX22.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX22.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX22.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=22;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 24:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=23;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX23.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX23.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX23.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX23.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX23.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX23.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX23.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX23.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=23;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 25:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=24;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX24.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX24.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX24.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX24.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX24.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX24.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX24.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX24.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=24;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 26:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=25;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX25.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX25.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX25.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX25.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX25.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX25.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX25.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX25.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=25;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 27:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=26;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX26.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX26.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX26.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX26.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX26.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX26.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX26.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX26.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=26;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 28:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=27;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX27.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX27.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX27.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX27.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX27.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX27.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX27.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX27.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=27;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 29:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=28;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX28.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX28.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX28.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX28.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX28.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX28.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX28.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX28.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=28;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 30:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=29;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX29.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX29.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX29.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX29.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX29.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX29.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX29.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX29.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=29;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 31:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=30;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX30.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX30.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX30.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX30.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX30.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX30.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX30.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX30.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=30;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	case 32:
	{
	    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
  		ECanaShadow.CANMC.bit.CDR=1;
   		ECanaShadow.CANMC.bit.MBNR=31;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;


		ECanaMboxes.MBOX31.MDL.byte.BYTE0=Byte3;
		ECanaMboxes.MBOX31.MDL.byte.BYTE1=Byte2;
		ECanaMboxes.MBOX31.MDL.byte.BYTE2=Byte1;
		ECanaMboxes.MBOX31.MDL.byte.BYTE3=Byte0;
		ECanaMboxes.MBOX31.MDH.byte.BYTE4=Byte7;
		ECanaMboxes.MBOX31.MDH.byte.BYTE5=Byte6;
		ECanaMboxes.MBOX31.MDH.byte.BYTE6=Byte5;
		ECanaMboxes.MBOX31.MDH.byte.BYTE7=Byte4;

		ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
   		ECanaShadow.CANMC.bit.CDR=0;
   		ECanaShadow.CANMC.bit.MBNR=31;
   		ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

	}break;

	default :
	break;
        
 }
}


void Wait_Send_Ack(unsigned char Mbx)
{
 switch(Mbx)
 {
	case 1:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA0 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA0 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 2:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA1 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA1 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 3:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA2 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA2 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 4:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA3 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA3 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 5:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA4 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA4 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 6:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA5 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA5 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 7:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA6 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA6 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 8:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA7 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA7 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 9:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA8 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA8 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 10:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA9 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA9 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 11:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA10 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA10 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 12:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA11 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA11 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 13:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA12 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA12 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 14:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA13 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA13 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 15:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA14 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA14 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 16:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA15 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA15 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 17:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA16 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA16 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 18:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA17 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA17 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 19:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA18 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA18 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 20:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA19 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA19 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 21:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA20 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA20 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 22:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA21 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA21 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 23:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA22 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA22 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 24:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA23 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA23 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 25:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA24 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA24 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 26:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA25 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA25 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 27:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA26 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA26 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 28:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA27 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA27 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 29:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA28 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA28 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 30:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA29 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA29 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 31:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA30 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA30 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	case 32:
	{
       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA31 == 0);   // Wait for TA bit to be set..

       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA31 = 1;     	         // Clear TA bit
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;
	}break;

	default :
	break;
 }


}

void Set_RTRbit_Mailbox(unsigned char Mbx)
{

switch(Mbx)
 {
	case 1:
	{
        Disable_CAN_Mailbox(1);
	    ECanaMboxes.MBOX0.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(1);

	}break;

	case 2:
	{
        Disable_CAN_Mailbox(2);
	    ECanaMboxes.MBOX1.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(2);

	}break;

	case 3:
	{
        Disable_CAN_Mailbox(3);
	    ECanaMboxes.MBOX2.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(3);

	}break;

	case 4:
	{
        Disable_CAN_Mailbox(4);
	    ECanaMboxes.MBOX3.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(4);

	}break;

	case 5:
	{
        Disable_CAN_Mailbox(5);
	    ECanaMboxes.MBOX4.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(5);

	}break;

	case 6:
	{
        Disable_CAN_Mailbox(6);
	    ECanaMboxes.MBOX5.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(6);

	}break;

	case 7:
	{
        Disable_CAN_Mailbox(7);
	    ECanaMboxes.MBOX6.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(7);

	}break;

	case 8:
	{
        Disable_CAN_Mailbox(8);
	    ECanaMboxes.MBOX7.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(8);

	}break;

	case 9:
	{
        Disable_CAN_Mailbox(9);
	    ECanaMboxes.MBOX8.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(9);

	}break;

	case 10:
	{
        Disable_CAN_Mailbox(10);
	    ECanaMboxes.MBOX9.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(10);

	}break;

	case 11:
	{
        Disable_CAN_Mailbox(11);
	    ECanaMboxes.MBOX10.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(11);

	}break;

	case 12:
	{
        Disable_CAN_Mailbox(12);
	    ECanaMboxes.MBOX11.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(12);

	}break;

	case 13:
	{
        Disable_CAN_Mailbox(13);
	    ECanaMboxes.MBOX12.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(13);

	}break;

	case 14:
	{
        Disable_CAN_Mailbox(14);
	    ECanaMboxes.MBOX13.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(14);

	}break;

	case 15:
	{
        Disable_CAN_Mailbox(15);
	    ECanaMboxes.MBOX14.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(15);

	}break;

	case 16:
	{
        Disable_CAN_Mailbox(16);
	    ECanaMboxes.MBOX15.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(16);

	}break;

	case 17:
	{
        Disable_CAN_Mailbox(17);
	    ECanaMboxes.MBOX16.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(17);

	}break;

	case 18:
	{
        Disable_CAN_Mailbox(18);
	    ECanaMboxes.MBOX17.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(18);

	}break;

	case 19:
	{
        Disable_CAN_Mailbox(19);
	    ECanaMboxes.MBOX18.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(19);

	}break;

	case 20:
	{
        Disable_CAN_Mailbox(20);
	    ECanaMboxes.MBOX19.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(1);

	}break;

	case 21:
	{
        Disable_CAN_Mailbox(21);
	    ECanaMboxes.MBOX20.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(21);

	}break;

	case 22:
	{
        Disable_CAN_Mailbox(22);
	    ECanaMboxes.MBOX21.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(22);

	}break;

	case 23:
	{
        Disable_CAN_Mailbox(23);
	    ECanaMboxes.MBOX22.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(23);

	}break;

	case 24:
	{
        Disable_CAN_Mailbox(24);
	    ECanaMboxes.MBOX23.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(24);

	}break;

	case 25:
	{
        Disable_CAN_Mailbox(25);
	    ECanaMboxes.MBOX24.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(25);

	}break;

	case 26:
	{
        Disable_CAN_Mailbox(26);
	    ECanaMboxes.MBOX25.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(26);

	}break;

	case 27:
	{
        Disable_CAN_Mailbox(27);
	    ECanaMboxes.MBOX26.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(27);

	}break;

	case 28:
	{
        Disable_CAN_Mailbox(28);
	    ECanaMboxes.MBOX27.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(28);

	}break;

	case 29:
	{
        Disable_CAN_Mailbox(29);
	    ECanaMboxes.MBOX28.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(29);

	}break;

	case 30:
	{
        Disable_CAN_Mailbox(30);
	    ECanaMboxes.MBOX29.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(30);

	}break;

	case 31:
	{
        Disable_CAN_Mailbox(31);
	    ECanaMboxes.MBOX30.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(31);

	}break;

	case 32:
	{
        Disable_CAN_Mailbox(32);
	    ECanaMboxes.MBOX31.MSGCTRL.bit.RTR=1;
	    Enable_CAN_Mailbox(32);

	}break;
	
	default:
	break;


 }

}  


long Read_Mailbox(unsigned char Mbx, unsigned char ByteX)
{
 long Data;

 switch(Mbx)
 {

	case 1:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX0.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX0.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX0.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX0.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX0.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX0.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX0.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX0.MDH.byte.BYTE4;
            }break;

			default: 
			break;
		}

	}break;


	case 2:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX1.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX1.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX1.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX1.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX1.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX1.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX1.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX1.MDH.byte.BYTE4;
            }break; 

			default: 
			break;
		}
	}break;

	case 3:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX2.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX2.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX2.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX2.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX2.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX2.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX2.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX2.MDH.byte.BYTE4;
            }break; 

			default: 
			break;
		}	
	}break;

	case 4:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX3.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX3.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX3.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX3.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX3.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX3.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX3.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX3.MDH.byte.BYTE4;
            }break;

			default: 
			break;
		}
	}break;

	case 5:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX4.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX4.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX4.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX4.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX4.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX4.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX4.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX4.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}
	}break;

	case 6:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX5.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX5.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX5.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX5.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX5.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX5.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX5.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX5.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}
	}break;

	case 7:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX6.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX6.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX6.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX6.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX6.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX6.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX6.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX6.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}
	}break;

	case 8:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX7.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX7.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX7.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX7.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX7.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX7.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX7.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX7.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 9:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX8.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX8.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX8.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX8.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX8.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX8.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX8.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX8.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 10:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX9.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX9.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX9.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX9.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX9.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX9.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX9.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX9.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}
	}break;

	case 11:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX10.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX10.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX10.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX10.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX10.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX10.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX10.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX10.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		} 

	}break;

	case 12:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX11.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX11.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX11.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX11.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX11.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX11.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX11.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX11.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 13:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX12.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX12.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX12.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX12.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX12.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX12.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX12.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX12.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 14:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX13.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX13.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX13.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX13.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX13.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX13.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX13.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX13.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 15:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX14.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX14.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX14.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX14.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX14.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX14.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX14.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX14.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 16:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX15.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX15.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX15.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX15.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX15.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX15.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX15.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX15.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 17:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX16.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX16.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX16.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX16.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX16.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX16.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX16.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX16.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 18:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX17.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX17.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX17.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX17.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX17.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX17.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX17.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX17.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 19:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX18.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX18.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX18.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX18.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX18.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX18.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX18.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX18.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 20:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX19.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX19.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX19.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX19.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX19.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX19.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX19.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX19.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;


	case 21:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX20.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX20.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX20.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX20.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX20.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX20.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX20.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX20.MDH.byte.BYTE4;
            }break;

			default: 
			break; 
		}

	}break;

	case 22:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX21.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX21.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX21.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX21.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX21.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX21.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX21.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX21.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 23:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX22.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX22.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX22.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX22.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX22.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX22.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX22.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX22.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 24:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX23.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX23.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX23.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX23.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX23.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX23.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX23.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX23.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 25:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX24.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX24.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX24.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX24.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX24.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX24.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX24.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX24.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 26:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX25.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX25.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX25.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX25.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX25.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX25.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX25.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX25.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}

	}break;

	case 27:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX26.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX26.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX26.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX26.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX26.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX26.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX26.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX26.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 

	}break;

	case 28:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX27.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX27.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX27.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX27.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX27.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX27.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX27.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX27.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		} 

	}break;

	case 29:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX28.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX28.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX28.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX28.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX28.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX28.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX28.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX28.MDH.byte.BYTE4;
            }break;

			default: 
			break; 
		} 
	}break;

	case 30:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX29.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX29.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX29.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX29.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX29.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX29.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX29.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX29.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
		}
	}break;

	case 31:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX30.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX30.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX30.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX30.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX30.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX30.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX30.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX30.MDH.byte.BYTE4;
            }break; 

			default: 
			break; 
	 	}
	}break;


	case 32:
	{
		switch (ByteX)
		{
			case 0:
			{
				Data=ECanaMboxes.MBOX31.MDL.byte.BYTE3;
            }break;
			case 1:
            {
				Data=ECanaMboxes.MBOX31.MDL.byte.BYTE2;
            }break;
			case 2:
            {
				Data=ECanaMboxes.MBOX31.MDL.byte.BYTE1;
            }break;
			case 3:
            {
				Data=ECanaMboxes.MBOX31.MDL.byte.BYTE0;
            }break;
			case 4:
            {
				Data=ECanaMboxes.MBOX31.MDH.byte.BYTE7;
            }break;
			case 5:
            {
				Data=ECanaMboxes.MBOX31.MDH.byte.BYTE6;
            }break;
			case 6:
            {
				Data=ECanaMboxes.MBOX31.MDH.byte.BYTE5;
            }break;
			case 7:
			{
				Data=ECanaMboxes.MBOX31.MDH.byte.BYTE4;
            }break; 

			default: 
			break;
	    }
	}break;

	   default :
        break;

   }
 }
 return Data;

}



