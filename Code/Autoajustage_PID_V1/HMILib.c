/** \file HMILib.c
* \brief Library to use the Delfino HMI card
* \author Sylvain Decastel
* \date 06.2009
*/

#include "PeripheralHeaderIncludes.h"
#include "UARTBLib.h"
#include "HMILib.h"
#include "stdio.h"

/*-----------------------------------------------------------+
|                       CONSTANTS                            |
+-----------------------------------------------------------*/

#define HMI_DATA_MAX_LENGTH     25  /**< \brief max length of the data frames */

/** \name Control bytes
* Control bytes for the HMI UART interface 
*/
// @{
#define SOH   0x01    /**< \brief Start of header */
#define STX   0x02    /**< \brief Start Of Text */
#define ETX   0x03    /**< \brief End Of Text */
#define DLE   0x10    /**< \brief Data Link Escape */
#define ACK   0x06    /**< \brief Acknowledgement */
#define NAK   0x15    /**< \brief Negative Acknowledgement */
//@}

/** \name Header bytes
* Header of the HMI UART frames
*/
// @{
#define H_LCD       'L' /**< \brief LCD cotrol frame */
#define H_Text      'T' /**< \brief LCD write text frame */
#define H_Buzzer    'B' /**< \brief Buzzer beep frame */
#define H_Rot       'R' /**< \brief Rotactor control frame */
#define H_LED       'E' /**< \brief LED control frame */
#define H_Switchs   'S' /**< \brief Switchs control frame */


/*-----------------------------------------------------------+
|                        MACROS                              |
+-----------------------------------------------------------*/
//@{
/** \brief Macro to select UART interface (A or B) */
#define UART_Send       UARTB_Send      
#define UART_GetChar    UARTB_GetChar   
//@}

/*-----------------------------------------------------------+
|                         TYPES                              |
+-----------------------------------------------------------*/

/** \brief Structure to access the fields of the HMI interface frames
*/
typedef struct
{
	char header;                    /**< \brief Header */
	char data[HMI_DATA_MAX_LENGTH]; /**< \brief Data */
	unsigned char length;           /**< \brief Length of the valid data */
}HMI_Frame_T;

/*-----------------------------------------------------------+
|                         VARIABLES                          |
+-----------------------------------------------------------*/

static HMI_Frame_T HMI_FrameSend;   /**< \brief Buffer for the next frame to send */
static HMI_Frame_T HMI_FrameReceive;/**< \brief Buffer for the last received frame */


static bool DLEFlag = false;        /**< \brief Flag to manage the DLE char */
static bool NewFrameFlag = false;   /**< \brief Flag to send the event for a new frame */

/** \brief States for the receive state machine */
static enum{
waitSOH,    /**< Waiting the Start Of Header byte */
getHeader,  /**< Receiving the header */
waitSTX,    /**< Waiting the Start Of Text byte */
getData     /**< Receiving the data and checking for End Of Text byte */
}decodeState = waitSOH;



/*-----------------------------------------------------------+
|                         PROTOTYPES                         |
+-----------------------------------------------------------*/
void sendFrame(HMI_Frame_T frame);
void receiveFrame(void);
void decodeFrame(void);



/*-----------------------------------------------------------+
|                         FUNCTIONS                          |
+-----------------------------------------------------------*/

/** \brief Init the HMI interface 
*
* This function init the HMI card :
* - Resets the rotactor counter
* - Turns all the LED off
* - clears the LCD
* 
* \author Sylvain Decastel
* \date 06.2009
*/

void HMILib_Init(void)
{
	LCD_Clear();	// too long !!
	LCD_SetOptions(false,false);

	ROT_SetCounter(0);
	LED_AllOff();
}



/** \brief Background task to manage the HMI interface
*
* This function must be called periodically in the system idle loop. 
* It checks for new incoming frame and update global variables if 
* necessary.
*
* \author Sylvain Decastel
* \date 06.2009
*/
void HMILib_Background(void)
{

	receiveFrame();

	if(NewFrameFlag == true)
	{
		NewFrameFlag = false;

		decodeFrame();
	}

}

