#include "Lazo.hpp"

Lazo::Lazo(Sensor& _sensor):sensor(_sensor){
  mOnNuevoValorSensor.pmethod = Lazo::onNuevoValorSensorStatic;
  mOnNuevoValorSensor.obj = this;
  conectar
  sensor.addOnNuevoValorListener(&mOnNuevoValorSensor);
}
    
Sensor& Lazo::getSensor(){
  return sensor;
}

Lazo::~Lazo(){
  desconectar();
}

void Lazo::desconectar(){
  sensor.deleteOnNuevoValorListener(&mOnNuevoValorSensor);
}

void conectar(){
  sensor.addOnNuevoValorListener(&mOnNuevoValorSensor);
}

void Lazo::onNuevoValorSensorStatic(void* _self){
  Lazo * self = (Lazo*)_self;
  self->onNuevoValorSensor();
}