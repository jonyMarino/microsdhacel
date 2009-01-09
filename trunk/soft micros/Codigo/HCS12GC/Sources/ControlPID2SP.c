/*MODULE: ControlPID2SP.c*/
/*
**     Filename  : ControlPID2SP.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 07/03/2008, 14:42
**     Abstract  :
**							Control PID con Eventos
*/
#include <stdarg.h>
#include <stddef.h>		
#include <stdlib.h>

#include "PE_Types.h"
#include "funciones.h"
#include "IFsh10.h"
#include "ControlPID2SP.h"



void PID2SP_DefConstructor(void * self,va_list * args);
void PID_Constructor(void * self,void * conf,void * sensor,void* salida,int time_desc);
void PID_OnSensNewVal(void * self);

const struct TControl TableControlPID2SP={
    sizeof(struct ControlPID2SP),
    PID2SP_DefConstructor,
    NULL,
    NULL,
    PID2SP_setSP,
    PID2SP_getSP,
    PID_OnSensNewVal
};

const void *const ControlPID2SP= &TableControlPID2SP;



/*
** ===================================================================
**     Method      :  PID2SP_Constructor 
**     Description :  Constructor del control PID
** ===================================================================
*/
void PID2SP_Constructor(void * self,void * conf,void * sensor,void* salida,int time_desc, bool (*chgSP) (void)){
  struct ControlPID2SP * _cont = self;
  
  PID_Constructor(self,conf,sensor,salida,time_desc);
  _cont->chgSP = chgSP;
   
}

/*
** ===================================================================
**     Method      :  PID_DefConstructor 
**     Description :  Constructor por defecto del control PID
** ===================================================================
*/
void PID2SP_DefConstructor(void * self,va_list * args){
  PID2SP_Constructor(self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,int),va_arg(*args,void*));  
}

/*
** ===================================================================
**     Method      :  PID2SP_getSP 
**     Description :  Obtengo el SP operativo
** ===================================================================
*/


int  PID2SP_getSP (void* self){
  struct ControlPID2SP * _cont = self;
  bool ischg = (*_cont->chgSP)();
  
  if(ischg)
    return PID2SP_getConfSP2(self);
  else
		return PID_getConfSP(self);
}


/*
** ===================================================================
**     Method      :  PID2SP_setSP 
**     Description :  Seteo el SP operativo
** ===================================================================
*/


byte  PID2SP_setSP (void* self, int val){
  struct ControlPID2SP * _cont = self;
  bool ischg = (*_cont->chgSP)();
  
  if(ischg)
    return PID2SP_setSP2(self, val);
  else
		return PID_setConfSP(self, val);
}

/*


/*
** ===================================================================
**     Method      :  PID2SP_getSP 
**     Description :  Obtengo el SP auxiliar
** ===================================================================
*/


int PID2SP_getConfSP2(void* self){
  struct ControlPID * _cont = self;
  return ((Control2SPConf*) _cont->_conf)->iSP2;
}
     
byte PID2SP_setSP2(void* self, int val){
  struct ControlPID * _cont = self;
  return EscribirWord((word) &((Control2SPConf*) _cont->_conf)->iSP2, val);
  
}



