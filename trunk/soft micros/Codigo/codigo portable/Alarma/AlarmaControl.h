#ifndef _ALARMA_CONTROL_H
#define _ALARMA_CONTROL_H

#include "Alarma.h"
#include "Control.h"
#include "AlarmaCntrConf.h"
#include "LazoAlarmaControl.h"
#include "RetransmisionPWM.h"
#include "Control.h"

struct AlarmaControl {
  struct Alarma super;
//%-
  struct Control * control;
  struct Lazo* lazo;      /*LazoActual*/  
  struct LazoAlarmaControl lazoAlarmaControl;
  struct RetransmisionPWM retransmisionPWM;
};


extern const struct Class AlarmaControl;

#define _AlarmaControl_getLazo(self) (struct Lazo*)((struct AlarmaControl*)self)->lazo

TTipoAlarma  AlarmaControl_getTipo(void*);

byte AlarmaControl_setTipo(void*,TTipoAlarma tipoAlarma);

TAdaptador  AlarmaControl_getAdaptadorSalida(void*);

byte AlarmaControl_setAdaptadorSalida(void*,TAdaptador adaptSalida);

int AlarmaControl_adaptSalidaLimSup(void * _self);

TControlAlarma  AlarmaControl_getControl(void*);

byte AlarmaControl_setControl(void*,TControlAlarma);

int   AlarmaControl_getValor(void*_self);
byte  AlarmaControl_setValor(void*_self,int valor);

int    AlarmaControl_getHisteresis(void*_self);
byte   AlarmaControl_setHisteresis(void*_self,int histeresis);

TipoSalida    AlarmaControl_getTipoSalida(void*_self);
byte   AlarmaControl_setTipoSalida(void*_self,TipoSalida tipoSalida);

struct Sensor * AlarmaControl_getSensor(void * _self);

#endif
