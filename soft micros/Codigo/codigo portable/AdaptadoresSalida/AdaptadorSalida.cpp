
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

void AdaptadorSalida::setHisteresis(int histeresis) {
  configuracion.setHisteresis(histeresis);
}
  
int AdaptadorSalida::getTipoSalida() {
  return configuracion.getTipoSalida();
}

void AdaptadorSalida::setTipoSalida(TipoSalida tipoSalida){
  configuracion.setTipoSalida(tipoSalida);
}  

ISalida& AdaptadorSalida::getSalida(){
  return salida;
}


