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

  /* Write your code here ... */ 
  MethodContainer_execute(&listeners1ms);	
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
void add1msListener(void method(void*),void*Obj){
  struct Method * methodTmp = new(&Method,method,Obj);
  if(!methodTmp)
    return; //error
  Cpu_DisableInt();
  MethodContainer_add(&listeners1ms,methodTmp);
  Cpu_EnableInt();    
}

/*
** ===================================================================
**     Method      :  TI_add40msListener 
**    Description : 
** ===================================================================
*/
void add40msListener(void method(void*),void*Obj){
  struct Method * methodTmp = new(&Method,method,Obj);
  if(!methodTmp)
    return; //error
  Cpu_DisableInt();
  MethodContainer_add(&listeners40ms,methodTmp);
  Cpu_EnableInt();    
}


