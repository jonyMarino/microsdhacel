/*  MODULE: BoxPropBase.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxPropBase.h"

#pragma DATA_SEG BOX_PROP_BASE_DATA                                            
#pragma CODE_SEG BOX_PROP_BASE_CODE 

#pragma CONST_SEG DEFAULT

 const struct BoxClass BoxPropBase={
        BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPropBase,
                          ObjBox,
                          BoxPropBase_DefConstructor,
                          BoxPropBase_Destructor,
                          NULL,
                          NULL,
                          NULL,
                          BoxPropBase_ProcKey,
                          NULL)
};

/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPropBase_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){
  struct BoxPropBase * _box = _self;
  struct BlockConstBoxPropBase * Block =  BlockConst;
  struct PropWInc * prop =pProp_Constructor(Block->_c_prop,Obj); 
  char * desc;
  
  ObjBox_Constructor(_self,NumObj);
  
  _box->prop=prop;
  _box->pBlockSelf=Block;
  _box->save=FALSE;
 
  desc = PropVisual_getDescripcion(prop);
  ObjBox_PrintDescription(_self,desc,_DPY_INF); 
  _GetterPrint(prop,_DPY_SUP);
    
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPropBase_DefConstructor(void * _self, va_list*args){
  BoxPropBase_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPropBase_Destructor(void* _self){
  struct BoxPropBase * _box = _self;
  deleteAndNil(&((struct Tclass **)_box->prop));
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void BoxPropBase_Refresh(void* _self){
  struct BoxPropBase * _box=_self;
  struct ObjBox * _Objbox=(struct ObjBox *)_self;
   
  PropWInc_Refresh(_box->prop);
  
  _GetterPrint(_box->prop,_DPY_SUP);

}
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxPropBase_ProcKey(void* _self,uchar tecla){
  struct BoxPropBase * _box=_self;
  
  if ((tecla=='u') || (tecla=='d')){ // Fue presionada una Tecla UP o Down???
			  if(tecla=='u')
			    vPropWInc_Inc(_box->prop);
			  else if(tecla=='d')
			    vPropWInc_Dec(_box->prop);			  
			  _box->save=TRUE;							            // Grabar parametros
			  _GetterPrint(_box->prop,_DPY_SUP);
			  return STAY_BOX;
  } else if (tecla=='r'){
    if(_box->save)
	    PropWInc_Save(_box->prop);	
    return EXIT_BOX;
  }
  
  return STAY_BOX;  

}

#pragma CODE_SEG BOX_PROP_BASE_CODE 


