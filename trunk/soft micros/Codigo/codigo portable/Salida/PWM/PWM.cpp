
#include "PWM.hpp"
#include "pwm_periodos.h"


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

void PWM::setPotencia(unsigned int _potencia) {
  if(getTipoSalida()==SALIDA_PROPORCIONAL) 
    potencia = _potencia; 
  else{
    if(_potencia)
      potencia = 1000;
    else
      potencia = 0;
  }  
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

void PWM::Salida_setPotencia(unsigned int potencia) {
  if(!getConectada() || potencia<0 || potencia>1000)  
    return; //error
    
setPotencia(potencia);
  
}