#ifndef _ALARMA_SENSOR_HPP
#define _ALARMA_SENSOR_HPP


#include "LazoControl.hpp"
#include "ValorControlProporcionalInvertido.hpp"
#include "SalidaBloqueada.hpp"
#include "SalidaBanda.hpp"
#include "SalidaRetenidaBajo.hpp"
#include "SalidaRetenida.hpp"
#include "SalidaConPolaridad.hpp"

typedef enum{
  SALIDA_RETENIDA,
  SALIDA_DEFECTO_RETENIDA,
  SALIDA_DEFECTO_BLOQUEADA,
  SALIDA_DEFECTO,
  SALIDA_EXCESO
}TipoAdaptadorSalida;
    
class ConfiguracionAlarmaSensor{
  public:
    virtual TipoAdaptadorSalida getAdaptadorSalida()=0;
    virtual void setAdaptadorSalida(TipoAdaptadorSalida)=0;
};

class AlarmaSensor:public LazoControl{
  public:
    AlarmaSensor(ConfiguracionAlarmaSensor& configuracion,ConfiguracionValorControl& confValorControl,Sensor&sensor,AdaptadorSalidaConfiguracion& confAdaptadorSalida,ISalida& salida);
    TipoAdaptadorSalida  AlarmaSensor::getAdaptadorSalida();
    void AlarmaSensor::setAdaptadorSalida(TipoAdaptadorSalida adaptSalida);
  private:
    ConfiguracionAlarmaSensor& configuracion;
    ValorControlProporcionalInvertido valorControl;   
    union{
      byte salidaBloqueada[sizeof(SalidaBloqueada)];
      byte salidaBanda[sizeof(SalidaBanda)];
      byte salidaRetenida[sizeof(SalidaRetenida)];
      byte salidaRetenidaBajo[sizeof(SalidaRetenidaBajo)]; 
    }adaptadorSalida;
    
    SalidaConPolaridad salidaConPolaridad;
    
    void crearAdaptadorSalida(TipoAdaptadorSalida adaptSalida);

};


#endif