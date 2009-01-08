/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.H
**     Project   : CVS
**     Processor : MC9S12GC32CFU16
**     Beantype  : MC9S12GC16_80
**     Version   : Bean 02.001, Driver 02.01, CPU db: 2.87.392
**     Datasheet : 9S12C128DGV1/D V01.05
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04/12/2008, 15:32
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
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
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
#define PEcfg_GC32CFU16 1

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE Cpu. */


#pragma DATA_SEG DEFAULT

#define CPU_BUS_CLK_HZ              8000000UL /* Initial value of the bus clock frequency in Hz */

#define CPU_INSTR_CLK_HZ            8000000UL /* Initial value of the instruction clock frequency in Hz */

#define CPU_EXT_CLK_HZ              16000000UL /* Value of the main clock frequency (crystal or external clock) in Hz */

#define CPU_CORE_HCS12                 /* Specification of the core type of the selected cpu */
#define CPU_DERIVATIVE_MC9S12GC32      /* Name of the selected cpu derivative */
#define CPU_PARTNUM_MC9S12GC32CFU16    /* Part number of the selected cpu */

/* Global variables */

extern volatile byte CCR_reg;          /* Current CCR reegister */
/* Entry point routine(s) prototypes */

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void _EntryPoint(void);
/*
** ===================================================================
**     Method      :  _EntryPoint (bean MC9S12GC16_80)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* Interrupt routine(s) prototypes */

/* Forward declaration of the default interrupt routine(s) */
__interrupt void Cpu_Interrupt(void);

#pragma CODE_SEG DEFAULT

#define Cpu_SetStopMode()  {__asm("ANDCC #0x7F"); __asm("STOP"); }
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

#define Cpu_SetWaitMode()  __asm("WAI")
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

void PE_low_level_init(void);
/*
** ===================================================================
**     Method      :  PE_low_level_init (bean MC9S12GC16_80)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

/* END Cpu. */

#endif /* ifndef __Cpu */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
