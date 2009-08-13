#include "BaseTimers_protected.h"
#include "Timer.h"

void BaseTimers_ctor(void * _self,va_list args);

const struct BaseTimersClass BaseTimers ={
    CLASS_INITIALIZATION(BaseTimersClass,
                       BaseTimers,
                       LinkedList,
                       BaseTimers_ctor,
                       BaseTimers_dtor,
                       LinkedList_Differ,
                       Object_puto)
};

void BaseTimers_ctor(void * _self,va_list args){
  struct BaseTimers *self = _self;
  super_ctor(&BaseTimers,_self,args);
  self->cuenta = 0;
}

void BaseTimers_agregar(void * _self,void * timerPersonalizado){
  struct BaseTimers *self = _self;
  LinkedList_add(self,timerPersonalizado);
}

void BaseTimers_inc(void *_self,uint ms){
  struct BaseTimers *self = _self;
  self->cuenta+=ms;
}

void BaseTimers_remover(void *_self,void * timerPersonalizado){
  struct BaseTimers* self = _self;
  lockInc(_self);
  LinkedList_deleteReference(self,timerPersonalizado);
  unlockInc(_self);
}


void BaseTimers_actualizarTimers(void *_self){
  struct BaseTimers *self = _self;
  struct LinkedListIterator iterator;
  
  LinkedList_linkedListIterator(self,&iterator);
  
  while(Iterator_hasNext(&iterator)){
    TimerComp(Iterator_next(&iterator));      
  }
}

ulong BaseTimers_getCuenta(void *_self){
  struct BaseTimers *self = _self;
  ulong cuentatmp;
 // lockInc(_self);      //EN ASSEMBLER SE HACE UN SOLO READ, y self->cuenta+=ms nunca tiene un valor invalido POR ESO NO HACE FALTA
  cuentatmp = self->cuenta;
//  unlockInc(_self);   
  return cuentatmp;
}

void lockInc(void * _self){
  struct BaseTimersClass * class = classOf(_self);
  class->lockInc(_self);    
}

void unlockInc(void * _self){
  struct BaseTimersClass * class = classOf(_self);
  class->unlockInc(_self);    
}

