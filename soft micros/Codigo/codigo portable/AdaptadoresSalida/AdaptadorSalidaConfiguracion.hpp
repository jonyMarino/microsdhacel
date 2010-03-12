#ifndef _ADAPTSALIDACONF_HPP
#define _ADAPTSALIDACONF_HPP


#include "Salida/TipoSalida.hpp"

class AdaptadorSalidaConfiguracion {
  public:
  virtual int getHisteresis() = 0;
  virtual TipoSalida getTipoSalida() = 0;
  virtual void setHisteresis(int) = 0;
  virtual void setTipoSalida(TipoSalida) = 0;
};
#endif
