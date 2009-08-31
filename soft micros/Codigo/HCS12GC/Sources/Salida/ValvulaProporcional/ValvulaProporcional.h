#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H
#include "Salida.h"
#include "MethodTimer.h"
#include "FshTypeSizes.h"
#include "Errores.h"
#include "RlxMTimer.h"

#define  MAX_TIEMPOABIERTO 10000
#define  MAX_BANDAMUERTA   10000

typedef struct{
  int tiempoAbierto;
  int bandaMuerta;
}ConfValvulaProporcional;

struct ValvulaProporcional{
  struct Salida super;
  ConfValvulaProporcional * conf;
  //struct MethodTimer timer;
  struct RlxMTimer timer;
  byte * puertoApertura;
  byte mascaraApertura;
  byte * puertoCierre;
  byte mascaraCierre;
  long timeCloseInit;
  word timeActual;
};
  
  extern const struct ISalidaClass ValvulaProporcional; 
  
  int get_tiempoAbierto(void *_self);

  TError set_tiempoAbierto(void *_self, int value);

  TError set_bandaMuerta(void *_self,int value);

  int get_bandaMuerta(void *_self);
  
  int get_LimSup_tiempoAbierto(void); 
  
  int get_LimSup_bandaMuerta(void);
    
#endif
