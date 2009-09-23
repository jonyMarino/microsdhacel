#ifndef _PWMTIMER_H
#define _PWMTIMER_H


#include "PWM.hpp"
#include "TipoSalida.hpp"
#include "errores.h"
#include "pwm_periodos.h"
#include "PE_Types.h"


class PWMTimer : public PWM {
  protected:
    virtual void pwm_setPotencia(unsigned int _potencia);
  
  private:
     bool estadoSalida;   /*TRUE salida en 1, FALSE salida en 0*/
    
    unsigned int potencia;

    bool conectado;
    
    unsigned char pinNum;

    unsigned long ticksPeriodo;

    unsigned long ticksDuty;

    unsigned long ticksDutyFree;
  
  public:
    
    PWMTimer(struct ManejadorMemoria & _manejadorMemoria,TConfPWM & _conf, uchar pin_out);
     
    virtual void setPotencia(unsigned int potencia);

    unsigned char setPeriodo(TPeriod period);
    
    TPeriod getPeriodo();
     
    virtual void setTipoSalida(TipoSalida tipoSalida);

    virtual  TipoSalida getTipoSalida();
    
    void Salida_setPotencia(unsigned int potencia);

    bool getConectada();

    void setConectada(bool conectada);

    virtual unsigned int getPotencia();
    
    bool getEstadoSalida ();

    friend void pwm_timer_set_periodo( PWMTimer * pwm,ulong periodo);

    friend void pwm_timer_set_duty( PWMTimer * pwm,ulong duty);

    friend byte setPWM_period( PWMTimer * pwm,byte Mode);
    
    friend byte PWM_SetRatio16( PWMTimer * pwm,word Ratio);
    
    friend dword Conf_Toggle( PWMTimer * pwm,bool * next_Value);

  
  
      
};
#endif
