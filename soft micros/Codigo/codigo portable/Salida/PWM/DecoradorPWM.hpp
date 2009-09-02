#ifndef _DECORADORPWM_H
#define _DECORADORPWM_H


#include "DecoradorSalida.hpp"
#include "IPWM.hpp"

/**
 * Llama al metodo homologo del atributo decorado.
 */
class DecoradorPWM : public DecoradorSalida, public IPWM {
  public:
  virtual unsigned char setPeriodo(int period);

  virtual int getPeriodo();

};
#endif
