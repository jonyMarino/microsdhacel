/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : PTSL.H
**     Project   : contador_12_06_06
**     Processor : MC9S12GC32CFU16
**     Beantype  : BitsIO
**     Version   : Bean 02.092, Driver 03.08, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 06/05/2009, 9:16
**     Abstract  :
**         This bean "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**         Note: This bean is set to work in Output direction only.
**     Settings  :
**         Port name                   : T
**
**         Bit mask of the port        : 3
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
**                    0      |    5    |   PT0_PWM0_IOC0
**                    1      |    6    |   PT1_PWM1_IOC1
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents  :
**         PutBit - void PTSL_PutBit(byte Bit,bool Val);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef PTSL_H_
#define PTSL_H_

/* MODULE PTSL. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma CODE_SEG PTSL_CODE
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
void PTSL_PutBit(byte Bit, bool Val);

#pragma CODE_SEG DEFAULT

/* END PTSL. */
#endif /* #ifndef __PTSL_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
