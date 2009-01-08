/*
**     Filename  : BoxGetCond.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 29/01/2008, 15:43
**     Abstract  :
**							Este Box decide si aparecer cuando se lo llama
**      mediante un puntero a funcion (ej: La Potencia actual
**      no aparece en modo manual) 
*/
#ifndef _BOX_GET_COND_H
#define _BOX_GET_COND_H

#include "stddef.h"
#include "PE_Types.h"
#include "ReadOnlyBox.h"



struct BlockConstrBoxGetCond{
  struct BlockConstrReadOnlyBox _base;
  uchar (*Appear)(void*); 				 //recibe el Objeto de la propiedad
};

struct BoxGetCond{
  struct ReadOnlyBox _base;
  bool Appear;
};

extern const struct BoxClass BoxGetCond;


#endif
