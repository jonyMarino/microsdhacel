
#include "PWM.hpp"
#include "pwm_periodos.h"



PWM::PWM(struct ManejadorMemoria &_manejadorMemoria, TConfPWM &_conf):listeners(),manejadorMemoria(_manejadorMemoria),conf(_conf){
     potencia = 0;
     //setPotenciaGuardada();
  }


unsigned char PWM::setPeriodoConfiguracion(TPeriod period) {
  
 return manejadorMemoria.setByte(&(conf.periodo),period);
}

TPeriod PWM::getPeriodoConfiguracion() {
  return manejadorMemoria.getByte(&(conf.periodo));
}

fbyte PWM::getLimSupPeriodo() {
  return PWM_MAX_VALUE_PERIODS;
}

void PWM::addOnToggleListener(struct Method* method){
  listeners.add (method);

}

void PWM::callOnToggleListeners(){
  listeners.executeMethods();
}

TPeriod PWM::getPeriodo(){
 return getPeriodoConfiguracion();
}

unsigned int PWM::getPotencia() {

  return potencia;
}

bool PWM::getConectada() {

  return conectado;
}

 void PWM::setConectada(bool conectada) {
  if(conectado && !conectada)
    setPotencia(0); 
   
   conectado=conectada;
  
}

void PWM::setPotencia(unsigned int _potencia) {
  if(!getConectada() || _potencia<0 || _potencia>1000)  
    return; //error
  if(getTipoSalida()==SALIDA_PROPORCIONAL) 
    potencia = _potencia; 
  else{
    if(_potencia)
      potencia = 1000;
    else
      potencia = 0;
  }  
    
  setPotenciaGuardada();
  
}
