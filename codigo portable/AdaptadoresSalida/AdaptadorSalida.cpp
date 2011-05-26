
#include "AdaptadorSalida.hpp"


AdaptadorSalida::AdaptadorSalida(ISalida& _salida,AdaptadorSalidaConfiguracion& _configuracion):configuracion(_configuracion),salida(_salida){
}

void AdaptadorSalida::setPotenciaSalida(int valorDeControl) {
  int duty = calcularPotencia(valorDeControl);
  
  salida.setPotencia(duty);
}

AdaptadorSalidaConfiguracion& AdaptadorSalida::getConfiguracion(){
  return configuracion;
}

int AdaptadorSalida::getHisteresis() {
  return configuracion.getHisteresis();
}
 
int AdaptadorSalida::getTipoSalida() {
  return configuracion.getTipoSalida();
}  

ISalida& AdaptadorSalida::getSalida(){
  return salida;
}


