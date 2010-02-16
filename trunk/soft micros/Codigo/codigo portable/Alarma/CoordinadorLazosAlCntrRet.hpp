#ifndef _COORDINADOR_LAZOS_ALARMA_CONTROL_RETRANSMISION_HPP
#define _COORDINADOR_LAZOS_ALARMA_CONTROL_RETRANSMISION_HPP

#include "AlarmaControl.hpp"
#include "Retransmision.hpp"


typedef enum{
  ALARMA,
  RETRANSMISION
}TipoLazo;
    
class ConfiguracionCoordinadorLazosAlCntrRet {
  public:
    virtual TipoLazo getLazo()=0;
    virtual void setLazo(TipoLazo)=0;    
};

class CoordinadorLazosAlCntrRet{
  public:
    CoordinadorLazosAlCntrRet( ConfiguracionCoordinadorLazosAlCntrRet& configuracion,
                              ConfiguracionAlarmaControl& confAlarma,
                              ConfiguracionValorControl& confValorControl,
                              AdaptadorSalidaConfiguracion& confAdaptadorSalida,
                              ConfiguracionRetransmision& confRetransmision,
                              ControlPID& control,
                              IPWM&pwm);
                              
    TipoAdaptadorSalida getAdaptadorSalida();
    void setAdaptadorSalida(TipoAdaptadorSalida adaptSalida);
    TipoControl  getTipoControl();
    void setTipoControl(TipoControl tipoControl); 
    TipoLazo getLazo();
    void setLazo(TipoLazo);

  private:
    class RetransmisionOptMem:public Retransmision{
      public:
        RetransmisionOptMem(Sensor&sensor,IPWM&pwm,ConfiguracionRetransmision& configuracion);
        void * operator new(size_t size,byte * dir);

        void operator delete(void *ptr);
    };
    
    class AlarmaOptMem:public AlarmaControl{
      public:
        AlarmaOptMem(ConfiguracionAlarmaControl& configuracion,ConfiguracionValorControl& confValorControl,AdaptadorSalidaConfiguracion& confAdaptadorSalida,ControlPID& control,ISalida&salida);
        void * operator new(size_t size,byte * dir);

        void operator delete(void *ptr);
    };
    union{
      byte retransmision[sizeof(CoordinadorLazosAlCntrRet::RetransmisionOptMem)];
      byte alarma[sizeof(CoordinadorLazosAlCntrRet::AlarmaOptMem)];    
    }poolLazo;
    LazoControl * lazo;
    ConfiguracionCoordinadorLazosAlCntrRet& configuracion;
    ConfiguracionAlarmaControl& confAlarma;
    ConfiguracionValorControl& confValorControl;
    AdaptadorSalidaConfiguracion& confAdaptadorSalida;
    ConfiguracionRetransmision& confRetransmision;
    ControlPID& control;
    void crearLazo(TipoLazo tipo,IPWM&pwm);
};

#endif
