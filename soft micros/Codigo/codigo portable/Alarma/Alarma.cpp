
#include "Alarma.hpp"
//#include "PWM.hpp"
#include "Sensor/Sensor.hpp"
#include "PE_Types.h"

Alarma::Alarma(ConfiguracionAlarma& conf):configuracion(conf){
}

void Alarma::setLazo(int lazo) {
  configuracion.setLazo(lazo);
}

int Alarma::getLazo() {
  return configuracion.getLazo();
}
/*
int Alarma::getAdaptadorSalida() {
}

void Alarma::setAdaptadorSalida(int adaptador) {
}
*/

ConfiguracionAlarma& Alarma::getConfiguracion() {
  return configuracion;
}

int Alarma::getRetLow(){
  return configuracion.getRetLow();
}
    
void Alarma::setRetLow(int valor){
  configuracion.setRetLow(valor);
}

int Alarma::getRetHi(){
  return configuracion.getRetHi();
}

void Alarma::setRetHi(int valor){
  configuracion.setRetHi(valor);
}
