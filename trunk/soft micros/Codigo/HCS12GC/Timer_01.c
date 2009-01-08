#include <stdarg.h>
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"
#include "Timer_01.h"
#include "WDog1.h"

void Timer_DefConstruct(struct Timer * self,va_list *);
void Timer_OnTime(struct Time * self);
void EnterTimer(struct Timer * timer);

const T_Timer TTimer={
  sizeof(struct Timer),
  Timer_DefConstruct,
  NULL,
  Timer_Destruct,
  NULL,
  Timer_OnTime
};

const T_Timer * const Timer=&TTimer;

struct Timer ** Timers=NULL; 
uint timers;
uint alloced_timers;

/*
** ===================================================================
**     Method      :  Timer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del contador
** ===================================================================
*/
void Timer_Construct(struct Timer * self,ulong tiempo){
  
  self->tiempo= tiempo;
  self->cuenta=0;
  self->finished=FALSE;
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
  Cpu_DisableInt();
  *(self->container)=NULL;
  Cpu_EnableInt();  
  if(self->container){ 
    self->container=NULL;
    timers--;
  }
  self->finished=FALSE;
  
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
    Timers=malloc(sizeof(struct Timer *)*10); //inicio con 10 timers
    timers=0;
    alloced_timers=10;
  }
  
  if(timers>=alloced_timers){
    alloced_timers=alloced_timers*2;
    ptmp=realloc(Timers,sizeof(struct Timer *)*alloced_timers);
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
      timers++;
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
  self->finished=TRUE;
}

/*
** ===================================================================
**     Method      :  IncTimer 
**    Description : Incrementa el valor de la cuenta del Timer
** ===================================================================
*/
void TimerInc(struct Timer * self,Byte inc){  
  self->cuenta+=inc;
  if (self->cuenta >= self->tiempo){
    self->cuenta=  self->cuenta - self->tiempo;
    (* (self->_timer->OnTime))(self);
  }
}


/*
** ===================================================================
**     Method      :  IncTimers 
**    Description : Incrementa el valor de la cuenta de Todos los timers
** ===================================================================
*/
void IncTimers(Byte inc){ 
Byte i;
  for(i=0;i<alloced_timers;i++){
    if(Timers[i] && !(Timers[i])->finished){ 
      Cpu_DisableInt();
//      while((word)Timers[i]==3)
//            WDog1_Clear();
      TimerInc(Timers[i],inc); 
      
      Cpu_EnableInt();  
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
  return self->finished;
}

/*
** ===================================================================
**     Method      :  Timer_getCuenta 
**    Description : Regresa la cuenta actual que se resetea al llegar al tiempo
** ===================================================================
*/
ulong Timer_getCuenta(struct Timer * self){
ulong cuenta;  
  Cpu_DisableInt();
  cuenta=self->cuenta;
  Cpu_EnableInt();
  return cuenta;
}

/*
** ===================================================================
**     Method      :  Timer_Restart 
**    Description : Reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_Restart(struct Timer * self){
  Cpu_DisableInt();
  self->cuenta=0;
  self->finished=FALSE;
  Cpu_EnableInt();
}

/*
** ===================================================================
**     Method      :  Timer_setTime 
**    Description : Setea un tiempo nuevo y reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_setTime(struct Timer * self,ulong tiempo){
  Timer_Restart(self);					 
  self->tiempo=tiempo;
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
  self->finished=TRUE;
}


