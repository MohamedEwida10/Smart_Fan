/* 
 * File:   hal_Timer1.h
 * Author: Blu-Ray
 *
 * Created on June 24, 2024, 7:17 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/******************* Section : Macro Declarations *******************/

#define Timer1_counter_mode     1
#define Timer1_timer_mode       0

#define Timer1_ASYNC_counter_mode      1
#define Timer1_SYNC_counter_mode       0

#define Timer1_OSC_HW_enable        1
#define Timer1_OSC_HW_disable       0

#define Timer1_RW_REG_8bit_MODE     0
#define Timer1_RW_REG_16bit_MODE    1

#define TIMER1_Prescaler_div_by_1  0
#define TIMER1_Prescaler_div_by_2  1
#define TIMER1_Prescaler_div_by_4  2
#define TIMER1_Prescaler_div_by_8  3 

/******************* Section : Macro Functions Declarations *******************/
#define Timer1_module_Enable()  (T1CONbits.TMR1ON = 1)
#define Timer1_module_Disable() (T1CONbits.TMR1ON = 0)

#define Timer1_timer_mode_enable()    (T1CONbits.TMR1CS = 0)
#define Timer1_counter_mode_enable()  (T1CONbits.TMR1CS = 1)

#define Timer1_ASYNC_counter_mode_enable()    (T1CONbits.T1SYNC = 1)
#define Timer1_SYNC_counter_mode_enable()     (T1CONbits.T1SYNC = 0)

#define Timer1_OSC_HW_Enable()  (T1CONbits.T1OSCEN = 1)
#define Timer1_OSC_HW_Disable() (T1CONbits.T1OSCEN = 0)

#define Timer1_Set_Prescaler_Value(_config) (T1CONbits.T1CKPS = _config)

#define Timer1_system_clk_status()  (T1CONbits.T1RUN )

#define Timer1_RW_REG_8bit_MODE_enable()  (T1CONbits.RD16 = 0)
#define Timer1_RW_REG_16bit_MODE_enable() (T1CONbits.RD16 = 1)


/******************* Section : MacroData Type Declarations *******************/
typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TMR1_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg priority;
#endif  
    uint16 timer1_prelaod_value; 
    uint8 Prescaler_Value:2;    
    uint8 timer1_mode :1 ;
    uint8 timer1_counter_mode :1 ;
    uint8 timer1_osc_cfg :1 ;   
    uint8 timer1_reg_rw_mode :1 ;
    uint8 timer1_reserved :2 ;
}TIMER1_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType Timer1_Init(const TIMER1_t *_timer);
STD_ReturnType Timer1_DeInit(const TIMER1_t *_timer);
STD_ReturnType Timer1_Write_Value(const TIMER1_t *_timer,uint16 _value);
STD_ReturnType Timer1_Read_Value(const TIMER1_t *_timer,uint16 *_value);


#endif	/* HAL_TIMER1_H */

