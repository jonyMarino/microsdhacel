#include "Lazo.h"

const struct Class LazoClass={
  CLASS_INITIALIZATION(Class,LazoClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};
const struct LazoClass Lazo={
  CLASS_INITIALIZATION(LazoClass,Lazo,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};


void Lazo_constructor(void * _self,struct Sensor * sensor){
  struct Lazo * self = (struct Lazo *)_self;
  struct LazoClass ** vTable = (struct LazoClass **)_self;
  newAlloced(&self->nuevaMedicion,&Method,(**vTable).onNuevaMedicion,_self);
  Sensor_addNuevaMedicionListener(sensor,&self->nuevaMedicion); 
}

void Lazo_destructor(void * _self){
  struct Lazo * self = (struct Lazo *)_self;
  Sensor_deleteNuevaMedicionListener(getSensor(_self),&self->nuevaMedicion);
}

void onNuevaMedicion(void * _self){
  struct LazoClass ** vTable = (struct LazoClass **)_self;
  (**vTable).onNuevaMedicion(_self);
}

struct Sensor * getSensor(void * _self ){
  struct LazoClass ** vTable = (struct LazoClass **)_self;
  return (**vTable).getSensor(_self);
}

struct ISalida * getSalida(void * _self ){
  struct LazoClass ** vTable = (struct LazoClass **)_self;  
  return (**vTable).getSalida(_self);
}