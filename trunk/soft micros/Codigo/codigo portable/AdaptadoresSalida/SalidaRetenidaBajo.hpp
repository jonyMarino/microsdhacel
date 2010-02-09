#ifndef _SALIDA_RETENIDA_BAJO_HPP
#define _SALIDA_RETENIDA_BAJO_HPP

#include "SalidaRetenida.hpp"

class SalidaRetenidaBajo:public SalidaRetenida{
  public:
    SalidaRetenidaBajo(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion);
  protected:  
    int calcularPotencia(int valorControl);    
};

#endif