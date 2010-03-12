#include "configuracionLazoAlarmas.hpp"

ConfiguracionLazoAlarmas::ConfiguracionLazoAlarmas( LazoAlarmConf &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){}

TipoLazo ConfiguracionLazoAlarmas::getLazo(){
   return configuracion.tipoLazo;
}

void ConfiguracionLazoAlarmas::setLazo(TipoLazo val){
   manejadorMemoria.setWord((unsigned int * const)&configuracion.tipoLazo,val);
}