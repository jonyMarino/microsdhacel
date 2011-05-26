#ifndef _ISALIDA_HPP
#define _ISALIDA_HPP

#include "../../Librerias/PE/include/PE_Types.h"
#include "Salida/TipoSalida.hpp"

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
