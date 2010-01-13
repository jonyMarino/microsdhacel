#ifndef _ADAPTSALIDACONF_H
#define _ADAPTSALIDACONF_H


#include "TipoSalida.hpp"

class AdaptadorSalidaConfiguracion {
  public:
  virtual int getHisteresis() = 0;

  virtual void setHisteresis(int histeresis) = 0;

  virtual TipoSalida getTipoSalida() = 0;

  virtual void setTipoSalida(TipoSalida tipoSalida) = 0;

};
#endif
