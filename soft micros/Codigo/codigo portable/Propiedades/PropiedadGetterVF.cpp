#include <stdio.h>
#include "PropiedadGetterVF.hpp"

/*
** ===================================================================
**     Method      :  GetterVisual_Constructor 
**     Description :  Constructor del GetterVisual
** ===================================================================
*/
PropiedadGetterVF::PropiedadGetterVF(void* _obj,int _Vtmp,const struct ArgumentosPropiedadGetterVF* arg):obj(_obj),Vtmp(_Vtmp),pget(arg){}

/*
** ===================================================================
**     Method      :  GetterVisual_getObj 
**     Description :  Devuelve el objeto asociado al getter
** ===================================================================
*/
void *PropiedadGetterVF::getObjeto(){  
   return obj;
}

int PropiedadGetterVF::getNumero(){  
   return Vtmp;
}


/*
** ===================================================================
**     Method      :  get
**     Description :  Obtiene el valor del getter
** ===================================================================
*/
int PropiedadGetterVF::getVal(){
   return (*(pget->get))(obj,Vtmp);
}

/*
** ===================================================================
**     Method      :  print 
**     Description :  Forma en que imprime 
** ===================================================================
*/
void PropiedadGetterVF::print(OutputStream& os){
  os.write(getVal());
}
   

 
/* 
** ===================================================================
**     Method      :  getArgumentos
**     Description :  
** ===================================================================
*/
const struct ArgumentosPropiedadGetterVF* PropiedadGetterVF::getArgumentos(){
  return pget;
}
