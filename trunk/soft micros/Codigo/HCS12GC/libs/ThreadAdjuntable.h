#ifndef _THREAD_ADJUNTABLE_H
#define _THREAD_ADJUNTABLE_H

#include "Object.h"
#include "MethodContainer.h"
#include "adjuntador_a_hilo.h"

struct ThreadAdjuntable{
  struct MethodContainer methodContainer;
};

extern const void * const ThreadAdjuntable;

#define  ThreadAdjuntable_Adjuntar MethodContainer_add

struct AdjuntadorAHilo * ThreadAdjuntable_getAdjuntador(void * _self);

#endif