/** \brief State machine for receiving frame from the HMI interface
*
* This function checks if there are new char in the UART receive buffer and 
* get them. The state machine wait for the "start of header" char and begin
* a new reception. The global flag NewFrameFlag is set if a new valid frame
* has been received.
*
* \author Sylvain Decastel
* \date 06.2009
*/
void receiveFrame(void)
{

	char c;

	while(UART_GetChar(&c) == true)
	{
    
	    if(DLEFlag == false && c == DLE)
	    {
	      DLEFlag = true;
	      continue;
	    }
    
	    // detect SOH
	    if(DLEFlag == false && c == SOH)
	    {
	      decodeState = getHeader;
	      continue;
	    }
  
    	switch(decodeState)
    	{
		    default:
			decodeState = waitSOH;
			
		    case waitSOH:
		    {
		        if(DLEFlag == false && c == SOH)
		        {
		          // yeah ! go to get header
		          decodeState = getHeader;
		        }
		        
		 	}break;
	      
	    	case getHeader:
	      	{
		        // only one char !
		        if(DLEFlag == false && (c == STX || c == ETX))
		        {
		          // error ! return to waitSOH
		          decodeState = waitSOH;
		        }
		        else
		        {
		          // get header
		          HMI_FrameReceive.header = c;
		          // go to wait STX
		          decodeState = waitSTX;
		        }
	      	}break;
      
		    case waitSTX:
		    {
		        // this char MUST be STX
		        if(DLEFlag == false && c != STX)
		        {
		          // return to waitSOH
		          decodeState = waitSOH;
		        }
		        else
		        {
		          // go to get data
		          decodeState = getData;
		          // reset length 
		          HMI_FrameReceive.length = 0;
		        }
	        
	      	}break;
      
	    	case getData:
	      	{
		        if(DLEFlag == false && c == ETX)
		        {
		          // end of text detected ! go to endOfFrame
		          	          
		          // set new frame flag
		          NewFrameFlag = true;
		          
		          // return to waitSOH
		          decodeState = waitSOH;
		          
		        }
		        else if(HMI_FrameReceive.length >= HMI_DATA_MAX_LENGTH)
		        {
		          // error !! frame too long
		          // return to waitSOH
		          decodeState = waitSOH;
		        }
		        else
		        {
		          // get next char
		          HMI_FrameReceive.data[HMI_FrameReceive.length] = c;
		          HMI_FrameReceive.length++;
		        }          
	     	}break;
   	 	}
    
	    // clear DLE Flag !
	    if(DLEFlag == true)
	      DLEFlag = false;
  	}
}

/** \brief Decode the new valid frame and execute the correct action
*
* This function is called in the HMILib_Background() function directly after
* the receiveFrame() function if a new valid frame has been received. The new valid
* frame is in the global variable HMI_FrameReceive. The frame is decoded and if needed
* an action is done.
*
* \author Sylvain Decastel
* \date 06.2009
*/
void decodeFrame(void)
{


	// frame from rotactor
	if(HMI_FrameReceive.header == 'R' && \
	HMI_FrameReceive.length == 3 && \
	HMI_FrameReceive.data[0] == '4')
	{
		// low in data[1] / high byte in data[2]
		HMIRotCounter = HMI_FrameReceive.data[1] + (HMI_FrameReceive.data[2] << 8);
	}

	//frame from switch
	if(HMI_FrameReceive.header == 'S' && \
	HMI_FrameReceive.length == 2 && \
	HMI_FrameReceive.data[0] == '3') // for now only support hexa format !
	{
		unsigned char bitmask = 0x01;
		int i;


		for(i=0; i<5; i++)
		{
			if(HMI_FrameReceive.data[1] & bitmask)
			{
				// set the correpsonding bit
				HMISwitchs.byte |= bitmask;
			}
			else
			{
				// clear the correpsonding bit
				HMISwitchs.byte &= ~bitmask;				
			}
			
			// next bit
			bitmask = bitmask << 1;
		}		

	}

}

/** \brief Send the command to clear the LCD display
*
* \author Sylvain Decastel
* \date 06.2009
* \attention The clear action need some time, wait a moment before sending new text to the display
*/
void LCD_Clear(void)
{
    HMI_FrameSend.header = H_LCD;
    HMI_FrameSend.data[0] = '1';
    HMI_FrameSend.length = 1;
    sendFrame(HMI_FrameSend);
}

