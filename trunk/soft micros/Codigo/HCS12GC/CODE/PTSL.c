/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PTSL.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitsIO
**     Version   : Bean 02.065, Driver 03.04, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 07/11/2006, 07:53 p.m.
**     Abstract  :
**         This bean "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This bean is set to work in Output direction only.
**     Settings  :
**         Port name                   : T
**
**         Bit mask of the port        : 12
**         Number of bits/pins         : 2
**         Single bit numbers          : 0 to 1
**         Values range                : 0 to 3
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTT       [576]
**         Port control register       : DDRT      [578]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    7    |   PT2_PWM2_IOC2
**                    1      |    8    |   PT3_PWM3_IOC3
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents  :
**         PutBit - void PTSL_PutBit(byte Bit,bool Val);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE PTSL. */

#include "PTSL.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "mc9s12gc32.h"
#include "Cpu.h"

#pragma DATA_SEG PTSL_DATA                                            
#pragma CODE_SEG PTSL_CODE                     
#pragma CONST_SEG PTSL_CONST           /* Constant section for this module */

byte PTSL_GetMsk (byte PinIndex);
/*
** ===================================================================
**     Method      :  PTSL_PutBit (bean BitsIO)
**
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 1)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void PTSL_PutBit(byte Bit, bool Val)
{
  byte const Mask = PTSL_GetMsk(Bit);  /* Temporary variable - put bit mask */
  if (Val) {
    setReg8Bits(PTT, Mask);            /* PTT[bit (Bit+2)]=1 */
  } else { /* !Val */ 
    clrReg8Bits(PTT, Mask);            /* PTT[bit (Bit+2)]=0 */
  } /* !Val */ 
}

/*
** ===================================================================
**     Method      :  PTSL_GetMsk (bean BitsIO)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static const byte PTSL_Table[2] = {    /* Table of mask constants */
   8, 4
};

static byte PTSL_GetMsk (byte PinIndex)
{
  return PinIndex<2 ? PTSL_Table[PinIndex] : 0; /* Check range and return appropriate bit mask */
}


/* END PTSL. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
