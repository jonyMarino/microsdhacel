/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ADC1.H
**     Project   : _7_12
**     Processor : MC9S12GC32CFU16
**     Beantype  : Init_ADC
**     Version   : Bean 01.079, Driver 01.02, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 14/12/2005, 09:44
**     Abstract  :
**          This file implements the ADC (ADC0) module initialization
**          according to the Peripheral Initialization Bean settings,
**          and defines interrupt service routines prototypes.The ADC module
**          is an 8-channel (16-channel), 10-bit, multiplexed input successive
**          approximation analog-to-digital converter. Refer to device electrical
**          specifications for ATD accuracy. The block is designed to be 
**          upwards compatible with the 68HC11 standard 8-bit A/D converter.
**          In addition, there are new operating modes that are unique to 
**          the HC12 design.
**          Features :
**          - 8/10 Bit Resolution.
**          - 7msec, 10-Bit Single Conversion Time.
**          - Sample Buffer Amplifier.
**          - Programmable Sample Time.
**          - Left/Right Justified, Signed/Unsigned Result Data.
**          - External Trigger Control.
**          - Conversion Completion Interrupt Generation.
**          - Analog Input Multiplexer for 8 (16)Analog Input Channels.
**          - Analog/Digital Input Pin Multiplexing.
**          - 1 to 8 (1 to 16)Conversion Sequence Lengths.
**          - Continuous Conversion Mode.
**          - Multiple Channel Scans.
**     Comment   :
**         sacar setReg8 ( ATD0TL5, XXX);
**     Settings  :
**          Bean name                                      : ADC1
**          Device                                         : ADC0
**          Sample Time                                    : 16 A/D conversion clock periods
**          Prescaler                                      : 3
**          Frequency                                      : 500 kHz
**          Channel select code                            : AN0
**          Channel select code                            : AN0
**          Conv. sequence length                          : 4
**          Conv. sequence length                          : 8
**          Conversion mode                                : Single conversion
**          Channel sample mode                            : Only one channel
**          Fast flag clear all                            : Enabled
**          Wrap around channel                            : AN15
**          External trigger source                        : AN15
**          Wrap around channel                            : AN7
**          External trigger source                        : AN7
**          External trigger                               : Disabled
**          External trigger control                       : Falling edge
**          Conv. results are placed in                    : Corresponding result register
**          Result data formats                            : 10-bit/right justified/unsigned
**          Background debug freeze                        : Freeze Immediately
**          Special channel conversion                     : Disabled
**          Power down in Wait mode                        : Enabled
**          AN0                                            : Disabled
**          AN1                                            : Disabled
**          AN2                                            : Disabled
**          AN3                                            : Disabled
**          AN4                                            : Disabled
**          AN5                                            : Enabled
**          Pin                                            : PAD05_AN05
**          Pin Signal                                     : 
**          Digital Input                                  : Disabled
**          AN6                                            : Enabled
**          Pin                                            : PAD06_AN06
**          Pin Signal                                     : 
**          Digital Input                                  : Disabled
**          ETRIG/AN7                                      : Disabled
**          AN7                                            : Disabled
**          AN8                                            : Disabled
**          AN9                                            : Disabled
**          AN10                                           : Disabled
**          AN11                                           : Disabled
**          AN12                                           : Disabled
**          AN13                                           : Disabled
**          AN14                                           : Disabled
**          ETRIG/AN15                                     : Disabled
**          AN15                                           : Disabled
**          Sequence Complete                              : Enabled
**          Interrupt                                      : Vatd0
**          Priority                                       : maximal priority
**          ISR name                                       : ADC_Interrupt
**          Call Init in CPU init. code                    : yes
**          Module                                         : Enabled
**     Contents  :
**         Init - void ADC1_Init(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
#ifndef __ADC1
#define __ADC1

/* MODULE ADC1. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "Cpu.h"





void ADC1_Init(void);
/*
** ===================================================================
**     Method      :  ADC1_Init (bean Init_ADC)
**
**     Description :
**         This method initializes registers of the ADC module
**         according to this Peripheral Initialization Bean settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the bean for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
** The interrupt service routine must be implemented by user in one
** of the user modules (see ADC1.c file for more information).
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED     
__interrupt void ADC_Interrupt(void);
#pragma CODE_SEG DEFAULT                                   
/* END ADC1. */

#endif /* ifndef __ADC1 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
