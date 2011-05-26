/* MODULE: PropVisual.c*/

#include "stddef.h"
#include "display.h"
#include "PropVisual.h"

void PropVisual_DefConstructor(void* _self,va_list* args);
void PropVisual_Print(void* self,uchar num_display);

const struct GetterWNameClass PropVisual={
  GETTER_W_NAME_CLASS_INITIALIZATION(GetterWNameClass,
                                     PropVisual,
                                     Propiedad,
                                     PropVisual_DefConstructor,
                                     NULL,
                                     NULL,
                                     NULL,
                                     Prop_getVal,
                                     PropVisual_Print,
                                     PropVisual_getDescripcion)
};


/*
** ===================================================================
**     Function      :  pProp_Constructor
**     Type        :  Polimorfica 
**     Description :  Constructor general de propiedad mediante 
**                    una propiedad de clase
** ===================================================================
*/
void * pProp_Constructor(void * ClassProp,void * Obj){
  struct ClassPropVisual * p=(struct ClassPropVisual *)ClassProp;
  return _new((struct Class*)(p->classOf),ClassProp,Obj);
  
}
/*
** ===================================================================
**     Method      :  PropVisual_DefConstructor 
**     Description :  Constryctor por defecto de la PropVisual
** ===================================================================
*/
void PropVisual_DefConstructor(void* _self,va_list* args){
  Prop_Constructor(_self,va_arg(*args,void*),va_arg(*args,void*));    
}

/*
** ===================================================================
**     Method      :  PropVisual_getDescripcion 
**     Description :  Obtiene un string con la descripción de la
**                   propiedad
** ===================================================================
*/

char * PropVisual_getDescripcion(void * self){
  struct GetterVisual * prop=(struct GetterVisual *)self;
  return ((struct ClassPropVisual*)(prop->_CGetter))->descripcion;  
}
/*
** ===================================================================
**     Method      :  PropVisual_Print 
**     Description :  Forma en que imprime 
** ===================================================================
*/
void PropVisual_Print(void* self,uchar num_display){
  struct Propiedad * prop=(struct Propiedad *)self;
  int val;
  
  val= Prop_getVal(prop);
  Pasar_Numero(val,num_display,0); 
}