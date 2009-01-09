#ifndef _MANEJADORINTERRUPCION_H
#define _MANEJADORINTERRUPCION_H

#include "Object.h"
#include "MethodContainer.h"

struct ManejadorInterrupcion {
  struct Object super;  
  struct MethodContainer listeners;
};


//%+
void enable(void * _self);

void disable(void * _self);

void addOnInterruptListener(void * _self,struct Method * metodo) ;

void deleteOnInterruptListener(void * _self,struct Method * metodo);
//%#
void onInterrupt(void * _self);
    

struct ManejadorInterrupcionClass{
  struct Class super;
  void(*enable)(void*);
  void(*disable)(void*);
};

extern const struct ManejadorInterrupcionClass ManejadorInterrupcion;


void ManejadorInterrupcion_defConstructor(void * _self,va_list * args);

#endif
