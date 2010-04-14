#ifndef _PWMHARD23_H
#define _PWMHARD23_H

#include "PWM.hpp"
#include "pwm_periodos.h"
#include "PWMHard.hpp"
#include "TipoSalida.hpp"
#include "Salida.hpp"
#include "Memoria/ManejadorMemoria.hpp" 
#include "TConfPWM.hpp"

#pragma DATA_SEG PWM_HARD_23_DATA                                            
#pragma CODE_SEG PWM_HARD_23_CODE                     
#pragma CONST_SEG PWM_HARD_23_CONST   


class PWMHard23 : public PWMHard {
  public:
    void PWMHard23(struct ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf);
    
    virtual void setTipoSalida(TipoSalida tipoSalida);

    virtual TipoSalida getTipoSalida();

    virtual unsigned char setPeriodo(TPeriod period);
    
    virtual bool getEstadoSalida();
  protected:
    virtual void setPotenciaGuardada(); 
};
#endif

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT                     
#pragma CONST_SEG DEFAULT  
