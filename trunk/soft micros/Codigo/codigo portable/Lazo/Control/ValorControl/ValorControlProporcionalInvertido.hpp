#ifndef _VALOR_CONTROL_PROPORCIONAL_INVERTIDO_HPP
#define _VALOR_CONTROL_PROPORCIONAL_INVERTIDO_HPP

#include "ValorControlProporcional.hpp"

class ValorControlProporcionalInvertido: public ValorControlProporcional{
  public:
    ValorControlProporcionalInvertido(ConfiguracionValorControl& configuracion,Sensor&sensor);
    virtual int getValorControl();
};

#endif