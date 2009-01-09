#ifndef _FUNCTION_CONTAINER_H
#define _FUNCTION_CONTAINER_H

#include "Object.h"
#include "stddef.h"
#include "Errores.h"

#ifndef pf
  typedef void (*Pf)(void);
#endif
 
struct FncContainer{
  struct Object super;
  Pf * pfArray;
  uint size;   
};

extern const void *const FncContainer;

/*
** ===================================================================
**     Method     :  FncContainer_Constructor 
**    Description : Constructor del objeto 
** ===================================================================
*/
//newObj(FncContainer)
/*
** ===================================================================
**     Method     :  FncContainer_Destructor 
**    Description : Destructor del objeto 
** ===================================================================
*/
void *FncContainer_Destructor(void*);

/*
** ===================================================================
**     Method     :  FncContainer_Add 
**    Description : Agrega una funcion al contenedor 
** ===================================================================
*/
TError FncContainer_Add(void *,Pf);

/*
** ===================================================================
**     Method     :  FncContainer_Execute 
**    Description : Ejecuta las funciones agergadas al contenedor
** ===================================================================
*/
void FncContainer_Execute(void*);
/*
** ===================================================================
**     Method     :  FncContainer_isEmpty 
**    Description : Indica si no hay funciones en el contenedor
** ===================================================================
*/
uchar FncContainer_isEmpty(void*_self);

#endif