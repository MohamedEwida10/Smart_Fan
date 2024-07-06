/* 
 * File:   mcal_internal_interrupt.h
 * Author: Blu-Ray
 * LinkedIn : https://www.linkedin.com/in/mohamed-ewida-181151264/
 * Created on February 12, 2024, 10:24 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/******************* Section : Includes *******************/
#include "mcal_interrupt_cfg.h"
/******************* Section : Macro Declarations *******************/


/******************* Section : Macro Functions Declarations *******************/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for ADC interrupt module */
#define ADC_INTERRUPT_ENABLE()            (PIE1bits.ADIE = 1)
/* this macro clear the interrupt enable for ADC interrupt module */
#define ADC_INTERRUPT_DISABLE()           (PIE1bits.ADIE = 0)
/* this macro clear the interrupt flag for ADC interrupt module*/
#define ADC_INTERRUPT_CLEAR_FLAG()        (PIR1bits.ADIF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the ADC interrupt priority to be HIGH PRIORTY  */
#define ADC_HighPrioritySet()            (IPR1bits.ADIP= 1)
/* this macro set the ADC interrupt priority to be LOW PRIORTY  */
#define ADC_LowPrioritySet()            (IPR1bits.ADIP= 0)
#endif
#endif 
/******************************************************************************/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for TIMER0 interrupt module */
#define TIMER0_INTERRUPT_ENABLE()            (INTCONbits.TMR0IE = 1)
/* this macro clear the interrupt enable for TIMER0 interrupt module */
#define TIMER0_INTERRUPT_DISABLE()           (INTCONbits.TMR0IE = 0)
/* this macro clear the interrupt flag for TIMER0 interrupt module*/
#define TIMER0_INTERRUPT_CLEAR_FLAG()        (INTCONbits.TMR0IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the TIMER0 interrupt priority to be HIGH PRIORTY  */
#define TIMER0_HighPrioritySet()            (INTCON2bits.TMR0IP= 1)
/* this macro set the TIMER0 interrupt priority to be LOW PRIORTY  */
#define TIMER0_LowPrioritySet()             (INTCON2bits.TMR0IP= 0)
#endif
#endif 
/******************************************************************************/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for TIMER1 interrupt module */
#define TIMER1_INTERRUPT_ENABLE()            (PIE1bits.TMR1IE = 1)
/* this macro clear the interrupt enable for TIMER1 interrupt module */
#define TIMER1_INTERRUPT_DISABLE()           (PIE1bits.TMR1IE = 0)
/* this macro clear the interrupt flag for TIMER1 interrupt module*/
#define TIMER1_INTERRUPT_CLEAR_FLAG()        (PIR1bits.TMR1IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the TIMER1 interrupt priority to be HIGH PRIORTY  */
#define TIMER1_HighPrioritySet()            (IPR1bits.TMR1IP = 1)
/* this macro set the TIMER1 interrupt priority to be LOW PRIORTY  */
#define TIMER1_LowPrioritySet()             (IPR1bits.TMR1IP = 0)
#endif
#endif 
/******************************************************************************/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for TIMER2 interrupt module */
#define TIMER2_INTERRUPT_ENABLE()            (PIE1bits.TMR2IE = 1)
/* this macro clear the interrupt enable for TIMER2 interrupt module */
#define TIMER2_INTERRUPT_DISABLE()           (PIE1bits.TMR2IE = 0)
/* this macro clear the interrupt flag for TIMER2 interrupt module*/
#define TIMER2_INTERRUPT_CLEAR_FLAG()        (PIR1bits.TMR2IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the TIMER2 interrupt priority to be HIGH PRIORTY  */
#define TIMER2_HighPrioritySet()            (IPR1bits.TMR2IP = 1)
/* this macro set the TIMER2 interrupt priority to be LOW PRIORTY  */
#define TIMER2_LowPrioritySet()             (IPR1bits.TMR2IP = 0)
#endif
#endif 
/******************************************************************************/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for TIMER3 interrupt module */
#define TIMER3_INTERRUPT_ENABLE()            (PIE2bits.TMR3IE = 1)
/* this macro clear the interrupt enable for TIMER3 interrupt module */
#define TIMER3_INTERRUPT_DISABLE()           (PIE2bits.TMR3IE = 0)
/* this macro clear the interrupt flag for TIMER3 interrupt module*/
#define TIMER3_INTERRUPT_CLEAR_FLAG()        (PIR2bits.TMR3IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the TIMER3 interrupt priority to be HIGH PRIORTY  */
#define TIMER3_HighPrioritySet()            (IPR2bits.TMR3IP = 1)
/* this macro set the TIMER3 interrupt priority to be LOW PRIORTY  */
#define TIMER3_LowPrioritySet()             (IPR2bits.TMR3IP = 0)
#endif
#endif 
/******************************************************************************/
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for CCP1 interrupt module */
#define CCP1_INTERRUPT_ENABLE()            (PIE1bits.CCP1IE = 1)
/* this macro clear the interrupt enable for CCP1 interrupt module */
#define CCP1_INTERRUPT_DISABLE()           (PIE1bits.CCP1IE = 0)
/* this macro clear the interrupt flag for CCP1 interrupt module*/
#define CCP1_INTERRUPT_CLEAR_FLAG()        (PIR1bits.CCP1IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the CCP1 interrupt priority to be HIGH PRIORTY  */
#define CCP1_HighPrioritySet()            (IPR1bits.CCP1IP = 1)
/* this macro set the CCP1 interrupt priority to be LOW PRIORTY  */
#define CCP1_LowPrioritySet()            (IPR1bits.CCP1IP = 0)
#endif
#endif 
/******************************************************************************/
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro set the interrupt enable for CCP2 interrupt module */
#define CCP2_INTERRUPT_ENABLE()            (PIE2bits.CCP2IE = 1)
/* this macro clear the interrupt enable for CCP2 interrupt module */
#define CCP2_INTERRUPT_DISABLE()           (PIE2bits.CCP2IE = 0)
/* this macro clear the interrupt flag for CCP2 interrupt module*/
#define CCP2_INTERRUPT_CLEAR_FLAG()        (PIR2bits.CCP2IF = 0)   

#if INTERRUPT_PRIORITY_LEVEL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* this macro set the CCP2 interrupt priority to be HIGH PRIORTY  */
#define CCP2_HighPrioritySet()            (IPR2bits.CCP2IP = 1)
/* this macro set the CCP2 interrupt priority to be LOW PRIORTY  */
#define CCP2_LowPrioritySet()            (IPR2bits.CCP2IP = 0)
#endif
#endif 
/******************************************************************************/

/******************* Section : MacroData Type Declarations *******************/


/******************* Section : Functions Declarations *******************/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

