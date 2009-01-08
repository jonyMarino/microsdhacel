#include "BaseTimers_protected.h"
#include "timer_interrupt.h"
#include "TI1.h"

struct BaseTimersGral{
  struct BaseTimers super;
};

void BaseTimersGral_DefConstruct(void*_self,va_list *args);
void *BaseTimersGral_Destruct(void * _self);
void BaseTimersGral_lockInc(void * _self);
void BaseTimersGral_unlockInc(void * _self);
static void BaseTimersGral_inc1(void * _self);
static void BaseTimersGral_inc40(void * _self);

const struct BaseTimersClass BaseTimersGral={
    CLASS_INITIALIZATION(BaseTimersClass,
                       BaseTimersGral,
                       BaseTimers,
                       BaseTimersGral_DefConstruct,
                       BaseTimers_dtor,
                       LinkedList_Differ,
                       Object_puto),
                       LinkedList_add,
                       LinkedList_Vaciar,
                       LinkedList_contains,   
                       LinkedList_Vacia,
                       LinkedList_iterator,
                       LinkedList_deleteReference, 
                       LinkedList_Cantidad,
                       LinkedList_get,
                       LinkedList_addFirst,
                       LinkedList_addLast,
                       LinkedList_getFirst,
                       LinkedList_getLast,
                       LinkedList_Eliminar_Primero,
                       LinkedList_removeLast,
                       BaseTimersGral_lockInc,
                       BaseTimersGral_unlockInc                     
};

static void * instance =NULL;

void BaseTimersGral_DefConstruct(void*_self,va_list *args){
  struct BaseTimersGral * self = _self;
  super_ctor(&BaseTimersGral,_self,args);
  add1msListener(BaseTimersGral_inc1,_self);
  add40msListener(BaseTimersGral_inc40,_self);
}

void *BaseTimersGral_getInstance(void){
  if(!instance)
    instance = new(&BaseTimersGral);
  return instance;
}

void BaseTimersGral_lockInc(void * _self){
  struct BaseTimersGral * self = _self;
  TI1_Disable();
}

void BaseTimersGral_unlockInc(void * _self){
  struct BaseTimersGral * self = _self;
  TI1_Enable();
}

static void BaseTimersGral_inc1(void * _self){
  BaseTimers_inc(_self,1);
  BaseTimers_actualizarTimers(_self);
}

static void BaseTimersGral_inc40(void * _self){
  BaseTimers_inc(_self,TIEMPO_GRABACION);
  BaseTimers_actualizarTimers(_self);
}


