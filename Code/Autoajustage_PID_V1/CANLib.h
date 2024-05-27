#ifndef __CANLIB_H
#define __CANLIB_H


// Fonction permettant de configurer une des 32 Mailbox disponible
// Paramètres :  Mbx-> numéro de la mailbox (1 à 32)
//		 ID -> Addresse de la mailbox à mettre en hexa (exemple 0x301)
//		 Dir -> Direction de la mailbox ( 1:receive, 0: transmit)	
//		 Data_lenght -> Nombre de byte de donnée à envoyer/recevoir
//		 Remote -> à utiliser lors d'une trame de requete (1: remote request, 0: normale)
//		 Auto_Ans -> à utiliser lorsqu'une mailbox doit répondre à une trame de requete 

void Config_CAN_Mailbox(unsigned char Mbx, int ID, unsigned char Dir, unsigned char Data_lenght, unsigned char Remote, unsigned char Auto_Ans);


// Fonction permettant d'activé une des 32 Mailbox disponibles.
void Enable_CAN_Mailbox(unsigned char Mbx);


// Fonction permettant de désactivé une des 32 Mailbox disponibles.
void Disable_CAN_Mailbox(unsigned char Mbx);


// Fonction permettant d'attendre l'accusée de réception certifiant que le message de la mailbox Mbx a été envoyé correctement
void Wait_Send_Ack(unsigned char Mbx);


// Fonction permettant de démarrer l'envoi des données contenu dans l'une des mailbox
void Send_Mailbox(unsigned char Mbx);

// Fonction permettant de vérifier si un nouveau message est arrivé
int Check_Receive_Mailbox(unsigned char Mbx);


// Fonction permettant de lire les donnée contenu dans une mailbox
long Read_Mailbox(unsigned char Mbx, unsigned char ByteX);


// Fonction permettant de définir une mailbox devant effectuer une trame de requete (une fois utiliser le bit est remis à zéro, pour continuer à envoyer remettre à 1)
void Set_RTRbit_Mailbox(unsigned char Mbx);


// Fonction permettant de définir les données contenu dans une mailbox
void Set_Data_Mailbox(unsigned char Mbx, char Byte0, char Byte1, char Byte2, char Byte3, char Byte4, char Byte5, char Byte6, char Byte7);

#endif
