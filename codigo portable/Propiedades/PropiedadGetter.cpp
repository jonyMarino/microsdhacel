#include <stdio.h>
#include "PropiedadGetter.hpp"

/*
** ===================================================================
**     Method      :  GetterVisual_Constructor 
**     Description :  Constructor del GetterVisual
** ===================================================================
*/
PropiedadGetter::PropiedadGetter(void* _obj,const struct ArgumentosPropiedadGetter* arg):obj(_obj),pget(arg){}

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
int PropiedadGetter::getVal(){
   return (*(pget->get))(obj);
}

/*
** ===================================================================
**     Method      :  print 
**     Description :  Forma en que imprime 
** ===================================================================
*/
void PropiedadGetter::print(OutputStream& os){
  os.write(getVal());
}
   

 
/* 
** ===================================================================
**     Method      :  getArgumentos
**     Description :  
** ===================================================================
*/
const struct ArgumentosPropiedadGetter* PropiedadGetter::getArgumentos(){
  return pget;
}

