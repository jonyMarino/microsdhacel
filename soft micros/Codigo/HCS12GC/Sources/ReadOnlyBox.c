/*MODULE: ReadOnlyBox.c*/




#include <stdarg.h>
#include <stddef.h>

#include "display.h"
#include "ReadOnlyBox.h"

void * ReadOnlyBox_Destructor(void* _self);
void ReadOnlyBox_Refresh(void* _self);
BOX_State ReadOnlyBox_ProcKey(void* _self,uchar tecla);


 const struct BoxClass ReadOnlyBox={
  BOXCLASS_INITIALIZATION(BoxClass,
                          ReadOnlyBox,
                          Box,
                          ReadOnlyBox_DefConstructor,
                          ReadOnlyBox_Destructor,
                          NULL,
                          NULL,
                          ReadOnlyBox_Refresh,
                          ReadOnlyBox_ProcKey,
                          NULL)
};

/*
** ===================================================================
**     Method      :  ReadOnlyBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void ReadOnlyBox_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){
  struct ReadOnlyBox * _box = _self;
  struct BlockConstrReadOnlyBox * Block =  BlockConst;
  struct GetterVisual * _g =pGetter_Constructor(Block->_c_g,Obj); 
  char * desc;
  
  ObjBox_Constructor(_self,NumObj);
  
  _box->_getter=_g;
 
  desc = GetterVisual_getDescripcion(_g);
  ObjBox_PrintDescription(_self,desc,_DPY_INF); 
  _GetterPrint(_g,_DPY_SUP);
    
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void ReadOnlyBox_DefConstructor(void * _self, va_list*args){
  ReadOnlyBox_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * ReadOnlyBox_Destructor(void* _self){
  struct ReadOnlyBox * _box = _self;
  delete(_box->_getter);
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxPropBase_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void ReadOnlyBox_Refresh(void* _self){
  struct ReadOnlyBox * _box=_self;
  
  _GetterPrint(_box->_getter,_DPY_SUP);

}
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State ReadOnlyBox_ProcKey(void* _self,uchar tecla){
  
  if (tecla=='r')
    return EXIT_BOX;  
  return STAY_BOX;  

}


