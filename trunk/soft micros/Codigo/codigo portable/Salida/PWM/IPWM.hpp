#ifndef _IPWM_H
#define _IPWM_H

#include "pwm_periodos.h"
#include "ISalida.hpp"

class IPWM : public ISalida {
  public:
  //void addOnToggleListener(struct Method* method) ;
  
  virtual unsigned char setPeriodo(TPeriod period) = 0;

  virtual TPeriod getPeriodo() = 0;

  virtual unsigned char getEstadoSalida () = 0;
};
#endif
