/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : In1.C
**     Project   : Funciones
**     Processor : MC9S08AC128CLK
**     Beantype  : BitIO
**     Version   : Bean 02.071, Driver 03.16, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 05/12/2008, 9:10
**     Abstract  :
**         This bean "BitIO" implements an one-bit input/output.
**         It uses one bit/pin of a port.
**         Methods of this bean are mostly implemented as a macros
**         (if supported by target language and compiler).
**     Settings  :
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       4             |  PTF0_TPM1CH2
**             ----------------------------------------------------
**
**         Port name                   : PTF
**
**         Bit number (in port)        : 0
**         Bit mask of the port        : $0001
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0
**         Initial pull option         : off
**
**         Port data register          : PTFD      [$000A]
**         Port control register       : PTFDD     [$000B]
**
**         Optimization for            : speed
**     Contents  :
**         GetDir    - bool In1_GetDir(void);
**         SetDir    - void In1_SetDir(bool Dir);
**         SetInput  - void In1_SetInput(void);
**         SetOutput - void In1_SetOutput(void);
**         GetVal    - bool In1_GetVal(void);
**         PutVal    - void In1_PutVal(bool Val);
**         ClrVal    - void In1_ClrVal(void);
**         SetVal    - void In1_SetVal(void);
**         NegVal    - void In1_NegVal(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
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
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  In1_GetVal (bean BitIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pin and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---             - Input value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)

** ===================================================================
*/
/*
bool In1_GetVal(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_PutVal (bean BitIO)
**
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val             - Output value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
**     Returns     : Nothing
** ===================================================================
*/
void In1_PutVal(bool Val)
{
  if (Val) {
    setReg8Bits(PTFD, 0x01);           /* PTFD0=0x01 */
    Shadow_PTF |= 0x01;                /* Set-up shadow variable */
  } else { /* !Val */
    clrReg8Bits(PTFD, 0x01);           /* PTFD0=0x00 */
    Shadow_PTF &= ~0x01;               /* Set-up shadow variable */
  } /* !Val */
}

/*
** ===================================================================
**     Method      :  In1_ClrVal (bean BitIO)
**
**     Description :
**         This method clears (sets to zero) the output value.
**           a) direction = Input  : sets the output value to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void In1_ClrVal(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_SetVal (bean BitIO)
**
**     Description :
**         This method sets (sets to one) the output value.
**           a) direction = Input  : sets the output value to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void In1_SetVal(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_NegVal (bean BitIO)
**
**     Description :
**         This method negates (inverts) the output value.
**           a) direction = Input  : inverts the output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly inverts the value
**                                   of the appropriate pin
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void In1_NegVal(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_GetDir (bean BitIO)
**
**     Description :
**         This method returns direction of the bean.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the bean (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
** ===================================================================
*/
/*
bool In1_GetDir(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_SetDir (bean BitIO)
**
**     Description :
**         This method sets direction of the bean.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Dir        - Direction to set (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
**     Returns     : Nothing
** ===================================================================
*/
void In1_SetDir(bool Dir)
{
  if (Dir) {
    setReg8(PTFD, (getReg8(PTFD) & (~0x01)) | (Shadow_PTF & 0x01)); /* PTFD0=Shadow_PTF[bit 0] */
    setReg8Bits(PTFDD, 0x01);          /* PTFDD0=0x01 */
  } else { /* !Dir */
    clrReg8Bits(PTFDD, 0x01);          /* PTFDD0=0x00 */
  } /* !Dir */
}

/*
** ===================================================================
**     Method      :  In1_SetInput (bean BitIO)
**
**     Description :
**         This method sets direction of the bean to input.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void In1_SetInput(void)

**  This method is implemented as a macro. See In1.h file.  **
*/

/*
** ===================================================================
**     Method      :  In1_SetOutput (bean BitIO)
**
**     Description :
**         This method sets direction of the bean to output.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void In1_SetOutput(void)
{
  setReg8(PTFD, (getReg8(PTFD) & (~0x01)) | (Shadow_PTF & 0x01)); /* PTFD0=Shadow_PTF[bit 0] */
  setReg8Bits(PTFDD, 0x01);            /* PTFDD0=0x01 */
}


/* END In1. */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
