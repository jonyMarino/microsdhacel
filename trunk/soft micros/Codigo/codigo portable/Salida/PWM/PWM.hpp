#ifndef _PWM_H
#define _PWM_H


#include "IPWM.hpp"

struct TConfPWM;

class PWM : public IPWM {
  public:
   #define PWM_MAX_VALUE_PERIODS 9

   PWM_setPeriodo(int period);
   
   int PWM_getPeriodo();

   int PWM_getLimSupPeriodo();



  private:
    TConfPWM * conf;


  
  
};
#endif
