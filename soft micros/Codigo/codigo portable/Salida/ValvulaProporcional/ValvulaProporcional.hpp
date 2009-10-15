#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H


#include "Salida.hpp"
#include "TipoSalida.hpp"
#include "RlxMTimer.h"

class ValvulaProporcional : public Salida {
  
  public:
    typedef struct  {
      private:
        unsigned int tiempoAbierto;

        unsigned int bandaMuerta;

    }ConfValvulaProporcional;
    
    unsigned int getTiempoAbierto();

  unsigned char setTiempoAbierto(unsigned int value);

  unsigned int getBandaMuerta();

  unsigned char setBandaMuerta(unsigned int bandaMuerta);

  static unsigned int getLimiteSuperiorTiempoAbierto();

  static unsigned int getLimiteSuperiorBandaMuerta();

  virtual unsigned int getPotencia();

  virtual  setPotencia(unsigned int potencia);

    virtual TipoSalida getTipoSalida();

  virtual  setTipoSalida(TipoSalida tipoSalida);


  protected:
  void cerrar();

  void abrir();

   detener();
   
   private:
    struct ManejadorMemoria manejadorMemoria;
    
    ConfValvulaProporcional * conf;

   struct RlxMTimer timer;

    byte * puertoApertura;

    unsigned char mascaraApertura;

    byte * puertoCierre;  

    unsigned char mascaraCierre;

    long timeCloseInit;

    static void onCheckear();

    unsigned int timeActual;



};
#endif
