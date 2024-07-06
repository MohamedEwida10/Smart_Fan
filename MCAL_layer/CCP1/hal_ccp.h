/* 
 * File:   hal_ccp1.h
 * Author: Blu-Ray
 *
 * Created on June 28, 2024, 11:32 AM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "../GPIO/hal_gpio.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include"ccp_cfg.h"
/******************* Section : Macro Declarations *******************/
#define CCP_MODULE_DISABLE                              0

#define CCP_CAPTURE_MODE_1_FALLING_EDGE                 4
#define CCP_CAPTURE_MODE_1_RISING_EDGE                  5
#define CCP_CAPTURE_MODE_4_RISING_EDGE                  6
#define CCP_CAPTURE_MODE_16_RISING_EDGE                 7

#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH                2
#define CCP_COMPARE_MODE_SET_PEN_LOW_ON_MATCH           8
#define CCP_COMPARE_MODE_SET_PEN_HIGH_ON_MATCH          9
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT_ON_MATCH      10
#define CCP_COMPARE_MODE_GEN_EVENT_ON_MATCH             11

#define CCP_PWM_MODE                                    12

#define CCP_CAPTURE_READY                               1  
#define CCP_CAPTURE_NOT_READY                           0

#define CCP_COMPARE_READY                               1  
#define CCP_COMPARE_NOT_READY                           0

/* Timer2 Input Clock Post-scaler */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

/* Timer2 Input Clock Pre-scaler */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16


/******************* Section : Macro Functions Declarations *******************/
#define CCP1_SET_MODE(_CONFIG) (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG) (CCP2CONbits.CCP2M = _CONFIG)
/******************* Section : MacroData Type Declarations *******************/
typedef enum{
ccp_capture_mode_selsected = 0,
ccp_compare_mode_selsected ,
ccp_pwm_mode_selsected ,        
}ccp_mode_t;

typedef union{
    struct{
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16bit;
    };    
}CCP_REG_T;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;

typedef struct{
ccp_inst_t ccp_inst;
ccp_mode_t ccp_mode;
uint8  ccp_sub_mode;
pin_config_t pin;
ccp_capture_timer_t ccp_capture_timer;
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP1_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg CCP1_priority;
#endif  
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP2_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg CCP2_priority;
#endif      
    
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED) ||  (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)           
    uint32 pwm_freq;
    uint8 Postscaler_Value:4;
    uint8 Prescaler_Value :2; 
#endif

}ccp_t;

/******************* Section : Functions Declarations *******************/
STD_ReturnType CCP_Init(const ccp_t *_ccp_obj);
STD_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED)    
STD_ReturnType CCP_IsCapturedDataReady(const ccp_t *_ccp_obj,uint8 *capture_status);
STD_ReturnType CCP_Capture_Mode_Read_value(const ccp_t *_ccp_obj,uint16 *capture_value);
#endif
/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)    
STD_ReturnType CCP_IsCompareComplete(const ccp_t *_ccp_obj,uint8 *compare_status);
STD_ReturnType CCP_Compare_Mode_Set_value(const ccp_t *_ccp_obj,uint16 compare_value);
#endif
/************************************************************************/
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE_SELECTED)    
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj,const uint8 duty);
STD_ReturnType CCP_PWM_start(const ccp_t *_ccp_obj);
STD_ReturnType CCP_PWM_stop(const ccp_t *_ccp_obj);
#endif
/************************************************************************/

#endif	/* HAL_CCP1_H */

