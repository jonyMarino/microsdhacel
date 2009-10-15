#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 


#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"
#include "Timer.h"
#include "BaseTimersGral.h"

#pragma DATA_SEG Timer_DATA                                            
#pragma CODE_SEG Timer_CODE 
#pragma CONST_SEG DEFAULT

void Timer_DefConstruct(struct Timer * self,va_list *);
void Timer_OnTime(struct Time * self);
//void EnterTimer(struct Timer * timer);

const struct TimerClass TimerClass;

const struct TimerClass Timer={
  TIMER_CLASS_INITIALIZATION(TimerClass,Timer,Object,Timer_DefConstruct,Timer_Destruct,NULL,NULL,Timer_OnTime)
  
};

/*
** ===================================================================
**     Method      :  Timer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del contador
** ===================================================================
*/
void Timer_Construct(struct Timer * self,ulong tiempo){
  void * baseTimer = BaseTimersGral_getInstance(); 
  ulong cuenta = BaseTimers_getCuenta(baseTimer);
  self->baseTimer = baseTimer;
  self->tiempo= tiempo;
  self->next_cuenta=cuenta+tiempo;
  
  if(cuenta >= self->next_cuenta)
    self->of=TRUE;  
  else
    self->of=FALSE;
    
  add(baseTimer,self);

}

/*
** ===================================================================
**     Method      :  Timer_DefConstruct 
**    Description : Constructor por defecto
** ===================================================================
*/
void Timer_DefConstruct(struct Timer * self,va_list *args){
  Timer_Construct(self,va_arg(*args,ulong));
}

/*
** ===================================================================
**     Method      :  Timer_Destruct 
**    Description : Metodo para destruir el Timer
** ===================================================================
*/
void * Timer_Destruct(struct Timer * self){
  Timer_Stop(self);  
  return self;
}

/*
** ===================================================================
**     Method      :  setBaseTimer 
**    Description : setea la entrada de ticks del timer
** ===================================================================
*/
void setBaseTimer(void * _self,void * base){
  struct Timer * self = _self;  
  self->baseTimer = base;
}
/*
** ===================================================================
**     Method      :  Timer_OnTime 
**    Description : Evento al llegar al tiempo fijado
** ===================================================================
*/
void Timer_OnTime(struct Timer * self){
  Timer_Stop(self);
}

/*
** ===================================================================
**     Method      :  IncTimer 
**    Description : Incrementa el valor de la cuenta del Timer
** ===================================================================
*/
void TimerComp(struct Timer * self){  
  bool comp;
  void * baseTimer = self->baseTimer;  
  ulong cuentaTmp = BaseTimers_getCuenta( baseTimer );
  ulong nextCuentaTmp = self->next_cuenta;
  ulong tiempoTmp = self->tiempo;
  
  if(self->of)
    comp= cuentaTmp <= nextCuentaTmp;
  else
    comp= cuentaTmp >= nextCuentaTmp;
  
  if (comp ){
    int error = cuentaTmp - nextCuentaTmp;
    error = (error<0)?-error:error;
    nextCuentaTmp +=   error + tiempoTmp;
    self->next_cuenta=nextCuentaTmp;    
    if(cuentaTmp >= nextCuentaTmp){
      self->of=TRUE;        
    }
    (**(struct TimerClass**)self).onTime(self);
  }
}

/*
** ===================================================================
**     Method      :  Timer_getCuenta 
**    Description : Regresa la cuenta actual que se resetea al llegar al tiempo
** ===================================================================
*/
ulong Timer_getCuenta(struct Timer * self){
  ulong cuentaTmp;
  ulong nextCuentaTmp;
  ulong tiempoTmp;
  
  if(Timer_isfinish(self) )
    return 0;
  cuentaTmp = BaseTimers_getCuenta( self->baseTimer );

  Cpu_DisableInt();
    nextCuentaTmp = self->next_cuenta;
    tiempoTmp = self->tiempo;
  Cpu_EnableInt();
   
  return cuentaTmp - (nextCuentaTmp - tiempoTmp);
}



/*
** ===================================================================
**     Method      :  Timer_setTime 
**    Description : Setea un tiempo nuevo y reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_setTime(struct Timer * self,ulong tiempo){					 
  self->tiempo=tiempo;
  Timer_Restart(self);
}

/*
** ===================================================================
**     Method      :  Timer_Restart 
**    Description : Reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_Restart(struct Timer * self){
  ulong cuenta = BaseTimers_getCuenta( self->baseTimer );
  self->next_cuenta= cuenta + self->tiempo ;
  if(cuenta >= self->next_cuenta)
    self->of=TRUE;  
  else
    self->of=FALSE;
  if(Timer_isfinish(self))
    add(self->baseTimer,self);
}

/*
** ===================================================================
**     Method      :  Timer_isfinish 
**    Description : Indica si ya termino la cuenta
** ===================================================================
*/
uchar Timer_isfinish(struct TimerAllocable * self){
//uchar Timer_isfinish(struct Timer * self){
  if(self->baseTimer)
    return !contains(self->baseTimer,self);
  return TRUE;
}

/*
** ===================================================================
**     Method      :  Timer_getTime 
**    Description : Obtiene el tiempo a alcanzar
** ===================================================================
*/
ulong Timer_getTime(struct Timer * self){
  return self->tiempo;
}

/*
** ===================================================================
**     Method      :  Timer_Stop 
**    Description : Detiene la cuenta del timer
** ===================================================================
*/
void Timer_Stop(struct Timer * self){  
  moveOut(self->baseTimer,self);
}

#pragma CODE_SEG Timer_CODE


