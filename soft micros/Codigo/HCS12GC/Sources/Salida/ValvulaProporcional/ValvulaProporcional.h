#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H
#include "Salida.h"
#include "MethodTimer.h"
#define  MAX_TIEMPOABIERTO 65500
#define  MAX_BANDAMUERTA   65500

typedef struct{
  int tiempoAbierto;
  int bandaMuerta; 
}ConfValvulaProporcional;

struct ValvulaProporcional{
  struct Salida super;
  ConfValvulaProporcional * conf;
  struct MethodTimer timer;
};
  
  extern const struct ISalidaClass ValvulaProporcional; 
  
  int get_tiempoAbierto(void *_self);

  void set_tiempoAbierto(void *_self, int value);

  int get_bandaMuerta(void *_self);

  void set_bandaMuerta(void *_self, int value);

  int get_tiempoAbierto(void *_self);
  
  int get_LimSup_tiempoAbierto(void);

  int get_bandaMuerta(void *_self);
  
  int get_LimSup_bandaMuerta(void);
  
  void  ValvulaProporcional_onCheckear(void *_self,int potencia);
  
#endif
