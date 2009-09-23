/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Rele2.C
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
**                       79            |  PP5_PWM5_KWP5
**             ----------------------------------------------------
**
**         Port name                   : P
**
**         Bit number (in port)        : 5
**         Bit mask of the port        : 32
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
**         PutVal - void Rele2_PutVal(bool Val);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE Rele2. */

#include "Rele2.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG Rele2_DATA
#pragma CODE_SEG Rele2_CODE
#pragma CONST_SEG Rele2_CONST          /* Constant section for this module */
/*
** ===================================================================
**     Method      :  Rele2_PutVal (bean BitIO)
**
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void Rele2_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PTP, 32);              /* PTP5=1 */
  } else { /* !Val */
    clrReg8Bits(PTP, 32);              /* PTP5=0 */
  } /* !Val */
}


/* END Rele2. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
