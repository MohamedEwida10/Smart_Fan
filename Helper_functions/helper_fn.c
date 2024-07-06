/* 
 * File:   helper_fn.c
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on March 8, 2024, 2:59 PM
 */


#include"helper_fn.h"


void set_fan_timer_value(uint8 *time,uint8 *counter)                             
{

uint8 keypad_value  = 0;
uint8 lcd_counter = 1;
keypad_value = 0;

     while(1){
        do{
        ecu_keypad_get_value(&keypad,&keypad_value);   // to read the keypad button pressed
        __delay_ms(160);
        }while((keypad_value == 0) );
        
        if(keypad_value == '#' && *counter > 0 ){ // if you pressed '#' ,you want to delete the last char
           (*counter)--; 
           time[*counter] = '\0'; 
           (lcd_counter)--; 
           lcd_4bit_send_char_data_pos(&LCD,2,lcd_counter,' ');
               
        }
        else{    // store the operation and send it to the LCD     
            if(keypad_value == '='){ //  getting the '='  
                lcd_4bit_send_command(&LCD,_LCD_CLEAR);
                break;
            }
            else{
                if((*counter) < 4){ // make sure that maxmum digits of the number array is 4  
                    time[*counter] = keypad_value; // store the number_array element by element
                    lcd_4bit_send_char_data_pos(&LCD,2,lcd_counter,keypad_value);
                    (lcd_counter)++;    
                    (*counter)++;    
                }
                else{ // hint message
                    lcd_4bit_send_string_pos(&LCD,4,1,"ERROR");
                     __delay_ms(500);
                     lcd_4bit_send_string_pos(&LCD,4,1,"                  "); 
                     __delay_ms(500);    
                }
                
                
            }
            
        }
           

    }

}

void convert_arr_to_int( const uint8 *arr,const uint8 counter_time,uint16 *time_value){
uint8 count = 0;    
uint8 count_power = counter_time-1;  
for(count;count < counter_time;count++){
*time_value = *time_value + (arr[count] - 48)* (pow(10,count_power));
count_power--;
}    
}

void decreasing_counter(uint16 time_value){
    uint16 count = time_value;
    uint16 result_str[4]; 
    
    lcd_4bit_send_command(&LCD,_LCD_CLEAR);
    while(count--){
    __delay_ms(1000);
    convert_short_to_string(count,result_str);
    lcd_4bit_send_string_pos(&LCD,2,10,result_str);
    }
    lcd_4bit_send_command(&LCD,_LCD_CLEAR);
    
    
}

void initialize_var(void){
    
for(int count = 0;count< 3;count++){
    time[count] = 0;
}
 counter_time = 0;
 time_value = 0;

}