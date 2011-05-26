#ifndef _SALIDARETENIDABAJO_HPP
#define _SALIDARETENIDABAJO_HPP

#include "AdaptadorSalidaConfiguracion.hpp"
#include "SalidaRetenida.hpp"

/**
 * SalidaRetenidaBajo
 */
class SalidaRetenidaBajo : public SalidaRetenida {
  public:
    SalidaRetenidaBajo(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion);   
    int calcularDuty(int valorDeControl);
};



#endif
