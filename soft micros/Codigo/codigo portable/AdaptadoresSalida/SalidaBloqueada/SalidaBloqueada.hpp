#ifndef _SALIDABLOQUEDA_H
#define _SALIDABLOQUEDA_H


#include "AdaptadorSalida.hpp"

class SalidaBloqueada : public AdaptadorSalida {
  public:
    SalidaBloqueada(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion);
    void setTipoSalida(int histeresis);

  protected:
    int calcularPotencia(int valorControl);
  private:
    bool bloqueada;

};
#endif
