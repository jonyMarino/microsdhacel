/*MODULE: FunctionContainer.c*/

#include <stdlib.h>
#include <stdarg.h>
#include "FunctionContainer.h"

void FncContainer_DefConstructor(void * _self,va_list * args);
void *FncContainer_Destructor(void* _self);

const struct Class TableFncContainer={
    &Class,
  "",
  &Object,
  sizeof(struct FncContainer),
  FncContainer_DefConstructor,
  FncContainer_Destructor,
  NULL, // differ
  NULL, // puto
};

const void *const  FncContainer=&TableFncContainer;

/*
** ===================================================================
**     Method     :  FncContainer_Constructor 
**    Description : Constructor del objeto 
** ===================================================================
*/
void FncContainer_Constructor(void * _self){
  struct FncContainer * fc= _self;
  fc->size=0;
  fc->pfArray=NULL;   
}
/*
** ===================================================================
**     Method     :  FncContainer_DefConstructor 
**    Description : Constructor por defecto del objeto 
** ===================================================================
*/
void FncContainer_DefConstructor(void * _self,va_list * args){
  FncContainer_Constructor(_self);  
}
/*
** ===================================================================
**     Method     :  FncContainer_Destructor 
**    Description : Destructor del objeto 
** ===================================================================
*/
void *FncContainer_Destructor(void* _self){
  struct FncContainer * fc= _self;
  free(fc->pfArray);
  return _self;
}

/*
** ===================================================================
**     Method     :  FncContainer_Add 
**    Description : Agrega una funcion al contenedor 
** ===================================================================
*/
TError FncContainer_Add(void * _self,Pf _pf){
  struct FncContainer * fc= _self;
  void * p_tmp;
  
  ++fc->size;
  p_tmp= realloc(fc->pfArray,fc->size*sizeof(Pf));
  if(p_tmp){
    fc->pfArray= p_tmp;
    fc->pfArray[fc->size-1]= _pf;
    return ERR_OK;     
  }
  --fc->size;
  return ERR_MEM;
}

/*
** ===================================================================
**     Method     :  FncContainer_Execute 
**    Description : Ejecuta las funciones agergadas al contenedor
** ===================================================================
*/
void FncContainer_Execute(void*_self){
  struct FncContainer * fc= _self;
  uint i;
  
  for(i=0;i<fc->size;i++)
    (*(fc->pfArray[i]))();
  
}

/*
** ===================================================================
**     Method     :  FncContainer_isEmpty 
**    Description : Indica si no hay funciones en el contenedor
** ===================================================================
*/
uchar FncContainer_isEmpty(void*_self){
  struct FncContainer * fc= _self;
  return fc->size==0;
}

