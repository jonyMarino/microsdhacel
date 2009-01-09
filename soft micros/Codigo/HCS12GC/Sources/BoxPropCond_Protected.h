#ifndef _BOX_PROP_COND_PROTECTED_H
#define _BOX_PROP_COND_PROTECTED_H


/*
** ===================================================================
**     Method      :  BoxPropCond_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxPropCond_Constructor(void * _self, void * BlockConst,void * Obj,uchar NumObj);
/*
** ===================================================================
**     Method      :  BoxPropCond_DefConstructor 
**     Description :  Constructor por defecto del Box
** ===================================================================
*/
void BoxPropCond_DefConstructor(void * _self, va_list*args);
/*
** ===================================================================
**     Method      :  BoxPropCond_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
void * BoxPropCond_Destructor(void* _self);
/*
** ===================================================================
**     Method      :  BoxPropCond_Refresh 
**     Description :  Refresca los valores del Box 
** ===================================================================
*/
void BoxPropCond_Refresh(void* _self);
/*
** ===================================================================
**     Method      :  BoxPropCond_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxPropCond_ProcKey(void* _self,uchar tecla);
/*
** ===================================================================
**     Method      :  BoxPropCond_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * BoxPropCond_getNext(void * _self,uchar tecla);
#endif