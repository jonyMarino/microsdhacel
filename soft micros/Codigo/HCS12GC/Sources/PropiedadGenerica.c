/*  MODULE: ClassClassPropiedad.c*/

#include "Object.h"
#include "stddef.h"
#include "PropiedadGenerica.h"
#include "display.h"

const struct Class PropiedadGenericaClass={
  CLASS_INITIALIZATION(Class,PropiedadGenericaClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)    
};

const struct PropiedadGenericaClass PropiedadGenerica={
  PROPIEDAD_GENERICA_CLASS_INITIALIZATION(PropiedadGenericaClass,
                                          PropiedadGenerica,
                                          GetterGenerico,
                                          NULL,
                                          NULL,
                                          NULL,
                                          NULL,
                                          Getter_getVal,
                                          ClassProp_setVal,
                                          ClassProp_getLimInf,
                                          ClassProp_getLimSup)

};
/*
** ===================================================================
**     Method      :  Prop_getVal 
**     Description :  Obtiene el valor de la ClassPropiedad del objeto
** ===================================================================
*/
int ClassProp_getVal(void * self,void * Obj){
  return Getter_getVal(self,Obj);        
}


/*
** ===================================================================
**     Method      :  Prop_setVal 
**     Description :  Setea el valor de la ClassPropiedad del objeto
** ===================================================================
*/
TError ClassProp_setVal(void * self,void * Obj,int Val){
  struct PropiedadGenerica * _prop= (struct PropiedadGenerica *)self;
  if(_prop->_set)
    return (*(_prop->_set))(Obj,Val);
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Prop_getLimInf 
**     Description :  Obtiene el valor del limite inferior
**                    de la ClassPropiedad del objeto
** ===================================================================
*/
int ClassProp_getLimInf(void * self,void * Obj){
  struct PropiedadGenerica * _prop=(struct PropiedadGenerica *)self;
  if(_prop->_LimInf)
    return (*(_prop->_LimInf))(Obj);
  else
    return MIN_NUM_DISPLAY;
}

/*
** ===================================================================
**     Method      :  Prop_getLimSup 
**     Description :  Obtiene el valor del limite superior
**                    de la ClassPropiedad del objeto
** ===================================================================
*/
int ClassProp_getLimSup(void * self,void * Obj){
  struct PropiedadGenerica * _prop=(struct PropiedadGenerica *)self;
  if(_prop->_LimSup) 
    return (*(_prop->_LimSup))(Obj); 
  else
    return MAX_NUM_DISPLAY;    
}

/*
** ===================================================================
**     Function      :  get_0 
**     Description :  Funcion de utileria. Devvuelve un cero
** ===================================================================
*/
int get_0(void * a){return 0;}


