#include "PropiedadGetter.hpp"

/*
** ===================================================================
**     Method      :  GetterVisual_Constructor 
**     Description :  Constructor del GetterVisual
** ===================================================================
*/
PropiedadGetter::PropiedadGetter(void* _obj,struct ConstructorPropiedadGetter * _constructor):obj(_obj),constructor(_constructor){}

/*
** ===================================================================
**     Method      :  GetterVisual_getObj 
**     Description :  Devuelve el objeto asociado al getter
** ===================================================================
*/
void *PropiedadGetter::getObjeto(){  
   return obj;
}

/*
** ===================================================================
**     Method      :  get
**     Description :  Obtiene el valor del getter
** ===================================================================
*/
int PropiedadGetter::get(){
   return (*(constructor->get))(obj);
}
   

/*
** ===================================================================
**     Method      :  getInstancia
**     Description :  
** ===================================================================
*/
/*PropiedadGetter& PropiedadGetter::PropiedadGetterFactory::getPropiedad(void*obj,struct ConstructorPropiedadGetter* args)const{
    PropiedadGetter p(obj,args);
    PropiedadGetter*p=new PropiedadGetter(obj,args);
    return *((PropiedadGetter*)(new PropiedadGetter(obj,args)));
} */
PropiedadGetter* PropiedadGetter::creator(void* _obj,struct ConstructorPropiedadGetter* _constructor){
  return new PropiedadGetter(_obj,_constructor);  
}  
/* 
** ===================================================================
**     Method      :  getGetter
**     Description :  
** ===================================================================
*/
/*static Getter * PropiedadGetter::getGetter(PropiedadGetter::ConstructorPropiedadGetter * self,void * obj){
  return (void*)0;
}   */
