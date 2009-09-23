/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PP4.H
**     Project   : contador_12_06_06
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitIO
**     Version   : Bean 02.068, Driver 03.09, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 06/05/2009, 9:16
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
**                       51            |  PAD00_AN00
**             ----------------------------------------------------
**
**         Port name                   : AD0
**
**         Bit number (in port)        : 0
**         Bit mask of the port        : 1
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTAD      [624]
**         Port control register       : DDRAD     [626]
**
**         Optimization for            : speed
**     Contents  :
**         ClrVal - void PP4_ClrVal(void);
**         SetVal - void PP4_SetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef PP4_H_
#define PP4_H_

/* MODULE PP4. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG PP4_CODE
/*
** ===================================================================
**     Method      :  PP4_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define PP4_ClrVal() ( \
    (void)clrReg8Bits(PTAD, 1)         /* PTAD0=0 */ \
  )

/*
** ===================================================================
**     Method      :  PP4_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define PP4_SetVal() ( \
    (void)setReg8Bits(PTAD, 1)         /* PTAD0=1 */ \
  )

#pragma CODE_SEG DEFAULT

/* END PP4. */
#endif /* #ifndef __PP4_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
