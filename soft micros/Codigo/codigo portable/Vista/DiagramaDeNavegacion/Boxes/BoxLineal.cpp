//#include <typeinfo>
#include <stddef.h>
#include "PE/include/PE_Types.h"
#include "BoxLineal.hpp"
#include "obtenciondisplay.hpp"


/*
** ===================================================================
**     Method      :  BoxLineal_Constructor 
**     Description :  Constructor del Box Lineal
** ===================================================================
*/
BoxLineal::BoxLineal(struct ConstructorBoxLineal * _constructor,void*obj,uchar numObjeto):Box(numObjeto){
  constructor =  _constructor;
  numProp=0;
  mostrarPropiedad(obj); 
  
}

/*
** ===================================================================
**     Method      :  BoxLineal_Destructor 
**     Description :  Destructor del Box Lineal
** ===================================================================
*/
BoxLineal::~BoxLineal(){

  delete propiedadActual;
}

/*
** ===================================================================
**     Method      :  BoxLineal_setBox 
**     Description :  Setea los valores de la Propiedad correspondiente
** ===================================================================
*/

void BoxLineal::mostrarPropiedad(void * obj){

 /* PropiedadIncrementable&*/ propiedadActual = (PropiedadIncrementable*)&(constructor->propiedades[numProp])->getPropiedad(obj); 
  const char * desc;
   
  //propiedadActual=&propTmp; 
  //typeof(propiedadActual);
  //PropiedadIncrementable * prop = dynamic_cast< propiedadActual >;
  save=FALSE;
   
  desc = propiedadActual->getDescripcion();
  propiedadActual->print(getDisplay(0));
  printDescripcion(desc,getDisplay(1)); 
  
}

/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Refresca los valores del Box Lineal
** ===================================================================
*/
void BoxLineal::refresh(){  
  //PropWInc_Refresh(_box->prop_actual);  
  propiedadActual->print(getDisplay(0));
}
/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxLineal::procesarTecla(uchar tecla,TEstadoBox& estado){

  
  if ((tecla=='u') || (tecla=='d')){ // Fue presionada una Tecla UP o Down???
			  if(tecla=='u')
			    propiedadActual->incrementar();
			  if(tecla=='d')
			    propiedadActual->decrementar();			  
			  save=TRUE;							            // Grabar parametros
			  propiedadActual->print(getDisplay(0));
			  estado = STAY_BOX;
			  return NULL;
  } else if (tecla=='r'){
    if(save)
	    propiedadActual->guardar();
    void * obj = propiedadActual->getObjeto(); 
    delete(propiedadActual);
    numProp++;  //siguiente propiedad
    if(constructor->propiedades[numProp]==NULL){    
      estado = EXIT_BOX;
      if(!constructor)
        return NULL;
      return constructor->proximoBox->getBox(obj,getNumObjeto());
    }
    mostrarPropiedad(obj); 
    
  } 
  
  estado = STAY_BOX;  
  return NULL;
}

