

/*MODULE: UpdatedBox.c*/


#include "UpdatedBox.h"





#include <stdarg.h>
#include <stddef.h>

#include "display.h"

#pragma DATA_SEG UpdatedBox_DATA                                            
#pragma CODE_SEG UpdatedBox_CODE 
#pragma CONST_SEG DEFAULT


void UpdatedBox_DefConstructor(void * _self, va_list*args);

void * UpdatedBox_Destructor(void* _self);
void ReadOnlyBox_Refresh(void* _self);
BOX_State ReadOnlyBox_ProcKey(void* _self,uchar tecla);
void * ReadOnlyBox_Destructor(void* _self);

BOX_State UpdatedBox_ProcKey(void* _self,uchar tecla);

 const struct BoxClass UpdatedBox={
   BOXCLASS_INITIALIZATION(BoxClass,
                          UpdatedBox,
                          ReadOnlyBox,
                          UpdatedBox_DefConstructor,
                          UpdatedBox_Destructor,
                          NULL,
                          NULL,
                          ReadOnlyBox_Refresh,
                          UpdatedBox_ProcKey,
                          NULL)
};

/*
** ===================================================================
**     Method      :  ReadOnlyBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void UpdatedBox_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj){
  struct UpdatedBox * _box = _self;
  struct BlockConstrUpdatedBox * Block =  BlockConst;
  
  ReadOnlyBox_Constructor ( _self, BlockConst, Obj, NumObj);
  newAlloced(&_box->timer,&Timer, (ulong) Block->time);
}
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void UpdatedBox_DefConstructor(void * _self, va_list*args){
  UpdatedBox_Constructor(_self,va_arg(*args,void *),va_arg(*args,void *),(uchar)va_arg(*args,int));  
}
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * UpdatedBox_Destructor(void* _self){
  struct UpdatedBox * _box = _self;
  deleteAlloced(&_box->timer);
  ReadOnlyBox_Destructor (_self);
  return _self; 
}


/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State UpdatedBox_ProcKey(void* _self,uchar tecla){
  
  struct UpdatedBox * _box = _self;
  if(Timer_isfinish(&_box->timer)){
         ReadOnlyBox_Refresh(_self);
				 Timer_Restart(&_box->timer);
  }
  return ReadOnlyBox_ProcKey(_self, tecla);
 }



				