/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI2.C
**     Project   : contador_12_06_06
**     Processor : MC9S12GC32CFU16
**     Beantype  : TimerInt
**     Version   : Bean 02.151, Driver 01.16, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 06/05/2009, 9:16
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TIM_Counter (16-bit)
**         Compare name                : TC2
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 8000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 16000
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.0010000
**             Hz                      : 1000
**             kHz                     : 1
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Disabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TCNT      [68]
**              Mode                   : TIOS      [64]
**              Run                    : TSCR1     [70]
**              Prescaler              : TSCR2     [77]
**
**         Compare registers
**              Compare                : TC2       [84]
**
**         Flip-flop registers
**              Mode                   : TCTL2     [73]
**     Contents  :
**         Enable - byte TI2_Enable(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE TI2. */

#include "Events.h"
#include "TI2.h"

#pragma DATA_SEG TI2_DATA
#pragma CODE_SEG TI2_CODE
#pragma CONST_SEG DEFAULT


/* Internal method prototypes */


/* End of Internal methods declarations */

/*
** ===================================================================
**     Method      :  TI2_Enable (bean TimerInt)
**
**     Description :
**         This method enables the bean - it starts the timer. Events
**         may be generated (<DisableEvent>/<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte TI2_Enable(void)
{
  TC2 = TCNT + (word)8000;             /* Store new value to the compare register */ 
  TFLG1 = 4;                           /* Reset interrupt request flag */ 
  TIE_C2I = 1;                         /* Enable interrupt */ 
  return ERR_OK;                       /* OK */
}

/*lint -save -e718 -e746 -e937 -e957 -e18 -e516 -e532 -e14 Disable MISRA rule (71,72,25) checking. */
/*
** ===================================================================
**     Method      :  TI2_Interrupt (bean TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes event(s) of the bean.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(TI2_Interrupt)
{
  TC2 += (word)8000;                   /* Add value corresponding with periode */
  TFLG1 = 4;                           /* Reset interrupt request flag */
  TI2_OnInterrupt();                   /* Invoke user event */
}

#pragma CODE_SEG TI2_CODE
/*lint -restore */

/* END TI2. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
