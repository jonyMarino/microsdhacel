#ifndef _ALARMA_CONREOL_HPP
#define _ALARMA_CONTROL_HPP


#include "LazoControl.hpp"
#include "ValorControlProporcionalInvertido.hpp"
#include "ValorControlBanda.hpp"
#include "ValorControlRelativo.hpp"
#include "SalidaBloqueada.hpp"
#include "SalidaBanda.hpp"
#include "SalidaRetenidaBajo.hpp"
#include "SalidaRetenida.hpp"
#include "SalidaConPolaridad.hpp"
#include "ControlPID.hpp"

typedef enum{
  SALIDA_RETENIDA,
  SALIDA_DEFECTO_RETENIDA,
  SALIDA_DEFECTO_BLOQUEADA,
  SALIDA_DEFECTO,
  SALIDA_EXCESO
}TipoAdaptadorSalida;

typedef enum{
  CONTROL_PROPORCIONAL,
  CONTROL_RELATIVO,
  CONTROL_BANDA
}TipoControl;
    
class ConfiguracionAlarmaControl{
  public:
    virtual TipoAdaptadorSalida getAdaptadorSalida()=0;
    virtual void setAdaptadorSalida(TipoAdaptadorSalida)=0;
    virtual TipoControl getTipoControl()=0;
    virtual void setTipoControl(TipoControl)=0;
};

class AlarmaControl:public LazoControl{
  public:
    AlarmaControl(ConfiguracionAlarmaControl& configuracion,ConfiguracionValorControl& confValorControl,AdaptadorSalidaConfiguracion& confAdaptadorSalida,ControlPID& control,ISalida&salida);
    TipoAdaptadorSalida  getAdaptadorSalida();
    void setAdaptadorSalida(TipoAdaptadorSalida adaptSalida);
    TipoControl  getTipoControl();
    void setTipoControl(TipoControl tipoControl);    
  private:
    class GetterSP:public Getter{
      public:
        GetterSP(ControlPID& control);
        int getVal();
        void print(OutputStream&os);
        ControlPID& control;  
    }getterSP;
    ConfiguracionAlarmaControl& configuracion;
    union{   
      byte  relativo[sizeof(ValorControlRelativo)];  
      byte  propInv[sizeof(ValorControlProporcionalInvertido)]; 
      byte  banda[sizeof(ValorControlBanda)]; 
    }tipoControl;
       
    union{
      byte salidaBloqueada[sizeof(SalidaBloqueada)];
      byte salidaBanda[sizeof(SalidaBanda)];
      byte salidaRetenida[sizeof(SalidaRetenida)];
      byte salidaRetenidaBajo[sizeof(SalidaRetenidaBajo)]; 
    }adaptadorSalida;
    
    SalidaConPolaridad salidaConPolaridad;
    
    void crearAdaptadorSalida(TipoAdaptadorSalida adaptSalida);
    void crearTipoControl(TipoControl tipoControl);
};


#endif