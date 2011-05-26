#ifndef _SALIDABANDA_HPP
#define _SALIDABANDA_HPP

#include "../AdaptadorSalida.hpp" 

/**
 * Usada para accion por exceso y defecto
 */
class SalidaBanda: public AdaptadorSalida {
public:
  SalidaBanda(ISalida& _salida,AdaptadorSalidaConfiguracion& _configuracion);
protected:
  virtual int calcularPotencia(int valorControl);  
};

#endif
