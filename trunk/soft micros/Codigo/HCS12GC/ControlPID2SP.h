#ifndef _CONTROL_PID_2SP_H
#define _CONTROL_PID_2SP_H

#include "ControlPID.h"

#define MIN_POTENCIA  0
#define MAX_POTENCIA  1000

typedef struct{
  ControlConf base;
  int iSP2;
}Control2SPConf;


#define Control2SPDefaultConf {		\
  10,															\
  0,															\
  100,														\
  0,															\
  0,															\
  CNTR_ONOFF,											\
	_CAL,														\
	0,															\
	0,															\
	0,															\
	1000,														\
	0,															\
	0 															\
}																	\

struct ControlPID2SP{
  struct ControlPID base;
  bool (*chgSP) (void);  
};

extern const void *const ControlPID2SP;

 /*
** ===================================================================
**     Method      :  PID2SP_setSP 
**     Description :  Seteo el SP operativo
** ===================================================================
*/

byte  PID2SP_setSP (void* self, int val);
/*
** ===================================================================
**     Method      :  PID2SP_getSP 
**     Description :  Obtengo el SP operativo
** ===================================================================
*/


int  PID2SP_getSP (void* self);
/*
** ===================================================================
**     Method      :  PID2SP_getSP 
**     Description :  Obtengo el SP auxiliar
** ===================================================================
*/


int PID2SP_getConfSP2(void* self);

byte PID2SP_setSP2(void* self, int val);
     
#endif