
#include "PWMTimer.hpp"
#include "utils_pwm_timer.hpp"
#include "PWM.hpp"
//#include "Salida.hpp"


void PWMTimer::PWMTimer(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf, uchar pin_out):PWM(_manejadorMemoria,_conf){
 //PWM(_manejadorMemoria,_conf);
 pinNum=pin_out;
 setPWM_period(this,_conf.periodo);
 PWM_init(this,pin_out);
}

void PWMTimer::setPotencia(unsigned int potencia) {
  if(pwm_timer_isEnable(pinNum))			/* PID?*/
    PWM_SetRatio16(this,potencia);
  else{
    if(potencia==0){
      estadoSalida=FALSE;
      PWM_ClrValue(pinNum);
    }else{
      estadoSalida=TRUE;
      PWM_SetValue(pinNum);  
    }
  }
  
  pwm_setPotencia(potencia);
}


unsigned char PWMTimer::setPeriodo(TPeriod period) {
  unsigned char err;
  if(period<0 || period>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= setPeriodoConfiguracion(period);
  if(!err)
    setPWM_period(this,(uchar)period);
  return err;
}

TPeriod PWMTimer::getPeriodo(){
 return getPeriodoConfiguracion();
}

void PWMTimer::setTipoSalida(TipoSalida tipoSalida) {
  if(tipoSalida==SALIDA_ONOFF)
    PWM_Disable(pinNum); 
  else
    PWM_Enable(pinNum);
}

TipoSalida PWMTimer::getTipoSalida() {
  return (pwm_timer_isEnable(pinNum))?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}


bool PWMTimer::getConectada() {

  return conectado;
}

 void PWMTimer::setConectada(bool conectada) {
  if(conectado && !conectada)
    setPotencia(0); 
   
   conectado=conectada;
  
}

unsigned int PWMTimer::getPotencia() {

  return potencia;
}

 void PWMTimer::pwm_setPotencia(unsigned int _potencia) {
  
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
}

bool PWMTimer:: getEstadoSalida(){
  return estadoSalida;
}