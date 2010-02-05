#ifndef _VALOR_CONTROL_HPP
#define _VALOR_CONTROL_HPP

#include "Sensor/Sensor.hpp"

class ConfiguracionValorControl{
  public:
    virtual int getValorControlador()=0;
    virtual void setValorControlador(int)=0;
};

class ValorControl{
  public:
    ValorControl(ConfiguracionValorControl& configuracion,Sensor&sensor);
    virtual int getValorControl()=0;
    int getValorControlador();
    void setValorControlador(int);
    Sensor& getSensor();
  private:
    ConfiguracionValorControl& configuracion;
    Sensor& sensor;
};

#endif