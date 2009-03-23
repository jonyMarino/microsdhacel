/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI1.C
**     Project   : _10_03
**     Processor : MC9S12GC32CFU16
**     Beantype  : TimerInt
**     Version   : Bean 02.092, Driver 01.09, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 24/07/2006, 08:49 a.m.
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload 
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TIM (16-bit)
**         Compare name                : TC2
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-4
**           Initial period/frequency
**             Xtal ticks              : 8000
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.0010000
**             Hz                      : 1000
**             kHz                     : 1
**
**         Runtime setting             : modes (list of settings)
**            -----------------------------------------------------------------------
**            |  period  |     Prescaler      |        Real period [seconds]        |
**     --------    or    |-----------------------------------------------------------
**     | mode | freqency | high | low  | slow |    high    |    low     |    slow   |
**     ------------------------------------------------------------------------------
**     |  0   |  1ms     | 4    | -    | -    | 0.0010000  | -          | -         | 
**     |  1   |  4ms     | 4    | -    | -    | 0.0040000  | -          | -         | 
**     ------------------------------------------------------------------------------
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
**              Compare                : TC2       [84]
**
**         Flip-flop registers
**              Mode                   : TCTL2     [73]
**     Contents  :
**         SetPeriodMode - byte TI1_SetPeriodMode(byte Mode);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE TI1. */

#include "Events.h"
#include "TI1.h"
#include "timer_interrupt.h"

#pragma DATA_SEG TI1_DATA                                            
#pragma CODE_SEG TI1_CODE                     
#pragma CONST_SEG DEFAULT

#define  TICKS_1ms  500
#define  TICKS_40ms 20000
static const word HighComp[2] = {TICKS_1ms,TICKS_40ms};

static word CmpVal;                    /* Value periodicly addded to compare register */


/*
** ===================================================================
**     Method      :  TI1_Enable (bean TimerInt)
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
byte TI1_Enable(void)
{
  //TC0 = TCNT + CmpVal;                 /* Store new value to the compare register */ 
  TFLG1 = 1;                           /* Reset interrupt request flag */ 
  TIE_C0I = 1;                         /* Enable interrupt */ 
  return ERR_OK;                       /* OK */
}

void TI1_Disable(void)
{
  TFLG1 = 1;                           /* Reset interrupt request flag */
  TIE_C0I = 0;                        
}

/*
** ===================================================================
**     Method      :  TI1_Disable (bean TimerInt)
**
**     Description :
**         This method disables the bean - it stops the timer. No
**         events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte TI1_Disable(void)


/*
** ===================================================================
**     Method      :  TI1_SetPeriodMode (bean TimerInt)
**
**     Description :
**         Switches the bean to a specified mode (changes the period/frequency
**         using the mode values). This method reduces the time needed
**         for setting of a new period value. This method can be used only when
**         a list of possible period settings is specified at design time.
**         Each of these settings constitutes a mode and Processor Expert
**         assigns them a mode identifier. The prescaler and compare values
**         corresponding to each mode are calculated at design time.
**         Modes can be switched at runtime just by referring to a mode
**         identifier. No run-time calculations are performed, all the
**         calculations are performed at design time. The modes and mode
**         identifiers may be found in the include file *.h.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Mode       - Mode to switch to (0 to 1)
**                         0.   1ms
**                         1.   40ms
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_VALUE - Value out of range,
**                           requested timing mode is not defined
** ===================================================================
*/
byte TI1_SetPeriodMode(TI1_mode Mode)
{               
  if(Mode>1)	 /* Is a values of mode identifier out of range? */
    		return ERR_VALUE;								/* If yes then error */
  CmpVal = HighComp[Mode];             /* Store given value to the variable CmpVal */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_Init (bean TimerInt)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void TI1_Init(void)
{
  CmpVal = TICKS_1ms;                       /* Store given value to the variable CmpVal */
  TC0 = TICKS_1ms;                          /* Store value to the compare register */
  setReg8(TIE, 1);   
}

/*
** ===================================================================
**     Method      :  TI1_Interrupt (bean TimerInt)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED     
ISR(TI1_Interrupt)
{
  TC0 += CmpVal;                       /* Add value corresponding with periode */
  TFLG1 = 1;                           /* Reset interrupt request flag */
  Cpu_EnableInt();
  if (CmpVal==TICKS_1ms)								/* Interrupcion de 1ms */
    TI1ms_OnInterrupt();                   /* Invoke user event de interrupcion 1ms*/
  else														 /* Interrupcion de 40ms */
    TI40ms_OnInterrupt();                  /* Invoke user event de interrupcion 40ms*/
}

#pragma CODE_SEG TI1_CODE                     

/* END TI1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
