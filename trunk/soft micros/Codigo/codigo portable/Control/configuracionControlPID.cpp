#include "configuracionControlPID.hpp"
 
ConfiguracionControlPID::ConfiguracionControlPID( ControlConf &_conf_,SetPoint *_setPoint, struct ManejadorMemoria & _manejadorMemoria):configuracion(_conf_),setPoint(_setPoint),manejadorMemoria(_manejadorMemoria){
}
    
int ConfiguracionControlPID::getSetPoint(){
    if(setPoint)
      return setPoint->getVal();
    else
      return configuracion.iSP;
}

void ConfiguracionControlPID::setSetPoint(int val){
   if(setPoint) 
    setPoint->setVal(val);
   else 
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iSP,val);
   
}

int ConfiguracionControlPID::getLimiteInferiorSetPoint(){
    return configuracion.iLimInfSP;
}

void ConfiguracionControlPID::setLimiteInferiorSetPoint(int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iLimInfSP,val);
}

int ConfiguracionControlPID::getLimiteSuperiorSetPoint(){
    return configuracion.iLimSupSP;
}

void ConfiguracionControlPID::setLimiteSuperiorSetPoint(int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iLimSupSP,val); 
}

int ConfiguracionControlPID::getReset(){
    return configuracion.iReset;
}

void ConfiguracionControlPID::setReset(int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iReset,val);
}

int ConfiguracionControlPID::getTipoControl(){
     return configuracion.eTipoControl;
}

void ConfiguracionControlPID::setTipoControl(int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.eTipoControl,val);
}

int ConfiguracionControlPID::getTipoSalida(){
    return configuracion.eSalidaControl;
}

void ConfiguracionControlPID::setTipoSalida(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.eSalidaControl,val);
}

int ConfiguracionControlPID::getHisteresis(){
    return configuracion.iHisteresis;
}

void ConfiguracionControlPID::setHisteresis(int val){
     manejadorMemoria.setWord((unsigned int * const)&configuracion.iHisteresis,val);
}

int ConfiguracionControlPID::getIntegral(){
    return configuracion.iIntegral;
}

void ConfiguracionControlPID::setIntegral(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iIntegral,val);
}

int ConfiguracionControlPID::getDerivada(){
    return configuracion.iDerivada;
}

void ConfiguracionControlPID::setDerivada(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iDerivada,val);
}

int ConfiguracionControlPID::getLimiteInferiorPotencia(){
    return configuracion.iPotenciaInf;
}

void ConfiguracionControlPID::setLimiteInferiorPotencia(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iPotenciaInf,val);
}

int ConfiguracionControlPID::getLimiteSuperiorPotencia(){
    return configuracion.iPotenciaSup;
}

void ConfiguracionControlPID::setLimiteSuperiorPotencia(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iPotenciaSup,val);
}

int ConfiguracionControlPID::getPotenciaManual(){
    return configuracion.iPotenciaManual;
}

void ConfiguracionControlPID::setPotenciaManual(int val){
    manejadorMemoria.setWord((unsigned int * const)&configuracion.iPotenciaManual,val);
}

