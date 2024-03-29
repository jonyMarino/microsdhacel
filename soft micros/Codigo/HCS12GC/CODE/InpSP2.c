/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : InpSP2.C
**     Project   : pad3
**     Processor : MC9S12GC32CFA16
**     Beantype  : InputPin
**     Version   : Bean 01.004, Driver 03.02, CPU db: 2.87.323
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 07/03/2008, 15:36
**     Abstract  :
**
**     Settings  :
**
**     Contents  :
**         GetVal - bool InpSP2_GetVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE InpSP2. */

#include "InpSP2.h"
  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "mc9s12gc32.h"
#include "Cpu.h"

#pragma DATA_SEG InpSP2_DATA                                            
#pragma CODE_SEG InpSP2_CODE                     
#pragma CONST_SEG InpSP2_CONST         /* Constant section for this module */


void InpSP2_Init(void){
  
/* ATDDIEN: IEN2=1 */
  
  setReg8Bits(ATDDIEN, 4); 
}
/*
** ===================================================================
**     Method      :  InpSP2_GetVal (bean InputPin)
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
bool InpSP2_GetVal(void)

**  This method is implemented as a macro. See InpSP2.h file.  **
*/


/* END InpSP2. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
