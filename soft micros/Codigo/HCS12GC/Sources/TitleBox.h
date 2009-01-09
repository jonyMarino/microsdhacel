#ifndef _TITLE_BOX_H
#define _TITLE_BOX_H

/*  CLASE PURA  */
#include <stdtypes.h>

#include "ClassBox.h"
#include "PropWithInc.h"

struct TitleBox{
  struct Box _box;
};

extern const struct BoxClass TitleBox;

#pragma CODE_SEG TIT_BOX
/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void TitleBox_Constructor(void * _self, char*str1,char*str2);
/*
** ===================================================================
**     Method      :  DataBox_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void TitleBox_DefConstructor(void * _self, va_list*args);
/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State TitleBox_ProcKey(void* _self,uchar tecla);

#pragma CODE_SEG DEFAULT


#endif 