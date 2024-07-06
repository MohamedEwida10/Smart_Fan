/* 
 * File:   hal_adc.c
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on April 15, 2024, 4:15 PM
 */

#include"hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_INTERRUPT_HANDLER)(void) = NULL;            
#endif 

static void ADC_input_channel_port_configuration(ADC_channel_select_t channel);
static void ADC_select_result_format(const adc_conf_t *_adc);
static void ADC_voltage_reference_configuration(const adc_conf_t *_adc);

/********************************************************************************/

/**
 * @brief this routine initialize the ADC
 * @precondition none
 * @param _adc pointer to ADC configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed 
 */
STD_ReturnType ADC_Init(const adc_conf_t *_adc){
  STD_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable ADC */
        ADC_CONVERSION_DISABLE();
        /* configure the acquisition_time*/
        ADC_ACQUISITION_TIME_SELECT(_adc->acquisition_time);
        /* configure the conversion_clock*/
        ADC_CONVERSION_CLOCK_SELECT(_adc->conversion_clock);
        /* configure the default channel*/
        ADCON0bits.CHS = _adc->ADC_channel_select ;
        ADC_input_channel_port_configuration(_adc->ADC_channel_select);
        /* configure the interrupt*/
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
            #if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelEnable();
            if(Interrupt_HIGH_PRIORITY == _adc->priority){
                INTERRUPT_GlobalIterruptHighEnable();
                ADC_HighPrioritySet();
            }
            else if(Interrupt_LOW_PRIORITY == _adc->priority){
                INTERRUPT_GlobalIterruptLowEnable();
                ADC_LowPrioritySet();
            }
            else{/* nothing */}
            #else
            INTERRUPT_GlobalIterruptEnable();
            INTERRUPT_PeriphralInterruptEnable(); 
            #endif
        ADC_INTERRUPT_HANDLER = _adc->ADC_INTERRUPR_HANDLER;    
        #endif 
        /* configure the result format*/
        ADC_select_result_format(_adc);
        /* configure the voltage reference*/
        ADC_voltage_reference_configuration(_adc);
        /* enable ADC */
        ADC_CONVERSION_ENABLE();
    }
    
     return ret;     
}

/**
 * @brief this routine DE_initialize the ADC
 * @precondition none
 * @param _adc pointer to ADC configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ADC_DeInit(const adc_conf_t *_adc){
  STD_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable ADC */
        ADC_CONVERSION_DISABLE();
        /* disable interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();     
        #endif 
    }
    
     return ret;      
}

/**
 * @brief this routine allow select of the channel for conversion
 * @precondition ADC_Init() : function should have called before calling this function
 * @param _adc pointer to ADC configuration
 * @param channel defines the channel available for conversion
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ADC_SelectChannel(const adc_conf_t *_adc,ADC_channel_select_t channel){
  STD_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* configure the default channel*/
        ADCON0bits.CHS = channel ;
        ADC_input_channel_port_configuration(channel);
    }
    
     return ret;      
}
/**
 * @brief this routine starts the conversion process 
 * @precondition ADC_Init() : function should have called before calling this function
 * @param _adc pointer to ADC configuration
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ADC_StartConversion(const adc_conf_t *_adc){
  STD_ReturnType ret = E_OK;
    if(NULL == _adc)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ADC_START_CONVERSION();
    }
    
     return ret;      
}

/**
 * @brief this routine determine if the conversion process is complete
 *        when the conversion is complete routine returns true,false otherwise 
 * @precondition ADC_Init() : function should have called before calling this function
 *               ADC_StartConversion() : function should have called before calling this function
 * @param _adc pointer to ADC configuration
 * @param conversion_status the conversion status complete or not
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc,uint8 *conversion_status){
  STD_ReturnType ret = E_OK;
    if((NULL == _adc )||(NULL == conversion_status ))
    {
        ret = E_NOT_OK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
    }
    
     return ret;      
}

/**
 * @brief this routine is used to get the analog to digital converted value from specific channel
 * @precondition ADC_Init() : function should have called before calling this function
 *               ADC_IsConversionDone() : after this routine returns true{the conversion process complete}
 * @param _adc pointer to ADC configuration
 * @param conversion_result the conversion value
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed
 */
STD_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc,ADC_result_t *conversion_result){
  STD_ReturnType ret = E_OK;
    if((NULL == _adc )||(NULL == conversion_result ))
    {
        ret = E_NOT_OK;
    }
    else
    {
        if(_adc->result_format == ADC_RESULT_RIGHT_FORMAT){   
            *conversion_result = (ADC_result_t)((ADRESH << 8)+ADRESL);
        }
        else if(_adc->result_format == ADC_RESULT_LEFT_FORMAT){
            *conversion_result = (ADC_result_t)(((ADRESH << 8)+ADRESL) >> 6);
        }
        else{
           *conversion_result = (ADC_result_t)((ADRESH << 8)+ADRESL);
        }
        
    }
    
     return ret;      
}

/**
 * @brief this routine is used to select the desired channel for conversion and 
 *        returns the result of the conversion result
 * @precondition ADC_Init() : function should have called before calling this function
 * @param _adc pointer to ADC configuration
 * @param channel defines the channel available for conversion
 * @param conversion_result the conversion value
 * @return status of the function
 *         (E_OK): The function done successfully 
 *         (E_NOT_OH): The function failed 
 */
STD_ReturnType ADC_GetConversion_blocking(const adc_conf_t *_adc,ADC_channel_select_t channel
                                ,ADC_result_t *conversion_result){
  STD_ReturnType ret = E_OK;
    if((NULL == _adc )||(NULL == conversion_result) )
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select channel */
        ADC_SelectChannel(_adc,channel);
        /* start conversion */
        ADC_StartConversion(_adc);
        /* blocking until the conversion finishes */
        while(ADCON0bits.GO_nDONE);
        /* get conversion result */
        ADC_GetConversionResult(_adc,conversion_result);
    }
    
     return ret;      
}

 
STD_ReturnType ADC_StartConversion_interrupt(const adc_conf_t *_adc,ADC_channel_select_t channel ){
  STD_ReturnType ret = E_OK;
    if(NULL == _adc )
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* select channel */
        ADC_SelectChannel(_adc,channel);
        /* start conversion */
        ADC_StartConversion(_adc);
    }
    
     return ret;      
}

/********************************************************************************/
static void ADC_input_channel_port_configuration(ADC_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SIT_BIT(TRISA,_TRISA_RA0_POSN)  ;break;
        case ADC_CHANNEL_AN1 : SIT_BIT(TRISA,_TRISA_RA1_POSN)  ;break;
        case ADC_CHANNEL_AN2 : SIT_BIT(TRISA,_TRISA_RA2_POSN)  ;break;
        case ADC_CHANNEL_AN3 : SIT_BIT(TRISA,_TRISA_RA3_POSN)  ;break;
        case ADC_CHANNEL_AN4 : SIT_BIT(TRISA,_TRISA_RA5_POSN)  ;break;
        case ADC_CHANNEL_AN5 : SIT_BIT(TRISE,_TRISE_RE0_POSN)  ;break;
        case ADC_CHANNEL_AN6 : SIT_BIT(TRISE,_TRISE_RE1_POSN)  ;break;
        case ADC_CHANNEL_AN7 : SIT_BIT(TRISE,_TRISE_RE2_POSN)  ;break;
        case ADC_CHANNEL_AN8 : SIT_BIT(TRISB,_TRISB_RB2_POSN)  ;break;
        case ADC_CHANNEL_AN9 : SIT_BIT(TRISB,_TRISB_RB3_POSN)  ;break;
        case ADC_CHANNEL_AN10 : SIT_BIT(TRISB,_TRISB_RB1_POSN)  ;break;
        case ADC_CHANNEL_AN11 : SIT_BIT(TRISB,_TRISB_RB4_POSN)  ;break;
        case ADC_CHANNEL_AN12 : SIT_BIT(TRISB,_TRISB_RB0_POSN)  ;break;
        
    }
}

static void ADC_select_result_format(const adc_conf_t *_adc){
    if(_adc->result_format == ADC_RESULT_RIGHT_FORMAT){
        ADC_RIGHT_RESULT_FORMAT();
  
    }
    else if(_adc->result_format == ADC_RESULT_LEFT_FORMAT){
        ADC_LEFT_RESULT_FORMAT();
    }
    else{
        ADC_RIGHT_RESULT_FORMAT();
    }
}

static void ADC_voltage_reference_configuration(const adc_conf_t *_adc){
    if(_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_ENABLE){
        
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(_adc->voltage_reference == ADC_VOLTAGE_REFERENCE_DISABLE){
         ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_INTERRUPT_HANDLER){
       ADC_INTERRUPT_HANDLER(); 
    }
}