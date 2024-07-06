/* 
 * File:   hal_Timer1.c
 * Author: Blu-Ray
 *
 * Created on June 24, 2024, 7:17 PM
 */

#include"hal_Timer1.h"

/********************************************************************/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR1_INTERRUPT_HANDLER)(void) = NULL;   
#endif
static uint16 Timer1_Prelaod = 0; 

/********************************************************************/
static inline void timer1_mode_select(const TIMER1_t *_timer);

/********************************************************************/
STD_ReturnType Timer1_Init(const TIMER1_t *_timer){
STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer1_module_Disable();
        Timer1_Set_Prescaler_Value(_timer->Prescaler_Value);
        timer1_mode_select(_timer);
        TMR1H = (_timer->timer1_prelaod_value) >> 8;
        TMR1L = (uint8)(_timer->timer1_prelaod_value);
        Timer1_Prelaod = _timer->timer1_prelaod_value;
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TMR1_INTERRUPT_HANDLER = _timer->TMR1_INTERRUPR_HANDLER;
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(Interrupt_HIGH_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptHighEnable();
                TIMER1_HighPrioritySet();
            }
            else if(Interrupt_LOW_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptLowEnable();
                TIMER1_LowPrioritySet();
            }
            else{/* nothing */}
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable(); 
            #endif           
        #endif        
        Timer1_module_Enable();
    }    
return ret; 
}

STD_ReturnType Timer1_DeInit(const TIMER1_t *_timer){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer1_module_Disable();
        #if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE() ;
        #endif
    }

     return ret;  
        
}

STD_ReturnType Timer1_Write_Value(const TIMER1_t *_timer,uint16 _value){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
    }

     return ret;  
}
STD_ReturnType Timer1_Read_Value(const TIMER1_t *_timer,uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 l_tmr1l = 0,l_tmr1h = 0;
    if((NULL == _timer) || (NULL == _value) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_value = (uint16)((l_tmr1h << 8) + l_tmr1l);
    }

     return ret;     
}
/********************************************************************/
static inline void timer1_mode_select(const TIMER1_t *_timer){
    if(Timer1_timer_mode == _timer->timer1_mode){
        Timer1_timer_mode_enable();
    }
    else if(Timer1_counter_mode == _timer->timer1_mode){
        Timer1_counter_mode_enable();  
        if(Timer1_ASYNC_counter_mode == _timer->timer1_counter_mode){
            Timer1_ASYNC_counter_mode_enable();
        }
        else if(Timer1_SYNC_counter_mode == _timer->timer1_counter_mode){
            Timer1_SYNC_counter_mode_enable();
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}

/********************************************************************/
void TMR1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (Timer1_Prelaod) >> 8;
    TMR1L = (uint8)(Timer1_Prelaod);
    if(TMR1_INTERRUPT_HANDLER){
       TMR1_INTERRUPT_HANDLER(); 
    }
}

