#ifndef _COORDINADOR_LAZOS_ALARMA_SENSOR_RETRANSMISION_HPP
#define _COORDINADOR_LAZOS_ALARMA_SENSOR_RETRANSMISION_HPP

#include "AlarmaSensor.hpp"
#include "Retransmision.hpp"


typedef enum{
  ALARMA,
  RETRANSMISION
}TipoLazo;
    
class ConfiguracionCoordinadorLazosAlSenRet{
  public:
    virtual TipoLazo getLazo()=0;
    virtual void setLazo(TipoLazo)=0;    
};

class CoordinadorLazosAlSenRet{
  public:
    CoordinadorLazosAlSenRet( ConfiguracionCoordinadorLazosAlSenRet& configuracion,
                              ConfiguracionAlarmaSensor& confAlarma,
                              ConfiguracionValorControl& confValorControl,
                              AdaptadorSalidaConfiguracion& confAdaptadorSalida,
                              ConfiguracionRetransmision& confRetransmision,
                              Sensor& sensor,
                              ISalida& salida);
                              
    TipoAdaptadorSalida getAdaptadorSalida();

    void setAdaptadorSalida(TipoAdaptadorSalida adaptSalida);
    
    TipoLazo getLazo();
    void setLazo(TipoLazo);

  private:
    union{
      byte retransmision[sizeof(Retransmision)];
      byte alarma[sizeof(AlarmaSensor)];    
    }poolLazo;
    Lazo * lazo;
    ConfiguracionCoordinadorLazosAlSenRet& configuracion;
    ConfiguracionAlarmaSensor& confAlarma;
    ConfiguracionValorControl& confValorControl;
    AdaptadorSalidaConfiguracion& confAdaptadorSalida;
    ConfiguracionRetransmision& confRetransmision;
    
    void crearLazo(TipoLazo tipo,Sensor& sensor,ISalida& salida);
};

#endif
