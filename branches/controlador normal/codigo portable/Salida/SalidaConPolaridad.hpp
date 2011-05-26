#ifndef _SALIDACONPOLARIDAD_HPP
#define _SALIDACONPOLARIDAD_HPP

#include "DecoradorSalida.hpp"

class SalidaConPolaridad:public DecoradorSalida{
  public:
    SalidaConPolaridad(ISalida& aDecorar);
    virtual void setPotencia(unsigned int potencia);
    bool getPolaridad();
    void setPolaridad(bool polaridad);
  private:
    bool polaridad;  
};


#endif
