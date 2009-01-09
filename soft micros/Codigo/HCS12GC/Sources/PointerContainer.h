#ifndef _POINTER_CONTAINER_H
#define _POINTER_CONTAINER_H

#include "Class.h"
#include "stddef.h"
#include "Errores.h"
 
struct PContainer{
  void * _class;
  void ** pArray;
  uint size;   
};

extern const void *const PContainer;

/*
** ===================================================================
**     Method     :  PContainer_Constructor 
**    Description : Constructor del objeto 
** ===================================================================
*/
//newObj(PContainer)
/*
** ===================================================================
**     Method     :  PContainer_Destructor 
**    Description : Destructor del objeto 
** ===================================================================
*/
void *PContainer_Destructor(void*);

/*
** ===================================================================
**     Method     :  PContainer_Add 
**    Description : Agrega una funcion al contenedor 
** ===================================================================
*/
TError PContainer_Add(void *,void*);

/*
** ===================================================================
**     Method     :  PContainer_isEmpty 
**    Description : Indica si no hay funciones en el contenedor
** ===================================================================
*/
uchar PContainer_isEmpty(void*_self);

/*
** ===================================================================
**     Method     :  PContainer_getSize 
**    Description :  retorna la cantidad de punteros guardados
** ===================================================================
*/
uint PContainer_getSize(void*_self);

/*
** ===================================================================
**     Method     :  PContainer_getPointer 
**    Description :  retorna el puntero guardado
** ===================================================================
*/
void * PContainer_getPointer(void*_self,uint index);

/*
** ===================================================================
**     Method     :  PContainer_Delete 
**    Description :  Elimina el puntero guardado
** ===================================================================
*/
void *PContainer_Delete(void*_self,void * p);

#endif