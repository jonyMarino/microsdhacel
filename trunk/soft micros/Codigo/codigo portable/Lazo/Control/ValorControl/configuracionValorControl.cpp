#include "configuracionValorControl.hpp"

ConfiguracionValorControlado::ConfiguracionValorControlado( ValorControlConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):_configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

int ConfiguracionValorControlado::getValorControlador(){
  return _configuracion.valAControlar;
}

void ConfiguracionValorControlado::setValorControlador(int val){
  manejadorMemoria.setWord((unsigned int * const)&_configuracion.valAControlar,val);
}