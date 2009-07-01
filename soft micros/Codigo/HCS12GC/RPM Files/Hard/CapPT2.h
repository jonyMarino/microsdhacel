/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : CapPT2.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : Capture
**     Version   : Bean 02.083, Driver 01.08, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 14/04/2008, 01:06 p.m.
**     Abstract  :
**         This bean "Capture" simply implements the capture function
**         of timer. The counter counts the same way as in free run mode. On
**         the selected edge of the input signal (on the input pin), the current
**         content of the counter register is written into the capture
**         register and the OnCapture event is called.
**     Settings  :
**             Timer capture encapsulation : Capture
**
**         Timer
**             Timer                   : TIM
**             Counter shared          : Yes
**
**         High speed mode
**             Prescaler               : divide-by-32
**           Maximal time for capture register
**             Xtal ticks              : 1048576
**             microseconds            : 131072
**             milliseconds            : 131
**             seconds (real)          : 0.1310720
**             Hz                      : 8
**           One tick of timer is
**             microseconds            : 2
**
**         Initialization:
**              Timer                  : Disabled
**              Events                 : Enabled
**
**         Timer registers
**              Capture                : TC2       [84]
**              Counter                : TCNT      [68]
**              Mode                   : TIOS      [64]
**              Run                    : TSCR1     [70]
**              Prescaler              : TSCR2     [77]
**
**         Used input pin              : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       7             |  PT2_PWM2_IOC2
**             ----------------------------------------------------
**
**         Port name                   : T
**         Bit number (in port)        : 2
**         Bit mask of the port        : 4
**
**         Signal edge/level           : rising
**         Pull option                 : off
**
**     Contents  :
**         Enable          - byte CapPT2_Enable(void);
**         Disable         - byte CapPT2_Disable(void);
**         Reset           - byte CapPT2_Reset(void);
**         GetCaptureValue - byte CapPT2_GetCaptureValue(word *Value);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __CapPT2
#define __CapPT2

/* MODULE CapPT2. */

#include "Cpu.h"
#include "Capture.h"

#pragma DATA_SEG CapPT2_DATA                                            
#pragma CODE_SEG CapPT2_CODE                     
extern volatile word CapPT2_CntrState; /* Content of counter */

byte CapPT2_Enable(void);
/*
** ===================================================================
**     Method      :  CapPT2_Enable (bean Capture)
**
**     Description :
**         Enables the bean - it starts the capture. Events may be
**         generated ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte CapPT2_Disable(void);
/*
** ===================================================================
**     Method      :  CapPT2_Disable (bean Capture)
**
**     Description :
**         Disables the bean - it stops the capture. No events will
**         be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/


#define CapPT2_GetCaptureValue(Value) \
 (*(Value) = TC2 , *(Value) -= CapPT2_CntrState , ERR_OK)
 
/*
** ===================================================================
**     Method      :  CapPT2_GetCaptureValue (bean Capture)
**
**     Description :
**         This method gets the last value captured by enabled timer.
**         Note: one tick of timer is
**               2 us in high speed mode 
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Value           - A pointer to the content of the
**                           capture register
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
void CapPT2_GetCapResult(TCapture * result);
 /*
** ===================================================================
**     Method      :  CapPT2_GetCapResult (bean Capture)
**
**     Description :
**         Este metodo obtiene el numero de pulsos que se obtuvieron a
**		 la entrada, y los microsegundos que transcurrieron entre el primero
**     y el ultimo pulso.
**     Parameters  :
**         NAME            - DESCRIPTION
**     Returns     :
**         ---             - Resultado del capturador
** ===================================================================
*/

void CapPT2_Init(void);
/*
** ===================================================================
**     Method      :  CapPT2_Init (bean Capture)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED     
__interrupt void CapPT2_Interrupt(void);
#pragma CODE_SEG Cap1_CODE                     
/*
** ===================================================================
**     Method      :  Interrupt (bean Capture)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED     
__interrupt void CapPT2_IntOverflow(void);
#pragma CODE_SEG Cap1_CODE                     
/*
** ===================================================================
**     Method      :  IntOverflow (bean Capture)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   

/* END CapPT2. */

#endif /* ifndef __CapPT2 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/