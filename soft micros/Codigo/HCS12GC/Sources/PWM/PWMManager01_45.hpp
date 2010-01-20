#ifndef _PWMMANAGER01_45_H
#define _PWMMANAGER01_45_H

#include "pwm_periodos.h"
#include "PWMHard.hpp"
#include "TipoSalida.hpp"
#include "Salida.hpp"
#include "PWMHard23.hpp"
#include "TConfPWM.hpp"
#include "PWM.hpp"
#include "PWMHard.hpp"
#include "errores.h"

class PWMManager01_45 {
  private:
    class PWMHard01 : public PWMHard {
      public:
      
      void PWMHard01(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf);
      
      unsigned char setPeriodo(TPeriod periodo);

      virtual void setPotencia(unsigned int potencia);

      virtual TipoSalida getTipoSalida();

      virtual void setTipoSalida(TipoSalida tipoSalida);
      
      virtual bool getEstadoSalida ();
      
      
    };
    
    class PWMHard45 : public PWMHard {
      public:
     
      void PWMHard45(struct ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf);
      
      unsigned char setPeriodo(TPeriod periodo);

      virtual void setPotencia(unsigned int potencia);

      virtual TipoSalida getTipoSalida();

      virtual void setTipoSalida(TipoSalida tipoSalida);
      
      virtual bool getEstadoSalida ();
    
    };
    

  public:
    static TError PWMManager01_45_setPeriodo( PWM * self,TPeriod periodo);
  
    static void PWMManager01_45_configCaso1(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodo05);
    
    static void PWMManager01_45_configCaso2(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodoNo05,TPeriod periodoNo05);
    
    static void PWMManager01_45_configCaso3(PWMHard::ReferenciaPWM pwmPeriodo1,TPeriod periodo1,PWMHard::ReferenciaPWM pwmPeriodo2,TPeriod periodo2);
    
    static void PWM45_actualizarPotencia(uint duty);
    
    static void PWM01_actualizarPotencia(uint duty);
    
    PWMHard* get01();

    PWMHard* get45();

    static PWMHard01* pwmHard01;

    static PWMHard45* pwmHard45;
    

};


 
#endif