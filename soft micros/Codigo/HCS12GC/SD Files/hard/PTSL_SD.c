/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PTSL.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitsIO
**     Version   : Bean 02.065, Driver 03.04, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 30/04/2008, 12:40 p.m.
**     Abstract  :
**         This bean "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This bean is set to work in Output direction only.
**     Settings  :
**         Port name                   : P
**
**         Bit mask of the port        : 15
**         Number of bits/pins         : 4
**         Single bit numbers          : 0 to 3
**         Values range                : 0 to 15
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTP       [600]
**         Port control register       : DDRP      [602]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    4    |   PP0_PWM0_KWP0
**                    1      |    3    |   PP1_PWM1_KWP1
**                    2      |    2    |   PP2_PWM2_KWP2
**                    3      |    1    |   PP3_PWM3_KWP3
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
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG PTSL_DATA                                            
#pragma CODE_SEG PTSL_CODE                     
#pragma CONST_SEG PTSL_CONST           /* Constant section for this module */
/*
** ===================================================================
**     Method      :  PTSL_GetMsk (bean BitsIO)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
static const byte PTSL_Table[4] = {    /* Table of mask constants */
   8, 4, 2, 1
};

static byte PTSL_GetMsk (byte PinIndex)
{
  return PinIndex<4 ? PTSL_Table[PinIndex] : 0; /* Check range and return appropriate bit mask */
}

/*
** ===================================================================
**     Method      :  PTSL_PutBit (bean BitsIO)
**
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 3)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void PTSL_PutBit(byte Bit, bool Val)
{
  byte const Mask = PTSL_GetMsk(Bit);  /* Temporary variable - put bit mask */
  if (Val) {
    setReg8Bits(PTP, Mask);            /* PTP[bit (Bit)]=1 */
  } else { /* !Val */ 
    clrReg8Bits(PTP, Mask);            /* PTP[bit (Bit)]=0 */
  } /* !Val */ 
}


/* END PTSL. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
