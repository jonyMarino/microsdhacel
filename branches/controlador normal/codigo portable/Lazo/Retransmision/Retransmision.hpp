#ifndef _RETRANSMISION_HPP
#define _RETRANSMISION_HPP

#include "Lazo/Lazo.hpp"
#include "IPWM.hpp"

#pragma DATA_SEG Retransmision_DATA                                            
#pragma CODE_SEG Retransmision_CODE 
#pragma CONST_SEG DEFAULT

class ConfiguracionRetransmision{
  public:
    virtual int getLimiteInferior()=0;
    virtual int getLimiteSuperior()=0;
    virtual void setLimiteInferior(int)=0;
    virtual void setLimiteSuperior(int)=0;
};

class Retransmision:public Lazo{
  public:
    Retransmision(Sensor&sensor,IPWM&pwm,ConfiguracionRetransmision& configuracion);
    int getLimiteInferior();
    int getLimiteSuperior();
    void setLimiteInferior(int);
    void setLimiteSuperior(int);
  protected:
    virtual ISalida& getSalida();
    virtual void onNuevoValorSensor();
  private: 
    ConfiguracionRetransmision& configuracion;
    IPWM& pwm;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif