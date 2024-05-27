/*******************************************************************************
*  EIA-FR / Génie électrique / 3ème année bachelor / Projet de semestre 6      *
*                                                                              *
*                                                                              *
*   Titre :             POSITIONNEMENT - REGULATEUR Auto-tunning PID           *
*							                                                   *
*   Détails :           Implémentation sur carte DELFINO pour cet              *
*                       asservissement en position d'une MCC de 6.5W (ELMERE)  *
*                       avec régulateur PID (ses coefficients                  *
*                       ont été déterminés par méthode d'auto-ajustement selon *
*                       Astrom et Haaglung   AH                                *
*                       Le moteur est muni d'un codeur incrémental             *
*                       de position (QEP), à 500 impulsions / tour.            *
*                                                                              *
*                       En pressant le bouton-poussoir BP2, Le programme se    *
*                       met en recherche des paramètres Kp,Ki,Kd. Ceci grâce   *
*                       Au régulateur à relais (hysteresis). Une fois les      *
* 						param. trouvé, le programme bascule sur le régulateur  *
*						PID.                                                   *
*						                                                       *
*						Saut de consigne à 0.4 -> une demi tour.               *
*						Ce saut de consigne est idéal pour l'observation de    *
*                       la réponse en position car la stratégie appliquée      *
* 						ici fixe la plage à un demi-tour de part et d'autre    *
* 						du zéro. Avec 0.4, on ménage ainsi une zone possible   *
* 						de dépassement. En effet, si la position réelle        *
* 						dépasse le demi-tour, alors il y a discontinuité:      *  
* 						il est ici interprété comme un demi-tour à l'opposé !  *
*																			   *
*						Cette application est ici réglée pour une MCC sans     *
*                      	inertie additionnelle.                                 *
*                                                                              *
*   Version :          	1.0                                                    *
*   Auteurs :          	Maillard                                               *
*   Date :             	21-03.2024                                             *
*   Nom du projet :    	ReglageAutoTuning_DelfinoV4                            *
*                                                                              *
*   Remarques de code: 	Dans le programme, les variables sont en minuscules,   *
*					   	les constantes sont une majuscule. 					   *
*                                                                              *
*******************************************************************************/


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * * * * *   I M P O R T A T I O N S   * * * * * * * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "UARTBLib.h"
#include "user.h"
#include "math.h"
#include "HMILib.h"
#include "ADCLib.h"
#include "PWMLib.h"
#include "QEPLib.h"
#include "DACLib.h"
#include "TimeoutLib.h"
#include "PeripheralHeaderIncludes.h"
#include "Configuration.h"
#include "CANLib.h"
#include "HMILib.h"
#include "time.h"
#include "stdio.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * * * * *   D É C L A R A T I O N S   * * * * * * * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// Pour la séquence d'affichage:
static int ViewTimer;
static int Timer1000ms;
static int WaitTimer;
static int WaitFlag = 0;              // Flag d'attente pour l'écran d'accueil
const float Period_Interrupt = 200.0; // Période d'interruption [us] (min. 100)
									  // Ne peut être modifiée en cours d'exéc.
									  
//==============================================================================
//	   CONSTANTES & VARIABLES "UTILISATEUR"
//==============================================================================
#define nbrEchantillon 1000

float Te;                       //période d'échantillonnage (=période d'interruption) [s]

// Codeur
int comptCod;					// Compteur du codeur [imp]
int ResolCod = 2000;    		// Résolution du codeur = [impulsion/tour].
						
//Affichage
// Bouton-poussoir (BP) du HMI
unsigned switch1_prec = 1;      // Etat précédent de BP1 (0 = pressé)
unsigned switch2_prec = 1;      // Etat précédent de BP2 (0 = pressé)

//consignes
float cons_t = 0.0;       		// Consigne de position [tour](1 tour = 2000 impulsions)
float consigneReg=0.3;          // Consigne pour le régulateur à relais min=0.3
int cons_pc ;             		// consigne de position en [%] (100% = 1 tour) pour affichage
float mesure_t[2];        		// Position mesurée [tour], en vecteur pour stocker  2 valeurs dans le temps ([0]=à k,[1]=à k-1)
float Kp=0.4478;                // Gain Proportionnel
float Ki=0.0342;                // Gain Intégrateur
float Kd=0.0037;                // Gain Dérivateur
float b;                        // Gain pour méthode AH
float Yrp;                      // sortie régulateur proportionnel
float Yri[2]={0.0, 0.0} ;       // sortie régulateur intégral 2 valeurs dans le temps ([0]=à k,[1]=à k-1)
float Yrd;                      // sortie régulateur dérivé

