/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Display1.H
**     Project   : Funciones
**     Processor : MC9S08AC128CLK
**     Beantype  : BitsIO
**     Version   : Bean 02.097, Driver 03.17, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 05/12/2008, 9:02
**     Abstract  :
**         This bean "BitsIO" implements a multi-bit input/output.
**         It uses selected pins of one 1-bit to 8-bit port.
**     Settings  :
**         Port name                   : PTA
**
**         Bit mask of the port        : $00FF
**         Number of bits/pins         : 8
**         Single bit numbers          : 0 to 7
**         Values range                : 0 to 255
**
**         Initial direction           : Output (direction can be changed)
**         Safe mode                   : yes
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         Port data register          : PTAD      [$0000]
**         Port control register       : PTADD     [$0001]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    34   |   PTA0
**                    1      |    35   |   PTA1
**                    2      |    36   |   PTA2
**                    3      |    37   |   PTA3
**                    4      |    38   |   PTA4
**                    5      |    39   |   PTA5
**                    6      |    40   |   PTA6
**                    7      |    41   |   PTA7
**             ----------------------------------------------------
**
**         Optimization for            : speed
**     Contents  :
**         GetDir    - bool Display1_GetDir(void);
**         SetDir    - void Display1_SetDir(bool Dir);
**         SetInput  - void Display1_SetInput(void);
**         SetOutput - void Display1_SetOutput(void);
**         GetVal    - byte Display1_GetVal(void);
**         PutVal    - void Display1_PutVal(byte Val);
**         GetBit    - bool Display1_GetBit(byte Bit);
**         PutBit    - void Display1_PutBit(byte Bit, bool Val);
**         SetBit    - void Display1_SetBit(byte Bit);
**         ClrBit    - void Display1_ClrBit(byte Bit);
**         NegBit    - void Display1_NegBit(byte Bit);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef Display1_H_
#define Display1_H_

/* MODULE Display1. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#define P_DISPLAY1 PTAD

/*
** ===================================================================
**     Method      :  Display1_GetVal (bean BitsIO)
**
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 255)
** ===================================================================
*/
byte Display1_GetVal(void);

/*
** ===================================================================
**     Method      :  Display1_PutVal (bean BitsIO)
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
**         Val        - Output value (0 to 255)
**     Returns     : Nothing
** ===================================================================
*/
void Display1_PutVal(byte Val);

/*
** ===================================================================
**     Method      :  Display1_GetBit (bean BitsIO)
**
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 7)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Display1_GetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Display1_PutBit (bean BitsIO)
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
**         Bit        - Number of the bit (0 to 7)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Display1_PutBit(byte Bit, bool Val);

/*
** ===================================================================
**     Method      :  Display1_ClrBit (bean BitsIO)
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
**         Bit        - Number of the bit to clear (0 to 7)
**     Returns     : Nothing
** ===================================================================
*/
void Display1_ClrBit(byte Bit);

/*
** ===================================================================
**     Method      :  Display1_SetBit (bean BitsIO)
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
**         Bit        - Number of the bit to set (0 to 7)
**     Returns     : Nothing
** ===================================================================
*/
void Display1_SetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Display1_NegBit (bean BitsIO)
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
void Display1_NegBit(byte Bit);

/*
** ===================================================================
**     Method      :  Display1_GetDir (bean BitsIO)
**
**     Description :
**         This method returns direction of the bean.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the bean (FALSE or TRUE)
**                      FALSE = Input, TRUE = Output
** ===================================================================
*/
#define Display1_GetDir() ( \
    (bool)((getReg8(PTADD) & 0x01))    /* Return pin direction, 0==GPI, nonzero==GPO */ \
  )

/*
** ===================================================================
**     Method      :  Display1_SetDir (bean BitsIO)
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
void Display1_SetDir(bool Dir);

/*
** ===================================================================
**     Method      :  Display1_SetOutput (bean BitsIO)
**
**     Description :
**         This method sets direction of the bean to output.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Display1_SetOutput(void);

/*
** ===================================================================
**     Method      :  Display1_SetInput (bean BitsIO)
**
**     Description :
**         This method sets direction of the bean to input.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define Display1_SetInput() ( \
    /*  PTADD0=0x00, PTADD1=0x00, PTADD2=0x00, PTADD3=0x00, PTADD4=0x00, PTADD5=0x00, PTADD6=0x00, PTADD7=0x00 */ \
    (void)clrReg8Bits(PTADD, 0xFF) \
  )



/* END Display1. */
#endif /* #ifndef __Display1_H_ */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/