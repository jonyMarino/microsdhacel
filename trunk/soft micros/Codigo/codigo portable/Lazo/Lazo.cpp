#include "Lazo.hpp"

Lazo::Lazo(Sensor& _sensor):sensor(_sensor){
  mOnNuevoValorSensor.pmethod = Lazo::onNuevoValorSensor;
  mOnNuevoValorSensor.obj = this;

  sensor.addOnNuevoValorListener(&mOnNuevoValorSensor);
}
    
Sensor& Lazo::getSensor(){
  return sensor;
}

Lazo::~Lazo(){
  sensor.deleteOnNuevoValorListener(&mOnNuevoValorSensor);
}