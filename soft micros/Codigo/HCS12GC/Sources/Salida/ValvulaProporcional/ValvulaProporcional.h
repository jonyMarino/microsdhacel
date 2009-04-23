#ifndef _VALVULAPROPORCIONAL_H
#define _VALVULAPROPORCIONAL_H
#include "Salida.h"

typedef struct{
  int tiempoAbierto;
  int bandaMuerta; 
}ConfValvulaProporcional;

struct ValvulaProporcional{
  struct Salida super;
  ConfValvulaProporcional * conf;
};
  
  int get_tiempoAbierto(void *_self);

  void set_tiempoAbierto(void *_self, int value);

  int get_bandaMuerta(void *_self);

  void set_bandaMuerta(void *_self, int value);


#endif
