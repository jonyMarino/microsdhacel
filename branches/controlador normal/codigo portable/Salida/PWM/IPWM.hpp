#ifndef _IPWM_H
#define _IPWM_H

#include "pwm_periodos.h"
#include "ISalida.hpp"

class IPWM : public ISalida {
  public:
  //void addOnToggleListener(struct Method* method) ;
  
  virtual unsigned char setPeriodo(TPeriod period) = 0;

  virtual TPeriod getPeriodo() = 0;

  virtual bool getEstadoSalida () = 0;
  
  virtual bool getConectada() = 0;

  virtual void setConectada(bool conectada) = 0;

};
#endif
