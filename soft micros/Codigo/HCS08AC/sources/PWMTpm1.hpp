#ifndef _PWMTPM1_H
#define _PWMTPM1_H


#include "PWM.hpp"
#include "TipoSalida.hpp"

/**
 * este  PWM  utiliza el hard del HCS08
 */
class PWMTpm1 : public PWM {
  public:
  virtual unsigned char setPeriodo(int period);

  virtual int getPeriodo();

    virtual unsigned int getPotencia();

  virtual  setPotencia(unsigned int potencia);

    virtual TipoSalida getTipoSalida();

  virtual  setTipoSalida(TipoSalida tipoSalida);

    virtual bool getConectada();

  virtual void setConectada(bool conectada);

};
#endif
