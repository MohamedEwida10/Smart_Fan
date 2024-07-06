/* 
 * File:   hal_timer0.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on April 25, 2024, 11:42 AM
 */

#include "hal_timer0.h"

/********************************************************************/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR0_INTERRUPT_HANDLER)(void) = NULL;   
#endif
static uint16 Timer0_Prelaod = 0; 

/********************************************************************/
static inline void timer0_prescaler_config(const TIMER0_t *_timer);
static inline void timer0_mode_select(const TIMER0_t *_timer);
static inline void timer0_register_size_config(const TIMER0_t *_timer);
/********************************************************************/
STD_ReturnType Timer0_Init(const TIMER0_t *_timer){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer0_module_Disable();
        timer0_prescaler_config(_timer);
        timer0_mode_select(_timer);
        timer0_register_size_config(_timer);
        TMR0H = (_timer->timer0_prelaod_value) >> 8;
        TMR0L = (uint8)(_timer->timer0_prelaod_value);
        Timer0_Prelaod = _timer->timer0_prelaod_value;
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TMR0_INTERRUPT_HANDLER = _timer->TMR0_INTERRUPR_HANDLER;
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(Interrupt_HIGH_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptHighEnable();
                TIMER0_HighPrioritySet();
            }
            else if(Interrupt_LOW_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptLowEnable();
                TIMER0_LowPrioritySet();
            }
            else{/* nothing */}
            #else
            INTERRUPT_GlobalIterruptEnable();
            INTERRUPT_PeriphralInterruptEnable(); 
            #endif
        #endif

        Timer0_module_Enable();
    }

     return ret;  
}


STD_ReturnType Timer0_DeInit(const TIMER0_t *_timer){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer0_module_Disable();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE() ;
        #endif
    }

     return ret;  
    
}


STD_ReturnType Timer0_Write_Value(const TIMER0_t *_timer,uint16 _value){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
    }

     return ret;  
}


STD_ReturnType Timer0_Read_Value(const TIMER0_t *_timer,uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 l_tmr0l = 0,l_tmr0h = 0;
    if((NULL == _timer) || (NULL == _value) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_value = (uint16)((l_tmr0h << 8) + l_tmr0l);
    }

     return ret;  
}
/********************************************************************/
static inline void timer0_prescaler_config(const TIMER0_t *_timer){
    if(Timer0_Prescaler_enable_cfg == _timer->Prescaler_enable){
        Timer0_Prescaler_enable();
        T0CONbits.T0PS =(_timer->Prescaler_Value);
    }
    else if(Timer0_Prescaler_disable_cfg == _timer->Prescaler_enable){
         Timer0_Prescaler_disable();        
    }
    else{/* nothing */}
}

static inline void timer0_mode_select(const TIMER0_t *_timer){
    if(Timer0_timer_mode == _timer->timer0_mode){
        Timer0_timer_mode_enable();
    }
    else if(Timer0_counter_mode == _timer->timer0_mode){
        Timer0_counter_mode_enable();  
        if(Timer0_RisingEdge_cfg == _timer->timer0_counter_edge){
            Timer0_RisingEdge_enable();
        }
        else if(Timer0_FallingEdge_cfg == _timer->timer0_counter_edge){
            Timer0_FallingEdge_enable();
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

static inline void timer0_register_size_config(const TIMER0_t *_timer){
    if(Timer0_8bit_register_mode == _timer->timer0_register_size){
        Timer0_8BIT_register_mode_enable();
    }
    else if(Timer0_16bit_register_mode == _timer->timer0_register_size){
        Timer0_16BIT_register_mode_enable();
    }
    else{/* nothing */}
}

/********************************************************************/
void TMR0_ISR(void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (Timer0_Prelaod) >> 8;
    TMR0L = (uint8)(Timer0_Prelaod);
    if(TMR0_INTERRUPT_HANDLER){
       TMR0_INTERRUPT_HANDLER(); 
    }
}
