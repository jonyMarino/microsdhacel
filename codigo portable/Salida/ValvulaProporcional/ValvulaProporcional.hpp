#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H

#include "ManejadorMemoria.h"
#include "LinkedList.hpp"
#include "Salida.hpp"
#include "TipoSalida.hpp"
#include "Errores.h"
#include "RlxMTimer.h"


#define  MAX_TIEMPOABIERTO 10000
#define  MAX_BANDAMUERTA   10000
#define  FACTOR_SEGURIDAD  1
#define  CERRANDO 2
#define  ABRIENDO 1
#define  DETENIDA 0

class ValvulaProporcional : public Salida {
  
  public:
  
    
    typedef struct  {
     // private:
        unsigned int tiempoAbierto;

        unsigned int bandaMuerta;

    }ConfValvulaProporcional;
    
  
  ValvulaProporcional(struct ManejadorMemoria &_manejadorMemoria,ConfValvulaProporcional* conf,byte * puertoApertura,int bitApertura,byte * puertoCierre,int bitCierre); 
    
  static unsigned int getTiempoAbierto(void*_self);

  static unsigned char setTiempoAbierto(void*_self,unsigned int value);

  static unsigned int getBandaMuerta(void*_self);

  static unsigned char setBandaMuerta(void*_self,unsigned int bandaMuerta);

  static unsigned int getLimiteSuperiorTiempoAbierto(void*_self);

  static unsigned int getLimiteSuperiorBandaMuerta(void*_self);

  virtual unsigned int getPotencia();

  virtual void setPotencia(unsigned int potencia);

  virtual TipoSalida getTipoSalida();

  virtual void setTipoSalida(TipoSalida tipoSalida);

  virtual bool getConectada();
  
  virtual void setConectada(bool conectada);
  
  long getTimeCloseInit(){return timeCloseInit;}
  
  char getStatus();
  
  protected:
   void cerrar();

   void abrir();

   void detener();
   
  // void onCheckear();
   
   private:
    
    static void onCheckear(void * self);
    
    struct ManejadorMemoria & manejadorMemoria;
    
    ConfValvulaProporcional * conf;

    struct RlxMTimer timer;
     //struct MethodTimer timer;

    byte * puertoApertura;

    unsigned char mascaraApertura;

    byte * puertoCierre;  

    unsigned char mascaraCierre;
    
    unsigned int timeActual;
    
    long timeCloseInit;
    
    char status; /* 0:detenida
                    1:abriendo
                    2:cerrendo
                   */
    unsigned int _potencia;               
    
};

#endif
