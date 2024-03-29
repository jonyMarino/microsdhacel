/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : FC321.C
**     Project   : TestSalida
**     Processor : MC9S12GC32CFU16
**     Beantype  : FreeCntr32
**     Version   : Bean 02.065, Driver 01.14, CPU db: 2.87.396
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 22/09/2009, 16:27
**     Abstract  :
**         This device "FreeCntr32" implements 32-bit Free Running Counter
**     Settings  :
**         Timer name                  : TIM_Counter (16-bit)
**         Compare name                : TC7
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 8000000 Hz
**           Resolution of timer
**             Xtal ticks              : 160
**             microseconds            : 10
**             seconds (real)          : 0.0000100
**             Hz                      : 100000
**             kHz                     : 100
**
**         Initialization:
**              Timer                  : Enabled
**
**         Timer registers
**              Counter                : TCNT      [68]
**              Mode                   : TIOS      [64]
**              Run                    : TSCR1     [70]
**              Prescaler              : TSCR2     [77]
**
**         Compare registers
**              Compare                : TC7       [94]
**     Contents  :
**         Enable    - byte FC321_Enable(void);
**         Disable   - byte FC321_Disable(void);
**         Reset     - byte FC321_Reset(void);
**         GetTimeUS - byte FC321_GetTimeUS(word *Time);
**         GetTimeMS - byte FC321_GetTimeMS(word *Time);
**
**     (c) Copyright UNIS, a.s. 1997-2008
**     UNIS, a.s.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE FC321. */

#include "FC321.h"

#pragma DATA_SEG FC321_DATA
#pragma CODE_SEG FC321_CODE

static dword TTicks;                   /* Counter of timer ticks */
static dword LTicks;                   /* Working copy of variable TTicks, loaded by function LoadTicks */
static bool TOvf;                      /* Counter overflow flag */
/*
** ===================================================================
**     Method      :  FC321_Enable (bean FreeCntr32)
**
**     Description :
**         This method enables the bean, i.e. timer is enabled and the
**         internal clocks are counted. The method usually also reset
**         the counter (if it is supported by HW). 
**         The method is not available if the counter is shared.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte FC321_Enable(void)
{
  TFLG1 = 128;                         /* Reset interrupt request flag */ 
  TIE_C7I = 1;                         /* Enable interrupt */ 
  TSCR1_TEN = 1;                       /* Start timer */ 
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  FC321_Disable (bean FreeCntr32)
**
**     Description :
**         This method disables the bean, i.e. timer is disabled and
**         the internal clocks are stopped. Last counter value is
**         usually preserved in the counter (if it is supported by HW).
**         The method is not available if the counter is shared.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
/*
byte FC321_Disable(void)

**      This method is implemented as a macro. See header module. **
*/

/*
** ===================================================================
**     Method      :  LoadTicks (bean FreeCntr32)
**
**     Description :
**         The function loads actual number of timer ticks and returns 
**         actual state of overflow flag.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static bool LoadTicks(void)
{
  EnterCritical();                     /* Save the CCR register */
  LTicks = TTicks;                     /* Loading actual number of timer ticks */
  if (TOvf) {                          /* Test actual state of "overflow flag" */
    ExitCritical();                    /* Restore the CCR register */
    return TRUE;                       /* Return OVERFLOW set */
  } else {
    ExitCritical();                    /* Restore the CCR register */
    return FALSE;                      /* Return "NO overflow" */
  }
}

/*
** ===================================================================
**     Method      :  FC321_Reset (bean FreeCntr32)
**
**     Description :
**         Clears the counter.
**     Parameters  : None
**     Returns     :
**         ---       - Error Code
** ===================================================================
*/
byte FC321_Reset(void)
{
  EnterCritical();                     /* Save the CCR register */
  TTicks =  0;                         /* Reset counter of timer ticks */
  TOvf = FALSE;                        /* Reset counter overflow flag */
  ExitCritical();                      /* Restore the CCR register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  FC321_GetTimeUS (bean FreeCntr32)
**
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in microseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in microseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
byte FC321_GetTimeUS(word *Time)
{
  dlong RTval;                         /* Result of two 32-bit numbers multiplication */

  if (LoadTicks()) {                   /* Load actual state of counter */
    return ERR_OVERFLOW;               /* If yes then error */
  }
  PE_Timer_LngMul(LTicks, 167772160UL, &RTval); /* Multiply ticks and high speed CPU mode coefficient */
  if (PE_Timer_LngHi3(RTval[0], RTval[1], Time)) { /* Is the result greater or equal than 65536 ? */
    return ERR_MATH;                   /* If yes then error */
  } else {                             /* Is the result less than 65536 ? */
    return ERR_OK;                     /* If yes then OK */
  }
}

/*
** ===================================================================
**     Method      :  FC321_GetTimeMS (bean FreeCntr32)
**
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in milliseconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in milliseconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
byte FC321_GetTimeMS(word *Time)
{
  dlong RTval;                         /* Result of two 32-bit numbers multiplication */

  if (LoadTicks()) {                   /* Load actual state of counter */
    return ERR_OVERFLOW;               /* If yes then error */
  }
  PE_Timer_LngMul(LTicks, 42949673UL, &RTval); /* Multiply ticks and high speed CPU mode coefficient */
  if (PE_Timer_LngHi4(RTval[0], RTval[1], Time)) { /* Is the result greater or equal than 65536 ? */
    return ERR_MATH;                   /* If yes then error */
  } else {                             /* Is the result less than 65536 ? */
    return ERR_OK;                     /* If yes then OK */
  }
}

/*
** ===================================================================
**     Method      :  FC321_Init (bean FreeCntr32)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void FC321_Init(void)
{
  TTicks = 0;                          /* Counter of timer ticks */
  TOvf = FALSE;                        /* Counter overflow flag */
  /* TC7: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0,BIT7=0,BIT6=1,BIT5=0,BIT4=0,BIT3=1,BIT2=1,BIT1=1,BIT0=1 */
  setReg16(TC7, 79);                   /* Store given value to the compare register */ 
}

/*
** ===================================================================
**     Method      :  FC321_Interrupt (bean FreeCntr32)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         .
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(FC321_Interrupt)
{
  TTicks++;                            /* Increment counter of timer ticks */
  if (TTicks == 0) {                   /* Testing counter overflow */
    TOvf = TRUE;                       /* If yes then set overflow flag */
  }
  TFLG1 = 128;                         /* Reset interrupt request flag */
}

#pragma CODE_SEG FC321_CODE

/* END FC321. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.00 [04.12]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
