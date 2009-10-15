#ifndef _PWMHARD_H
#define _PWMHARD_H


#include "PWM.hpp"
#include "MC9S12GC32.h"

/**
 * Este PWM usa el PWM del hardware del HCS12
 */
#define CONTROLADOR_PWM_INIT(PWM1,PWM2){\
  PWMCTL_CON##PWM1##PWM2 = 1; /*Concatenar  PWM1 y PWM2*/\
  PWMPOL_PPOL##PWM2 = 1; /*sin duty se queda en 0*/\
  PWME_PWME##PWM2 = 0;   /* Stop counter */				\
  PWMCNT##PWM1##PWM2 = 0;																\
} 
 
class PWMHard : public PWM {
 
 public:
  enum ReferenciaPWM {
      RefPWM01,
      RefPWM23,
      RefPWM45
    };
    
  void PWMHard(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf):PWM(_manejadorMemoria,_conf){}
  
  static void setDuty(ReferenciaPWM pwm, int duty);

  void setPrescaler(ReferenciaPWM pwm, unsigned char valor);

  static void setPeriodoHard(ReferenciaPWM pwm, unsigned int periodo);

  static void escalar(ReferenciaPWM pwm);

  static void noEscalar(ReferenciaPWM pwm);
  
  bool getConectada();

  void setConectada(bool conectada);
  
  private:
   bool conectado;
};




#endif
