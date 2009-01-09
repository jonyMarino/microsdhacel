/*
**     Filename  : BoxPropVarName.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 29/01/2008, 13:39
**     Abstract  :
**							El nombre es variable
*/
#ifndef _BOX_PROP_VAR_NAME_H
#define _BOX_PROP_VAR_NAME_H

#include "stddef.h"
#include "BoxProp.h"



struct BlockConstBoxPropVarName{
  struct BlockConstBoxProp _base;
  char * (*getName)(void*); 				 //recibe la propiedad
};

struct BoxPropVarName{
  struct BoxPropBase _base;
};

extern const struct BoxClass BoxPropVarName; 


#endif
