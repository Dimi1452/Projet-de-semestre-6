/** \file configuration.h
* \brief Configuration set by the user to enable or disable some features
* \author Kneuss André
* \date 11.2010
*/

#include "GenericIncludes.h"

// declare variables in main.c file, declare as extern in other files
#ifdef __MAIN

/*-----------------------------------------------------------+
|                       VARIABLES                            |
+-----------------------------------------------------------*/
// Pour activer une fonction il faut mettre à '1' la variable appropriée.
// Par exemple, pour activer le PontH_1 il faut mettre "PontH_ELMERE1 = 1;"
//
// Il est possible d'activer plusieurs fonctionnalités en parallèle
// selon le tableau ci-dessous :
//
//
//	   		   | Ond_1	| Ond_2	| PtH_EL_1	| PtH_EL_2	| PtH_EL_3	| PtH_OND_1	| PtH_OND_2 |
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  Ond_1	   |--------|	X	|		    |	 X	    |		    |           |     X     | Ond_1 et Ond_2 ou Ond_1 et PtH_EL_2 ou Ond_1 et PtH_OND2
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  Ond_2	   |   X	|-------|	 X	    |      		|    		|     X     |           | Ond_2 et Ond_1 ou Ond_2 et PtH_EL1 ou Ond_2 et PtH_OND_1
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  PtH_EL_1 | 		|	X	|-----------|	 X	    |	  X	    |           |     X     | PtH_EL_1 et PtH_EL_2 et PtH_EL_3 ou PtH_EL_1 et Ond_2 ou PtH_EL_1 et PtH_OND2
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  PtH_EL_2 |   X	|		|	 X	    |-----------|	  X	    |     X     |           | PtH_EL_2 et PtH_EL_1 et PtH_EL_3 ou PtH_EL_2 et Ond_1 ou PtH_EL_2 et PtH_OND1
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  PtH_EL_3 | 		|		|	 X	    |	 X	    |-----------|           |           | PtH_EL_3 et PtH_EL_1 et PtH_EL_2 
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  PtH_OND_1|    	|	X	|		    |	 X	    |           |-----------|     X     | PtH_OND_1 et Ond_2 ou PtH_OND_1 et PtH_EL_2 ou PtH_OND_1 et PtH_OND_2
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
//	  PtH_OND_2|   X	|		|	 X	    |	  	    |           |     X     |-----------| PtH_OND_2 et Ond_1 ou PtH_OND_2 et PtH_EL_1 ou PtH_OND_2 et PtH_OND_1
//	  ---------|--------|-------|-----------|-----------|-----------|-----------|-----------|
 
const Uint16	Onduleur_1		= 0; /**< \brief Set to 1 to enable the Onduleur_1 signals */ 
const Uint16	Onduleur_2		= 0; /**< \brief Set to 1 to enable the Onduleur_2 signals */
const Uint16	PontH_ELMERE_1	= 1; /**< \brief Set to 1 to enable the H-Bridge 1 signals */
const Uint16	PontH_ELMERE_2	= 1; /**< \brief Set to 1 to enable the H-Bridge 2 signals */
const Uint16	PontH_ELMERE_3	= 1; /**< \brief Set to 1 to enable the H-Bridge 3 signals */
const Uint16	PontH_OND_1		= 0; /**< \brief Set to 1 to enable the H-Bridge 3 signals */
const Uint16	PontH_OND_2		= 0; /**< \brief Set to 1 to enable the H-Bridge 3 signals */


int PWM_freq         = 20;       /**< \brief Set the frequency of the PWM output signals in kHz */
int PWM_duty         = 75;       /**< \brief Set the duty cycle of the PWM output signals in % */
int PWM_phase        = 0;        /**< \brief Set the phase between the PWM signals \attention Be careful, read the documentation !! */
int PWM_deadtime     = 0;        /**< \brief Set the deadtime of the PWM signals, try to set betwee 100 and 1000 */


//============================================================================
#else

extern const float Period_Interrupt;		// Time in [us]
extern const Uint16	Onduleur_1;
extern const Uint16	Onduleur_2;
extern const Uint16	PontH_ELMERE_1;
extern const Uint16	PontH_ELMERE_2;
extern const Uint16	PontH_ELMERE_3;
extern const Uint16	PontH_OND_1;
extern const Uint16	PontH_OND_2;

//============================================================================
extern int PWM_freq;
extern int PWM_duty;
extern int PWM_phase;
extern int PWM_deadtime;


#endif



