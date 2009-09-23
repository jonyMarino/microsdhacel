#ifndef _PWMHARD_H
#define _PWMHARD_H


#include "PWM.hpp"

/**
 * Este PWM usa el PWM del hardware del HCS12
 */
class PWMHard : public PWM {
  protected:
   setDuty();

   setPrescaler();

  inline  setPeriodoHard();

  inline  escalar();

  inline  noEscalar();

    enum ReferenciaPWM {
      RefPWM01,
      RefPWM23,
      RefPWM45

    };

};
inline  PWMHard::setPeriodoHard(const ReferenciaPWM pwm, unsigned int periodo) {
}

inline  PWMHard::escalar(PWMHard::ReferenciaPWM pwm) {
}

inline  PWMHard::noEscalar() {
}

#endif
