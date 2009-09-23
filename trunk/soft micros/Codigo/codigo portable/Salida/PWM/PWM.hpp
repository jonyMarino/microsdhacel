#ifndef _PWM_H
#define _PWM_H

#include "FshTypeSizes.h"
#include "IPWM.hpp"
#include "MethodContainer.hpp"
#include "Method.h"
#include "pwm_periodos.h"
#include "ManejadorMemoria.h"
//#include "utils_pwm_timer.hpp"

#include "TConfPWM.hpp"

class PWM : public IPWM {
  
  protected:
   unsigned char setPeriodoConfiguracion(TPeriod period);
    
   TPeriod getPeriodoConfiguracion();
   
   void callOnToggleListeners();


  private:
    TConfPWM& conf;
    MethodContainer listeners;
    struct ManejadorMemoria &manejadorMemoria;
    PWM();//{stderr<<"error";}
  

  public:
   
  PWM(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf):listeners(),manejadorMemoria(_manejadorMemoria),conf(_conf){}
  
  fbyte getLimSupPeriodo();
  
  void addOnToggleListener(struct Method* method);

  friend void llama_callOnToggleListeners(char n);
};
#endif
