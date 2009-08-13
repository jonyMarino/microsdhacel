 /* MODULE: GetterGenerico.c*/
 
#include "GetterGenerico.h"
 
const struct Class GetterGenericoClass={
  CLASS_INITIALIZATION(Class,GetterGenericoClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)    
};

const struct GetterGenericoClass GetterGenerico={
  GETTER_GENERICO_CLASS_INITIALIZATION(GetterGenericoClass,
                                       GetterGenerico,
                                       Object,
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL,
                                       Getter_getVal)
}; 

/*
** ===================================================================
**     Method      :  Prop_getVal 
**     Description :  Obtiene el valor de la propiedad del objeto
** ===================================================================
*/
int Getter_getVal(void * self,void * Obj){
  const struct GetterGenerico * _g= (const struct GetterGenerico *)self;
  return (*(_g->_get))(Obj);
}