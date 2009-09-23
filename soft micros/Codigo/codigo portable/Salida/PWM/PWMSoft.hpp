#ifndef _PWMSOFT_H
#define _PWMSOFT_H


#include "PWM.hpp"
#include "TipoSalida.hpp"

class PWMSoft : public PWM {
  public:
  virtual  setPotencia(unsigned int potencia);

  virtual unsigned char setPeriodo(int period);

  virtual  setTipoSalida(TipoSalida tipoSalida);

    virtual TipoSalida getTipoSalida();


  private:
    MethodTimer timer;

    byte * salida;

    unsigned char mascara;

};
#endif
