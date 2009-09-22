/** ###################################################################
**     Filename  : Events.H
**     Project   : contador_28_04
**     Processor : MC9S12GC32CFU16
**     Beantype  : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 28/04/2006, 08:51
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         TI1_OnInterrupt - void TI1_OnInterrupt(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Display1.h"
#include "Display2.h"
#include "vx1.h"
#include "vx2.h"
#include "bits5ULN.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "AS1.h"
#include "FLASH1.h"
#include "TI2.h"
#include "TI1.h"
#include "Rele1.h"
#include "Rele2.h"
#include "Reset.h"
#include "PP4.h"
#include "PP3.h"
#include "FreeCounter.h"
#include "DL2.h"

extern void (*pfContar)(void);

void TI1_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     From bean   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


void TI2_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI2_OnInterrupt (module Events)
**
**     From bean   :  TI2 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Puls1_OnOverflow(void);
/*
** ===================================================================
**     Event       :  Puls1_OnOverflow (module Events)
**
**     From bean   :  Puls1 [PulseAccumulator]
**     Description :
**         This event is called when pulse accumulator oveflows.
**         (only when the bean is enabled - "Enable" and the events
**         are enabled - "EnableEvent"
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Puls1_OnEdge(void);
/*
** ===================================================================
**     Event       :  Puls1_OnEdge (module Events)
**
**     From bean   :  Puls1 [PulseAccumulator]
**     Description :
**         This event is called when the selected edge is detected
**         at the input pin. (only when the bean is enabled -
**         "Enable" and the events are enabled - "EnableEvent"
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void WDog1_OnWatchDog(void);
/*
** ===================================================================
**     Event       :  WDog1_OnWatchDog (module Events)
**
**     From bean   :  WDog1 [WatchDog]
**     Description :
**         This event is called whenever the watchdog starts "barking"
**         (e.g., after a specified period of the last clearing).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
