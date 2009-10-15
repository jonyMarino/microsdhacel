#ifndef _PWMSOFT_H
#define _PWMSOFT_H


#include "PWM.hpp"
#include "TipoSalida.hpp"
#include "MethodTimer.h"

class PWMSoft : public PWM {
  public:
  virtual void setPotencia(unsigned int potencia);

  virtual unsigned char setPeriodo(int period);

  virtual void setTipoSalida(TipoSalida tipoSalida);

  virtual TipoSalida getTipoSalida();
   
  friend void Salida_setPotencia(unsigned int potencia);

  private:
    TipoSalida tipoSalida; 
    
    MethodTimer timer;

    byte * salida;

    unsigned char mascara;

};
#endif
