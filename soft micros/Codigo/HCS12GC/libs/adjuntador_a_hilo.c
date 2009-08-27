#include <stdarg.h>
#include "adjuntador_a_hilo.h"
#include "stdtypes.h"

void AdjuntadorAHilo_defConstructor(void * self,va_list * args);

const struct Class TableAdjuntadorAHilo={
    &Class,
  "",
  &Object,
  sizeof(struct AdjuntadorAHilo),
  AdjuntadorAHilo_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
};


const void * const AdjuntadorAHilo= &TableAdjuntadorAHilo;


/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_constructor 
**     Description :  Constructor de la clase
** ===================================================================
*/
#pragma INLINE
void AdjuntadorAHilo_constructor(void * _self,struct ThreadAdjuntable * thread){
  struct AdjuntadorAHilo* _a=_self;
  
  _a->threadAdjuntable= thread;   
}

/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_Defconstructor 
**     Description :  Constructor por defecto de la clase
** ===================================================================
*/
void AdjuntadorAHilo_defConstructor(void * self,va_list * args){
  AdjuntadorAHilo_constructor(self,va_arg(*args,void*));  
}


/*
** ===================================================================
**     Method      :  AdjuntadorAHilo_adjuntar 
**     Description :  adjunta el metodo al hilo de ejecucion
** ===================================================================
*/

void AdjuntadorAHilo_adjuntar(void * _self,pMethod method, void * Obj){
  struct AdjuntadorAHilo* _a=_self;
  struct Method * methodObj= _new(&Method,method,Obj);
  ThreadAdjuntable_Adjuntar(_a->threadAdjuntable,methodObj);
}
