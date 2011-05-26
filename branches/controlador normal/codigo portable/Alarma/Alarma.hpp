#ifndef _ALARMA_HPP
#define _ALARMA_HPP

#include "AlarmaConf.hpp"
 
typedef enum{
  ALARMA_CONTROL,
  ALARMA_RETRANSMISION   
}TTipoAlarma;

class ConfiguracionAlarma{
  public:
    virtual int getLazo()=0;
    
    virtual void setLazo(int lazo)=0;
    
    virtual int getRetLow()=0;
    
    virtual void setRetLow(int valor)=0;

    virtual int getRetHi()=0;

    virtual void setRetHi(int valor)=0;   
};

class Alarma {

  public:
    Alarma(ConfiguracionAlarma &configuracion);
    
    void setLazo(int lazo);

    int getLazo();

    virtual int getAdaptadorSalida()=0;

    virtual void setAdaptadorSalida(int adaptador)=0;
    
    int getRetLow();
    
    void setRetLow(int valor);

    int getRetHi();

    void setRetHi(int valor); 
  protected:
    ConfiguracionAlarma& getConfiguracion();
  private:
    ConfiguracionAlarma &configuracion;   
};

#endif
