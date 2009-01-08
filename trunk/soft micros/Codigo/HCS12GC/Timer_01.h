#ifndef _TIMER_H
#define _TIMER_H

#include "stdtypes.h"
#include "Object.h"

/*  Definicion del Timer*/
struct Timer;

typedef struct{
  struct Class super;
  void (*OnTime)(struct Timer*); 
}T_Timer;

struct Timer{
  const T_Timer * _timer;
//Private:
  ulong cuenta;
  ulong tiempo;
  uchar finished;
  struct Timer ** container;
};

extern const T_Timer * const Timer;

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
**     Method      :  IncTimer 
**    Description : Incrementa el valor de la cuenta del Timer
** ===================================================================
*/
void TimerInc(struct Timer * self,Byte inc);
/*
** ===================================================================
**     Method      :  IncTimers 
**    Description : Incrementa el valor de la cuenta de Todos los timers
** ===================================================================
*/
void IncTimers(Byte inc);
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
 


#endif