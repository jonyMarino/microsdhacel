/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Bits2ULN.H
**     Project   : Funciones
**     Processor : MC9S08AC128CLK
**     Beantype  : BitsIO
**     Version   : Bean 02.097, Driver 03.17, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 05/12/2008, 9:10
**     Abstract  :
**         This bean "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**     Settings  :
**         Port name                   : PTJ
**
**         Bit mask of the port        : $00C0
**         Number of bits/pins         : 2
**         Single bit numbers          : 0 to 1
**         Values range                : 0 to 3
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTJD      [$001A]
**         Port control register       : PTJDD     [$001B]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    29   |   PTJ6
**                    1      |    30   |   PTJ7
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents  :
**         GetDir    - bool Bits2ULN_GetDir(void);
**         SetDir    - void Bits2ULN_SetDir(bool Dir);
**         SetInput  - void Bits2ULN_SetInput(void);
**         SetOutput - void Bits2ULN_SetOutput(void);
**         GetVal    - byte Bits2ULN_GetVal(void);
**         PutVal    - void Bits2ULN_PutVal(byte Val);
**         GetBit    - bool Bits2ULN_GetBit(byte Bit);
**         PutBit    - void Bits2ULN_PutBit(byte Bit, bool Val);
**         SetBit    - void Bits2ULN_SetBit(byte Bit);
**         ClrBit    - void Bits2ULN_ClrBit(byte Bit);
**         NegBit    - void Bits2ULN_NegBit(byte Bit);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef Bits2ULN_H_
#define Bits2ULN_H_

/* MODULE Bits2ULN. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Bits2ULN_GetVal (bean BitsIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 3)
** ===================================================================
*/
byte Bits2ULN_GetVal(void);

/*
** ===================================================================
**     Method      :  Bits2ULN_PutVal (bean BitsIO)
**
**     Description :
**         This method writes the new output value.
**           a) direction = Input  : sets the new output value;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes the value to the
**                                   appropriate pins
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 3)
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_PutVal(byte Val);

/*
** ===================================================================
**     Method      :  Bits2ULN_GetBit (bean BitsIO)
**
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 1)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Bits2ULN_GetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Bits2ULN_PutBit (bean BitsIO)
**
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**           a) direction = Input  : sets the value of the specified
**                                   bit; this operation will be
**                                   shown on output after the
**                                   direction has been switched to
**                                   output (SetDir(TRUE);)
**           b) direction = Output : directly writes the value of the
**                                   bit to the appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 1)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_PutBit(byte Bit, bool Val);

/*
** ===================================================================
**     Method      :  Bits2ULN_ClrBit (bean BitsIO)
**
**     Description :
**         This method clears (sets to zero) the specified bit
**         of the output value.
**         [ It is the same as "PutBit(Bit,FALSE);" ]
**           a) direction = Input  : sets the specified bit to "0";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   beenswitched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "0" to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to clear (0 to 1)
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_ClrBit(byte Bit);

/*
** ===================================================================
**     Method      :  Bits2ULN_SetBit (bean BitsIO)
**
**     Description :
**         This method sets (sets to one) the specified bit of the
**         output value.
**         [ It is the same as "PutBit(Bit,TRUE);" ]
**           a) direction = Input  : sets the specified bit to "1";
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly writes "1" to the
**                                   appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to set (0 to 1)
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_SetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Bits2ULN_NegBit (bean BitsIO)
**
**     Description :
**         This method negates (inverts) the specified bit of the
**         output value.
**           a) direction = Input  : inverts the specified bit;
**                                   this operation will be shown on
**                                   output after the direction has
**                                   been switched to output
**                                   (SetDir(TRUE);)
**           b) direction = Output : directly inverts the value
**                                   of the appropriate pin
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to invert (0 to 31)
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_NegBit(byte Bit);

/*
** ===================================================================
**     Method      :  Bits2ULN_GetDir (bean BitsIO)
**
**     Description :
**         This method returns direction of the bean.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the bean (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
** ===================================================================
*/
#define Bits2ULN_GetDir() ( \
    (bool)((getReg8(PTJDD) & 0x40))    /* Return pin direction, 0==GPI, nonzero==GPO */ \
  )

/*
** ===================================================================
**     Method      :  Bits2ULN_SetDir (bean BitsIO)
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
void Bits2ULN_SetDir(bool Dir);

/*
** ===================================================================
**     Method      :  Bits2ULN_SetOutput (bean BitsIO)
**
**     Description :
**         This method sets direction of the bean to output.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Bits2ULN_SetOutput(void);

/*
** ===================================================================
**     Method      :  Bits2ULN_SetInput (bean BitsIO)
**
**     Description :
**         This method sets direction of the bean to input.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Bits2ULN_SetInput() ( \
    /*  PTJDD6=0x00, PTJDD7=0x00 */ \
    (void)clrReg8Bits(PTJDD, 0xC0) \
  )



/* END Bits2ULN. */
#endif /* #ifndef __Bits2ULN_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/