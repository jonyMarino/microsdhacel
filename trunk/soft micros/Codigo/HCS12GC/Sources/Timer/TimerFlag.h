#ifndef TIMER_FLAG_H
#define TIMER_FLAG_H

#include "stdtypes.h"
#include "Timer.h"
#include "Object.h"

typedef void(*pfunction)(void);
/*  Definicion del Timer*/

struct TimerFlag{
  struct Timer _base;
//Protected:
  bool flag;
};

extern const struct TimerClass TimerFlag;


/*
** ===================================================================
**     Method      :  TimerFlag_reset 
**    Description : 
** ===================================================================
*/
void TimerFlag_reset(void * _self);
/*
** ===================================================================
**     Method      :  TimerFlag_getFlag 
**    Description : Retorna el estado del flag
** ===================================================================
*/
#define TimerFlag_getFlag(timer) ((struct TimerFlag*)timer)->flag

#endif 