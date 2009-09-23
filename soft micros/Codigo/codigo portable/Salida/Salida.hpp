#ifndef _SALIDA_HPP
#define _SALIDA_HPP


#include "ISalida.hpp"

class Salida : public ISalida {
  private:
    unsigned int potencia;

    bool conectado;


  public:
   void Salida_setPotencia(unsigned int potencia);

   bool getConectada();

   void setConectada(unsigned int conectada);

   virtual unsigned int getPotencia();


  protected:
  virtual void setPotencia(unsigned int _potencia);

};
#endif
