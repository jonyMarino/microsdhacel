/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : WDog1.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC64CFU16
**     Beantype  : WatchDog
**     Version   : Bean 02.082, Driver 01.10, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 04/03/2009, 12:37
**     Abstract  :
**         This device "WatchDog" implements a watchdog.
**         When enabled, the watchdog timer counts until it reaches
**         a critical value corresponding to the period specified
**         in 'Properties'. Then, the watchdog causes a CPU reset.
**         Applications may clear the timer before it reaches the critical
**         value. The timer then restarts the watchdog counter.
**         Watchdog is used for increasing the safety of the system
**         (unforeseeable situations can cause system crash or an
**         infinite loop - watchdog can restart the system or handle
**         the situation).
**
**         Note: Watchdog can be enabled or disabled in the initialization
**               code only. If the watchdog is once enabled user have
**               to call Clear method in defined time intervals.
**     Settings  :
**         Watchdog causes             : Reset CPU
**
**         Initial Watchdog state      : Enabled
**
**         Mode of operation           : Normal
**
**
**         High speed mode
**           Watchdog period/frequency
**             microseconds            : 2097152
**             milliseconds            : 2097
**             seconds                 : 2
**
**         Run register                : COPCTL    [60]
**         Mode register               : COPCTL    [60]
**         Prescaler register          : COPCTL    [60]
**     Contents  :
**         Clear - byte WDog1_Clear(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __WDog1
#define __WDog1

/* MODULE WDog1. */

#include "Cpu.h"

#pragma CODE_SEG WDog1_CODE

/*
** ===================================================================
**     Method      :  WDog1_Clear (bean WatchDog)
**
**     Description :
**         Clears the watchdog timer (it makes the timer restart from
**         zero).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - The Bean is disabled
** ===================================================================
*/
#define WDog1_Clear() (ARMCOP = 85, ARMCOP = 170, ERR_OK)

#pragma CODE_SEG DEFAULT

/* END WDog1. */

#endif /* ifndef __WDog1 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
