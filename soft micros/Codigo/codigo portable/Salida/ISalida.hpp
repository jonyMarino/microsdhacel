#ifndef _ISALIDA_H
#define _ISALIDA_H

#include "PE_Types.h"
#include "TipoSalida.hpp"

class ISalida {
  public:
    virtual unsigned int getPotencia() = 0;

    virtual void setPotencia(unsigned int potencia) = 0;

    virtual TipoSalida getTipoSalida() = 0;

    virtual void setTipoSalida(TipoSalida tipoSalida) = 0;

    virtual bool getConectada() = 0;

    virtual void setConectada(bool conectada) = 0;

};
#endif
