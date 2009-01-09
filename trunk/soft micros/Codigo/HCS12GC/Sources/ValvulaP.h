#ifndef _VALVULA_P_H
#define _VALVULA_P_H


#include "display.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
#else
  #include "Control.h"
#endif
#include "O7.h"
#include "O2.h"

#define VP_SALIDA_CONTROL 0
#define VP_SALIDA_ALARMA  2

#define VP_SALIDA_1 OUT_CNTR_1
#define VP_SALIDA_2 OUT_AL_3

#define VP_CLOSE_FACTOR 3/2		/* cantidad de veces el tiempo de 
                              vuelta que tiene que estar cerrandose 
                              la valvula al encender el aparato */
#define VP_ACT_TIME 500 //en ms, Tiempo de actualizacion

void VP_Init(void);

void VP_SetDuty(int duty);

//byte VP_setDeadBand(int dbnd,byte s);

int VP_getTime(void);

int VP_getDeadBand(void);

/**************** FUNCIONES GET & SET *******************************/    
/*  Tiempo  */
int get_VpTime(byte a);
byte set_VpTime(int val, byte a);
int get_LimInf_VpTime(byte a);
/*  Banda Muerta */
int get_VpDeadB(byte a);
byte set_VpDeadB(int val,byte a);
int get_LimInf_VpDeadB(byte a);



#endif 