/* 
 * File:   hal_timer0.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on April 25, 2024, 11:42 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******************* Section : Macro Declarations *******************/
#define Timer0_Prescaler_enable_cfg    1
#define Timer0_Prescaler_disable_cfg   0

#define Timer0_RisingEdge_cfg    1
#define Timer0_FallingEdge_cfg   0

#define Timer0_timer_mode     1
#define Timer0_counter_mode   0

#define Timer0_8bit_register_mode     1
#define Timer0_16bit_register_mode    0

/******************* Section : Macro Functions Declarations *******************/
#define Timer0_module_Enable()  (T0CONbits.TMR0ON = 1)
#define Timer0_module_Disable() (T0CONbits.TMR0ON = 0)

#define Timer0_8BIT_register_mode_enable()  (T0CONbits.T08BIT = 1)
#define Timer0_16BIT_register_mode_enable() (T0CONbits.T08BIT = 0)

#define Timer0_timer_mode_enable()    (T0CONbits.T0CS = 0)
#define Timer0_counter_mode_enable()  (T0CONbits.T0CS = 1)

#define Timer0_FallingEdge_enable()  (T0CONbits.T0SE = 1)
#define Timer0_RisingEdge_enable()   (T0CONbits.T0SE = 0)

#define Timer0_Prescaler_disable()     (T0CONbits.PSA = 1)
#define Timer0_Prescaler_enable()      (T0CONbits.PSA = 0)

#define Timer0_Set_Prescaler_Value(_config) (T0CONbits.T0PS = _config)

/******************* Section : MacroData Type Declarations *******************/
typedef enum{
    TIMER0_Prescaler_div_by_2 = 0,
    TIMER0_Prescaler_div_by_4,
    TIMER0_Prescaler_div_by_8,
    TIMER0_Prescaler_div_by_16,
    TIMER0_Prescaler_div_by_32,
    TIMER0_Prescaler_div_by_64,
    TIMER0_Prescaler_div_by_128,
    TIMER0_Prescaler_div_by_256,          
}Timer0_Prescaler_Select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR0_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg priority;
#endif 
    Timer0_Prescaler_Select_t  Prescaler_Value;
    uint16 timer0_prelaod_value;
    uint8 Prescaler_enable :1 ;
    uint8 timer0_counter_edge :1 ;
    uint8 timer0_mode :1 ;
    uint8 timer0_register_size :1 ;
    uint8 timer0_reserved :4 ;
     
}TIMER0_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType Timer0_Init(const TIMER0_t *_timer);
STD_ReturnType Timer0_DeInit(const TIMER0_t *_timer);
STD_ReturnType Timer0_Write_Value(const TIMER0_t *_timer,uint16 _value);
STD_ReturnType Timer0_Read_Value(const TIMER0_t *_timer,uint16 *_value);

#endif	/* HAL_TIMER0_H */

