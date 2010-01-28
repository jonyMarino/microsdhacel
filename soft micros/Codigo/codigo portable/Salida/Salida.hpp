#ifndef _SALIDA_HPP
#define _SALIDA_HPP


#include "ISalida.hpp"
#include "TipoSalida.hpp"

class Salida : public ISalida {
 
  
  public:
  
   typedef struct { 
      unsigned int potencia;
      bool conectado;
      TipoSalida tipoSalida;
   }confSalida;


  
   Salida(confSalida _conf_);
   
   bool getConectada();

   void setConectada(unsigned int conectada);

   virtual unsigned int getPotencia();
   
   virtual TipoSalida getTipoSalida();
   
   virtual void setTipoSalida(TipoSalida _tipoSalida);


  protected:
  virtual void setPotencia(unsigned int _potencia);

   private:
   
    confSalida _confSalida;

};
#endif
