#include "configuracionVF.hpp"
 
ConfiguracionVF::ConfiguracionVF( ConfVF &_conf_, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),manejadorMemoria(_manejadorMemoria){
}
    
unsigned char ConfiguracionVF::getCantidadDeEtapas(){
    return configuracion.iCantDeEtapas;
}

void ConfiguracionVF::setCantidadDeEtapas(unsigned char val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iCantDeEtapas,(unsigned int)val);
}

unsigned char ConfiguracionVF::getVelDeEtapa(unsigned char nroEtp){
    return configuracion.iEtapa[nroEtp-1].velocidad;
}

void ConfiguracionVF::setVelDeEtapa(unsigned char nroEtp,unsigned char val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].velocidad,(unsigned int)val);
}

unsigned char ConfiguracionVF::getTempDeEtapa(unsigned char nroEtp){
    return configuracion.iEtapa[nroEtp-1].temperatura;
}

void ConfiguracionVF::setTempDeEtapa(unsigned char nroEtp,unsigned char val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].temperatura,(unsigned int)val); 
}

unsigned char ConfiguracionVF::getTiempoDeEtapa(unsigned char nroEtp){
    return configuracion.iEtapa[nroEtp-1].tiempo;
}

void ConfiguracionVF::setTiempoDeEtapa(unsigned char nroEtp,unsigned char val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iEtapa[nroEtp-1].tiempo,(unsigned int)val);
}

