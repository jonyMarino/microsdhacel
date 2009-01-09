#ifndef _ALARMA_SENSOR_H
#define _ALARMA_SENSOR_H

#include "Alarma.h"
#include "AlarmaSenConf.h"
#include "LazoControlAlSen.h"
#include "RetransmisionPWM.h"

//cambiar : Primero hago alarma de sensor, luego modifico

#define FATTER_LAZO_SIZE sizeof(struct LazoControlAlSen)
struct AlarmaSensor {
  struct Alarma super;
//%-  
  byte lazo[FATTER_LAZO_SIZE]; //combinacion de maximo uso de memoria
                               //cambiar con m4
}; 

extern const struct Class AlarmaSensor;

TTipoAlarma  AlarmaSensor_getTipo(void*);

byte AlarmaSensor_setTipo(void*,TTipoAlarma tipoAlarma);

TAdaptador  AlarmaSensor_getAdaptadorSalida(void*);

byte AlarmaSensor_setAdaptadorSalida(void*,TAdaptador adaptSalida);

//TValorControl  AlarmaSensor_getControlador(void*);

//byte AlarmaSensor_setControlador(void*,TValorControl);

int   Alarma_getValor(void*_self);
byte  Alarma_setValor(void*_self,int valor);

int    Alarma_getHisteresis(void*_self);
byte   Alarma_setHisteresis(void*_self,int histeresis);

#endif
