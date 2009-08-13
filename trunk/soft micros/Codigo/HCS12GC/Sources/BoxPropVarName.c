/*MODULE: BoxPropVarName*/
/*
**     Filename  : BoxPropVarName.c
**     Project   : Controlador
**     Processor : MC9S12GC32CFU
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 29/01/2008, 13:39
**     Abstract  :
**							El nombre es variable
*/

#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxPropVarName.h"

char * BoxPropVarName_getDescription(void * _self);
void BoxPropVarName_DefConstructor(void * _self, va_list*args);
BOX_State BoxPropVarName_ProcKey(void* _self,uchar tecla);

const struct BoxClass BoxPropVarName={
             BOXCLASS_INITIALIZATION(BoxClass,
                          BoxPropVarName,
                          BoxPropBase,
                          BoxPropVarName_DefConstructor,
                          BoxPropBase_Destructor,
                          NULL,
                          NULL,
                          BoxPropBase_Refresh,
                          BoxPropVarName_ProcKey,
                          BoxProp_getNext)      
};

/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPropVarName_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){
  struct BoxPropBase * _box = (struct BoxPropBase *)_self;
  char * desc;
  
  BoxPropBase_Constructor(_self,BlockConst,Obj,NumObj); 
  desc= BoxPropVarName_getDescription(_self); 
  ObjBox_PrintDescription(_self,desc,_DPY_INF);   
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPropVarName_DefConstructor(void * _self, va_list*args){
  BoxPropVarName_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
BOX_State BoxPropVarName_ProcKey(void* _self,uchar tecla){
  BOX_State state= BoxPropBase_ProcKey(_self,tecla);
  
  char *desc;
  
  if(tecla=='u' || tecla=='d'){
    desc= BoxPropVarName_getDescription(_self); 
    ObjBox_PrintDescription(_self,desc,_DPY_INF);    
  }
  return state;
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
char * BoxPropVarName_getDescription(void * _self){
  struct BoxPropBase * _box = (struct BoxPropBase *)_self;
  
  return (*((struct BlockConstBoxPropVarName *)_box->pBlockSelf)->getName)(_box->prop);
}







