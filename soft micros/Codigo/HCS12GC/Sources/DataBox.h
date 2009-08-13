#ifndef _CLASS_DATA_BOX_H
#define _CLASS_DATA_BOX_H

#include <stdtypes.h>

#include "ClassBox.h"
#include "PropWithInc.h"

#pragma DATA_SEG DATA_BOX_DATA                                            
#pragma CODE_SEG DATA_BOX_CODE
#pragma CONST_SEG DEFAULT

struct BlockConstDataBox{
  struct BlockBoxConstruct _base;
  struct ConstructorPropWInc * _c_prop;  
  struct BlockBoxConstruct * pNextBlckConst;     
};

struct DataBox{
  struct Box _box;
//Protected:  
  struct BlockConstDataBox *pBlockSelf;
  /*struct PropWInc*/void * prop;
  uchar save;
};

extern const struct BoxClass DataBox;

/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void DataBox_Constructor(void * _self, void * BlockConst);
/*
** ===================================================================
**     Method      :  DataBox_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void DataBox_DefConstructor(void * _self, va_list*args);
/*
** ===================================================================
**     Method      :  DataBox_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void DataBox_Destructor(void* _self);
/*
** ===================================================================
**     Method      :  DataBox_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void DataBox_Refresh(void* _self);
/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State DataBox_ProcKey(void* _self,uchar tecla);

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT

#endif 