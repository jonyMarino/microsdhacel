#ifndef _TIMER_INTERRUPT_H
#define _TIMER_INTERRUPT_H

#include "Method.hpp"

void timerInterrupt_init(void);

void TI40ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI40ms_OnInterrupt (module Events)
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
void TI1ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI1ms_OnInterrupt (module Events)
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
void add1msListener(struct Method * method);

void add40msListener(struct Method * method);

#endif
