#ifndef _PWMMANAGER01_45_HPP
#define _PWMMANAGER01_45_HPP

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
        PWMHard01(ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf);
        
        unsigned char setPeriodo(TPeriod periodo);

        virtual TipoSalida getTipoSalida();

        virtual void setTipoSalida(TipoSalida tipoSalida);
        
        virtual bool getEstadoSalida ();
        
        //void * operator new(size_t size,byte * dir){
        //return dir;};
        
      protected:
        virtual void setPotenciaGuardada();       
    };
    
    class PWMHard45 : public PWMHard {
      public:
     
        PWMHard45(ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf);
        
        unsigned char setPeriodo(TPeriod periodo);

        virtual TipoSalida getTipoSalida();

        virtual void setTipoSalida(TipoSalida tipoSalida);
        
        virtual bool getEstadoSalida ();
        
        //void * operator new(size_t size,byte * dir){
        //return dir;};
        
      protected:
        virtual void setPotenciaGuardada();      
    
    };
    static PWMHard01* pwmHard01;

    static PWMHard45* pwmHard45;    
  
  public:
    //PWMManager01_45 (ManejadorMemoria &_manejadorMemoria,const TConfPWM &_conf01,const TConfPWM &_conf45);
    
    static TError PWMManager01_45_setPeriodo( PWM * self,TPeriod periodo);
  
    static void PWMManager01_45_configCaso1(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodo05);
    
    static void PWMManager01_45_configCaso2(PWMHard::ReferenciaPWM pwmPeriodo50,PWMHard::ReferenciaPWM pwmPeriodoNo05,TPeriod periodoNo05);
    
    static void PWMManager01_45_configCaso3(PWMHard::ReferenciaPWM pwmPeriodo1,TPeriod periodo1,PWMHard::ReferenciaPWM pwmPeriodo2,TPeriod periodo2);
    
    static void PWM45_actualizarPotencia(uint duty);
    
    static void PWM01_actualizarPotencia(uint duty);
    
    static PWMHard* get01(ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf);

    static PWMHard* get45(ManejadorMemoria &_manejadorMemoria,TConfPWM &_conf); 
    
    //static byte poolPwm01[sizeof(PWMHard01)];
     
    //static byte poolPwm45[sizeof(PWMHard45)];
};


 
#endif
