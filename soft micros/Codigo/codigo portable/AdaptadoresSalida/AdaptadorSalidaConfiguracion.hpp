#ifndef _ADAPTSALIDACONF_H
#define _ADAPTSALIDACONF_H


#include "Salida/TipoSalida.hpp"

class AdaptadorSalidaConfiguracion {
  public:
  virtual int getHisteresis() = 0;

  virtual TipoSalida getTipoSalida() = 0;

};
#endif
