/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ADC.H
**     Project   : Metro13_07_05
**     Processor : MC9S12A256BCPV
**     Beantype  : ADC
**     Version   : Bean 01.279, Driver 01.07, CPU db: 2.87.260
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 09/09/2005, 8:39
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**         AD control register         : ATD0CTL2    [130]
**         AD control register         : ATD0CTL3    [131]
**         AD control register         : ATD0CTL4    [132]
**         AD control register         : ATD0CTL5    [133]
**         AD control register         : ATD0STAT0   [134]
**         AD control register         : ATD0STAT1   [139]
**         AD control register         : ATD0CTL23   [130]
**         AD control register         : ATD0CTL45   [132]
**         AD control register         : ATD0TEST1   [137]
**         AD control register         : ATD0DIEN    [141]
**         AD result register          : ATD0DR2     [148]
**         Interrupt name              : Vatd0
**         Interrupt enable reg.       : ATD0CTL2    [130]
**         Priority                    : 0
**         User handling procedure     : not specified
**         Number of conversions       : 1
**         AD resolution               : 10-bit
**
**         Input pins
**
**              Port name              : AD0
**              Bit number (in port)   : 2
**              Bit mask of the port   : 4
**              Port data register     : PORTAD0     [143]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-32
**     Contents  :
**         Start - byte ADC_Start(void);
**         Stop  - byte ADC_Stop(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __ADC
#define __ADC

/* MODULE ADC. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"

#pragma DATA_SEG ADC_DATA                                            
#pragma CODE_SEG ADC_CODE                     

#define ADC_EnableTrigger ADC_EnableExtChanTrigger
extern bool AD_proc;
/*
** ===================================================================
** The EnableTrigger method has been renamed to
** the EnableExtChanTrigger.
** This macro is here to keep project backward compatibility.
** ===================================================================
*/

#define ADC_DisableTrigger ADC_Stop
/*
** ===================================================================
** Now, the Stop method is used for disabling the trigger mode
** instead of the DisableTrigger.
** This macro is here to keep project backward compatibility.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED     
__interrupt void ADC_Interrupt(void);
#pragma CODE_SEG ADC_CODE                     
/*
** ===================================================================
**     Method      :  ADC_Interrupt (bean ADC)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


byte ADC_Start(char chan);
/*
** ===================================================================
**     Method      :  ADC_Start (bean ADC)
**
**     Description :
**         This method starts continuous conversion of the A/D
**         channels. When each measurement on all channels has
**         finished the <OnEnd > event may be invoked. This method
**         is not available if the <interrupt service> is disabled
**         and the device doesn't support the continuous mode. Note:
**         If time of measurement is too short and the instruction
**         clock is too slow then the conversion complete interrupt
**         and its handler may cause a system overflow.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
** ===================================================================
*/

byte ADC_Stop(void);
/*
** ===================================================================
**     Method      :  ADC_Stop (bean ADC)
**
**     Description :
**         This method stops the continuous measurement, which had
**         been started by <Start> method, or this method disables a
**         trigger mode which has been enabled by <EnableInt(Chan)
**         Trigger> or <EnableExt(Chan)Trigger> method (if these are
**         supported by HW). This method is available if at least
**         one of <Start>, <EnableInt(Chan)Trigger> or
**         <EnableExt(Chan)Trigger> methods is supported by A/D
**         converter device and it is enabled to be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
** ===================================================================
*/

void ADC_Init(void);
/*
** ===================================================================
**     Method      :  ADC_Init (bean ADC)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   

/* END ADC. */

#endif /* ifndef __ADC */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/