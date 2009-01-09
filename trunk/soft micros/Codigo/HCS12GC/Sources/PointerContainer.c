/*MODULE: PointerContainer.c*/

#include <stdlib.h>
#include <stdarg.h>
#include "PointerContainer.h"

void PContainer_DefConstructor(void * _self,va_list * args);
void *PContainer_Destructor(void* _self);

const struct Tclass TablePContainer={
  sizeof(struct PContainer),
  PContainer_DefConstructor,
  NULL,
  PContainer_Destructor
};

const void *const  PContainer=&TablePContainer;

/*
** ===================================================================
**     Method     :  PContainer_Constructor 
**    Description : Constructor del objeto 
** ===================================================================
*/
void PContainer_Constructor(void * _self){
  struct PContainer * pc= _self;
  pc->size=0;
  pc->pArray=NULL;   
}
/*
** ===================================================================
**     Method     :  PContainer_DefConstructor 
**    Description : Constructor por defecto del objeto 
** ===================================================================
*/
void PContainer_DefConstructor(void * _self,va_list * args){
  PContainer_Constructor(_self);  
}
/*
** ===================================================================
**     Method     :  PContainer_Destructor 
**    Description : Destructor del objeto 
** ===================================================================
*/
void *PContainer_Destructor(void* _self){
  struct PContainer * pc= _self;
  free(pc->pArray);
  return _self;
}

/*
** ===================================================================
**     Method     :  PContainer_Add 
**    Description : Agrega una funcion al contenedor 
** ===================================================================
*/
TError PContainer_Add(void * _self,void * _p){
  struct PContainer * pc= _self;
  void * p_tmp;
  
  ++pc->size;
  p_tmp= realloc(pc->pArray,pc->size*sizeof(void *));
  if(p_tmp){
    pc->pArray= p_tmp;
    pc->pArray[pc->size-1]= _p;
    return ERR_OK;     
  }
  --pc->size;
  return ERR_MEM;
}

/*
** ===================================================================
**     Method     :  PContainer_isEmpty 
**    Description : Indica si no hay funciones en el contenedor
** ===================================================================
*/
uchar PContainer_isEmpty(void*_self){
  struct PContainer * pc= _self;
  return pc->size==0;
}

/*
** ===================================================================
**     Method     :  PContainer_getSize 
**    Description :  retorna la cantidad de punteros guardados
** ===================================================================
*/
uint PContainer_getSize(void*_self){
  struct PContainer * pc= _self;
  return pc->size;
}

/*
** ===================================================================
**     Method     :  PContainer_getPointer 
**    Description :  retorna el puntero guardado
** ===================================================================
*/
void * PContainer_getPointer(void*_self,uint index){
  struct PContainer * pc= _self;
  
  return pc->pArray[index];
}

/*
** ===================================================================
**     Method     :  PContainer_Delete 
**    Description :  Elimina el puntero guardado
** ===================================================================
*/
void *PContainer_Delete(void*_self,void * p){
  struct PContainer * pc= _self;
  size_t i;
  
  for(i=0;i<pc->size;++i){
    if(pc->pArray[i]==p)
      break;  
  }
  ++i;
  for(;i<pc->size;++i){
    pc->pArray[i-1]=pc->pArray[i];  
  }
  pc->size--;
  
  
}

