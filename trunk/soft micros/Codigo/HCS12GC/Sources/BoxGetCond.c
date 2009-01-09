/*MODULE: ReadOnlyBox.c*/




#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "BoxGetCond.h"

void BoxGetCond_DefConstructor(void * _self, va_list*args);
void * BoxGetCond_Destructor(void* _self);
void BoxGetCond_Refresh(void* _self);
BOX_State BoxGetCond_ProcKey(void* _self,uchar tecla);


const struct BoxClass BoxGetCond={
    BOXCLASS_INITIALIZATION(BoxClass,
                          BoxGetCond,
                          ReadOnlyBox,
                          BoxGetCond_DefConstructor,
                          BoxGetCond_Destructor,
                          NULL,
                          NULL,
                          BoxGetCond_Refresh,
                          BoxGetCond_ProcKey,
                          NULL)
};

/*
** ===================================================================
**     Method      :  ReadOnlyBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxGetCond_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){

  struct BoxGetCond *_box=_self; 
  struct BlockConstrBoxGetCond * Block =  BlockConst;
  
  if( (*(Block->Appear))(Obj)  ){
    ReadOnlyBox_Constructor(_self,BlockConst,Obj,NumObj);  
    _box->Appear=TRUE;
  }else{
      _box->Appear=FALSE;
  }
    
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxGetCond_DefConstructor(void * _self, va_list*args){
  BoxGetCond_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxGetCond_Destructor(void* _self){
  struct BoxGetCond * _box = _self;
  if(_box->Appear)
    ReadOnlyBox_Destructor(_self);
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void BoxGetCond_Refresh(void* _self){
  struct BoxGetCond * _box = _self;
  if(!_box->Appear)
    ReadOnlyBox_Refresh(_box);
}
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxGetCond_ProcKey(void* _self,uchar tecla){
  struct BoxGetCond * _box = _self;
    
  if (!_box->Appear)
    return EXIT_BOX;  
  else
    return ReadOnlyBox_ProcKey(_self,tecla);  

}


