#ifndef _PWMMANAGER01_45_H
#define _PWMMANAGER01_45_H


#include "PWMHard.hpp"
#include "TipoSalida.hpp"

class PWMManager01_45 {
  private:
    class PWMHard01 : public PWMHard {
      public:
      inline  setPeriodo();

      virtual  setPotencia(unsigned int potencia);

        virtual TipoSalida getTipoSalida();

      virtual  setTipoSalida(TipoSalida tipoSalida);

    };
    
    class PWMHard45 : public PWMHard {
      public:
      inline  setPeriodo();

      virtual  setPotencia(unsigned int potencia);

        virtual TipoSalida getTipoSalida();

      virtual  setTipoSalida(TipoSalida tipoSalida);

    };
    

  public:
  PWMHard * get01();

  PWMHard* get45();

    PWMHard01 pwmHard01;

    PWMHard45 pwmHard45;

};
inline  PWMManager01_45::PWMHard01::setPeriodo(const ReferenciaPWM pwm, unsigned int periodo) {
}

inline  PWMManager01_45::PWMHard45::setPeriodo(const ReferenciaPWM pwm, unsigned int periodo) {
}

#endif