/** \brief Clear the selected line of the display
*
* \param[in] line Nb of the line to clear, 1 to 4
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_ClearLine(unsigned char line)
{
	HMI_FrameSend.header = H_LCD;
	HMI_FrameSend.data[0] = '2';
	HMI_FrameSend.data[1] = line;
	HMI_FrameSend.length = 2;

	sendFrame(HMI_FrameSend);

}

/** \brief Set the position of the cursor on the LCD display
*
* \param[in] line Nb of the line to position the cursor, 1 to 4
* \param[in] col Nb of the column to position the cursor, 1 to 20
* \attention If the line nb or the column nb are out of bounds, the cursor is not moved 
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_SetPosition(unsigned char line, unsigned char col)
{
	// check parameters
	if(line == 0 || line > 4 || col == 0 || col > 20)
		return;

	HMI_FrameSend.header  = H_LCD;
	HMI_FrameSend.data[0] = '3';
	HMI_FrameSend.data[1] = line;
	HMI_FrameSend.data[2] = col;
	HMI_FrameSend.length  = 3;

	sendFrame(HMI_FrameSend);
}

/** \brief Set the options of the LCD display
* 
* \param[in] enableCursor If true : The cursor is visible on the display
* \param[in] enableBlink  If true : The cursor is blinking
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_SetOptions(bool enableCursor, bool enableBlink)
{
	HMI_FrameSend.header = H_LCD;
	HMI_FrameSend.data[0] = '4';

	if(enableCursor == true)
		HMI_FrameSend.data[1] = 0xFF;
	else
		HMI_FrameSend.data[1] = 0x00;

	if(enableBlink == true)
		HMI_FrameSend.data[2] = 0xFF;
	else
		HMI_FrameSend.data[2] = 0x00;

	HMI_FrameSend.length = 3;

	sendFrame(HMI_FrameSend);

}

/** \brief Send a string to write on the LCD at the current cursor position
*
* \param[in] str String to display
* \param[in] strLength length of the string
* \attention If the string is too long for the line, result is unpredictable !
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_WriteString(char* str, unsigned int strLength)
{
	char* ptr = &HMI_FrameSend.data[1]; // 1st char is command

	if(strLength == 0)
		return;

	HMI_FrameSend.header = H_Text;
	HMI_FrameSend.length = strLength+1; // +1 = command
	HMI_FrameSend.data[0] = '1';
	
	while(strLength-- > 0)
		*ptr++ = *str++;

	sendFrame(HMI_FrameSend);

}

/** \brief Send a string to write on the LCD display at a specified position
*
* \param[in] line Nb of the line to write text
* \param[in] col Nb of the column to begin to write text
* \param[in] str String to display
* \param[in] strLength length of the string
* \attention If the string is too long for the line, result is unpredictable !
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_WriteStringPos(unsigned char line, unsigned char col, char* str, unsigned int strLength)
{
	char* ptr;

	// check parameters
	if(line == 0 || line > 4 || col == 0 || col > 20 || strLength == 0)
		return;

	HMI_FrameSend.header = H_Text;
	HMI_FrameSend.length = strLength+3; // + 3 = command + line + col
	HMI_FrameSend.data[0] = '2';
	HMI_FrameSend.data[1] = line;
	HMI_FrameSend.data[2] = col;
	ptr = &HMI_FrameSend.data[3];
	
	while(strLength-- > 0)
		*ptr++ = *str++;

	sendFrame(HMI_FrameSend);

}

/** \brief This function convert an integer number to an ASCII string ready to be send to the display !
*
* \param[in] var Integer to convert
* \param[out] string Pointer to the result string buffer
*
* \author Sylvain Decastel
* \date 06.2009
*/
void IntToString(int var, char* string)
{
	unsigned int divider;
	int digits;
	char *stringPtr;
	char testNeg;

// integer max = 32768
// test number of digit to display
	digits = 5;
	divider = 10000;
	testNeg = 0;

// test if number is negative
	if(var < 0)
	{
		testNeg = 1;
		var = -var;
	}

	while(var/divider == 0)
	{
		// decrement digit
		digits--;

		// number is not so big
		divider /= 10;
	}

	// test if number is 0
	if(digits == 0)
	{
		// print 0 
		string[0] = '0';
	}
	else // number is not 0 
	{
	// print '-' if number is negative
		if(testNeg == 1)
		{
			string[0] = '-';

			// init pointer 
			stringPtr = &string[digits];
		}
		else
		{
			// just init pointer
			stringPtr = &string[digits-1]; // string begins at pos 0

		}

		// begin from last digit
		while(digits-->0)
		{
			// convert next unit to ascii
			*stringPtr-- = var%10+'0';

			// next digit
			var /= 10;
		}
	}

}

