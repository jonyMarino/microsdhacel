/*MODULE TimerFlag*/


#include <stdarg.h>
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"
#include "Timer.h"
#include "TimerFlag.h"

 
#pragma CONST_SEG DEFAULT

void TimerFlag_OnTime(void * _self);
void TimerFlag_DefConstruct(void * _self,va_list *);
void TimerFlag_Construct(void * _self,ulong tiempo);

const struct TimerClass TimerFlag={
  TIMER_CLASS_INITIALIZATION(TimerClass,TimerFlag,Timer,TimerFlag_DefConstruct,Timer_Destruct,NULL,NULL,TimerFlag_OnTime)
};

/*
** ===================================================================
**     Method      :  FTimer_DefConstruct 
**    Description : Metodo por defecto para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void TimerFlag_DefConstruct(void * self,va_list *args){
  TimerFlag_Construct(self,va_arg(*args,ulong));
}
/*
** ===================================================================
**     Method      :  FTimer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void TimerFlag_Construct(void * _self,ulong tiempo){
  struct TimerFlag * self = _self;
  Timer_Construct((struct Timer *) self,tiempo);
  self->flag = FALSE;    
}



/*
** ===================================================================
**     Method      :  FTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void TimerFlag_OnTime(void * _self){
  struct TimerFlag * self = _self;
  self->flag = TRUE;  
}
/*
** ===================================================================
**     Method      :  TimerFlag_reset 
**    Description : 
** ===================================================================
*/
void TimerFlag_reset(void * _self){
  struct TimerFlag * self = _self;
  self->flag = FALSE;  
}

