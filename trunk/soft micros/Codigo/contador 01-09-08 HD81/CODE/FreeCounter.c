/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : FreeCounter.C
**     Project   : contador_12_06_06
**     Processor : MC9S12GC32CFU16
**     Beantype  : FreeCntr32
**     Version   : Bean 02.060, Driver 01.12, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 06/05/2009, 9:16
**     Abstract  :
**         This device "FreeCntr32" implements 32-bit Free Running Counter
**     Settings  :
**         Timer name                  : TIM_Counter (16-bit)
**         Compare name                : TC1
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 8000000 Hz
**           Resolution of timer
**             Xtal ticks              : 1600
**             microseconds            : 100
**             seconds (real)          : 0.0001000
**             Hz                      : 10000
**             kHz                     : 10
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
**              Compare                : TC1       [82]
**     Contents  :
**         Reset      - byte FreeCounter_Reset(void);
**         GetTimeSec - byte FreeCounter_GetTimeSec(word *Time);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE FreeCounter. */

#include "FreeCounter.h"

#pragma DATA_SEG FreeCounter_DATA
#pragma CODE_SEG FreeCounter_CODE

static dword TTicks;                   /* Counter of timer ticks */
static dword LTicks;                   /* Working copy of variable TTicks, loaded by function LoadTicks */
static bool TOvf;                      /* Counter overflow flag */
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
**     Method      :  FreeCounter_Reset (bean FreeCntr32)
**
**     Description :
**         Clears the counter.
**     Parameters  : None
**     Returns     :
**         ---       - Error Code
** ===================================================================
*/
byte FreeCounter_Reset(void)
{
  EnterCritical();                     /* Save the CCR register */
  TC1 = TCNT + (word)800;              /* Store new value to compare register */
  TTicks =  0;                         /* Reset counter of timer ticks */
  TOvf = FALSE;                        /* Reset counter overflow flag */
  ExitCritical();                      /* Restore the CCR register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  FreeCounter_GetTimeSec (bean FreeCntr32)
**
**     Description :
**         Returns the time (as a 16-bit unsigned integer) in seconds
**         since the last resetting after the last reset.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - A pointer to the returned 16-bit value
**                           in seconds
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_OVERFLOW - Software counter overflow
**                           ERR_MATH - Overflow during evaluation
** ===================================================================
*/
byte FreeCounter_GetTimeSec(word *Time)
{
  dlong RTval;                         /* Result of two 32-bit numbers multiplication */

  if (LoadTicks()) {                   /* Load actual state of counter */
    return ERR_OVERFLOW;               /* If yes then error */
  }
  PE_Timer_LngMul(LTicks, 109951163UL, &RTval); /* Multiply ticks and high speed CPU mode coefficient */
  if (PE_Timer_LngHi5(RTval[0], RTval[1], Time)) { /* Is the result greater or equal than 65536 ? */
    return ERR_MATH;                   /* If yes then error */
  } else {                             /* Is the result less than 65536 ? */
    return ERR_OK;                     /* If yes then OK */
  }
}

/*
** ===================================================================
**     Method      :  FreeCounter_Init (bean FreeCntr32)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void FreeCounter_Init(void)
{
  TTicks = 0;                          /* Counter of timer ticks */
  TOvf = FALSE;                        /* Counter overflow flag */
  /* TC1: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=1,BIT8=1,BIT7=0,BIT6=0,BIT5=1,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg16(TC1, 800);                  /* Store value to the compare register */ 
}

/*
** ===================================================================
**     Method      :  FreeCounter_Interrupt (bean FreeCntr32)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         .
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(FreeCounter_Interrupt)
{
  TC1 += (word)800;                    /* Add value corresponding with periode */
  TTicks++;                            /* Increment counter of timer ticks */
  if (TTicks == 0) {                   /* Testing counter overflow */
    TOvf = TRUE;                       /* If yes then set overflow flag */
  }
  TFLG1 = 2;                           /* Reset interrupt request flag */
}

#pragma CODE_SEG FreeCounter_CODE

/* END FreeCounter. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
