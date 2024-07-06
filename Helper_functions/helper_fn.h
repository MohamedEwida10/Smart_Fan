/* 
 * File:   helper_fn.h
 * Author: Blu-Ray
 *LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on March 8, 2024, 2:59 PM
 */

#ifndef HELPER_FN_H
#define	HELPER_FN_H


/******************* Section : Includes *******************/
#include "../application.h"
#include "math.h"

/******************* Section : Macro Declarations *******************/

/******************* Section : Macro Functions Declarations *******************/


/******************* Section : MacroData Type Declarations *******************/
uint8 time[4] = {0,0,0,0};
uint8 counter_time = 0;
uint16 time_value = 0;
/******************* Section : Functions Declarations *******************/
void set_fan_timer_value(uint8 *time,uint8 *counter_time);
void convert_arr_to_int( const uint8 *arr,const uint8 counter_time,uint16 *time_value);
void decreasing_counter(uint16 time_value);
void initialize_var(void);

#endif	/* HELPER_FN_H */

