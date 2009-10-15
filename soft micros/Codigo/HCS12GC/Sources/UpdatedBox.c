

/*MODULE: UpdatedBox.c*/
#include "ReadOnlyBox.h"
#include "TimerFlag.h"

struct UpdatedBox {
    struct ReadOnlyBox _base;
    struct TimerFlag timer;
};

#include "UpdatedBox.h"





#include <stdarg.h>
#include <stddef.h>

#include "display.h"

#pragma DATA_SEG UpdatedBox_DATA                                            
#pragma CODE_SEG UpdatedBox_CODE 
#pragma CONST_SEG DEFAULT


void UpdatedBox_DefConstructor(void * _self, va_list*args);

void UpdatedBox_Destructor(void* _self);
void ReadOnlyBox_Refresh(void* _self);
BOX_State ReadOnlyBox_ProcKey(void* _self,uchar tecla);


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
  struct UpdatedBox * _box = (struct UpdatedBox *)_self;
  struct BlockConstrUpdatedBox * Block = (struct BlockConstrUpdatedBox *) BlockConst;
  
  ReadOnlyBox_Constructor ( _self, BlockConst, Obj, NumObj);
  newAlloced(&_box->timer,&TimerFlag, (ulong) Block->time);
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
void UpdatedBox_Destructor(void* _self){
  struct UpdatedBox * _box = (struct UpdatedBox *)_self;
  deleteAlloced(&_box->timer);
  ReadOnlyBox_Destructor (_self);
}


/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State UpdatedBox_ProcKey(void* _self,uchar tecla){
  
  struct UpdatedBox * _box = (struct UpdatedBox *)_self;
  if(TimerFlag_getFlag(&_box->timer)){
         ReadOnlyBox_Refresh(_self);
         TimerFlag_reset(&_box->timer);
				 Timer_Restart(&_box->timer);
  }
  return ReadOnlyBox_ProcKey(_self, tecla);
 }



				