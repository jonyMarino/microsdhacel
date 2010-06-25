#ifndef _PWMSOFT_H
#define _PWMSOFT_H


#include "PWM.hpp"
#include "TipoSalida.hpp"
#include "Timer/MethodTimer/MethodTimer.hpp"

class PWMSoft : public PWM {
  public:
  
  PWMSoft(struct ManejadorMemoria &_manejadorMemoria,byte * _salida,TConfPWM &_conf, uchar pin_out);
  
  virtual void setPotencia(unsigned int potencia);

  virtual unsigned char setPeriodo(TPeriod period);

  virtual void setTipoSalida(TipoSalida tipoSalida);

  virtual TipoSalida getTipoSalida();
  
  bool getEstadoSalida ();
   
  void setPotenciaGuardada();
  
  unsigned char * salida;

  unsigned char mascara;

  static MethodTimer * time;
  
  static PWMSoft* pwmSoft_;
  
  private:
    
    TipoSalida tipoSalida; 
    
    static const struct Method onChg;

    
};
#endif
