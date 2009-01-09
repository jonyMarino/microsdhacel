/*MODULE: CntrlPidSt*/
/*
**     Filename  : CntrlPidSt.H
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 14/02/2008, 11:42
**     Abstract  :
**							Control PID con Eventos y auto sintonia.
*/

#ifndef _CNTRL_PID_ST_H
#define _CNTRL_PID_ST_H

#include "ControlPID.h"


typedef enum{
  ST_OFF,
  ST_RUNNING,
}T_ST_State;

struct CntrlPidSt{
  struct ControlPID _base;
  T_ST_State State;
};


//Definición de la VTable
struct TCntrlPidSt{
  struct TControl _base;
 // void (*RunSt)(void *);   // Manda a hacer una auto sintonia
};

#endif