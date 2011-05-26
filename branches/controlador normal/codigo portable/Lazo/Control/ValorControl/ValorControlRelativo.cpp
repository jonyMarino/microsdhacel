#include <stdlib.h>
#include "ValorControlRelativo.hpp"


ValorControlRelativo::ValorControlRelativo(ConfiguracionValorControl& configuracion,Sensor&sensor,Getter& _valorControl2):ValorControl(configuracion,sensor),valorControl2(_valorControl2){
}


int ValorControlRelativo::getValorControl(){
  int valControl1 = getValorControlador();
  int valControl2 = valorControl2.getVal();
  int valorSensor = getSensor().getVal();
  
  return valorSensor - (valControl1+ valControl2);  
}