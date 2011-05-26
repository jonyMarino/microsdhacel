#ifndef _VALOR_CONTROL_RELATIVO_HPP
#define _VALOR_CONTROL_RELATIVO_HPP

#include "ValorControl.hpp"
#include "Standard/Getter.hpp"

class ValorControlRelativo: public ValorControl{
  public:
    ValorControlRelativo(ConfiguracionValorControl& configuracion,Sensor&sensor,Getter& valorControl2);
    virtual int getValorControl();
  private:
    Getter& valorControl2;
};

#endif