int compt=0;					// compteur pour consigne cyclique

float ucm;           			// Correction totale
float ecart_t[2]={0.0, 0.0};    // Ecart de réglage [tour] 2 valeurs dasn le temps ([0]=à k,[1]=à k-1)
float urlim=1.0; 				// Limite anti-windup
float uclim=1.0;				// Limite du régualateur
    		                    // Gain de la vitesse (temps continu)

                                // Commande du modulateur PWM
int Freq_PWM = 40;   			// Fréquence de commutation des PWM [kHz]
int TmpsAnti = 8;     			// Temps d'antichevauchement, exprimé en [10ns]
int ucm_pc;	        			// Correction en [%]
int u_pc;             			// Commande PWM [0..100%] du pont H (mode "diagonale
					    		//   double", où 50% = 0V en moyenne)
float Maximum1;                 // Mesure de l'amplitude max du signal mesuré
float Maximum2;                 // Mesure de l'amplitude max du signal mesuré une periode après pour calculer la période
int PositionMax1;               // Index du Max1 du tableau Value[]
int PositionMax2;               // Index du Max2 du tableau Value[]
float Value[nbrEchantillon];    // Tableau pour calculer les paramètres AH
bool FirstTime=true;            // Variable pour init le tableau value[] à 0 (faite une seule fois)
bool FirstRelais=true;          // Variable pour initier le mouvement (faite une seule fois)

