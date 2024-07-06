/* 
 * File:   hal_ccp1.c
 * Author: Blu-Ray
 *
 * Created on June 28, 2024, 11:32 AM
 */

#include"hal_ccp.h"


#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP1_INTERRUPT_HANDLER)(void) = NULL;   
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP2_INTERRUPT_HANDLER)(void) = NULL;   
#endif

/************************************************************************/
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj);
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj);
static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj);
static void CCP_Capture_Mode_Config(const ccp_t *_ccp_obj);
static void CCP_Compare_Mode_Config(const ccp_t *_ccp_obj);
/************************************************************************/
STD_ReturnType CCP_Init(const ccp_t *_ccp_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == _ccp_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
            if(CCP1_INST == _ccp_obj->ccp_inst){
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
            }       
            else{/* nothing */}
        
        
        /* CCP Module Capture Mode Initialization */
        if(_ccp_obj->ccp_mode == ccp_capture_mode_selsected){
            
             CCP_Capture_Mode_Config(_ccp_obj);
            
        }/* CCP Module COMPARE Mode Initialization */
        else if(_ccp_obj->ccp_mode == ccp_compare_mode_selsected){
         
             CCP_Compare_Mode_Config(_ccp_obj);
            
        }
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)          
        /* CCP Module PWM Mode Initialization */
        else if(_ccp_obj->ccp_mode == ccp_pwm_mode_selsected){
            CCP_PWM_Mode_Config(_ccp_obj);
        }
#endif            
        else{/* nothing */}
        
        /* PIN Configurations */
        gpio_pin_initialize(&(_ccp_obj->pin));
        /* Interrupt Configurations for CCP1 and CCP2 Modules */
        CCP_Interrupt_Config(_ccp_obj);
  
    }

     return ret;      
}

STD_ReturnType CCP_DeInit(const ccp_t *_ccp_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == _ccp_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
            if(CCP1_INST == _ccp_obj->ccp_inst){
                CCP1_SET_MODE(CCP_MODULE_DISABLE);
                
                #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                CCP1_INTERRUPT_DISABLE() ;
                #endif
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                CCP2_SET_MODE(CCP_MODULE_DISABLE);
                
                #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                CCP2_INTERRUPT_DISABLE() ;
                #endif
            }       
            else{/* nothing */}

    }

     return ret;      
}

/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)    
STD_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj,uint8 *capture_status){
    STD_ReturnType ret = E_OK;
    if(NULL == capture_status || NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP1_INST == _ccp_obj->ccp_inst){
            
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();           
            }else{
                *capture_status = CCP_CAPTURE_NOT_READY;
            }      
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();           
            }else{
                *capture_status = CCP_CAPTURE_NOT_READY;
            }    
        }       
        else{/* nothing */}
        
        
    }

     return ret;      
}

STD_ReturnType CCP_Capture_Mode_Read_value(const ccp_t *_ccp_obj,uint16 *capture_value){
    STD_ReturnType ret = E_OK;
    CCP_REG_T capture_temp_value = {.ccpr_low = 0,.ccpr_high = 0};
    
    if(NULL == capture_value || NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
            if(CCP1_INST == _ccp_obj->ccp_inst){         
                capture_temp_value.ccpr_low = CCPR1L;
                capture_temp_value.ccpr_high = CCPR1H;
            }
            else if(CCP2_INST == _ccp_obj->ccp_inst){
                capture_temp_value.ccpr_low = CCPR2L;
                capture_temp_value.ccpr_high = CCPR2H;      
            }       
            else{/* nothing */}
            
            *capture_value = capture_temp_value.ccpr_16bit;
    
    }

     return ret;    
}
#endif
/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)    
STD_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj,uint8 *compare_status){
    STD_ReturnType ret = E_OK;
    if(NULL == compare_status || NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {       
        if(CCP1_INST == _ccp_obj->ccp_inst){
              
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
                *compare_status = CCP_COMPARE_READY;
                CCP1_INTERRUPT_CLEAR_FLAG();

            }else{
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
              
            if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
                *compare_status = CCP_COMPARE_READY;
                CCP2_INTERRUPT_CLEAR_FLAG();

            }else{
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        }       
        else{/* nothing */}

    }
     return ret;       
}

STD_ReturnType CCP_Compare_Mode_Set_value(const ccp_t *_ccp_obj,uint16 compare_value){
    STD_ReturnType ret = E_OK;  
    CCP_REG_T capture_temp_value = {.ccpr_low = 0,.ccpr_high = 0};
    
    if( NULL == _ccp_obj)
    {
        ret = E_NOT_OK;
    }
    else
    {
        capture_temp_value.ccpr_16bit = compare_value;
        
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCPR1L = capture_temp_value.ccpr_low;
            CCPR1H = capture_temp_value.ccpr_high;         
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCPR2L = capture_temp_value.ccpr_low;
            CCPR2H = capture_temp_value.ccpr_high;     
        }       
        else{/* nothing */}
        
    }
     return ret;     
}
#endif
/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)    
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj,const uint8 duty){
    STD_ReturnType ret = E_OK;
    uint16 l_duty_temp = 0;
    
    if(NULL == _ccp_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {       
        l_duty_temp = (uint16)((float)4 * ((float)PR2 + 1.0) * ((float)duty / 100.0));
        
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
        else{ /* Nothing */ }
        
    }

     return ret;     
}

STD_ReturnType CCP_PWM_start(const ccp_t *_ccp_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == _ccp_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{/* nothing */}   
    }
     return ret;    
}

