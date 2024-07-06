/* 
 * File:   application.h
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 21, 2023, 9:50 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H


/******************* Section : Includes *******************/
#include "ECU_layer/ecu_layer_init.h"
#include "MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "Helper_functions/helper_fn.h"
#include "MCAL_layer/Timer/hal_timer0.h"
#include "MCAL_layer/TIMER1/hal_Timer1.h"
#include "MCAL_layer/TIMER2/hal_Timer2.h"
#include "MCAL_layer/TIMER3/hal_Timer3.h"
#include "MCAL_layer/CCP1/hal_ccp.h"
/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/

/******************* Section : Functions Declarations *******************/
void Application_Initialization(void);




#endif	/* APPLICATION_H */

