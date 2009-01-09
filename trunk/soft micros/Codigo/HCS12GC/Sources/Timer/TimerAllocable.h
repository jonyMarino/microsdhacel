#ifndef _TIMER_ALLOCABLE_H
#define _TIMER_ALLOCABLE_H

#include "BaseTimers.h"


struct TimerClass{
  struct Class super;
  void (*onTime)(void*); 
};


struct TimerAllocable{
  struct Object super;
//Private:
  ulong next_cuenta;
  ulong tiempo;
  uchar of;
  struct BaseTimers * baseTimer;  
};

void Timer_Construct(struct Timer * self,ulong tiempo);
/*
** ===================================================================
**     Method      :  Timer_Destruct 
**    Description : Metodo para destruir el Timer
** ===================================================================
*/
void * Timer_Destruct(struct Timer * self);
/*
** ===================================================================
**     Method      :  setBaseTimer 
**    Description : setea la entrada de ticks del timer
** ===================================================================
*/
void setBaseTimer(void * _self,void * base);
/*
** ===================================================================
**     Method      :  TimerComp 
**    Description : Compara el valor del timer contra el ultimo valor de
**    la cuenta
** ===================================================================
*/
void TimerComp(struct Timer * self);
/*
** ===================================================================
**     Method      :  Timer_isfinish 
**    Description : Indica si ya termino la cuenta
** ===================================================================
*/
uchar Timer_isfinish(struct Timer * self);
/*
** ===================================================================
**     Method      :  Timer_getCuenta 
**    Description : Regresa la cuenta actual que se resetea al llegar al tiempo
** ===================================================================
*/
ulong Timer_getCuenta(struct Timer * self);
/*
** ===================================================================
**     Method      :  Timer_Restart 
**    Description : Reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_Restart(struct Timer * self);
/*
** ===================================================================
**     Method      :  Timer_setTime 
**    Description : Setea un tiempo nuevo y reinicia la cuenta del tiempo
** ===================================================================
*/
void Timer_setTime(struct Timer * self,ulong tiempo);
/*
** ===================================================================
**     Method      :  Timer_getTime 
**    Description : Obtiene el tiempo a alcanzar
** ===================================================================
*/
ulong Timer_getTime(struct Timer * self);
/*
** ===================================================================
**     Method      :  Timer_Stop 
**    Description : Detiene la cuenta del timer
** ===================================================================
*/
void Timer_Stop(struct Timer * self);

#define TIMER_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,onTime)\
  CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),  \
  onTime
 
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif
