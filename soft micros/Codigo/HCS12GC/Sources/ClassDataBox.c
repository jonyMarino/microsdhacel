/*  MODULE: DataBox.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "DataBox.h"

struct BlockBoxConstruct * BoxProp_getNext(void * _self,uchar tecla);

struct T_Box TableBoxProp={
  sizeof(struct BoxProp),
  BoxPropBase_DefConstructor,
  NULL,
  BoxPropBase_Destructor,
  NULL,
  BoxPropBase_Refresh,
  BoxPropBase_ProcKey,
  BoxProp_getNext 
};

const void * BoxProp = &TableBoxProp; 



/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void DataBox_Constructor(void * _self, void * BlockConst){
  struct BoxPropBase * _box = _self;
  struct BlockConstBoxPropBase * Block =  BlockConst;
  struct PropWInc * prop =pProp_Constructor(Block->_c_prop,NULL); 
  char * desc;
  
  ObjBox_Constructor(_self,NumObj);
  
  _box->prop=prop;
  _box->pBlockSelf=Block;
  _box->save=FALSE;
 
  desc = PropVisual_getDescripcion(prop);
  PasarASCII(desc,_DPY_INF); 
  vPropVisual_Print(prop,_DPY_SUP);
    
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void DataBox_DefConstructor(void * _self, va_list*args){
  BoxPropBase_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * DataBox_Destructor(void* _self){
  struct BoxPropBase * _box = _self;
  deleteObj((struct Tclass **)_box->prop);
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void DataBox_Refresh(void* _self){
  struct BoxPropBase * _box=_self;
  struct ObjBox * _Objbox=(struct ObjBox *)_self;
   
  PropWInc_Refresh(_box->prop);
  
  vPropVisual_Print(_box->prop,_DPY_SUP);

}
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State DataBox_ProcKey(void* _self,uchar tecla){
  struct BoxPropBase * _box=_self;
  
  if ((tecla=='u') || (tecla=='d')){ // Fue presionada una Tecla UP o Down???
			  if(tecla=='u')
			    vPropWInc_Inc(_box->prop);
			  if(tecla=='d')
			    vPropWInc_Dec(_box->prop);			  
			  _box->save=TRUE;							            // Grabar parametros
			  return STAY_BOX;
  } else if (tecla=='r'){
    if(_box->save)
	    PropWInc_Save(_box->prop);	
    return EXIT_BOX;
  } else if(tecla=='f'){    
    return EXIT_BOX;
  }
  
  return STAY_BOX;  

}


