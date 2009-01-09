/*
**     Filename  : BoxPropCond.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 29/01/2008, 11:43
**     Abstract  :
**							Este Box decide si aparecer cuando se lo llama
**      mediante un puntero a funcion (ej: El SP no aparece en  
**      modo manual) 
*/
#ifndef _BOX_PROP_COND_H
#define _BOX_PROP_COND_H

#include "stddef.h"
#include "PE_Types.h"
#include "BoxProp.h"



struct BlockConstBoxPropCond{
  struct BlockConstBoxProp _base;
  uchar (*Appear)(void*); 				 //recibe el Objeto de la propiedad
};

struct BoxPropCond{
  struct BoxPropBase _base;
  bool Appear;
};

extern  const struct BoxClass BoxPropCond; 


#endif
