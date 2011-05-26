#ifndef _PWMPERIODOEVENT_H
#define _PWMPERIODOEVENT_H


#include "DecoradorPWM.hpp"
#include "MethodContainer.hpp"

class Method;

/**
 * Agrega funcionalidad al PWM con evento al cambiar el periodo.
 */
class PWMPeriodoEvent : public DecoradorPWM {
  public:
  void addPeriodoListener(void * metodo);

  void deletePeriodoListenermetodo(void * metodo);


  private:
    MethodContainer listeners;


  public:
  virtual unsigned char setPeriodo(int period);

};
#endif
