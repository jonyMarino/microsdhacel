#ifndef _PWMHARD23_H
#define _PWMHARD23_H

#include "PWM.hpp"
#include "pwm_periodos.h"
#include "PWMHard.hpp"
#include "TipoSalida.hpp"
#include "Salida.hpp"
#include "Memoria/ManejadorMemoria.hpp" 
#include "TConfPWM.hpp"

static const int periodos[]={   
  25000,											//100 ms
  50000,											//200 ms
  1250 ,											//500 ms
  2500 ,											//1s
  5000 ,											//2s
  12500,											//5s
  25000, 											//10s
  50000,											//20s
  31250,											//50s
  1250   											//5ms
};


class PWMHard23 : public PWMHard {
  public:
    void PWMHard23(struct ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf);
    
    virtual void setTipoSalida(TipoSalida tipoSalida);

    virtual TipoSalida getTipoSalida();

    virtual unsigned char setPeriodo(TPeriod period);
    
    virtual bool getEstadoSalida();
  protected:
    virtual void setPotencia(); 
};
#endif
