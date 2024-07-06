/* 
 * File:   hal_adc.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on April 15, 2024, 4:15 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/******************* Section : Includes *******************/
#include "pic18f4620.h"
#include "hal_adc_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/******************* Section : Macro Declarations *******************/
/**
 *@brief Analog_to_digital configuration control
 */
#define ADC_ANALOG_FUNC_CHANNEL_AN0    0x0E
#define ADC_ANALOG_FUNC_CHANNEL_AN1    0x0D
#define ADC_ANALOG_FUNC_CHANNEL_AN2    0x0C
#define ADC_ANALOG_FUNC_CHANNEL_AN3    0x0B
#define ADC_ANALOG_FUNC_CHANNEL_AN4    0x0A
#define ADC_ANALOG_FUNC_CHANNEL_AN5    0x09
#define ADC_ANALOG_FUNC_CHANNEL_AN6    0x08
#define ADC_ANALOG_FUNC_CHANNEL_AN7    0x07
#define ADC_ANALOG_FUNC_CHANNEL_AN8    0x06
#define ADC_ANALOG_FUNC_CHANNEL_AN9    0x05
#define ADC_ANALOG_FUNC_CHANNEL_AN10   0x04
#define ADC_ANALOG_FUNC_CHANNEL_AN11   0x03
#define ADC_ANALOG_FUNC_CHANNEL_AN12   0x02
#define ADC_ANALOG_FUNC_ALL_CHANNELS   0x00
#define ADC_DIGITA_FUNC_ALL_CHANNELS   0x0F

#define ADC_RESULT_RIGHT_FORMAT        0x01
#define ADC_RESULT_LEFT_FORMAT         0x00

#define ADC_VOLTAGE_REFERENCE_ENABLE   0x01
#define ADC_VOLTAGE_REFERENCE_DISABLE  0x00

/******************* Section : Macro Functions Declarations *******************/

/**
 *@brief start A/D conversion 
 */
#define ADC_START_CONVERSION()     (ADCON0bits.GODONE = 1)
/**
 *@brief Analog to digital control
 *@note  ADC_CONVERSION_ENABLE  : enable the analog to digital
 *       ADC_CONVERSION_DISABLE : disable the analog to digital
 */
#define ADC_CONVERSION_ENABLE()    (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE()   (ADCON0bits.ADON = 0)

/**
 *@brief VOLTAGE REFERENCE CONFIGURATION
 *@note  ADC_ENABLE_VOLTAGE_REFERENCE  : voltage reference VREF- & VREF+
 *       ADC_DISABLE_VOLTAGE_REFERENCE : voltage reference VSS & VDD
 */
#define ADC_ENABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 1;ADCON1bits.VCFG0 = 1;}while(0)                                                    
#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ADCON1bits.VCFG1 = 0;ADCON1bits.VCFG0 = 0;}while(0)         
                                          
                                        

/**
 *@brief Analog_to_digital configuration control
 *@example  ADC_ANALOG_DIGITAL_PORT_CONFIG(ADC_ANALOG_FUNC_CHANNEL_AN4);
 *          when ADC_ANALOG_FUNC_CHANNEL_AN4 is configurated
 *          AN4,AN3,AN2,AN1,AN0 are analog functionality
 *          @ref Analog_to_digital configuration control
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

/**
 *@brief A/D result format select
 */
#define ADC_RIGHT_RESULT_FORMAT() (ADCON2bits.ADFM = 1)
#define ADC_LEFT_RESULT_FORMAT()  (ADCON2bits.ADFM = 0)

/**
 *@brief A/D set ACQUISITION_TIME
 */
#define ADC_ACQUISITION_TIME_SELECT(_CONFIG) (ADCON2bits.ACQT = _CONFIG) 
/**
 *@brief A/D set CONVERSION_CLOCK
 */
#define ADC_CONVERSION_CLOCK_SELECT(_CONFIG) (ADCON2bits.ADCS = _CONFIG) 
            

/******************* Section : MacroData Type Declarations *******************/
/**
 *@brief analog channel select
 */
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12            
}ADC_channel_select_t;

/**
 * @brief A/D Acquisition time select
 * @note Acquisition time(sampling time) is the time required for A/D to
 *       capture the input voltage during sampling
 */
typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,         
}ADC_acquisition_time__t;

/**
 * @brief A/D conversion clock select
 * @note if the A/D FRC clock source is selected.a delay of one
 *       instruction cycle is add before the A/D clock starts
 */
typedef enum{
    ADC_CONVERSION_CLOCK_Fosc_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_Fosc_DIV_8,
    ADC_CONVERSION_CLOCK_Fosc_DIV_32,
    ADC_CONVERSION_CLOCK_Fosc_DIV_FRC,  
    ADC_CONVERSION_CLOCK_Fosc_DIV_4,
    ADC_CONVERSION_CLOCK_Fosc_DIV_16,  
    ADC_CONVERSION_CLOCK_Fosc_DIV64,        
}ADC_conversion_clock__t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_INTERRUPR_HANDLER)(void);
    Interrupt_PRIORITY_cfg priority;
#endif    
    ADC_acquisition_time__t acquisition_time ;
    ADC_conversion_clock__t conversion_clock;
    ADC_channel_select_t ADC_channel_select;
    uint8 voltage_reference :1 ;
    uint8 result_format :1 ;
    uint8 adc_resreved :6 ;
}adc_conf_t;

typedef uint16 ADC_result_t;
/******************* Section : Functions Declarations *******************/
STD_ReturnType ADC_Init(const adc_conf_t *_adc);
STD_ReturnType ADC_DeInit(const adc_conf_t *_adc);
STD_ReturnType ADC_SelectChannel(const adc_conf_t *_adc,ADC_channel_select_t channel);
STD_ReturnType ADC_StartConversion(const adc_conf_t *_adc);
STD_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc,uint8 *conversion_status);
STD_ReturnType ADC_GetConversionResult(const adc_conf_t *_adc,ADC_result_t *conversion_result);
STD_ReturnType ADC_GetConversion_blocking(const adc_conf_t *_adc,ADC_channel_select_t channel
                                ,ADC_result_t *conversion_result);
STD_ReturnType ADC_StartConversion_interrupt(const adc_conf_t *_adc,ADC_channel_select_t channel );
                               
#endif	/* HAL_ADC_H */


