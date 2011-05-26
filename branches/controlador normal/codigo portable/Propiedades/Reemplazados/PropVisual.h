#ifndef _PROP_VISUAL_H
#define _PROP_VISUAL_H

#include "Object.h"
#include "stdtypes.h"
#include "Propiedad.h"

struct ClassPropVisual{
  struct PropiedadGenerica _prop_base;
  const void * classOf;              //Descriptor de la clase Visual
  char * descripcion;
};

struct PropVisual{
  struct Propiedad _prop_base;
};

extern const struct GetterWNameClass PropVisual;
/*
** ===================================================================
**     Function      :  pProp_Constructor
**     Type        :  Polimorfica 
**     Description :  Constructor general de propiedad mediante 
**                    una propiedad de clase
** ===================================================================
*/
void * pProp_Constructor(void * ClassProp,void * Obj);
/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/
char * PropVisual_getDescripcion(void * self);


#endif