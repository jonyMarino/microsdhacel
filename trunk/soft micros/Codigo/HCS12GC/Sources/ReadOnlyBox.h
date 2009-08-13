#ifndef _READ_ONLY_BOX_H
#define _READ_ONLY_BOX_H

#include <stdtypes.h>

#include "ClassObjBox.h"
#include "GettersVisual.h"

struct BlockConstrReadOnlyBox{
  struct BlockBoxConstruct _base;
  struct ConstrGetVisual * _c_g;     
};

struct ReadOnlyBox{
  struct ObjBox _box;
  /*struct GetterVisual*/void * _getter;
};

extern const struct BoxClass ReadOnlyBox;

/*
** ===================================================================
**     Method      :  ReadOnlyBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void ReadOnlyBox_Constructor(void * _self, void * BlockConst,void* Obj,uchar NumObj);
/*
** ===================================================================
**     Method      :  ReadOnlyBox_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void ReadOnlyBox_DefConstructor(void * _self, va_list*args);
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void ReadOnlyBox_Destructor(void* _self);
/*
** ===================================================================
**     Method      :  ReadOnlyBox_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void ReadOnlyBox_Refresh(void* _self);
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State ReadOnlyBox_ProcKey(void* _self,uchar tecla);



#endif