#include "Sensor.h"

const struct Class SensorDecLimClass; 
const struct SensorClass Sensor; 

void Sensor_constructor(void * _self){
  struct Sensor * self=_self;
  
  newAlloced(&self->nuevaMedicionListeners,&MethodContainer);  
}

void Sensor_addNuevaMedicionListener(void * _self, struct Method * metodo){
  struct Sensor * self=_self;
  MethodContainer_add(&self->nuevaMedicionListeners,metodo);
  
}

void Sensor_deleteNuevaMedicionListener(void * _self, struct Method * metodo){
  struct Sensor * self=_self;
  MethodContainer_delete(&self->nuevaMedicionListeners,metodo);
}


void Sensor_notificarListeners(void * _self){
  struct Sensor * self=_self;
  MethodContainer_execute(&self->nuevaMedicionListeners);
}


