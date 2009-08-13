#include "Sensor.h"

//void Sensor_defConstructor(void * _self,va_list * args);

const struct Class SensorDecLimClass={
    CLASS_INITIALIZATION(Class,SensorDecLimClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)  
}; 

const struct SensorClass Sensor={
    CLASS_INITIALIZATION(SensorClass,Sensor,Object,Object_ctor,Object_dtor,Object_differ,Object_puto)  

}; 

/*void Sensor_constructor(void * _self){
  struct Sensor * self= ( struct Sensor * )_self;
}

void Sensor_defConstructor(void * _self,va_list * args){
  Sensor_constructor(_self);  
}
  */

void Sensor_addNuevaMedicionListener(void * _self, struct Method * metodo){
  struct Sensor * self= (struct Sensor *)_self;
  self->nuevaMedicionListeners.add(metodo); 
}

void Sensor_deleteNuevaMedicionListener(void * _self, struct Method * metodo){
  struct Sensor * self=(struct Sensor *)_self;
  self->nuevaMedicionListeners.moveOut(metodo);
}


void Sensor_notificarListeners(void * _self){
  struct Sensor * self=(struct Sensor *)_self;
  self->nuevaMedicionListeners.executeMethods();
}


