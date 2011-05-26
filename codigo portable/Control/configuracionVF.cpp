#include "configuracionVF.hpp"
 
ConfiguracionVF::ConfiguracionVF( ConfVF &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){
}
    
int ConfiguracionVF::getCantidadDeEtapas(){
    return configuracion.iCantDeEtapas;
}

void ConfiguracionVF::setCantidadDeEtapas(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iCantDeEtapas,(unsigned int)val);
}

int ConfiguracionVF::getVelDeEtapa(int nroEtp){
    return configuracion.iEtapa[nroEtp-1].velocidad;
}

void ConfiguracionVF::setVelDeEtapa(int nroEtp,int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].velocidad,(unsigned int)val);
}

int ConfiguracionVF::getTempDeEtapa(int nroEtp){
    return configuracion.iEtapa[nroEtp-1].temperatura;
}

void ConfiguracionVF::setTempDeEtapa(int nroEtp,int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].temperatura,(unsigned int)val); 
}

int ConfiguracionVF::getTiempoDeEtapa(int nroEtp){
    return configuracion.iEtapa[nroEtp-1].tiempo;
}

void ConfiguracionVF::setTiempoDeEtapa(int nroEtp,int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].tiempo,(unsigned int)val);
}

