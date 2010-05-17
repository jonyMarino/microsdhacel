#ifndef _PWMTIMER_H
#define _PWMTIMER_H


#include "PWM.hpp"
#include "TipoSalida.hpp"
#include "errores.h"
#include "pwm_periodos.h"
#include "PE_Types.h"


class PWMTimer : public PWM {
  public:
    
    PWMTimer(struct ManejadorMemoria & _manejadorMemoria,TConfPWM & _conf, uchar pin_out);

    unsigned char setPeriodo(TPeriod period);
 
    virtual void setTipoSalida(TipoSalida tipoSalida);

    virtual  TipoSalida getTipoSalida();
    
    bool getEstadoSalida ();
    
    void setPotenciaGuardada(); 

    
  private:
    bool estadoSalida;   /*TRUE salida en 1, FALSE salida en 0*/
    
    unsigned char pinNum;

    unsigned long ticksPeriodo;

    unsigned long ticksDuty;

    unsigned long ticksDutyFree;
 

    friend void pwm_timer_set_periodo( PWMTimer * pwm,ulong periodo);

    friend void pwm_timer_set_duty( PWMTimer * pwm,ulong duty);

    friend byte setPWM_period( PWMTimer * pwm,byte Mode);
    
    friend byte PWM_SetRatio16( PWMTimer * pwm,word Ratio);
    
    friend dword Conf_Toggle( PWMTimer * pwm,bool * next_Value);     
};

#endif
