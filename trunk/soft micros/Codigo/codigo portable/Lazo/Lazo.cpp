#include "Lazo.hpp"

Lazo::Lazo(Sensor& _sensor):sensor(_sensor){
  mOnNuevoValorSensor.pmethod = Lazo::onNuevoValorSensorStatic;
  mOnNuevoValorSensor.obj = this;

  sensor.addOnNuevoValorListener(&mOnNuevoValorSensor);
}
    
Sensor& Lazo::getSensor(){
  return sensor;
}

Lazo::~Lazo(){
  sensor.deleteOnNuevoValorListener(&mOnNuevoValorSensor);
}

void Lazo::onNuevoValorSensorStatic(void* _self){
  Lazo * self = (Lazo*)_self;
  self->onNuevoValorSensor();
}