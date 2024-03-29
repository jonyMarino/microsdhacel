/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : MC9S12GC16_80
**     Version   : Bean 01.006, Driver 01.19.02, CPU db: 2.87.320
**     Datasheet : 9S12C128DGV1/D V01.05
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
**     Abstract  :
**         This bean "MC9S12GC16_80" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**     Contents  :
**         EnableInt  - void Cpu_EnableInt(void);
**         DisableInt - void Cpu_DisableInt(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __Cpu
#define __Cpu

#ifdef __cplusplus
#define __EXTERN_C  extern "C"
#else
#define __EXTERN_C
#endif


/* Active configuration define symbol */
#define PEcfg_GC32_80pin 1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "mc9s12gc32.h"


/* MODULE Cpu. */


#pragma DATA_SEG DEFAULT   

#define CPU_BUS_CLK_HZ              16000000UL /* Initial value of the bus clock frequency in Hz */

#define CPU_INSTR_CLK_HZ            16000000UL /* Initial value of the instruction clock frequency in Hz */

#define CPU_EXT_CLK_HZ              8000000UL /* Value of the main clock frequency (crystal or external clock) in Hz */

#define CPU_CORE_HCS12                 /* Specification of the core type of the selected cpu */
#define CPU_DERIVATIVE_MC9S12GC32      /* Name of the selected cpu derivative */
#define CPU_PARTNUM_MC9S12GC32CFU16    /* Part number of the selected cpu */

                               
#pragma CODE_SEG DEFAULT                                   

/* Global variables */
extern volatile byte CCR_reg;          /* Current CCR reegister */
extern byte CpuMode;                   /* Current speed mode */

void PLL_Init(void);

void Cpu_Delay100US(word us100);
/*
** ===================================================================
**     Method      :  Cpu_Delay100US (bean MC9S12GC16_80)
**
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. The method
**         is independent on selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**                         - The value of zero results in maximal 
**                           delay of approx. 6.5 seconds.
**     Returns     : Nothing
** ===================================================================
*/


#define   Cpu_SetStopMode()  {__asm("ANDCC #0x7F"); __asm("STOP"); }
/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (bean MC9S12GC16_80)
**
**     Description :
**         Set low power mode - Stop mode.
**         For more information about the stop mode see
**         documentation of this CPU.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define   Cpu_SetWaitMode()  __asm("WAI")
/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (bean MC9S12GC16_80)
**
**     Description :
**         Set low power mode - Wait mode.
**         For more information about the wait mode see
**         documentation of this CPU.
**         Release from Wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define   Cpu_DisableInt()  __DI()     /* Disable interrupts */
/*
** ===================================================================
**     Method      :  Cpu_DisableInt (bean MC9S12GC16_80)
**
**     Description :
**         Disable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define   Cpu_EnableInt()  __EI()      /* Enable interrupts */
/*
** ===================================================================
**     Method      :  Cpu_EnableInt (bean MC9S12GC16_80)
**
**     Description :
**         Enable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED     

__interrupt void Cpu_Interrupt(void);
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
__EXTERN_C void _EntryPoint(void);
/*
** ===================================================================
**     Method      :  _EntryPoint (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


#pragma CODE_SEG DEFAULT                                   

void PE_low_level_init(void);
/*
** ===================================================================
**     Method      :  PE_low_level_init (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

/* END Cpu. */

#endif /* ifndef __Cpu */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
