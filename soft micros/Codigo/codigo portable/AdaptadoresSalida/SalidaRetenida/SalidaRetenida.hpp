#ifndef _SALIDARETENIDA_HPP
#define _SALIDARETENIDA_HPP


#include "AdaptadorSalida.hpp"

/**
 * SalidaRetenida
 */
class SalidaRetenida : public AdaptadorSalida {
  public:
    SalidaRetenida(ISalida& _salida,AdaptadorSalidaConfiguracion& _configuracion);   
    inline const bool getRetenida() const;
    void setTipoSalida(TipoSalida tipoSalida);

  protected:  
    int calcularPotencia(int valorControl);
    void setRetenida(bool value);
  private:
    bool retenida;
};

inline const bool SalidaRetenida::getRetenida() const {
  return retenida;
}

#endif
