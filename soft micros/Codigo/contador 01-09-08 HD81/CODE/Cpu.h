/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.H
**     Project   : contador_12_06_06
**     Processor : MC9S12GC16CFU16
**     Beantype  : MC9S12GC16_80
**     Version   : Bean 01.006, Driver 01.19.02, CPU db: 2.87.320
**     Datasheet : 9S12C128DGV1/D V01.05
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 18/04/2008, 10:48 a.m.
**     Abstract  :
**         This bean "MC9S12GC16_80" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**     Contents  :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
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

/* Active configuration define symbol */
#define PEcfg_GC16_48pin 1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"

/* MODULE Cpu. */


#pragma DATA_SEG DEFAULT                                  
#pragma CODE_SEG DEFAULT                                   

/* Global variables */
extern volatile byte CCR_reg;          /* Current CCR reegister */
extern byte CpuMode;                   /* Current speed mode */

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


/*Shadow variables*/
extern byte Shadow_M;                  /* Shadow variable for I/O beans */


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
void _EntryPoint(void);
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
