#ifndef _PWM_HPP
#define _PWM_HPP

#include "FshTypeSizes.h"
#include "IPWM.hpp"
#include "MethodContainer.hpp"
#include "Method.h"
#include "pwm_periodos.h"
#include "Memoria/ManejadorMemoria.h" 
//#include "utils_pwm_timer.hpp"

#include "TConfPWM.hpp"

class PWM : public IPWM {
 
 public:
  
  
  PWM(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf):listeners(),manejadorMemoria(_manejadorMemoria),conf(_conf){}
  
  fbyte getLimSupPeriodo();
  
  void addOnToggleListener(struct Method* method);

  friend void llama_callOnToggleListeners(char n);
 
  TPeriod getPeriodo();
   
  virtual unsigned int getPotencia();
  
  virtual void setPotencia(unsigned int potencia);
  
  protected:
  
   void Salida_setPotencia(unsigned int potencia);
   
   unsigned char setPeriodoConfiguracion(TPeriod period);
    
   TPeriod getPeriodoConfiguracion();
   
   void callOnToggleListeners();
   
   bool getConectada();

   void setConectada(bool conectada);


  private:
  
    TConfPWM& conf;
  
    unsigned int potencia;
  
    bool conectado; 
    
    MethodContainer listeners;
    
    struct ManejadorMemoria &manejadorMemoria;
    
    
  
};
#endif
