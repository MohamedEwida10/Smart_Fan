/* 
 * File:   hal_Timer3.h
 * Author: Blu-Ray
 *
 * Created on June 26, 2024, 2:16 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
/******************* Section : Macro Declarations *******************/
#define Timer3_counter_mode     1
#define Timer3_timer_mode       0

#define Timer3_ASYNC_counter_mode      1
#define Timer3_SYNC_counter_mode       0

#define Timer3_RW_REG_8bit_MODE     0
#define Timer3_RW_REG_16bit_MODE    1

#define TIMER3_Prescaler_div_by_1  0
#define TIMER3_Prescaler_div_by_2  1
#define TIMER3_Prescaler_div_by_4  2
#define TIMER3_Prescaler_div_by_8  3 

/******************* Section : Macro Functions Declarations *******************/
#define Timer3_module_Enable()  (T3CONbits.TMR3ON = 1)
#define Timer3_module_Disable() (T3CONbits.TMR3ON = 0)

#define Timer3_timer_mode_enable()    (T3CONbits.TMR3CS = 0)
#define Timer3_counter_mode_enable()  (T3CONbits.TMR3CS = 1)

#define Timer3_ASYNC_counter_mode_enable()    (T3CONbits.T3SYNC = 1)
#define Timer3_SYNC_counter_mode_enable()     (T3CONbits.T3SYNC = 0)

#define Timer3_Set_Prescaler_Value(_config) (T3CONbits.T3CKPS = _config)

#define Timer3_RW_REG_8bit_MODE_enable()  (T3CONbits.RD16 = 0)
#define Timer3_RW_REG_16bit_MODE_enable() (T3CONbits.RD16 = 1)

/******************* Section : MacroData Type Declarations *******************/
typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR3_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg priority;
#endif  
    uint16 timer3_prelaod_value; 
    uint8 Prescaler_Value:2;    
    uint8 timer3_mode :1 ;
    uint8 timer3_counter_mode :1 ;   
    uint8 timer3_reg_rw_mode :1 ;
    uint8 timer3_reserved :3 ;
}TIMER3_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType Timer3_Init(const TIMER3_t *_timer);
STD_ReturnType Timer3_DeInit(const TIMER3_t *_timer);
STD_ReturnType Timer3_Write_Value(const TIMER3_t *_timer,uint16 _value);
STD_ReturnType Timer3_Read_Value(const TIMER3_t *_timer,uint16 *_value);



#endif	/* HAL_TIMER3_H */