/** \brief This function convert an integer to an ASCII string an write it on the LCD at the current cursor position
*
* \param[in] var Integer to display
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_WriteInt(int var)
{
	// int max size is 32768 or -32768 (5 digits)

	char string[6] = "      "; // 6 is max length with '-'

	IntToString(var, string);
	

	// display
	LCD_WriteString(string, 6);

}

/** \brief This function convert an integer to an ASCII string an write it on the LCD at a specified position
*
* \param[in] line Nb of the line to display the integer
* \param[in] col Nb of the column to display the integer
* \param[in] var Value of the integer to display
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LCD_WriteIntPos(unsigned char line, unsigned char col, int var)
{
	// int max size is 32768 or -32768 (5 digits)

	char string[6] = "      "; // 6 is max length with '-'

	IntToString(var, string);
	

	// display
	LCD_WriteStringPos(line, col, string, 6);
}



/** \brief This function convert an float to an ASCII string an write it on the LCD at the current cursor position
*
* \param[in] var Float to display
*
* \author Florian Berset
* \date 06.2009
*/
void LCD_WriteFloat(float var) // Ne pas utiliser pour le moment
{
	// int max size is 32768 or -32768 (5 digits)

	char string[7] = "       "; // 6 is max length with '-'
	
	//sprintf(string,"%03.02f",var);

	// display
	LCD_WriteString(string, 6);
}


/** \brief This function convert an float to an ASCII string an write it on the LCD at a specified position
*
* \param[in] line Nb of the line to display the integer
* \param[in] col Nb of the column to display the integer
* \param[in] var Value of the float to display
* \Permet d'afficher des float compris entre -999.99 -> 9999.99  // attention laisser un espace de minimum 3 caractères après le dernier chiffre affiché.
* \author Kneuss André
* \date 03.2010
*/
void LCD_WriteFloatPos(unsigned char line, unsigned char col, float var) // 
{

	char string1[5]="    ";
	char string2[6]="     ";
	
	int digits;
	
	int int1=0;
	int int2=0;

	int1=(int)var;

	int2=abs((int)((var-int1)*100.0));

	IntToString(int1, string1);
	IntToString(int2, string2);


	if(string1[1]==' '){digits=1;}
	else if(string1[2]==' '){digits=2;}
	else if(string1[3]==' '){digits=3;}
	else {digits=4;}


	LCD_WriteStringPos(line, col, string1, digits);
	LCD_WriteStringPos(line, col+digits, ".", 1);
	LCD_WriteStringPos(line, col+1+digits, string2, 5);

}


/** \brief Enable or disable the auto send function of the rotactor on the HMI interface
*
* \param[in] enableAutoSend If true, enable the auto send of the rotactor value if it changes
*
* \author Sylvain Decastel
* \date 06.2009
*
*/
void ROT_SetOptions(bool enableAutoSend)
{
	HMI_FrameSend.header = H_Rot;
	HMI_FrameSend.data[0] = '3';

	if(enableAutoSend == true)
		HMI_FrameSend.data[1] = 0xFF;
	else
		HMI_FrameSend.data[1] = 0x00;

	HMI_FrameSend.length = 2;

	sendFrame(HMI_FrameSend);
}

/** \brief Set the counter value of the rotactor on the HMI interface
* 
* \param[in] counter New value of the counter
*
* \author Sylvain Decastel
* \date 06.2009
*/
void ROT_SetCounter(int counter)
{

	HMI_FrameSend.header = H_Rot;
	HMI_FrameSend.data[0] = '1';

	// low byte first
	HMI_FrameSend.data[1] = (char)(0xFF & counter);
	// high byte
	HMI_FrameSend.data[2] = (char)((0xFF00 & counter)>>8);

	HMI_FrameSend.length = 3;

	sendFrame(HMI_FrameSend);
}

/** \brief Get the actual value of the rotactor counter, the value is update in the global var
* 
* \author Sylvain Decastel
* \date 06.2009
*/
void  ROT_UpdateCounter(void)
{
	HMI_FrameSend.header = H_Rot;
	HMI_FrameSend.data[0] = '2';
	HMI_FrameSend.length = 1;

	sendFrame(HMI_FrameSend);
}

/** \brief Enable or disable the auto send function of the switchs on the HMI interface
* 
* \param[in] enableAutoSend If true, enable the auto send function
*
* \author Sylvain Decastel
* \date 06.2009
*/
void SWITCH_SetOptions(bool enableAutoSend)
{
	HMI_FrameSend.header = H_Switchs;
	HMI_FrameSend.data[0] = '1';

	// auto send
	if(enableAutoSend == true)
		HMI_FrameSend.data[1] = 0xFF;
	else
		HMI_FrameSend.data[1] = 0x00;

	// format (set to ascii )
	HMI_FrameSend.data[2] = 0xFF;

	HMI_FrameSend.length = 3;

	sendFrame(HMI_FrameSend);
}

