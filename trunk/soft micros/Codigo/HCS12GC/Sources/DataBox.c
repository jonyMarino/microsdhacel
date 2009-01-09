/*  MODULE: DataBox.c*/



#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "DataBox.h"

#pragma DATA_SEG DATA_BOX_DATA                                            
#pragma CODE_SEG DATA_BOX_CODE
#pragma CONST_SEG DEFAULT

struct BlockBoxConstruct * DataBox_getNext(void * _self,uchar tecla);

const struct BoxClass DataBox={
  BOXCLASS_INITIALIZATION(BoxClass,
                          DataBox,
                          Box,
                          DataBox_DefConstructor,
                          DataBox_Destructor,
                          NULL,
                          NULL,
                          DataBox_Refresh,
                          DataBox_ProcKey,
                          DataBox_getNext) 
};



/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void DataBox_Constructor(void * _self, void * BlockConst){
  struct DataBox * _box = _self;
  struct BlockConstDataBox * Block =  BlockConst;
  struct PropWInc * prop =pProp_Constructor(Block->_c_prop,NULL); 
  char * desc;
  
  _box->prop=prop;
  _box->pBlockSelf=Block;
  _box->save=FALSE;
 
  desc = PropVisual_getDescripcion(prop);
  PasarASCII(desc,_DPY_INF); 
  _GetterPrint(prop,_DPY_SUP);
    
}
/*
** ===================================================================
**     Method      :  DataBox_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void DataBox_DefConstructor(void * _self, va_list*args){
  DataBox_Constructor(_self,va_arg(*args,void *));  
  va_arg(*args,void *);   //saco 
  va_arg(*args,void *);
}
/*
** ===================================================================
**     Method      :  DataBox_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * DataBox_Destructor(void* _self){
  struct DataBox * _box = _self;
  delete(_box->prop);
  return _self; 
}

/*
** ===================================================================
**     Method      :  DataBox_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void DataBox_Refresh(void* _self){
  struct DataBox * _box=_self;
   
  PropWInc_Refresh(_box->prop);
  
  _GetterPrint(_box->prop,_DPY_SUP);

}
/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State DataBox_ProcKey(void* _self,uchar tecla){
  struct DataBox * _box=_self;
  
  if ((tecla=='u') || (tecla=='d')){ // Fue presionada una Tecla UP o Down???
			  if(tecla=='u')
			    vPropWInc_Inc(_box->prop);
			  if(tecla=='d')
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


/*
** ===================================================================
**     Method      :  DataBox_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * DataBox_getNext(void * _self,uchar tecla){
  struct DataBox* _box=_self;
  if(tecla=='r')
    return ((struct BlockConstDataBox*)_box->pBlockSelf)->pNextBlckConst;
  else
    return NULL;
    
}


#pragma CODE_SEG DATA_BOX_CODE


