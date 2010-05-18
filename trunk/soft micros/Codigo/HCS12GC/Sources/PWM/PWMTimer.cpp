
#include "PWMTimer.hpp"
#include "utils_pwm_timer.hpp"
#include "PWM.hpp"
//#include "Salida.hpp"


void PWMTimer::PWMTimer(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf, uchar pin_out):PWM(_manejadorMemoria,_conf){
 //PWM(_manejadorMemoria,_conf);
 pinNum=pin_out;
 PWM_init(this,pin_out);
 setPWM_period(this,_conf.periodo);
 //setPotenciaGuardada();
 PWM_Enable(pin_out);
  
}

void PWMTimer::setPotenciaGuardada() {
  unsigned int potencia = getPotencia();
  if(pwm_timer_isEnable(pinNum)){/* PID?*/
    PWM_SetRatio16(this,potencia);
  }else{
    if(potencia==0){
      estadoSalida=FALSE;
      PWM_ClrValue(pinNum);
      
    }else{
      estadoSalida=TRUE;
      PWM_SetValue(pinNum);
      
    }
  }  
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


void PWMTimer::setTipoSalida(TipoSalida tipoSalida) {
  if(tipoSalida==SALIDA_ONOFF)
    PWM_Disable(pinNum); 
  else            
    PWM_Enable(pinNum);
}

TipoSalida PWMTimer::getTipoSalida() {
  return (pwm_timer_isEnable(pinNum))?SALIDA_PROPORCIONAL:SALIDA_ONOFF;
}

bool PWMTimer:: getEstadoSalida(){
  return estadoSalida;
}