float Ms= 1.4;                    // Coefficient de sensibilité
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * * * * *   I N I T I A L I S A T I O N   * * * * * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void UserInit(void)
{
	// Lancement des chronomètres (valeurs en [ms]):
	ViewTimer = Timeout_Open(50);
	Timer1000ms = Timeout_Open(1000);
	WaitTimer = Timeout_Open(3000);				
	
	// Ecran d'accueil (affiché pendant 3s):
	LCD_WriteStringPos(1,1,"    DELFINO Card    ",20);
	LCD_WriteStringPos(2,1,"        PS6         ",20);
	LCD_WriteStringPos(3,1,"   Regulateur PID   ",20);
	LCD_WriteStringPos(4,1,"    Auto-Tunning    ",20);
	BUZZER_Beep(100);

	// Initialisations :
	HMISwitchs.byte=0xff;		    // boutons-poussoirs
	Te = Period_Interrupt * 1e-6;	// période d'interruption [s]
	mesure_t[0] = 0.0;				// Position actuelle au premier instant [pu]
		
	// Initialisation des 2 branches du pont H_1 :
	//Set_Pwm_Topo(0,0,1,0); //Ondulateur_1,Ondulateur_2,PontH_1,PontH_2
	Set_Pwm_Freq(1,Freq_PWM);
	Set_Pwm_Freq(2,Freq_PWM);
	Set_Pwm_DeadTime(1,TmpsAnti);
	Set_Pwm_DeadTime(2,TmpsAnti);
  
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * *  F O N C T I O N   U T I L I S A T E U R   *  * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void RegRelais(void)
{
  //////////////////////Régulateur à Relais/////////////////////////////////
    if(FirstRelais==true)               //initier le mouvement
    {
        FirstRelais=false;
        mesure_t[0]=-0.4;
    }

               ecart_t[0] = mesure_t[0];

               if(ecart_t[0]>0.3)
               {
                   ucm=-consigneReg;
               }
               else if(ecart_t[0]<-0.3)
               {
                   ucm=consigneReg;

               }

}
void RegPID(void)
{
    //////////////////////Régulateur PID//////////////////////////////////////
    ecart_t[0]=cons_t - mesure_t[0];          // calcul de l'erreur

    Yrp= ecart_t[0];                          // Régulateur proportionnel

    Yri[0]= Yri[1] + ecart_t[0]*Te;           // Régulateur intégrateur


     // Anti Wind-up
     if (Yri[0]>0.5)
     {
         Yri[0] = urlim;
     }
     else if (Yri[0]<-0.5)
     {
         Yri[0] = -urlim;
     }

     Yrd= (ecart_t[0]-ecart_t[1])/Te;              // Régulateur dérivateur

     ucm= (Kp * Yrp + Ki * Yri[0] + Kd * Yrd);     // Sortie du régulateur

     Yri[1]=Yri[0];                               // mise à jour des variables dans le temps
     ecart_t[1]=ecart_t[0];

}
void CalcParam(void)
{
    //////////////////////Calculateur de paramètres///////////////////////////////////

    RegRelais();
    int index;
    for(index=0; index<=nbrEchantillon-1;index++)            // Remplissage du tableau Value avec les valeurs mesurées
    {
        if(Value[index]==0)
        {
            Value[index]=mesure_t[0];
            break;
        }
    }

    if(Value[nbrEchantillon-1]!=0)                          //test si la dernière cellule du tableau est remplie (!=0)
        {
        if(PositionMax2==0)
          {
            int i;
            for(i=50;i<nbrEchantillon-1;i++)              // Trouver les maximums locaux en passant les 100 premières cellules
                                                           // à cause des transitoires et ADC qui donnent des valeurs fausses
                {
                if(Value[i] >= Value[i-1]  && Value[i] >= Value[i-2]  && Value[i]>= Value[i+1] && Value[i] >= Value[i+2])
                    // trouver dans le tableau un maximum avec plusieurs condition à cause des transitoire et de l'ADC
                {
                    if(Maximum1==-INFINITY)
                    {
                        Maximum1 =Value[i];
                        PositionMax1=i;
                    }
                        else if(PositionMax1 != i)
                        {
                            Maximum2 =Value[i];
                            PositionMax2=i;
                         }
                    }
                }
         }
        }
    //// calcul des paramètres selon AH

    if(Maximum1 != -INFINITY && Maximum2 != -INFINITY)
    {
    float Tc = (PositionMax2 - PositionMax1) * Te; // Période d'oscillation
    float K0 = consigneReg / Maximum2;
    float Kc = (4 * Maximum2) / (M_PI * consigneReg);
    float k = 1 / (K0 * Kc);




        if(Ms==2) // Ms=2
        {
        b = 0.25* expf(0.56 * k - 0.12 * k * k);
        Kp = 0.72 * expf(-1.6 * k + 1.2 * k * k) * Kc;
        Kp= b * Kp;
        Ki = (0.59 * expf(-1.3 * k + 0.38 * k * k) * Tc);
        Kd = 0.15 * expf(-1.4 * k + 0.56 * k * k) * Tc;
        }
        else //Ms =1.4
        {
         b = 0.58* expf(-1.3 * k + 3.5 * k * k);
         Kp = 0.33 * expf(-0.31 * k - 1.0 * k * k) * Kc;
         Kp= b * Kp;
         Ki = (0.76 * expf(-1.6 * k - 0.36 * k * k) * Tc);
         Kd = 0.17 * expf(-0.46 * k - 2.1 * k * k) * Tc;

        }


    }



}





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * * * * * *   T Â C H E   D E   F O N D   * * * * * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void UserIdle(void)
{

   //===========================================================================
   //	   AFFICHAGE VENANT 3s APRÈS L'AFFICHAGE INITIAL
   //===========================================================================

   // Passage unique: image figée, sans réactualisation.
   if((Timeout_Expired(WaitTimer) == 1) && (WaitFlag == 0))
   {
   	   LCD_WriteStringPos(1,1," Auto-Ajustage PID  ",20); // 20 caractères disponible par lligne
	   LCD_WriteStringPos(2,1,"  BP1 saut de cons. ",20);
       LCD_WriteStringPos(3,1,"  Bp2 Param. init.  ",20);
       LCD_WriteStringPos(4,1,"                    ",20);
	   WaitFlag = 1;
   }
  
   //===========================================================================
   //	   LECTURE DES ENTREES DU HMI (chaque 50ms env.)
   //===========================================================================

   if((Timeout_Expired(ViewTimer) == 1) && (WaitFlag == 1))
   {
	   Timeout_Refresh(ViewTimer);
       // BP1 permet de commuter la consigne entre 0 et 0.4 pu
       // A la pression du BP1:
	   if ((HMISwitchs.bits.SW1 == 0) && (switch1_prec == 1)) 
       {
           switch1_prec = 0;
           if (cons_t==0.0) cons_t = 0.4;

           else cons_t = 0.0;
       }
       // A la relâche du BP1 :
	   if ((HMISwitchs.bits.SW1 == 1) && (switch1_prec == 0)) switch1_prec = 1;
   }
   

   if((Timeout_Expired(ViewTimer) == 1) && (WaitFlag == 1))
      {
          Timeout_Refresh(ViewTimer);
          // BP2 permet de réinitilaiser les paramètres du régulateurs à zéro
          if (HMISwitchs.bits.SW2 == 0)
          {
              Kp=0;Ki=0;Kd=0;b=0;
              Maximum1=-INFINITY;            // Mesure de l'amplitude max du signal mesuré
              Maximum2=-INFINITY;            // Mesure de l'amplitude max du signal mesuré une periode après pour calculer la période
              PositionMax1=0;                // Temps écoulé
              PositionMax2=0;
              FirstTime=true;
              FirstRelais=true;
          }
      }

   //======================================================================
   //	   RAFRAICHISSEMENT DES RESULTATS AFFICHES (chaque seconde env.)
   //======================================================================

   if((Timeout_Expired(Timer1000ms) == 1) && (WaitFlag == 1))
   {
		Timeout_Refresh(Timer1000ms);

   }
   
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// * * * * * * * * * * *   I N T E R R U P T I O N    * * * * * * * * * * * * *
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void UserTe(void)
{

    //=====================================================================
	//	   MESURE DE LA POSITION ET DE L'ECART
	//=====================================================================
   

   	comptCod = getQEP1Pos();            // Lecture du compteur de pos.
   	if (comptCod > ResolCod/2){ 		// Recentrage de la position mesurée
   	    comptCod -= ResolCod;           //   entre -1000 et +1000 [imp],
   	}                                   //   c'est-à-dire + ou - un 1/2 tour,
                                        //   en partant de la plage par défaut
                                        //   0 à 2000, qui présente donc une
                                        //   discontinuité gênante en zéro.
  	mesure_t[1] = mesure_t[0];          // Mémorisation de la pos. préc.
  	mesure_t[0] = (float)comptCod/(float)ResolCod; // Pos. actuelle

  	if(FirstTime==true)                 //Initailisation du tableau de valeur Value à 0
  	{
  	    FirstTime=false;
  	    int i;
  	    for(i=0;i<nbrEchantillon;i++)
  	    {
  	        Value[i]=0;
  	    }
  	}


    //=====================================================================
	//	   REGULATEUR PID Auto-ajustable
	//=====================================================================
 
	/* Schéma de principe qui rassemble autour du système à régler:
			

	             ____________
                ¦            |
              ->¦Reg à relais|----->¦
              | ¦____________|      ¦
//            |                     ¦
              |                     ¦                Plage de
              |      anti-windup    ¦   Limitation   la cmde
              |            ¦        ¦    [-1.. +1]   [0..+100%]
              |            ¦      + ¦    _____                  _________
              |  __________V_       ¦   ¦    _¦       __       ¦PWM pour ¦  pos
cons          | ¦            ¦ur +  V   ¦   / ¦ ucm  ¦  ¦u_pc  ¦pont H + ¦ [imp]
-----+----->O-->¦  Reg. PID  ¦----->O-->¦  /  ¦----->¦  ¦----->¦système  ¦---+-->
[tour]      ^   ¦____________¦          ¦_/   ¦      ¦__¦      ¦à régler ¦  _¦___
          - ¦                           ¦_____¦                ¦_________¦ ¦conv.¦
            ¦                                                              ¦_____¦
            ¦                                                                ¦
            ¦                                                                |
            ¦                                                                ¦
            ¦                                                                ¦
            ¦                                                                ¦
            ¦                                                                |
            ¦                                                                ¦
            ¦                                                                ¦
            ¦<----------------------------------------------------------------
                                       mesure [tour]





  	//consigne cyclique
  	compt++;
  	if (compt==1000) {
  		compt=0;
  		if (cons_t==0.0) cons_t=0.5; else cons_t=0.0;
  	}
*/
  	//////////////////////Régulateur PID Auto-ajustabe/////////////////////////////////

  	if(Kp==0 && Ki==0 && Kd==0 && b==0)   // test si les paramètres ont déjà été calculé
  	    {
  	        CalcParam();
  	    }


  	else
  	    {
            RegPID();
  	    }

  	// limitation
  	if (ucm>uclim)  {
	    ucm = uclim;            // Limitation positive
	    }
	    else if (ucm<-uclim) {
	    ucm = -uclim;           // Limitation négative
		}
  	// commande limitée en %
  	ucm_pc = (int)(ucm * 100);

	// Commande PWM [0..100%] du pontH n°1 qui utilise les branches 1 et 2: 
	u_pc = (ucm_pc+100) / 2;
    Set_Pwm_Duty(1,u_pc); 
	Set_Pwm_Duty(2,u_pc); 

	// Sorties analogiques pour mesures à l'oscilloscope:
  	DAC_SetChannelVolt(1 , 5*cons_t);	   	// Sortie 1 (consigne où 1[pu] = 5V)
  	DAC_SetChannelVolt(2 , 5*mesure_t[0]);	// Sortie 2 (position où 1[pu] = 5V)
  	DAC_SetChannelVolt(3 , 5*consigneReg);  // Sortie 3 (consigne où 1[pu] = 5V)


}
