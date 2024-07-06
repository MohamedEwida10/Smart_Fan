/* 
 * File:   ecu_layer_init.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on October 21, 2023, 9:11 PM
 */


#include "ecu_layer_init.h"

chr_lcd_4bit_t LCD = {
.rs.port = PORTC_INDEX,
.rs.pin = PIN0,
.rs.direction = DICRECTION_OUTOUT,
.rs.logic = LOW,

.en.port = PORTC_INDEX,
.en.pin = PIN1,
.en.direction = DICRECTION_OUTOUT,
.en.logic = LOW,

.data[0].port = PORTC_INDEX,
.data[0].pin = PIN4,
.data[0].direction = DICRECTION_OUTOUT,
.data[0].logic = LOW,
.data[1].port = PORTC_INDEX,
.data[1].pin = PIN5,
.data[1].direction = DICRECTION_OUTOUT,
.data[1].logic = LOW,
.data[2].port = PORTC_INDEX,
.data[2].pin = PIN6,
.data[2].direction = DICRECTION_OUTOUT,
.data[2].logic = LOW,
.data[3].port = PORTC_INDEX,
.data[3].pin = PIN7,
.data[3].direction = DICRECTION_OUTOUT,
.data[3].logic = LOW,
};


adc_conf_t LM_35 = {
.ADC_INTERRUPR_HANDLER = NULL,
.ADC_channel_select = ADC_CHANNEL_AN0,
.acquisition_time = ADC_12_TAD,
.conversion_clock = ADC_CONVERSION_CLOCK_Fosc_DIV_16,
.result_format= ADC_RESULT_RIGHT_FORMAT,
.voltage_reference = ADC_VOLTAGE_REFERENCE_DISABLE,
};

dc_motor_t motor = {
.dc_motor_pin[0].port = PORTA_INDEX,
.dc_motor_pin[0].pin = PIN1,
.dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS ,
.dc_motor_pin[0].direction = DICRECTION_OUTOUT,
.dc_motor_pin[1].port = PORTA_INDEX,
.dc_motor_pin[1].pin = PIN2,
.dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS ,
.dc_motor_pin[1].direction = DICRECTION_OUTOUT,
};

TIMER2_t timer2_obj = {
.TMR2_INTERRUPR_HANDLER = NULL ,
.Prescaler_Value = TIMER2_Prescaler_div_by_1 ,
.Postscaler_Value = TIMER2_Postscaler_div_by_1 ,
.timer2_prelaod_value = 0
};

TIMER3_t timer3_obj = {
.TMR3_INTERRUPR_HANDLER = NULL ,
.timer3_mode = Timer3_timer_mode,
.timer3_prelaod_value = 28036,
.timer3_reg_rw_mode = Timer3_RW_REG_16bit_MODE,
.Prescaler_Value = TIMER3_Prescaler_div_by_8,        
};

ccp_t ccp1_obj= {
.CCP1_INTERRUPR_HANDLER = NULL,
.ccp_inst = CCP1_INST,
.ccp_mode = ccp_pwm_mode_selsected,
.ccp_sub_mode = CCP_PWM_MODE,
.pwm_freq = 2000,
.Prescaler_Value = CCP_TIMER2_PRESCALER_DIV_BY_1,
.Postscaler_Value = CCP_TIMER2_POSTSCALER_DIV_BY_1,
.pin.port = PORTC_INDEX,
.pin.direction = DICRECTION_OUTOUT,
.pin.pin = PIN2
};

keypad_t keypad = {
.keypad_rows_pins[0].port = PORTD_INDEX,
.keypad_rows_pins[0].pin = PIN0,
.keypad_rows_pins[0].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[0].logic = LOW,
.keypad_rows_pins[1].port = PORTD_INDEX,
.keypad_rows_pins[1].pin = PIN1,
.keypad_rows_pins[1].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[1].logic = LOW,
.keypad_rows_pins[2].port = PORTD_INDEX,
.keypad_rows_pins[2].pin = PIN2,
.keypad_rows_pins[2].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[2].logic = LOW,
.keypad_rows_pins[3].port = PORTD_INDEX,
.keypad_rows_pins[3].pin = PIN3,
.keypad_rows_pins[3].direction = DICRECTION_OUTOUT,
.keypad_rows_pins[3].logic = LOW,

.keypad_columns_pins[0].port = PORTD_INDEX,
.keypad_columns_pins[0].pin = PIN4,
.keypad_columns_pins[0].direction = DICRECTION_INPUT,
.keypad_columns_pins[0].logic = LOW,
.keypad_columns_pins[1].port = PORTD_INDEX,
.keypad_columns_pins[1].pin = PIN5,
.keypad_columns_pins[1].direction = DICRECTION_INPUT,
.keypad_columns_pins[1].logic = LOW,
.keypad_columns_pins[2].port = PORTD_INDEX,
.keypad_columns_pins[2].pin = PIN6,
.keypad_columns_pins[2].direction = DICRECTION_INPUT,
.keypad_columns_pins[2].logic = LOW,
.keypad_columns_pins[3].port = PORTD_INDEX,
.keypad_columns_pins[3].pin = PIN7,
.keypad_columns_pins[3].direction = DICRECTION_INPUT,
.keypad_columns_pins[3].logic = LOW,
};

button_t btn_mode_changer ={
.button_connection = BUTTON_ACTIVE_HIGH,
.button_state = BUTTON_RELEASED,
.button_pin.port = PORTC_INDEX,
.button_pin.pin = PIN3,
.button_pin.direction = DICRECTION_INPUT,
.button_pin.logic = LOW
};

void ecu_layer_Initialization(void)
{
    lcd_4bit_initialize(&LCD);
    ADC_Init(&LM_35);
    ecu_dc_motor_initialize(&motor);
    CCP_Init(&ccp1_obj);
    Timer2_Init(&timer2_obj);
    ecu_keypad_initialize(&keypad);
    ecu_button_initialize(&btn_mode_changer);
    
}

