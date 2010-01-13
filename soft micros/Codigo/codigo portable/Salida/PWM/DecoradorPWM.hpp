#ifndef _DECORADORPWM_H
#define _DECORADORPWM_H


#include "DecoradorSalida.hpp"
#include "IPWM.hpp"

/**
 * Llama al metodo homologo del atributo decorado.
 */
class DecoradorPWM : public IPWM {
  public:
  
  virtual unsigned int getPotencia();

  virtual void setPotencia(unsigned int potencia);

  virtual TipoSalida getTipoSalida();

  virtual void setTipoSalida(TipoSalida tipoSalida);

  virtual bool getConectada();

  virtual void setConectada(bool conectada);

  
  virtual unsigned char setPeriodo(TPeriod period);

  virtual TPeriod getPeriodo();

};
#endif
