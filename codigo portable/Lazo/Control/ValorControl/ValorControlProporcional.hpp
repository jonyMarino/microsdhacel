#ifndef _VALOR_CONTROL_PROPORCIONAL_HPP
#define _VALOR_CONTROL_PROPORCIONAL_HPP

#include "ValorControl.hpp"
#include "Standard/Getter.hpp"

class ValorControlProporcional: public ValorControl{
  public:
    ValorControlProporcional(ConfiguracionValorControl& configuracion,Sensor&sensor);
    virtual int getValorControl();
};

#endif