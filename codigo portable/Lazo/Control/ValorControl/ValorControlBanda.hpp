#ifndef _VALOR_CONTROL_BANDA_HPP
#define _VALOR_CONTROL_BANDA_HPP

#include "ValorControl.hpp"
#include "Standard/Getter.hpp"

class ValorControlBanda: public ValorControl{
  public:
    ValorControlBanda(ConfiguracionValorControl& configuracion,Sensor&sensor,Getter& valorControl2);
    virtual int getValorControl();
  private:
    Getter& valorControl2;
};

#endif