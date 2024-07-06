/* 
 * File:   hal_Timer3.c
 * Author: Blu-Ray
 *
 * Created on June 26, 2024, 2:16 PM
 */

#include"hal_Timer3.h"

/********************************************************************/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR3_INTERRUPT_HANDLER)(void) = NULL;   
#endif
static uint16 Timer3_Prelaod = 0; 

/********************************************************************/
static inline void timer3_mode_select(const TIMER3_t *_timer);

/********************************************************************/

STD_ReturnType Timer3_Init(const TIMER3_t *_timer){
STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer3_module_Disable();
        Timer3_Set_Prescaler_Value(_timer->Prescaler_Value);
        timer3_mode_select(_timer);
        TMR3H = (_timer->timer3_prelaod_value) >> 8;
        TMR3L = (uint8)(_timer->timer3_prelaod_value);
        Timer3_Prelaod = _timer->timer3_prelaod_value;
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TMR3_INTERRUPT_HANDLER = _timer->TMR3_INTERRUPR_HANDLER;
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(Interrupt_HIGH_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptHighEnable();
                TIMER3_HighPrioritySet();
            }
            else if(Interrupt_LOW_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptLowEnable();
                TIMER3_LowPrioritySet();
            }
            else{/* nothing */}
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable(); 
            #endif           
        #endif        
        Timer3_module_Enable();
    }    
return ret;     
}
STD_ReturnType Timer3_DeInit(const TIMER3_t *_timer){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer3_module_Disable();
        #if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE() ;
        #endif
    }

     return ret;  
            
}
STD_ReturnType Timer3_Write_Value(const TIMER3_t *_timer,uint16 _value){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
    }

     return ret;      
}
STD_ReturnType Timer3_Read_Value(const TIMER3_t *_timer,uint16 *_value){
    STD_ReturnType ret = E_OK;
    uint8 l_tmr3l = 0,l_tmr3h = 0;
    if((NULL == _timer) || (NULL == _value) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
    }

     return ret;      
}

/********************************************************************/
static inline void timer3_mode_select(const TIMER3_t *_timer){
    if(Timer3_timer_mode == _timer->timer3_mode){
        Timer3_timer_mode_enable();
    }
    else if(Timer3_counter_mode == _timer->timer3_mode){
        Timer3_counter_mode_enable();  
        if(Timer3_ASYNC_counter_mode == _timer->timer3_counter_mode){
            Timer3_ASYNC_counter_mode_enable();
        }
        else if(Timer3_SYNC_counter_mode == _timer->timer3_counter_mode){
            Timer3_SYNC_counter_mode_enable();
        }
        else{/* nothing */}
    }
    else{/* nothing */}
}


/********************************************************************/
void TMR3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = (Timer3_Prelaod) >> 8;
    TMR3L = (uint8)(Timer3_Prelaod);
    if(TMR3_INTERRUPT_HANDLER){
       TMR3_INTERRUPT_HANDLER(); 
    }
}
