#ifndef _BASE_TIMERS_PROTECTED_H
#define _BASE_TIMERS_PROTECTED_H

#include "BaseTimers.h"

void BaseTimers_actualizarTimers(void *_self);
void lockInc(void * _self);
void unlockInc(void * _self);
 
#endif
