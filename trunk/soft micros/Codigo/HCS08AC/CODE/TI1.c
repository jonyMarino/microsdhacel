/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TI1.C
**     Project   : pwm_timer_4
**     Processor : MC9S08AC128CLK
**     Beantype  : TimerInt
**     Version   : Bean 02.154, Driver 01.14, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 18/12/2008, 8:07
**     Abstract  :
**         This bean "TimerInt" implements a periodic interrupt.
**         When the bean and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings  :
**         Timer name                  : TPM1 (16-bit)
**         Compare name                : TPM12
**         Counter shared              : Yes
**
**         High speed mode
**             Prescaler               : divide-by-32
**             Clock                   : 625000 Hz
**           Initial period/frequency
**             Xtal ticks              : 4000
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.0010000
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
**              Counter                : TPM1CNT   [$0021]
**              Mode                   : TPM1SC    [$0020]
**              Run                    : TPM1SC    [$0020]
**              Prescaler              : TPM1SC    [$0020]
**
**         Compare registers
**              Compare                : TPM1C2V   [$002C]
**
**         Flip-flop registers
**              Mode                   : TPM1C2SC  [$002B]
**     Contents  :
**         Enable  - byte TI1_Enable(void);
**         Disable - byte TI1_Disable(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE TI1. */

#include "Events.h"
#include "PE_Error.h"
#include "TI1.h"
#include "pwm_periodos.h"
#include "timer_interrupt.h"

#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */
#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter X declared in function F but not referenced */
#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used" */

static bool EnUser;                    /* Enable device by user */
static word CmpVal;                    /* Value added to compare register in ISR */
static bool paso; 

/* Internal method prototypes */


/*
** ===================================================================
**     Method      :  HWEnDi (bean TimerInt)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  word TmpCmpVal;                      /* Temporary variable for compare value */

  if (EnUser) {
    TmpCmpVal = (word)(TPM1CNT + CmpVal); /* Count current value for the compare register */
    TPM1C2V = TmpCmpVal;               /* Set compare register */
    while(TPM1C2V != TmpCmpVal) {}     /* Wait for register update (because of Latching mechanism) */
    /* TPM1C2SC: CH2F=0 */
    clrReg8Bits(TPM1C2SC, 0x80);       /* Reset request flag */ 
    /* TPM1C2SC: CH2IE=1 */
    setReg8Bits(TPM1C2SC, 0x40);       /* Enable compare interrupt */ 
  } else {
    /* TPM1C2SC: CH2IE=0 */
    clrReg8Bits(TPM1C2SC, 0x40);       /* Disable Compare interrupt */ 
  }
}

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
  if (!EnUser) {                       /* Is the device disabled by user? */
    EnUser = TRUE;                  /* If yes then set the flag "device enabled" */
    paso = FALSE;
    HWEnDi();                          /* Enable the device */
  }
  return ERR_OK;                       /* OK */
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
byte TI1_Disable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
    HWEnDi();                          /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TI1_Init (bean TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TI1_Init(void)
{
  /* TPM1C2SC: CH2F=0,CH2IE=0,MS2B=0,MS2A=1,ELS2B=0,ELS2A=0,??=0,??=0 */
  setReg8(TPM1C2SC, 0x10);             /* Set output compare mode and disable compare interrupt */ 
  EnUser = TRUE;                       /* Enable device */
  TI1_SetCV(0x0271U);                  /* Inicialize appropriate value to the compare/modulo/reload register */
  paso = FALSE;
  HWEnDi();
}
/*
** ===================================================================
**     Method      :  TI1_Interrupt (bean TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(TI1_Interrupt)
{
  /* TPM1C2SC: CH2F=0 */
  clrReg8Bits(TPM1C2SC, 0x80);         /* Reset compare interrupt request flag */ 
  
  if(CmpVal==25000 && (TPM1C2V+25000)<25000){
    paso = TRUE;
    TPM1C2V=TPM1C2V + 3035 + 25000;
  }
  
  if(TPM1C2V!=62500 && !paso)
    TPM1C2V += CmpVal;                   /* Count and save new value to the compare register */
  
  if(TPM1C2V == 62500) {
    TPM1C2V = CmpVal; 
  }
  paso = FALSE;
  TI1ms_OnInterrupt();                   /* Invoke user event */
}

void eleccionTiempo(timComp val) {
 
CmpVal =val;

if(val == 625)
  TPM1C2V = 625 ; 

}

/* END TI1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/