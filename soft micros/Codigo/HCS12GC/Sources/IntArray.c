//  MODULE: IntArray.c

#include <stdlib.h>
#include "stddef.h"
#include "IntArray.h"

void IntArray_DefConstructor(void *, va_list *);
void *IntArray_Destructor(void *);

const struct Tclass IntArrayTable={
  sizeof(struct IntArray),
  IntArray_DefConstructor,
  NULL,
  IntArray_Destructor,
};

const void *const IntArray = &IntArrayTable; 

/*
** ===================================================================
**     Method      :  IntArray_Constructor 
**    Description : Constructor
** ===================================================================
*/
void IntArray_Constructor(void * self, int max){
  struct IntArray *_a =self;
  
  _a->max=max;
  _a->values=malloc(sizeof(int)*max);  
}

/*
** ===================================================================
**     Method      :  IntArray_DefConstructor 
**    Description  :  Constructor por defecto   
** ===================================================================
*/
void IntArray_DefConstructor(void * self, va_list * arg){
  IntArray_Constructor(self, va_arg(*arg,int));  
}


/*
** ===================================================================
**     Method      :  IntArray_Destructor 
**    Description  :  Destructor
** ===================================================================
*/
void *IntArray_Destructor(void * self){
  struct IntArray* _a =self;
  
  free(_a->values);
  return self;
}

/*
** ===================================================================
**     Method      :  IntArray_Add 
**    Description : Agerga un nuevo valor en el Array en la posicion 0
**    y moviendo todos los elemento una casilla mas. El elemento en la
**    posicion max se elimina.
** ===================================================================
*/
void IntArray_Add(void * self, int val){
  struct IntArray *_a =self;
  int i;
  for(i=_a->max-1;i>0;i--)
    _a->values[i]=_a->values[i-1];
  _a->values[0]=val;
    
}

/*
** ===================================================================
**     Method      :  IntArray_AsArray 
**    Description : Devuelve el array con los valores
** ===================================================================
*/
int * IntArray_AsArray(void * self){
  struct IntArray* _a =self;
  
  return _a->values;
}


