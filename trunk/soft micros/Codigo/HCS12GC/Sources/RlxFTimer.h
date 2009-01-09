#ifndef _RELAXED_F_TIMER_H
#define _RELAXED_F_TIMER_H

#include "FTimer.h"

struct RlxFTimer{
  struct FTimer _base;
};

extern const void *const RlxFTimer;


/*
** ===================================================================
**    Event       :  RlxFTimer_Handler 
**    Type        :  Static
**    Description :  Manejador a llamar para ejecutar las funciones
** ===================================================================
*/
void RlxFTimer_Handler(void);


#endif