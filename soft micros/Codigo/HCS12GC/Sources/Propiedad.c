/*  MODULE: Propiedad.c*/

#include "Object.h"
#include "stddef.h"
#include "Propiedad.h"
#include "display.h"

void Prop_DefConstructor(void * self,va_list*args);

const struct GetterClass Propiedad={
  GETTER_CLASS_INITIALIZATION(GetterClass,
                              Propiedad,
                              Getter,
                              Prop_DefConstructor,
                              NULL,
                              NULL,
                              NULL,
                              Prop_getVal,
                              Prop_Print)
};


/*
** ===================================================================
**     Method      :  Prop_Constructor 
**     Description :  Constructor de la Propiedad
** ===================================================================
*/
void Prop_Constructor(void * self,struct ClassPropiedad * ClassProp,void * Obj){
  struct GetterVisual * _prop=self;
  
  _prop->_CGetter=ClassProp;
  _prop->Obj=Obj;
   
}

/*
** ===================================================================
**     Method      :  Prop_DefConstructor 
**     Description :  Constructor de la Propiedad
** ===================================================================
*/
void Prop_DefConstructor(void * self,va_list*args){
  Prop_Constructor(self,va_arg(*args,void*),va_arg(*args,void*));  
}
/*
** ===================================================================
**     Method      :  Prop_getVal 
**     Description :  Obtiene el valor de la propiedad del objeto
** ===================================================================
*/
int Prop_getVal(void * self){

  return GetterVisual_getVal(self);        
}

/*
** ===================================================================
**     Method      :  Prop_Print 
**     Description :  Imprime el valor de la propiedad del objeto
** ===================================================================
*/
void Prop_Print(void * self,uchar num_disp){

  Pasar_Numero(GetterVisual_getVal(self),num_disp,0);        
}

/*
** ===================================================================
**     Method      :  Prop_setVal 
**     Description :  Setea el valor de la propiedad del objeto
** ===================================================================
*/
TError Prop_setVal(void * self,int Val){
  struct GetterVisual * _prop=self;

  
  return ClassProp_setVal(_prop->_CGetter,_prop->Obj,Val);        
}

/*
** ===================================================================
**     Method      :  Prop_getLimInf 
**     Description :  Obtiene el valor del limite inferior
**                    de la propiedad del objeto
** ===================================================================
*/
int Prop_getLimInf(void * self){
  struct GetterVisual * _prop=self;

  
  return ClassProp_getLimInf(_prop->_CGetter,_prop->Obj);        
}

/*
** ===================================================================
**     Method      :  Prop_getLimSup 
**     Description :  Obtiene el valor del limite superior
**                    de la propiedad del objeto
** ===================================================================
*/
int Prop_getLimSup(void * self){
  struct GetterVisual * _prop=self;

  return ClassProp_getLimSup(_prop->_CGetter,_prop->Obj);      
}

/*
** ===================================================================
**     Method      :  Prop_getObj 
**     Description :  Devuelve un puntero al objeto que esta manejando
** ===================================================================
*/
void* Prop_getObj(void * self){
    struct GetterVisual * _prop=self;

    return _prop->Obj;  
}



