/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : In1.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : InputPin
**     Version   : Bean 01.004, Driver 03.02, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         GetVal - bool In1_GetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE In1. */

#include "In1.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
//#include "IO_Map.h"
#include "mc9s12gc32.h"
#include "Cpu.h"

#pragma DATA_SEG In1_DATA                                            
#pragma CODE_SEG In1_CODE                     
#pragma CONST_SEG In1_CONST            /* Constant section for this module */
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
/*
bool In1_GetVal(void)

**  This method is implemented as a macro. See In1.h file.  **
*/


/* END In1. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/