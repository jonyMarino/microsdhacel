
#include "PWMHard.hpp"

void PWMHard::setDuty(PWMHard::ReferenciaPWM pwm, int duty) {
  uint periodo = (&PWMPER01)[pwm];
  uint * pwm_duty =  &(&PWMDTY01)[pwm];
  *pwm_duty = (periodo * (dword)duty + 500) / 1000;
}

void PWMHard::setPrescaler(PWMHard::ReferenciaPWM pwm, unsigned char valor) {
  if(pwm == RefPWM23)
    PWMPRCLK_PCKB = valor;
  else
    PWMPRCLK_PCKA = valor;

}

void PWMHard::setPeriodoHard( PWMHard::ReferenciaPWM pwm, unsigned int periodo) {
  (&PWMPER01)[pwm]=periodo;
}

void PWMHard::escalar(PWMHard::ReferenciaPWM pwm) {
  PWMCLK|=(1<<(pwm*2));
}

void PWMHard::noEscalar(PWMHard::ReferenciaPWM pwm) {
  PWMCLK&=~(1<<(pwm*2));
}

bool PWMHard::getConectada(){
  return conectado;
}

void PWMHard::setConectada(bool conectada){
 if(conectado && !conectada)
    setPotencia(0); 
   
   conectado=conectada;
}