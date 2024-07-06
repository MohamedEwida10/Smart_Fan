/* 
 * File:   application.c
 * Author: mohamed.ewida
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on September 21, 2023, 9:11 PM
 */

#include "application.h"

uint16 lm35_res_1,lm35_res_1_Celsius_mv = 0;
uint8 lm35_res_1_txt[7];

uint8 CCP1_PWM1_Duty = 0;

uint8 keypad_value;

uint8 fan_mode = 0;

uint8 btn_state = BUTTON_RELEASED;




int main() { 
    STD_ReturnType ret = E_NOT_OK;
    Application_Initialization();

        lcd_4bit_send_string_pos(&LCD,1,5,"auto mode");   
        lcd_4bit_send_string_pos(&LCD,2,1,"temp :");
 
  while(1){         
        
        ret = ADC_GetConversion_blocking(&LM_35,ADC_CHANNEL_AN0,&lm35_res_1);
        lm35_res_1_Celsius_mv = (uint16)((float)lm35_res_1 * 4.8828125f /10.0); /* 5000(mv) / 1024(10-Bit) => 4.8828125 */
        ret = convert_short_to_string(lm35_res_1_Celsius_mv, lm35_res_1_txt);
        ret = lcd_4bit_send_string_pos(&LCD, 2, 8, lm35_res_1_txt);

        
        if(lm35_res_1_Celsius_mv <= 25){   
            CCP_PWM_Set_Duty(&ccp1_obj,0);         
        }      
        else if(lm35_res_1_Celsius_mv > 25 && lm35_res_1_Celsius_mv <= 28){       
            CCP_PWM_Set_Duty(&ccp1_obj,50);  
        }
        else if(lm35_res_1_Celsius_mv > 28 && lm35_res_1_Celsius_mv <= 32){  
            CCP_PWM_Set_Duty(&ccp1_obj,75);
        }
        else if(lm35_res_1_Celsius_mv > 32){  
            CCP_PWM_Set_Duty(&ccp1_obj,100);
        }      
        else{/* nothing */}
        CCP_PWM_start(&ccp1_obj);
        ecu_dc_motor_move_right(&motor);
        
        ecu_button_read_state(&btn_mode_changer,&btn_state);
        if(btn_state == BUTTON_PRESSED){
            lcd_4bit_send_command(&LCD,_LCD_CLEAR);
            ecu_dc_motor_stop(&motor);
            CCP_PWM_stop(&ccp1_obj);
            break;
        }
        else{/* nothing */}

}
home_page : 
ecu_dc_motor_stop(&motor);
lcd_4bit_send_string_pos(&LCD,1,5,"manual mode");   
lcd_4bit_send_string_pos(&LCD,3,1,"1 >> change speed"); 
lcd_4bit_send_string_pos(&LCD,4,1,"2 >> timer");         
while(1){
     
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(120);
        }while(keypad_value == 0 );
            
        if('1' == keypad_value){
            lcd_4bit_send_command(&LCD,_LCD_CLEAR);
            lcd_4bit_send_string_pos(&LCD,1,1,"1 >> stop"); 
            lcd_4bit_send_string_pos(&LCD,2,1,"2 >> speed1");
            lcd_4bit_send_string_pos(&LCD,3,1,"3 >> speed2");
            lcd_4bit_send_string_pos(&LCD,4,1,"4 >> speed3");
            while(1){

                do{
                ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
                __delay_ms(80);
                }while(keypad_value == 0 );

                if('1' == keypad_value){
                    CCP_PWM_stop(&ccp1_obj); 
                    CCP_PWM_Set_Duty(&ccp1_obj,0);  

                }
                else if('2' == keypad_value){
                    CCP_PWM_stop(&ccp1_obj);
                    CCP_PWM_Set_Duty(&ccp1_obj,50);

                }
                else if('3' == keypad_value){
                    CCP_PWM_stop(&ccp1_obj); 
                    CCP_PWM_Set_Duty(&ccp1_obj,75);

                }            
                else if('4' == keypad_value){
                    CCP_PWM_stop(&ccp1_obj); 
                    CCP_PWM_Set_Duty(&ccp1_obj,100);

                }
                else if('#' == keypad_value){
                    lcd_4bit_send_command(&LCD,_LCD_CLEAR);
                    CCP_PWM_stop(&ccp1_obj);
                    goto home_page;
                    break;
                }                
                else{/* nothing */}
                
                CCP_PWM_start(&ccp1_obj);
                ecu_dc_motor_move_right(&motor);
            }    
            
        }
        else if('2' == keypad_value){
           
           lcd_4bit_send_command(&LCD,_LCD_CLEAR);
           lcd_4bit_send_string_pos(&LCD,1,1,"enter the time(s):"); 
           __delay_ms(600);
        
           set_fan_timer_value(&time,&counter_time);
           convert_arr_to_int(&time,counter_time,&time_value);
           CCP_PWM_Set_Duty(&ccp1_obj,100);
           CCP_PWM_start(&ccp1_obj);
           ecu_dc_motor_move_right(&motor); 
           decreasing_counter(time_value);
           initialize_var();
           goto home_page;
           
        }
        
    }
     

    
return (EXIT_SUCCESS);
}
void Application_Initialization(void){

ecu_layer_Initialization();
}


