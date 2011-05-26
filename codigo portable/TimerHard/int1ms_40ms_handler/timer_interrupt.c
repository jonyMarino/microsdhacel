/*EVENT MODULE timer_interrupt*/
#include "Cpu.h"
#include "MethodContainer.hpp"
#include "timer_interrupt.h"


MethodContainer* listeners1ms;      //cambiar: los hice punteros por orden de inicializacion
MethodContainer* listeners40ms; 

void timerInterrupt_init(void){
  listeners40ms = new MethodContainer();
  listeners1ms = new MethodContainer(); 
 
}

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
void TI1ms_OnInterrupt(void)
{
  /* Write your code here ... */ 
  listeners1ms->executeMethods();	
}

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
void TI40ms_OnInterrupt(void)
{
  /* Write your code here ... */
  listeners40ms->executeMethods();													  
}


/*
** ===================================================================
**    Method      :  TI_add1msListener 
**    Description : 
** ===================================================================
*/
void add1msListener(struct Method * method){
  if(!method)
    return; //error
  Cpu_DisableInt();
  if(!listeners1ms)
    listeners1ms = new MethodContainer();
  listeners1ms->add(method);
  Cpu_EnableInt();    
}

/*
** ===================================================================
**     Method      :  TI_add40msListener 
**    Description : 
** ===================================================================
*/
void add40msListener(struct Method * method){
  if(!method)
    return; //error
  Cpu_DisableInt();
  if(!listeners40ms)
    listeners40ms = new MethodContainer();
  listeners40ms->add(method);
  Cpu_EnableInt();    
}