/** \brief Ask for an update of the switch's value.
*
* The new value is update via the global vars
* \author Sylvain Decastel
* \date 06.2009
*/
void SWITCH_Update(void)
{
	HMI_FrameSend.header = H_Switchs;
	HMI_FrameSend.data[0] = '2';
	HMI_FrameSend.length = 1;

	sendFrame(HMI_FrameSend);
}

/** \brief Set the color of one LED
* 
* \param[in] LED_No No of the LED to change, 1..4
* \param[in] color Color of the LED
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LED_SetOneLED(unsigned char LED_No, LED_Color_T color)
{
	HMI_FrameSend.header = H_LED;
	HMI_FrameSend.data[0] = '4';
	HMI_FrameSend.data[1] = LED_No;

	switch(color)
	{
		default:
		case LED_Off:
		{
			HMI_FrameSend.data[2] = 'O';
		}break;

		case LED_Green:
		{
			HMI_FrameSend.data[2]= 'G';
		}break;

		case LED_Red:
		{
			HMI_FrameSend.data[2] = 'R';
		}break;

		case LED_Yellow:
		{
			HMI_FrameSend.data[2] = 'Y';
		}break;
	}

	HMI_FrameSend.length = 3;

	sendFrame(HMI_FrameSend);
}

/** \brief Turn all the LED off
* 
* \author Sylvain Decastel
* \date 06.2009
*/
void LED_AllOff(void)
{
	HMI_FrameSend.header = H_LED;
	HMI_FrameSend.data[0] = '1';
	HMI_FrameSend.length = 1;

	sendFrame(HMI_FrameSend);

}

/** \brief Turn all the  on
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LED_AllOn(void)
{
	HMI_FrameSend.header = H_LED;
	HMI_FrameSend.data[0] = '2';
	HMI_FrameSend.length = 1;

	sendFrame(HMI_FrameSend);
}

/** \brief Set the color of the 4 LEDs
*
* \param[in] colors Colors of the 4 LEDs, tab of size 4 !
*
* \author Sylvain Decastel
* \date 06.2009
*/
void LED_SetLEDs(LED_Color_T* colors) // tab of 4 leds !
{
	unsigned int i;

	HMI_FrameSend.header = H_LED;
	HMI_FrameSend.data[0] = '3';
	HMI_FrameSend.length = 5;


	for(i=0; i<4; i++)
	{

		// data begins at i+1

		switch(colors[i])
		{
			default:
			case LED_Off:
			{
				HMI_FrameSend.data[i+1] = 'O';
			}break;

			case LED_Green:
			{
				HMI_FrameSend.data[i+1]= 'G';
			}break;

			case LED_Red:
			{
				HMI_FrameSend.data[i+1] = 'R';
			}break;

			case LED_Yellow:
			{
				HMI_FrameSend.data[i+1] = 'Y';
			}break;
		}
	}


	sendFrame(HMI_FrameSend);
}

/** \brief The buzzer beeps
* 
* \author Sylvain Decastel
* \date 06.2009
*/
void BUZZER_Beep(unsigned int time_ms)
{
	HMI_FrameSend.header = H_Buzzer;

	// low byte first
	HMI_FrameSend.data[0] = (char)(0xFF & time_ms);
	// high byte
	HMI_FrameSend.data[1] = (char)((0xFF00 & time_ms) >> 8);


	HMI_FrameSend.length = 2;

	sendFrame(HMI_FrameSend);
}


/** \brief Sends a frame to the HMI interface
*
* \param[in] frame Struct of the frame to send
*
* \author Sylvain Decastel
* \date 06.2009
*/
void sendFrame(HMI_Frame_T frame)
{
	char str[HMI_DATA_MAX_LENGTH+4]; // +4 : 1SOH, 1 STX, 1 ETX, 1 header
	char* ptr = frame.data;

	unsigned int frameLength;

	str[0] = SOH;
	str[1] = frame.header;
	str[2] = STX;

	frameLength = 3;
	
	while(frame.length-- > 0) 
	{
		// check if need of DLE
		if(*ptr == SOH || \
		*ptr == STX || \
		*ptr == ETX || \
		*ptr == DLE)
			str[frameLength++] = DLE;


		str[frameLength++] = *ptr++; 
	}

	str[frameLength++] = ETX; // increment i to have total length

	UART_Send(str, frameLength);
}
