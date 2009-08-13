/*  MODULE: ClassBox.c*/

#include "stddef.h"
#include "ClassBox.h"

const struct Class BoxClass={
  CLASS_INITIALIZATION(Class,BoxClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};
const struct BoxClass Box={
  CLASS_INITIALIZATION(BoxClass,Box,Object,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};  

/*
** ========================================================================
**     Function     :  vBoxes_Construct 
**     Type         :  Polimorfica
**     Description  :  Constructor de Boxes recibiendo un Bloque Constructor
**     Arguments    :
**      * pBlockConst   - puntero a Bloque constructor con la info que necesita el Box
**      * Obj           - puntero al Objeto que debe manejar el Box
**      NumObj          -Numero del Objeto
** ========================================================================
*/
void * vBoxes_Construct(void * pBlockConst,void * Obj,uchar numObj){
  struct BlockBoxConstruct * p=(struct BlockBoxConstruct *)pBlockConst;
  return _new( (struct Class *)(p->_box) ,pBlockConst,Obj,numObj);
}
/*
** ===================================================================
**     Method      :  vBox_Refresh 
**     Type         : Virtual
**     Description :  Funcion Para refrescar los valores del Box
** ===================================================================
*/
void vBox_Refresh(void * _self){
  struct BoxClass **p=(struct BoxClass **)_self;
  if((*p)->Refresh)
    (*((*p)->Refresh))(_self);
}

/*
** ===================================================================
**     Method      :  vBox_ProcKey 
**     Type        :  Virtual
**     Description :  Funcion que procesa la tecla del Box
**     Returns:     - STAY_BOX Sigue el mismo Box (si la tecla es de salida
**                    devuelve NULL ya que no tiene información del siguiente Box)
**                  - EXIT_BOX si el Box esta en condición de salida.
**                  
** ===================================================================
*/
BOX_State vBox_ProcKey(void * _self,uchar tecla){
  struct BoxClass **p=(struct BoxClass **)_self;
  if((*p)->ProcKey)
    return (*((*p)->ProcKey))(_self,tecla);
  return STAY_BOX;
}


/*
** ===================================================================
**     Method      :  vBox_getNextBlockConstr 
**     Type        :  Virtual
**     Description :  Funcion que devuelve el Bloque Constructor del siguiente Box
**     
**     Returns:     - NULL  (si 
**                    devuelve NULL es porque no tiene información del siguiente Box)
**                  - Puntero a Bloque Constructor del siguiente Box si ocurrio una salida.
**                  
** ===================================================================
*/
struct BlockBoxConstruct * vBox_getNextBlockConstr(void * _self,uchar tecla){
  struct BoxClass **p=(struct BoxClass **)_self;
  if((*p)->get_NextBlockConstr)
    return (*((*p)->get_NextBlockConstr))(_self,tecla);
  return NULL;
}

