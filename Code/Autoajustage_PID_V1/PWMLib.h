/** \file PWMLib.h
* \brief Definitions of the functions to control the PWM modules of the tms 28335
* \author Florian Berset
* \date 06.2009
*/
#ifndef __PWMLIB_H
#define __PWMLIB_H

/** \brief Init the PWM outputs with the values set in Configuration.h
*/
void ConfigPwm(void);

/** \brief Set the PWM frequency of the selected branch
*
* \param[in] Branch No of the branch to set up, 1..6
* \param[in] Value Value of the frequency in kHz (integer only)
*/
void Set_Pwm_Freq(int Branch, int Value);

/** \brief Set the duty cycle of the selected branch
*
* \param[in] Branch No of the branch to set up, 1..6
* \param[in] Value Value of the duty cycle in % (integer only)
*/
void Set_Pwm_Duty(int Branch, int Value);

/** \brief Set the PWM phase of the selected branch
*
* \param[in] Branch No of the branch to set up, 1..6
* \param[in] Value Value of the phase shift, in radian ?? 
*
* \todo This function must be tested and better described !! 
*/
void Set_Pwm_Phase(int Branch, int Value);

/** \brief Set the dead time between the 2 PWM signals of the same branch
*
* \param[in] Branch No of the branch to set up, 1..6
* \param[in] Value Value of the dead time, between 100 and 1000 depending the output frequency
*/
void Set_Pwm_DeadTime(int Branch, int Value);
#endif
