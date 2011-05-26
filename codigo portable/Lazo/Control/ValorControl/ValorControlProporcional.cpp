#include <stdlib.h>
#include "ValorControlProporcional.hpp"


ValorControlProporcional::ValorControlProporcional(ConfiguracionValorControl& configuracion,Sensor&sensor):ValorControl(configuracion,sensor){
}


int ValorControlProporcional::getValorControl(){
  int valControl = getValorControlador();
  int valorSensor = getSensor().getVal();
  
  return valControl - valorSensor;
}