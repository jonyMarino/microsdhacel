#ifndef _CLASS_PROPIEDAD_H
#define _CLASS_PROPIEDAD_H

#include "Errores.h"
#include "GetterGenerico.h"
/* Generalmente la propiedad se usara de forma const por lo tanto
  se debe asignar al primer puntero el descriptor de propiedad(Propiedad)
*/

struct PropiedadGenerica{
  //Public:
  struct GetterGenerico super;
  TError (*_set)(void*,int);
  int (*_LimInf)(void*);
  int (*_LimSup)(void*);
};

struct PropiedadGenericaClass{
  struct GetterGenericoClass super;
  TError (*_set)(void*,int);
  int (*_LimInf)(void*);
  int (*_LimSup)(void*);
};

extern const struct Class PropiedadGenericaClass;
extern const struct PropiedadGenericaClass PropiedadGenerica;

/*
** ===================================================================
**     Method      :  Prop_getVal 
**     Description :  Obtiene el valor de la propiedad del objeto
** ===================================================================
*/
int ClassProp_getVal(void * self,void * Obj);
/*
** ===================================================================
**     Method      :  Prop_setVal 
**     Description :  Setea el valor de la propiedad del objeto
** ===================================================================
*/
TError ClassProp_setVal(void * self,void * Obj,int Val);

/*
** ===================================================================
**     Method      :  Prop_getLimInf 
**     Description :  Obtiene el valor del limite inferior
**                    de la propiedad del objeto
** ===================================================================
*/
int ClassProp_getLimInf(void * self,void * Obj);

/*
** ===================================================================
**     Method      :  Prop_getLimSup 
**     Description :  Obtiene el valor del limite superior
**                    de la propiedad del objeto
** ===================================================================
*/
int ClassProp_getLimSup(void * self,void * Obj);
/*
** ===================================================================
**     Function      :  get_0 
**     Description :  Funcion de utileria. Devvuelve un cero
** ===================================================================
*/
int get_0(void * a);

#define PROPIEDAD_GENERICA_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getObjPropVal,setObjPropVal,limInf,limSup)\
   GETTER_GENERICO_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getObjPropVal),\
   setObjPropVal, \
   limInf,        \
   limSup
   
#endif 