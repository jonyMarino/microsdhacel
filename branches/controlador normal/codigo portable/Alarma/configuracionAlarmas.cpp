#include "configuracionAlarmas.hpp"

ConfiguracionAlarmas::ConfiguracionAlarmas( AlarmConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

TipoAdaptadorSalida ConfiguracionAlarmas::getAdaptadorSalidaAlarm(){
  return configuracion.tipoAdapSal;
}

void ConfiguracionAlarmas::setAdaptadorSalidaAlarm(TipoAdaptadorSalida val){
  manejadorMemoria.setWord((unsigned int * const)&configuracion.tipoAdapSal,val);
}

TipoControl ConfiguracionAlarmas::getTipoControl(){
  return configuracion.tipoCrl;
}

void ConfiguracionAlarmas::setTipoControl(TipoControl val){
   manejadorMemoria.setWord((unsigned int * const)&configuracion.tipoCrl,val);
}