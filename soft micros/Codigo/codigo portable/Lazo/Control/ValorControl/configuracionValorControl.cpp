#include "configuracionValorControl.hpp"

ConfiguracionValorControlado::ConfiguracionValorControlado( ValorControlConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

int ConfiguracionValorControlado::getValorControlador(){
  return configuracion.valAControlar;
}

void ConfiguracionValorControlado::setValorControlador(int val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.valAControlar,val);
}