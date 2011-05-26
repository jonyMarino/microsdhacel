#include <stdlib.h>
#include "ValorControlBanda.hpp"


ValorControlBanda::ValorControlBanda(ConfiguracionValorControl& configuracion,Sensor&sensor,Getter& _valorControl2):ValorControl(configuracion,sensor),valorControl2(_valorControl2){
}


int ValorControlBanda::getValorControl(){
  int valControl1 = getValorControlador();
  int valControl2 = valorControl2.getVal();
  int valorSensor = getSensor().getVal();
  
  return abs(valorSensor-valControl2)-(valControl1/2); 
}