#include "ConfiguracionAdapSalida.hpp"

ConfiguracionAdapSalida::ConfiguracionAdapSalida( AdapSalConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

int ConfiguracionAdapSalida::getHisteresis(){
  return configuracion.histeresis;
}

TipoSalida ConfiguracionAdapSalida::getTipoSalida(){
  return configuracion.tipoSalida;
}

void ConfiguracionAdapSalida::setHisteresis(int val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.histeresis,val);
}

void ConfiguracionAdapSalida::setTipoSalida(TipoSalida val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.tipoSalida,val);
}