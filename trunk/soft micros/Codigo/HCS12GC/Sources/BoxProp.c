/*  MODULE: BoxProp.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxProp.h"


struct BlockBoxConstruct * BoxProp_getNext(void * _self,uchar tecla);

const struct BoxClass BoxProp={
          BOXCLASS_INITIALIZATION(BoxClass,
                          BoxProp,
                          BoxPropBase,
                          BoxPropBase_DefConstructor,
                          BoxPropBase_Destructor,
                          NULL,
                          NULL,
                          BoxPropBase_Refresh,
                          BoxPropBase_ProcKey,
                          BoxProp_getNext)
};


/*
** ===================================================================
**     Method      :  BoxLineal_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * BoxProp_getNext(void * _self,uchar tecla){
  struct BoxPropBase* _box= ( struct BoxPropBase*)_self;
  if(tecla=='r')
    return ((struct BlockConstBoxProp*)_box->pBlockSelf)->pNextBlckConst;
  else
    return NULL;
    
}



