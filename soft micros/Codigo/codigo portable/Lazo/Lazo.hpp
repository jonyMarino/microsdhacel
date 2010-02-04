#ifndef _LAZO_HPP
#define _LAZO_HPP

#include "Sensor/Sensor.hpp"
#include "Salida/ISalida.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"

class Lazo{
  public:
    Lazo(Sensor& sensor);
    ~Lazo();
  protected:
    Sensor& getSensor();
    virtual ISalida& getSalida()=0;
  private:
    Sensor& sensor;
    struct Method mOnNuevoValorSensor;
    static void onNuevoValorSensor(void*);    
};

#endif 