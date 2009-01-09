
#include "ManejadorInterrupcion.h"

void ManejadorInterrupcion_enable(void * _self);
void ManejadorInterrupcion_disable(void * _self);

const struct ManejadorInterrupcionClass ManejadorInterrupcion={
  CLASS_INITIALIZATION(Class,
                       ManejadorInterrupcion,
                       Object,
                       ManejadorInterrupcion_defConstructor,
                       Object_dtor,
                       Object_differ,
                       Object_puto),
                       ManejadorInterrupcion_enable,
                       ManejadorInterrupcion_disable
};

void ManejadorInterrupcion_constructor(void * _self){
  struct ManejadorInterrupcion * self = _self; 
  newAlloced(&self->listeners,&MethodContainer);  
}

void ManejadorInterrupcion_defConstructor(void * _self,va_list * args){
  ManejadorInterrupcion_constructor(_self);  
}



void addOnInterruptListener(void * _self,struct Method * metodo) {
  struct ManejadorInterrupcion * self = _self;
  MethodContainer_add(&self->listeners,metodo);  
}

void deleteOnInterruptListener(void * _self,struct Method * metodo){
  struct ManejadorInterrupcion * self = _self;
  MethodContainer_delete(&self->listeners,metodo);  
}

void onInterrupt(void * _self) {
  struct ManejadorInterrupcion * self = _self;
  MethodContainer_execute(&self->listeners);  
}

void ManejadorInterrupcion_enable(void * _self){
}

void ManejadorInterrupcion_disable(void * _self){
}

//selectores
void enable(void * _self) {
  struct ManejadorInterrupcionClass * class = classOf(_self);
  class->enable(_self);
}

void disable(void * _self) {
  struct ManejadorInterrupcionClass * class = classOf(_self);
  class->disable(_self);
}

