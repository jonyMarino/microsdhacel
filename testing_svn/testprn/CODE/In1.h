/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : In1.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : InputPin
**     Version   : Bean 01.004, Driver 03.04, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 20/08/2009, 10:06
**     Abstract  :
**         This bean implements a one-bit input. Use of the bean 
**         is convenient if selected pin is used by some on-chip 
**         peripheral device (asychronous serial channel, 
**         synchronous serial channel,...) and there is some reason 
**         to read state on this pin. This is why bean neither 
**         allocate nor inicialize this pin. This bean can be used 
**         for autodiagnostics, where on-chip peripheral device is 
**         verified on functionality, for example sending and 
**         receiving of data by asychronous serial channel or 
**         synchronous serial channel or generating periodic signal 
**         by Timer.
**     Settings  :
**
**     Contents  :
**         GetVal - bool In1_GetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef In1_H_
#define In1_H_

/* MODULE In1. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG In1_CODE
/*
** ===================================================================
**     Method      :  In1_GetVal (bean InputPin)
**
**     Description :
**         Returns the value of the Input bean. If direction is
**         [input] then reads the input value of the pin and returns
**         it.
**     Parameters  : None
**     Returns     :
**         ---             - Input value
** ===================================================================
*/
#define In1_GetVal() ( \
    (getReg8(PTIAD) & 4)               /* Evaluate to port raw data */ \
  )

#pragma CODE_SEG DEFAULT

/* END In1. */
#endif /* #ifndef __In1_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
