/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : trx.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitIO
**     Version   : Bean 02.059, Driver 03.05, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
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
**                       65            |  PS2
**             ----------------------------------------------------
**
**         Port name                   : S
**
**         Bit number (in port)        : 2
**         Bit mask of the port        : 4
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTS       [584]
**         Port control register       : DDRS      [586]
**
**         Optimization for            : speed
**     Contents  :
**         ClrVal - void trx_ClrVal(void);
**         SetVal - void trx_SetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef trx_H_
#define trx_H_

/* MODULE trx. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
//#include "mc9s12gc32.h"
#include "mc9s12gc32.h"
#include "Cpu.h"

#pragma CODE_SEG trx_CODE                     
/*
** ===================================================================
**     Method      :  trx_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define trx_ClrVal() ( \
    (void)clrReg8Bits(PTS, 4)          /* PTS2=0 */ \
  )

/*
** ===================================================================
**     Method      :  trx_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define trx_SetVal() ( \
    (void)setReg8Bits(PTS, 4)          /* PTS2=1 */ \
  )

#pragma CODE_SEG DEFAULT                                   

/* END trx. */
#endif /* #ifndef __trx_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
