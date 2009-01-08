#ifndef _PROPIEDAD_H
#define _PROPIEDAD_H

#include "PropiedadGenerica.h"
#include "GettersVisual.h"
#include "Errores.h"
/*
  Esta Propiedad, a diferencia de ClassPropiedad es la propiedad de
  un objeto específico y no de la Clase en general.
*/

struct Propiedad{
  struct GetterVisual _base;    
};

extern const struct GetterClass Propiedad;
/*
** ===================================================================
**     Method      :  Prop_Constructor 
**     Description :  Constructor de la Propiedad
** ===================================================================
*/
void Prop_Constructor(void * self,struct ClassPropiedad * ClassProp,void * Obj);
/*
** ===================================================================
**     Method      :  Prop_getVal 
**     Description :  Obtiene el valor de la propiedad del objeto
** ===================================================================
*/
int Prop_getVal(void * self);
/*
** ===================================================================
**     Method      :  Prop_Print 
**     Description :  Imprime el valor de la propiedad del objeto
** ===================================================================
*/
void Prop_Print(void * self,uchar num_disp);
/*
** ===================================================================
**     Method      :  Prop_setVal 
**     Description :  Setea el valor de la propiedad del objeto
** ===================================================================
*/
TError Prop_setVal(void * self,int Val);

/*
** ===================================================================
**     Method      :  Prop_getLimInf 
**     Description :  Obtiene el valor del limite inferior
**                    de la propiedad del objeto
** ===================================================================
*/
int Prop_getLimInf(void * self);

/*
** ===================================================================
**     Method      :  Prop_getLimSup 
**     Description :  Obtiene el valor del limite superior
**                    de la propiedad del objeto
** ===================================================================
*/
int Prop_getLimSup(void * self);

/*
** ===================================================================
**     Method      :  Prop_getObj 
**     Description :  Devuelve un puntero al objeto que esta manejando
** ===================================================================
*/
void* Prop_getObj(void * self);


#endif 