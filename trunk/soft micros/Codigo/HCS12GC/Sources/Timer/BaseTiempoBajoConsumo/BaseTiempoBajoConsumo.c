#include "BaseTimers_protected.h"
#include "BaseTiempoBajoConsumo.h"
#include "ManejadorRTI.h"


void BaseTiempoBajoConsumo_DefConstruct(void*_self,va_list *args);
void BaseTiempoBajoConsumo_lockInc(void * _self);
void BaseTiempoBajoConsumo_unlockInc(void * _self);
static void BaseTiempoBajoConsumo_onRTI(void * _self);

const struct BaseTimersClass BaseTiempoBajoConsumo = {
    CLASS_INITIALIZATION(BaseTimersClass,
                       BaseTiempoBajoConsumo,
                       BaseTimers,
                       BaseTiempoBajoConsumo_DefConstruct,
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
                       BaseTiempoBajoConsumo_lockInc,
                       BaseTiempoBajoConsumo_unlockInc                     
};

void BaseTiempoBajoConsumo_DefConstruct(void*_self,va_list *args){
  struct BaseTiempoBajoConsumo * self = _self;
  super_ctor(&BaseTiempoBajoConsumo,_self,args);
  newAlloced(&self->onRTI,&Method,BaseTiempoBajoConsumo_onRTI,_self);
  addOnInterruptListener(ManejadorRTI_getInstance(),&self->onRTI);
  self->microSegAcumulados = 0;
}


void BaseTiempoBajoConsumo_lockInc(void * _self){
  struct BaseTiempoBajoConsumo * self = _self;
  ManejadorRTI_disable( ManejadorRTI_getInstance() );
}

void BaseTiempoBajoConsumo_unlockInc(void * _self){
  struct BaseTiempoBajoConsumo * self = _self;
  ManejadorRTI_enable( ManejadorRTI_getInstance() );
}

static void BaseTiempoBajoConsumo_onRTI(void * _self){
  struct BaseTiempoBajoConsumo * self = _self;
  ulong uS= getIntervaloMicroSeg( ManejadorRTI_getInstance() );
  self->microSegAcumulados += uS%1000;
  BaseTimers_inc(_self, uS/1000 + self->microSegAcumulados/1000);
  self->microSegAcumulados %= 1000;
  BaseTimers_actualizarTimers(_self);
}


