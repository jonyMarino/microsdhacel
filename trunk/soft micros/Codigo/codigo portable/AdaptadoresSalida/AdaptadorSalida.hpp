#ifndef _ADAPTADORSALIDA_HPP
#define _ADAPTADORSALIDA_HPP


#include "AdaptadorSalidaConfiguracion.hpp"
#include "Salida/ISalida.hpp"

/**
 * Transforma de un valor de control a un valor de potencia para la salida
 */
class AdaptadorSalida {
  public:
    AdaptadorSalida(ISalida& _salida,AdaptadorSalidaConfiguracion& _configuracion);
    void setPotenciaSalida(int valorDeControl);
    int getHisteresis();
    void setHisteresis(int histeresis);
    int getTipoSalida();
    void setTipoSalida(TipoSalida tipoSalida);
    ISalida& getSalida();
  protected:
    virtual int calcularPotencia(int valorControl)=0;

  private:
    ISalida& salida;
    AdaptadorSalidaConfiguracion& configuracion;
};


#endif
