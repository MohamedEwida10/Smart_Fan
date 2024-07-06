/* 
 * File:   ecu_layer_init.h
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 9:11 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H



/******************* Section : Includes *******************/
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "DC_motor/ecu_DC_motor.h"
#include "7_segment/ecu_seven_segment.h"
#include "Keypad/ecu_keypad.h"
#include "chr_LCD/ecu_chr_LCD.h"
#include "../MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "../MCAL_layer/EEPROM/hal_eeprom.h"
#include "../MCAL_layer/ADC/hal_adc.h"
#include "../MCAL_layer/Timer/hal_timer0.h"
#include "../MCAL_layer/TIMER1/hal_Timer1.h"
#include "../MCAL_layer/TIMER2/hal_Timer2.h"
#include "../MCAL_layer/TIMER3/hal_Timer3.h"
#include "../MCAL_layer/CCP1/hal_ccp.h"
/******************* Section : Macro Declarations *******************/
extern chr_lcd_4bit_t LCD;
extern adc_conf_t LM_35;
extern dc_motor_t motor;
extern TIMER2_t timer2_obj;
extern TIMER3_t timer3_obj;
extern ccp_t ccp1_obj;
extern keypad_t keypad;
extern button_t btn_mode_changer;
/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/


/******************* Section : Functions Declarations *******************/
void ecu_layer_Initialization(void);


#endif	/* ECU_LAYER_INIT_H */

