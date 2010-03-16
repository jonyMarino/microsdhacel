#include "ValorControl.hpp"

ValorControl::ValorControl(ConfiguracionValorControl& _configuracion,Sensor&_sensor):configuracion(_configuracion),sensor(_sensor){

}

int ValorControl::getValorControlador(){
  return configuracion.getValorControlador();
}

void ValorControl::setValorControlador(int val){
  configuracion.setValorControlador(val);
}

Sensor& ValorControl::getSensor(){
  return sensor;
}

ConfiguracionValorControl& ValorControl::getConfiguracion(){
  return configuracion;
}