STD_ReturnType CCP_PWM_stop(const ccp_t *_ccp_obj){
    STD_ReturnType ret = E_OK;
    if(NULL == _ccp_obj )
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(CCP1_INST == _ccp_obj->ccp_inst){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if(CCP2_INST == _ccp_obj->ccp_inst){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else{/* nothing */}   
    }
     return ret;     
}
#endif
/************************************************************************/

void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_INTERRUPT_HANDLER){
        CCP1_INTERRUPT_HANDLER();
    }
    else{ /* Nothing */ }
}

void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_INTERRUPT_HANDLER){
        CCP2_INTERRUPT_HANDLER();
    }
    else{ /* Nothing */ }
}
/************************************************************************/
static void CCP_Interrupt_Config(const ccp_t *_ccp_obj){
/* CCP1 Interrupt Configurations */ 
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP1_INTERRUPT_ENABLE();
    CCP1_INTERRUPT_CLEAR_FLAG();
    CCP1_INTERRUPT_HANDLER = _ccp_obj->CCP1_INTERRUPR_HANDLER;
    #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(Interrupt_HIGH_PRIORITY == _ccp_obj->CCP1_priority){
            INTERRUPT_GlobalIterruptHighEnable();
            CCP1_HighPrioritySet();
        }
        else if(Interrupt_LOW_PRIORITY == _ccp_obj->CCP1_priority){
            INTERRUPT_GlobalIterruptLowEnable();
            CCP1_LowPrioritySet();
        }
        else{/* nothing */}
    #else
        INTERRUPT_GlobalIterruptEnable();
        INTERRUPT_PeriphralInterruptEnable(); 
    #endif 
#endif
                
/* CCP2 Interrupt Configurations */ 
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    CCP2_INTERRUPT_ENABLE();
    CCP2_INTERRUPT_CLEAR_FLAG();
    CCP2_INTERRUPT_HANDLER = _ccp_obj->CCP2_INTERRUPR_HANDLER;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelEnable();
    if(Interrupt_HIGH_PRIORITY == _ccp_obj->CCP2_priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalIterruptHighEnable();
        CCP2_HighPrioritySet();
    }
    else if(Interrupt_LOW_PRIORITY == _ccp_obj->CCP2_priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalIterruptLowEnable();
        CCP2_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalIterruptEnable();
    INTERRUPT_PeriphralInterruptEnable();
#endif          
#endif 
}

#if (CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED)
static void CCP_PWM_Mode_Config(const ccp_t *_ccp_obj){
    /* PWM Frequency Initialization */
    PR2 = (uint8)(((float)_XTAL_FREQ / ((float)_ccp_obj->pwm_freq * 4.0 * 
                   (float)_ccp_obj->Postscaler_Value * (float)_ccp_obj->Prescaler_Value)) - 1);
    
    if(CCP1_INST == _ccp_obj->ccp_inst){
        if(_ccp_obj->ccp_sub_mode == CCP_PWM_MODE){
            CCP1_SET_MODE(CCP_PWM_MODE) ;
        }
        else{/* nothing */}
        }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        if(_ccp_obj->ccp_sub_mode == CCP_PWM_MODE){
            CCP2_SET_MODE(CCP_PWM_MODE) ;
        }
        else{/* nothing */}
        }  
    else{ /* Nothing */ }
}
#endif

static void CCP_Mode_Timer_Select(const ccp_t *_ccp_obj){
    if(CCP1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == _ccp_obj->ccp_capture_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER1 == _ccp_obj->ccp_capture_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else{ /* Nothing */ }
}

static void CCP_Capture_Mode_Config(const ccp_t *_ccp_obj){
    
    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_sub_mode){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default :  ;/* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP2 Module Capture variants Mode Initialization */
        switch(_ccp_obj->ccp_sub_mode){
            case CCP_CAPTURE_MODE_1_FALLING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE); break;
            case CCP_CAPTURE_MODE_1_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_4_RISING_EDGE  : CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);  break;
            case CCP_CAPTURE_MODE_16_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE); break;
            default :  ;/* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    CCP_Mode_Timer_Select(_ccp_obj);
    

}

static void CCP_Compare_Mode_Config(const ccp_t *_ccp_obj){
    
    if(CCP1_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_sub_mode){
            case CCP_COMPARE_MODE_SET_PEN_LOW_ON_MATCH      : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PEN_LOW_ON_MATCH)     ;break;
            case CCP_COMPARE_MODE_SET_PEN_HIGH_ON_MATCH     : CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PEN_HIGH_ON_MATCH)    ;break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH           : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH)          ;break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT_ON_MATCH : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT_ON_MATCH);break;
            case CCP_COMPARE_MODE_GEN_EVENT_ON_MATCH        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT_ON_MATCH)       ;break;
            default : ; /* Not supported variant */
        }
    }
    else if(CCP2_INST == _ccp_obj->ccp_inst){
        /* CCP1 Module Compare variants Mode Initialization */
        switch(_ccp_obj->ccp_sub_mode){
            case CCP_COMPARE_MODE_SET_PEN_LOW_ON_MATCH      : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PEN_LOW_ON_MATCH)     ;break;
            case CCP_COMPARE_MODE_SET_PEN_HIGH_ON_MATCH     : CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PEN_HIGH_ON_MATCH)    ;break;
            case CCP_COMPARE_MODE_TOGGLE_ON_MATCH           : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH)          ;break;
            case CCP_COMPARE_MODE_GEN_SW_INTERRUPT_ON_MATCH : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT_ON_MATCH);break;
            case CCP_COMPARE_MODE_GEN_EVENT_ON_MATCH        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT_ON_MATCH)       ;break;
            default : ; /* Not supported variant */
        }
    }
    else{ /* Nothing */ }
    
    CCP_Mode_Timer_Select(_ccp_obj);
    
}
