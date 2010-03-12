#include "ConfiguracionRetransmision.hpp"

ConfiguracionRetransm::ConfiguracionRetransm( RetConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

int ConfiguracionRetransm::getLimiteInferior(){
  return configuracion.retLow;
}

int ConfiguracionRetransm::getLimiteSuperior(){
 return configuracion.retHi; 
}

void ConfiguracionRetransm::setLimiteInferior(int val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.retLow,val);
}

void ConfiguracionRetransm::setLimiteSuperior(int val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.retHi,val);
}