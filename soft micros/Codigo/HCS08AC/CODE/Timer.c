#include <stdarg.h>
#include <stdlib.h>
#include <string.h> 


#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"
#include "Timer.h"
#include "WDog1.h"

#pragma DATA_SEG Timer_DATA                                            
#pragma CODE_SEG Timer_CODE 
#pragma CONST_SEG DEFAULT

void Timer_DefConstruct(struct Timer * self,va_list *);
void Timer_OnTime(struct Time * self);
void EnterTimer(struct Timer * timer);

const struct TimerClass TimerClass;

const struct TimerClass Timer={
  TIMER_CLASS_INITIALIZATION(TimerClass,Timer,Object,Timer_DefConstruct,Timer_Destruct,NULL,NULL,Timer_OnTime)
  
};

struct Timer ** Timers=NULL; 
uint timers;
uint alloced_timers;
ulong cuenta;

/*
** ===================================================================
**     Method      :  Timer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del contador
** ===================================================================
*/
void Timer_Construct(struct Timer * self,ulong tiempo){
  
  self->tiempo= tiempo;
  self->next_cuenta=cuenta+tiempo;
  
  if(cuenta >= self->next_cuenta)
    self->of=TRUE;  
  else
    self->of=FALSE;
  
  EnterTimer(self);

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
  if(!self)
    return NULL;
  Timer_Stop(self);
  
  return self;
}

/*
** ===================================================================
**     Method      :  EnterTimer 
**    Description : Ingresa el Timer en el loop de tiempo.
** ===================================================================
*/
void EnterTimer(struct Timer * timer){
size_t i;
struct Timer ** ptmp;

  if(Timers==NULL){
    Cpu_DisableInt(); 
    Timers=calloc(10,sizeof(struct Timer *)); //inicio con 10 timers
    Cpu_EnableInt(); 
    timers=0;
    alloced_timers=10;
  }
  
  if(timers>=alloced_timers){
    uint mem =alloced_timers*2;
    ptmp=realloc(Timers,sizeof(struct Timer *)*mem);
    memset(ptmp+alloced_timers,0,(mem-alloced_timers)*sizeof(struct Timer *));
    alloced_timers = mem;
    if(ptmp){      
      Cpu_DisableInt();
      Timers=ptmp;
      Cpu_EnableInt();
    }else
      return;
  }

  for(i=0;i<alloced_timers;i++){
    if(Timers[i]==NULL){
      timer->container=&Timers[i];
      Timers[i]=timer;
      Cpu_DisableInt();
      timers++;
      Cpu_EnableInt();
      return; 
    }
  }
  
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
  ulong cuentaTmp;
  ulong nextCuentaTmp;
  ulong tiempoTmp;
  
  Cpu_DisableInt();
    cuentaTmp = cuenta;
    nextCuentaTmp = self->next_cuenta;
    tiempoTmp = self->tiempo;
  Cpu_EnableInt();
  
  if(self->of)
    comp= cuentaTmp <= nextCuentaTmp;
  else
    comp= cuentaTmp >= nextCuentaTmp;
  
  if (comp ){
    nextCuentaTmp+=  (long)nextCuentaTmp - cuentaTmp + tiempoTmp;
    Cpu_DisableInt();
      self->next_cuenta=nextCuentaTmp;    
      if(cuenta >= nextCuentaTmp){
        self->of=TRUE;        
      }
    Cpu_EnableInt();
    (**(struct TimerClass**)self).onTime(self);
  }
}


/*
** ===================================================================
**     Method      :  IncTimers 
**    Description : Incrementa el valor de la cuenta de Todos los timers
** ===================================================================
*/
void IncTimers(int inc){ 
  Byte i;
  
  cuenta+=inc;
   
  for(i=0;i<alloced_timers;i++){
    if(Timers[i]){ 
      TimerComp(Timers[i]);      
    }
  }
}

/*
** ===================================================================
**     Method      :  Timer_isfinish 
**    Description : Indica si ya termino la cuenta
** ===================================================================
*/
uchar Timer_isfinish(struct Timer * self){
  return self->container==NULL;
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
  
  Cpu_DisableInt();
    cuentaTmp = cuenta;
    nextCuentaTmp = self->next_cuenta;
    tiempoTmp = self->tiempo;
  Cpu_EnableInt();
   
  return cuentaTmp - (nextCuentaTmp - tiempoTmp);
}

/*
** ===================================================================
**     Method      :  Timer_Restart 
**    Description : Reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_Restart(struct Timer * self){
  self->next_cuenta=cuenta + self->tiempo ;
  if(cuenta >= self->next_cuenta)
    self->of=TRUE;  
  else
    self->of=FALSE;
  if(Timer_isfinish(self))
    EnterTimer(self);
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
**     Method      :  Timer_Sys_getTime 
**    Description : Obtiene el tiempo a alcanzar
** ===================================================================
*/
ulong Timer_Sys_getTime(struct Timer * self){
  return self->tiempo;
}

/*
** ===================================================================
**     Method      :  Timer_Stop 
**    Description : Detiene la cuenta del timer
** ===================================================================
*/
void Timer_Stop(struct Timer * self){
  
  if(self->container){ 
    Cpu_DisableInt();
    *(self->container)=NULL;
    Cpu_EnableInt();  
    self->container=NULL;
    timers--;
  }
}

#pragma CODE_SEG Timer_CODE


