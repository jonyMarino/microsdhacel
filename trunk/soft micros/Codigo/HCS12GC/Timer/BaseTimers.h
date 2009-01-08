#ifndef _BASE_TIMERS_H
#define _BASE_TIMERS_H

#include "Object.h"
#include "LinkedList.h"



struct BaseTimers{
  struct LinkedList super;
  ulong cuenta;
  int index;
};

#define BaseTimers_dtor LinkedList_Destruct
void BaseTimers_inc(void *_self,uint ms);
ulong BaseTimers_getCuenta(void *_self);

struct BaseTimersClass{
  struct LinkedListClass super;
  void(*lockInc)(void*);
  void(*unlockInc)(void*);  
};

extern const struct BaseTimersClass BaseTimers;

#endif
