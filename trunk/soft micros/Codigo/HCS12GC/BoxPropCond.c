/*MODULE BoxPropCond*/
/*
**     Filename  : BoxPropCond.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 29/01/2008, 11:43
**     Abstract  :
**							Este Box decide si aparecer cuando se lo llama
**      mediante un puntero a funcion (ej: El SP no aparece en  
**      modo manual) 
*/

#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxPropBase.h"

#include "BoxPropCond.h"
#include "BoxPropCond_Protected.h"

 const struct BoxClass BoxPropCond={
              BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPropCond,
                          BoxPropBase,
                          BoxPropCond_DefConstructor,
                          BoxPropCond_Destructor,
                          NULL,
                          NULL,
                          BoxPropCond_Refresh,
                          BoxPropCond_ProcKey,
                          BoxPropCond_getNext)   
};

/*
** ===================================================================
**     Method      :  BoxPropCond_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPropCond_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){
  struct  BoxPropCond *_box=_self;
  struct  BoxPropBase *_box_base=_self;  
  struct BlockConstBoxPropCond * Block =  BlockConst;
  
  if( (*(Block->Appear))(Obj)  ){
    BoxPropBase_Constructor(_self,BlockConst,Obj,NumObj);  
    _box->Appear=TRUE;
  }else{
      _box->Appear=FALSE;
      _box_base->pBlockSelf=Block;
      _box_base->prop=NULL;
  }
    
}
/*
** ===================================================================
**     Method      :  BoxPropCond_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPropCond_DefConstructor(void * _self, va_list*args){
  BoxPropCond_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropCond_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPropCond_Destructor(void* _self){
  struct  BoxPropCond *_box=_self;

  if(_box->Appear)
    return BoxPropBase_Destructor(_self);
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxPropCond_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void BoxPropCond_Refresh(void* _self){
  struct  BoxPropCond *_box=_self;   
  if(_box->Appear)
    BoxPropBase_Refresh(_self);

}
/*
** ===================================================================
**     Method      :  BoxPropCond_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxPropCond_ProcKey(void* _self,uchar tecla){
  struct  BoxPropCond *_box=_self;
  
  if(!_box->Appear)
    return EXIT_BOX;
  else
    return BoxPropBase_ProcKey(_self,tecla);  
}

/*
** ===================================================================
**     Method      :  BoxPropCond_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * BoxPropCond_getNext(void * _self,uchar tecla){
  struct BoxPropBase* _box=_self;
  
  if(tecla==0)
    return ((struct BlockConstBoxProp*)_box->pBlockSelf)->pNextBlckConst;
  else
    return BoxProp_getNext(_self,tecla);
    
}



