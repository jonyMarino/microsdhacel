#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H


#include "Salida.hpp"
#include "TipoSalida.hpp"

class ValvulaProporcional : public Salida {
  public:
    unsigned int getTiempoAbierto();

    typedef struct  {
      private:
        unsigned int tiempoAbierto;

        unsigned int bandaMuerta;

    }ConfValvulaProporcional;
    

  private:
    ConfValvulaProporcional * configuracion;

    RlxMTimer timer;

    byte * puertoApertura;

    unsigned char mascaraApertura;

     puertoCierre;

    unsigned char mascaraCierre;

    long timeCloseInit;

    unsigned int timeActual;


  public:
   setTiempoAbierto();

  unsigned int getBandaMuerta();

   setBandaMuerta();

  static unsigned int getLimiteSuperiorTiempoAbierto();

  static  getLimiteSuperiorBandaMuerta();


  protected:
   cerrar();

   abrir();

   detener();


  private:
  static  onCheckear();


  public:
  virtual unsigned int getPotencia();

  virtual  setPotencia(unsigned int potencia);

    virtual TipoSalida getTipoSalida();

  virtual  setTipoSalida(TipoSalida tipoSalida);

};
#endif
