/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ComunLeds.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitIO
**     Version   : Bean 02.059, Driver 03.05, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 30/05/2008, 04:39 p.m.
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Note: This bean is set to work in Output direction only.
**         Methods of this bean are mostly implemented as a macros 
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       80            |  PP4_PWM4_KWP4
**             ----------------------------------------------------
**
**         Port name                   : P
**
**         Bit number (in port)        : 4
**         Bit mask of the port        : 16
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTP       [600]
**         Port control register       : DDRP      [602]
**
**         Optimization for            : speed
**     Contents  :
**         ClrVal - void ComunLeds_ClrVal(void);
**         SetVal - void ComunLeds_SetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef ComunLeds_H_
#define ComunLeds_H_

/* MODULE ComunLeds. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG ComunLeds_CODE                     
/*
** ===================================================================
**     Method      :  ComunLeds_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define ComunLeds_ClrVal() ( \
    (void)clrReg8Bits(PTP, 16)         /* PTP4=0 */ \
  )

/*
** ===================================================================
**     Method      :  ComunLeds_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define ComunLeds_SetVal() ( \
    (void)setReg8Bits(PTP, 16)         /* PTP4=1 */ \
  )

#pragma CODE_SEG DEFAULT                                   

/* END ComunLeds. */
#endif /* #ifndef __ComunLeds_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
