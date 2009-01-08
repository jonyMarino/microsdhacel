#ifndef BOX_PROP_BASE_H
#define BOX_PROP_BASE_H

#include "ClassObjBox.h"

#include "PropWithInc.h"

#pragma DATA_SEG BOX_PROP_BASE_DATA                                            
#pragma CODE_SEG BOX_PROP_BASE_CODE 

#pragma CONST_SEG DEFAULT

struct BlockConstBoxPropBase{
  struct BlockBoxConstruct _base;
  struct ConstructorPropWInc * _c_prop;    
};

struct BoxPropBase{
  struct ObjBox _base;
//Protected:  
  struct BlockConstBoxPropBase *pBlockSelf;
  struct PropWInc * prop;
  uchar save; 
};

extern  const struct BoxClass BoxPropBase;

/*
** ===================================================================
**     Method      :  BoxPropBase_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPropBase_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj);
/*
** ===================================================================
**     Method      :  BoxPropBase_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPropBase_DefConstructor(void * _self, va_list*args);
/*
** ===================================================================
**     Method      :  BoxPropBase_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPropBase_Destructor(void* _self);
/*
** ===================================================================
**     Method      :  BoxPropBase_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void BoxPropBase_Refresh(void* _self);
/*
** ===================================================================
**     Method      :  BoxPropBase_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxPropBase_ProcKey(void* _self,uchar tecla);

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif 