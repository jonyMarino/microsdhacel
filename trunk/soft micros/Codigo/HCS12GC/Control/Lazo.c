#include "Lazo.h"

const struct Class LazoClass;
const struct LazoClass Lazo;


void Lazo_constructor(void * _self,struct Sensor * sensor){
  struct Lazo * self = _self;
  struct LazoClass ** vTable = _self;
  newAlloced(&self->nuevaMedicion,&Method,(**vTable).onNuevaMedicion,_self);
  Sensor_addNuevaMedicionListener(sensor,&self->nuevaMedicion); 
}

void * Lazo_destructor(void * _self){
  struct Lazo * self = _self;
  Sensor_deleteNuevaMedicionListener(getSensor(_self),&self->nuevaMedicion);
  return _self;
}

void onNuevaMedicion(void * _self){
  struct LazoClass ** vTable = _self;
  (**vTable).onNuevaMedicion(_self);
}

struct Sensor * getSensor(void * _self ){
  struct LazoClass ** vTable = _self;
  return (**vTable).getSensor(_self);
}

struct ISalida * getSalida(void * _self ){
  struct LazoClass ** vTable = _self;  
  return (**vTable).getSalida(_self);
}