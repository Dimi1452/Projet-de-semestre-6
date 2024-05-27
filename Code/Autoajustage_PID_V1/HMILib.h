/** \file HMILib.h
* \brief Header of HMILib.h
* \author Sylvain Decastel
* \date 06.2009
*/


#ifndef __HMILIB_H
#define __HMILIB_H     

#include "bool.h"

/*----------------------------------------------------------+
|                         TYPES                             |
+----------------------------------------------------------*/

/** \brief Struct to access the 4 switchs of the HMI Interface
*
*/
typedef union
{
	struct 
	{
		unsigned char SW1:1;
		unsigned char SW2:1;
		unsigned char SW3:1;
		unsigned char SW4:1;
		unsigned char SWROT:1;
		unsigned char reserved:3;
	}bits;
	unsigned char byte;
}SwitchState_T;

/** \brief Enum that define the 4 colors of the LEDs
*/
typedef enum
{
	LED_Off,
	LED_Green, 
	LED_Red,
	LED_Yellow
}LED_Color_T;


/*----------------------------------------------------------+
|                      GLOBAL VARS                          |
+----------------------------------------------------------*/

#ifdef __MAIN

SwitchState_T	HMISwitchs; /**< \brief State of the HMI Switchs */
int				HMIRotCounter = 0; /**< \brief State of the rotactor counter */
bool			HMIEventFlag = false; /**< \brief Flag to signal a event on the HMI interface */

#else

extern SwitchState_T	HMISwitchs;
extern int				HMIRotCounter;
extern bool				HMIEventFlag;

#endif


/*----------------------------------------------------------+
|                      GLOBAL VARS                          |
+----------------------------------------------------------*/

/** \brief Init the HMI interface 
*
* This function init the HMI card :
* - Resets the rotactor counter
* - Turns all the LED off
* - clears the LCD
*/
void HMILib_Init(void);

/** \brief Background task to manage the HMI interface
*
* This function must be called periodically in the system idle loop. 
* It checks for new incoming frame and update global variables if 
* necessary.
*/
void HMILib_Background(void);

/** \brief Send the command to clear the LCD display
*
* \attention The clear action need some time, wait a moment before sending new text to the display
*/
void LCD_Clear(void);
/** \brief Clear the selected line of the display
*
* \param[in] line Nb of the line to clear, 1 to 4
*/
void LCD_ClearLine(unsigned char line);
/** \brief Set the options of the LCD display
* 
* \param[in] enableCursor If true : The cursor is visible on the display
* \param[in] enableBlink  If true : The cursor is blinking
*/
void LCD_SetOptions(bool enableCursor, bool enableBlink);
/** \brief Set the position of the cursor on the LCD display
*
* \param[in] line Nb of the line to position the cursor, 1 to 4
* \param[in] col Nb of the column to position the cursor, 1 to 20
* \attention If the line nb or the column nb are out of bounds, the cursor is not moved 
*/
void LCD_SetPosition(unsigned char line, unsigned char col);
/** \brief Send a string to write on the LCD at the current cursor position
*
* \param[in] str String to display
* \param[in] strLength length of the string
* \attention If the string is too long for the line, result is unpredictable !
*/
void LCD_WriteString(char* str, unsigned int length);
/** \brief Send a string to write on the LCD display at a specified position
*
* \param[in] line Nb of the line to write text
* \param[in] col Nb of the column to begin to write text
* \param[in] str String to display
* \param[in] strLength length of the string
* \attention If the string is too long for the line, result is unpredictable !
*/
void LCD_WriteStringPos(unsigned char line, unsigned char col, char* str, unsigned int length);

/** \brief This function convert an integer to an ASCII string an write it on the LCD at the current cursor position
*
* \param[in] var Integer to display
*/
void LCD_WriteInt(int var);
/** \brief This function convert an integer to an ASCII string an write it on the LCD at a specified position
*
* \param[in] line Nb of the line to display the integer
* \param[in] col Nb of the column to display the integer
* \param[in] var Value of the integer to display
*/
void LCD_WriteIntPos(unsigned char line, unsigned char col, int var);

/** \brief This function convert an integer to an ASCII string an write it on the LCD at the current cursor position
*
* \param[in] var Integer to display
*/
void LCD_WriteFloat(float var);

/** \brief This function convert an float to an ASCII string an write it on the LCD at a specified position
*
* \param[in] line Nb of the line to display the integer
* \param[in] col Nb of the column to display the integer
* \param[in] var Value of the float to display
*/
void LCD_WriteFloatPos(unsigned char line, unsigned char col, float var);


/** \brief Enable or disable the auto send function of the rotactor on the HMI interface
*
* \param[in] enableAutoSend If true, enable the auto send of the rotactor value if it changes
*/
void ROT_SetOptions(bool enableAutoSend);
/** \brief Set the counter value of the rotactor on the HMI interface
* 
* \param[in] counter New value of the counter
*/
void ROT_SetCounter(int counter);
/** \brief Get the actual value of the rotactor counter, the value is update in the global var
*/
void  ROT_UpdateCounter(void);

/** \brief Enable or disable the auto send function of the switchs on the HMI interface
* 
* \param[in] enableAutoSend If true, enable the auto send function
*/
void SWITCH_SetOptions(bool enableAutoSend);
/** \brief Ask for an update of the switch's value.
*
* The new value is update via the global vars
*/
void SWITCH_Update(void);

/** \brief Set the color of one LED
* 
* \param[in] LED_No No of the LED to change, 1..4
* \param[in] color Color of the LED
*/
void LED_SetOneLED(unsigned char LED_No, LED_Color_T color);
/** \brief Set the color of the 4 LEDs
*
* \param[in] colors Colors of the 4 LEDs, tab of size 4 !
*/
void LED_SetLEDs(LED_Color_T* colors); // tab of 4 leds !
/** \brief Turn all the LED off
*/
void LED_AllOff(void);
/** \brief Turn all the LED on
*/
void LED_AllOn(void);


/** \brief The buzzer beeps
*
* \param[in] time_ms Duration of the beep in ms
*/
void BUZZER_Beep(unsigned int time_ms);

#endif
