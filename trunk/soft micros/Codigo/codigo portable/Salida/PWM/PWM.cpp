
#include "PWM.hpp"
#include "pwm_periodos.h"


unsigned char PWM::setPeriodoConfiguracion(TPeriod period) {
  
 return _MANEJADOR_MEMORIA_SET_BYTE(&manejadorMemoria,&(conf.periodo),period);
}

TPeriod PWM::getPeriodoConfiguracion() {
  return _MANEJADOR_MEMORIA_GET_BYTE(&manejadorMemoria,&(conf.periodo));
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