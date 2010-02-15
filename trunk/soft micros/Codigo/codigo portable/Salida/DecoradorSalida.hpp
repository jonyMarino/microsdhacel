#ifndef _DECORADORSALIDA_H
#define _DECORADORSALIDA_H


#include "ISalida.hpp"
#include "TipoSalida.hpp"

/**
 * Llama al metodo homologo del atributo decorado.
 */
class DecoradorSalida : public ISalida {
  public:
    DecoradorSalida(ISalida& aDecorar);
     
    virtual unsigned int getPotencia();

    virtual void setPotencia(unsigned int potencia);

    virtual TipoSalida getTipoSalida();

    virtual void setTipoSalida(TipoSalida tipoSalida);

    virtual bool getConectada();

    virtual void setConectada(bool conectada);
  private:
    ISalida& decorado;
};
#endif