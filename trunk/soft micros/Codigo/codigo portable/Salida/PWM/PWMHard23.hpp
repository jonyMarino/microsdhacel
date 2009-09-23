#ifndef _PWMHARD23_H
#define _PWMHARD23_H


#include "PWMHard.hpp"
#include "TipoSalida.hpp"

class PWMHard23 : public PWMHard {
  public:
  virtual  setPotencia(unsigned int potencia);

  virtual  setTipoSalida(TipoSalida tipoSalida);

    virtual TipoSalida getTipoSalida();

  virtual unsigned char setPeriodo(int period);

};
#endif
