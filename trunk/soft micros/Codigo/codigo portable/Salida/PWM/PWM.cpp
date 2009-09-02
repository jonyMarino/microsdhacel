
#include "PWM.hpp"
#include "pwm_periodos.h"
#include "TConfPWM.hpp"

unsigned char PWM::setPeriodoConfiguracion(int period) {
  return setPeriodo(period);
}

fbyte PWM::getPeriodoConfiguracion() {
  return conf->periodo;
}

fbyte PWM::getLimSupPeriodo() {
  return PWM_MAX_VALUE_PERIODS;
}

