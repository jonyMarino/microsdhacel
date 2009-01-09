/*MODULE: MethodTimer.c*/

#include "MethodTimer.h"




#include <stdarg.h>
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"
#include "Timer.h"
#include "FTimer.h"

#pragma DATA_SEG MethodTimer_DATA                                            
#pragma CODE_SEG MethodTimer_CODE 
#pragma CONST_SEG DEFAULT

void MTimer_OnTime(void * self);
void MTimer_DefConstruct(void * self,va_list *);

const struct TimerClass MethodTimer={
  TIMER_CLASS_INITIALIZATION(TimerClass,MethodTimer,Timer,MTimer_DefConstruct,Timer_Destruct,NULL,NULL,MTimer_OnTime)
};


/*
** ===================================================================
**     Method      :  FTimer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void MTimer_Construct(void * self,ulong tiempo,void (*pf)(void*),void * Obj){
  struct MethodTimer * _timer=self;
  
  Timer_Construct((struct Timer *) self,tiempo);
  _timer->pf=pf;
  _timer->Obj=Obj;    
}

/*
** ===================================================================
**     Method      :  FTimer_DefConstruct 
**    Description : Metodo por defecto para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void MTimer_DefConstruct(void * self,va_list *args){
  MTimer_Construct(self,va_arg(*args,ulong),va_arg(*args,void*),va_arg(*args,void*));
}

/*
** ===================================================================
**     Method      :  FTimer_DefConstruct 
**    Description : Metodo por defecto para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void MTimer_setMetodo(void * _self,void (*pf)(void*),void * Obj){
  struct MethodTimer * _timer=_self;
  _timer->pf=pf;
  _timer->Obj=Obj;  
}
/*
** ===================================================================
**     Method      :  FTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void MTimer_OnTime(void * self){
  struct MethodTimer * _timer=self;
  (*(_timer->pf))(_timer->Obj);
}

#pragma CODE_SEG MethodTimer_CODE

