/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : RTI.H
**     Project   : _7_12
**     Processor : MC9S12GC32CFU16
**     Beantype  : TimerInt
**     Version   : Bean 02.092, Driver 01.09, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 12/12/2005, 15:10
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload 
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TIM (16-bit)
**         Compare name                : TC0
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-32
**             Clock                   : 781250 Hz
**           Initial period/frequency
**             Xtal ticks              : 7997
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.0009997
**             Hz                      : 1000
**             kHz                     : 1
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TCNT      [68]
**              Mode                   : TIOS      [64]
**              Run                    : TSCR1     [70]
**              Prescaler              : TSCR2     [77]
**
**         Compare registers
**              Compare                : TC0       [80]
**
**         Flip-flop registers
**              Mode                   : TCTL2     [73]
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __RTI
#define __RTI

/* MODULE RTI. */

#include "Cpu.h"

#pragma CODE_SEG __NEAR_SEG NON_BANKED     

void RTI_Init(void);

__interrupt void RTI_Interrupt(void);
/*
** ===================================================================
**     Method      :  RTI_Interrupt (bean TimerInt)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   


/* END RTI. */

#endif /* ifndef __RTI */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/