/*  MODULE: BoxCondicional.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxCondicional.h"

#pragma DATA_SEG BOX_CONDICIONAL_DATA                                            
#pragma CODE_SEG BOX_CONDICIONAL_CODE 

void 	 BoxCondicional_DefConstructor(void*,va_list*args);
struct BlockBoxConstruct * BoxCondicional_getNext(void * _self,uchar tecla);
BOX_State BoxCondicional_ProcKey(void* _self,uchar tecla);


#pragma CONST_SEG DEFAULT 

const struct BoxClass BoxCondicional={
            BOXCLASS_INITIALIZATION(BoxClass,
                          BoxCondicional,
                          BoxPropBase,
                          BoxCondicional_DefConstructor,
                          BoxPropBase_Destructor,
                          NULL,
                          NULL,
                          BoxPropBase_Refresh,
                          BoxCondicional_ProcKey,
                          BoxCondicional_getNext)
};



/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxCondicional_DefConstructor(void * _self, va_list*args){
  struct BoxCondicional * _box= (struct BoxCondicional *)_self;
  void * block=va_arg(*args,void *);
  void * Obj =va_arg(*args,void *); 
  uchar NumObj= (uchar)va_arg(*args,int);
  
  BoxPropBase_Constructor(_self,block,Obj,NumObj);
    
}
/*
** ===================================================================
**     Method      :  BoxLineal_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * BoxCondicional_getNext(void * _self,uchar tecla){
  struct BoxCondicional* _box=(struct BoxCondicional *)_self;
  struct BoxPropBase * _box_base = (struct BoxPropBase *)_self;
  struct BlockConstBoxCondicional* block= (struct BlockConstBoxCondicional*)_box_base->pBlockSelf;

  if(block->getNextBlckConst)
    return (*(block->getNextBlckConst))(_box_base->prop,tecla);
  return NULL;
    
}

/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxCondicional_ProcKey(void* _self,uchar tecla){
  struct BoxPropBase * _box=(struct BoxPropBase *)_self;
  BOX_State state;
  struct BlockConstBoxCondicional* block= (struct BlockConstBoxCondicional*)_box->pBlockSelf;
  
  
  state=BoxPropBase_ProcKey(_self,tecla);  
  
  if(BoxCondicional_getNext(_self,tecla))
    return EXIT_BOX;
  else
    return state;
}


#pragma CODE_SEG BOX_CONDICIONAL_CODE 



