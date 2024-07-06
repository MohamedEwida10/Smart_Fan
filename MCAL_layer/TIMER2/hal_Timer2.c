/* 
 * File:   hal_Timer2.c
 * Author: Blu-Ray
 *
 * Created on June 26, 2024, 2:16 PM
 */

#include"hal_Timer2.h"

/********************************************************************/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR2_INTERRUPT_HANDLER)(void) = NULL;   
#endif
static uint8 Timer2_Prelaod = 0; 

/********************************************************************/

STD_ReturnType Timer2_Init(const TIMER2_t *_timer){
STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer2_module_Disable();
        Timer2_Set_Prescaler_Value(_timer->Prescaler_Value);
        Timer2_Set_Postscaler_Value(_timer->Postscaler_Value);
        TMR2 = (uint8)(_timer->timer2_prelaod_value);
        Timer2_Prelaod = _timer->timer2_prelaod_value;
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE        
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        TMR2_INTERRUPT_HANDLER = _timer->TMR2_INTERRUPR_HANDLER;
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(Interrupt_HIGH_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptHighEnable();
                TIMER2_HighPrioritySet();
            }
            else if(Interrupt_LOW_PRIORITY == _timer->priority){
                INTERRUPT_GlobalIterruptLowEnable();
                TIMER2_LowPrioritySet();
            }
            else{/* nothing */}
            #else
                INTERRUPT_GlobalIterruptEnable();
                INTERRUPT_PeriphralInterruptEnable(); 
            #endif           
        #endif        
        Timer2_module_Enable();
    }    
return ret;     
}

STD_ReturnType Timer2_DeInit(const TIMER2_t *_timer){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {
        Timer2_module_Disable();
        #if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE() ;
        #endif
    }

     return ret;      
}

STD_ReturnType Timer2_Write_Value(const TIMER2_t *_timer,uint8 _value){
    STD_ReturnType ret = E_OK;
    if(NULL == _timer )
    {
        ret = E_NOT_OK;
    }
    else
    {    
        TMR2 = (_value);
    }

     return ret;      
}

STD_ReturnType Timer2_Read_Value(const TIMER2_t *_timer,uint8 *_value){
    STD_ReturnType ret = E_OK;
    if((NULL == _timer) || (NULL == _value) )
    {
        ret = E_NOT_OK;
    }
    else
    {        
        *_value = TMR2;
    }

     return ret;       
}

/********************************************************************/
void TMR2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = (Timer2_Prelaod);
    if(TMR2_INTERRUPT_HANDLER){
       TMR2_INTERRUPT_HANDLER(); 
    }
}