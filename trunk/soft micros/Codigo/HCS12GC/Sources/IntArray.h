#ifndef _INT_ARRAY_H
#define _INT_ARRAY_H

#include "Class.h"

struct IntArray{
  void * IntArray;
  int * values;
  int max;  
};

extern const void *const IntArray;

/*
** ===================================================================
**     Method      :  IntArray_Add 
**    Description : Agerga un nuevo valor en el Array en la posicion 0
**    y moviendo todos los elemento una casilla mas. El elemento en la
**    posicion max se elimina.
** ===================================================================
*/
void IntArray_Add(void *, int);

/*
** ===================================================================
**     Method      :  IntArray_AsArray 
**    Description : Devuelve el array con los valores
** ===================================================================
*/
int * IntArray_AsArray(void *); 


#endif