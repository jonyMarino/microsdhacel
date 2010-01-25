/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PP3.C
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
**                       52            |  PAD01_AN01
**             ----------------------------------------------------
**
**         Port name                   : AD0
**
**         Bit number (in port)        : 1
**         Bit mask of the port        : 2
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
**         ClrVal - void PP3_ClrVal(void);
**         SetVal - void PP3_SetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE PP3. */

#include "PP3.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG PP3_DATA
#pragma CODE_SEG PP3_CODE
#pragma CONST_SEG PP3_CONST            /* Constant section for this module */
/*
** ===================================================================
**     Method      :  PP3_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void PP3_ClrVal(void)

**  This method is implemented as a macro. See PP3.h file.  **
*/

/*
** ===================================================================
**     Method      :  PP3_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void PP3_SetVal(void)

**  This method is implemented as a macro. See PP3.h file.  **
*/


/* END PP3. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/