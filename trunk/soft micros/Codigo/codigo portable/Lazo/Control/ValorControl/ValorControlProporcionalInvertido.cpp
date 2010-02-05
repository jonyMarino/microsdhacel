#include <stdlib.h>
#include "ValorControlProporcionalInvertido.hpp"


ValorControlProporcionalInvertido::ValorControlProporcionalInvertido(ConfiguracionValorControl& configuracion,Sensor&sensor):ValorControlProporcional(configuracion,sensor){
}


int ValorControlProporcionalInvertido::getValorControl(){
  return -ValorControlProporcional::getValorControl();
}