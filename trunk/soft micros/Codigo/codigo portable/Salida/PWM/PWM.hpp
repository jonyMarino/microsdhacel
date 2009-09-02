#ifndef _PWM_H
#define _PWM_H

#include "FshTypeSizes.h"
#include "IPWM.hpp"

struct TConfPWM;

class PWM : public IPWM {
  protected:
   unsigned char setPeriodoConfiguracion(int period);


  private:
    TConfPWM * conf;


  protected:
  fbyte getPeriodoConfiguracion();


  public:
  fbyte getLimSupPeriodo();

};
#endif
