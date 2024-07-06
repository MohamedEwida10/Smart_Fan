/* 
 * File:   hal_Timer2.h
 * Author: Blu-Ray
 *
 * Created on June 26, 2024, 2:16 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/******************* Section : Macro Declarations *******************/
#define TIMER2_Prescaler_div_by_1   0
#define TIMER2_Prescaler_div_by_4   1
#define TIMER2_Prescaler_div_by_16  2 

#define TIMER2_Postscaler_div_by_1    0
#define TIMER2_Postscaler_div_by_2    1
#define TIMER2_Postscaler_div_by_3    2 
#define TIMER2_Postscaler_div_by_4    3 
#define TIMER2_Postscaler_div_by_5    4
#define TIMER2_Postscaler_div_by_6    5 
#define TIMER2_Postscaler_div_by_7    6
#define TIMER2_Postscaler_div_by_8    7
#define TIMER2_Postscaler_div_by_9    8 
#define TIMER2_Postscaler_div_by_10   9
#define TIMER2_Postscaler_div_by_11   10
#define TIMER2_Postscaler_div_by_12   11
#define TIMER2_Postscaler_div_by_13   12 
#define TIMER2_Postscaler_div_by_14   13
#define TIMER2_Postscaler_div_by_15   14
#define TIMER2_Postscaler_div_by_16   15

/******************* Section : Macro Functions Declarations *******************/
#define Timer2_module_Enable()  (T2CONbits.TMR2ON = 1)
#define Timer2_module_Disable() (T2CONbits.TMR2ON = 0)

#define Timer2_Set_Prescaler_Value(_config) (T2CONbits.T2CKPS = _config)

#define Timer2_Set_Postscaler_Value(_config) (T2CONbits.TOUTPS = _config)

/******************* Section : MacroData Type Declarations *******************/
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR2_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg priority;
#endif   
    uint8 timer2_prelaod_value; 
    uint8 Postscaler_Value:4;
    uint8 Prescaler_Value :2;     
    uint8 timer2_reserved :2;
}TIMER2_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType Timer2_Init(const TIMER2_t *_timer);
STD_ReturnType Timer2_DeInit(const TIMER2_t *_timer);
STD_ReturnType Timer2_Write_Value(const TIMER2_t *_timer,uint8 _value);
STD_ReturnType Timer2_Read_Value(const TIMER2_t *_timer,uint8 *_value);
#endif	/* HAL_TIMER2_H */

