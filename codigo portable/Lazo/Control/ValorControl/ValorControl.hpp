#ifndef _VALOR_CONTROL_HPP
#define _VALOR_CONTROL_HPP

#include "Sensor/Sensor.hpp"

class ConfiguracionValorControl{
  public:
    virtual int getValorControlador()=0;
};

class ValorControl{
  public:
    ValorControl(ConfiguracionValorControl& configuracion,Sensor&sensor);
    virtual int getValorControl()=0;
    int getValorControlador();
    //void setValorControlador(int); //pedir la configuracion para hacer un set
    Sensor& getSensor();
    ConfiguracionValorControl& getConfiguracion();
  private:
    ConfiguracionValorControl& configuracion;
    Sensor& sensor;
};

#endif