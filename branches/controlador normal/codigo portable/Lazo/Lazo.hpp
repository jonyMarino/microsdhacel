#ifndef _LAZO_HPP
#define _LAZO_HPP

#include "Sensor/Sensor.hpp"
#include "Salida/ISalida.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"

class Lazo{
  public:
    Lazo(Sensor& sensor);
    ~Lazo();
    void desconectar();
    void conectar();
    Sensor& getSensor();
    virtual ISalida& getSalida()=0;
  protected:
    virtual void onNuevoValorSensor()=0;
  private:
    Sensor& sensor;
    struct Method mOnNuevoValorSensor;
    static void onNuevoValorSensorStatic(void*);    
};

#endif 