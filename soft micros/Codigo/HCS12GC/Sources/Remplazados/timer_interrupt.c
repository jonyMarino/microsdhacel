/*EVENT MODULE timer_interrupt*/
#include "Cpu.h"
#include "MethodContainer.h"
#include "timer_interrupt.h"


NEW_METHOD_CONTAINER(listeners1ms);
NEW_METHOD_CONTAINER(listeners40ms);

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
  extern int timer_test;
  /* Write your code here ... */ 
  MethodContainer_execute(&listeners1ms);
  if( timer_test )
    timer_test--;	
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
  MethodContainer_execute(&listeners40ms);													  
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
  MethodContainer_add(&listeners1ms,method);
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
  MethodContainer_add(&listeners40ms,method);
  Cpu_EnableInt();    
}


