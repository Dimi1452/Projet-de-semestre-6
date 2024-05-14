#ifndef __CANLIB_H
#define __CANLIB_H


// Fonction permettant de configurer une des 32 Mailbox disponible
// Param�tres :  Mbx-> num�ro de la mailbox (1 � 32)
//		 ID -> Addresse de la mailbox � mettre en hexa (exemple 0x301)
//		 Dir -> Direction de la mailbox ( 1:receive, 0: transmit)	
//		 Data_lenght -> Nombre de byte de donn�e � envoyer/recevoir
//		 Remote -> � utiliser lors d'une trame de requete (1: remote request, 0: normale)
//		 Auto_Ans -> � utiliser lorsqu'une mailbox doit r�pondre � une trame de requete 

void Config_CAN_Mailbox(unsigned char Mbx, int ID, unsigned char Dir, unsigned char Data_lenght, unsigned char Remote, unsigned char Auto_Ans);


// Fonction permettant d'activ� une des 32 Mailbox disponibles.
void Enable_CAN_Mailbox(unsigned char Mbx);


// Fonction permettant de d�sactiv� une des 32 Mailbox disponibles.
void Disable_CAN_Mailbox(unsigned char Mbx);


// Fonction permettant d'attendre l'accus�e de r�ception certifiant que le message de la mailbox Mbx a �t� envoy� correctement
void Wait_Send_Ack(unsigned char Mbx);


// Fonction permettant de d�marrer l'envoi des donn�es contenu dans l'une des mailbox
void Send_Mailbox(unsigned char Mbx);

// Fonction permettant de v�rifier si un nouveau message est arriv�
int Check_Receive_Mailbox(unsigned char Mbx);


// Fonction permettant de lire les donn�e contenu dans une mailbox
long Read_Mailbox(unsigned char Mbx, unsigned char ByteX);


// Fonction permettant de d�finir une mailbox devant effectuer une trame de requete (une fois utiliser le bit est remis � z�ro, pour continuer � envoyer remettre � 1)
void Set_RTRbit_Mailbox(unsigned char Mbx);


// Fonction permettant de d�finir les donn�es contenu dans une mailbox
void Set_Data_Mailbox(unsigned char Mbx, char Byte0, char Byte1, char Byte2, char Byte3, char Byte4, char Byte5, char Byte6, char Byte7);

#endif
