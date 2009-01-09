/* MODULE: ClassBoxLineal.c  */

#include <stdarg.h>
#include <stddef.h>
#include "ClassBoxLineal.h"
#include "display.h"

void BoxLineal_Constructor(void * _self, va_list * args);
void * BoxLineal_Destructor(void* _self);
void BoxLineal_Refresh(void* _self);
BOX_State BoxLineal_ProcKey(void* _self,uchar tecla);
struct BlockBoxConstruct * BoxLineal_getNext(void * _self,uchar tecla);

void BoxLineal_setBox(struct BoxLineal *_self);

const struct BoxClass BoxLineal={
               BOXCLASS_INITIALIZATION(BoxClass,
                          BoxLineal,
                          ObjBox,
                          BoxLineal_Constructor,
                          BoxLineal_Destructor,
                          NULL,
                          NULL,
                          BoxLineal_Refresh,
                          BoxLineal_ProcKey,
                          BoxLineal_getNext)      
};

/*
** ===================================================================
**     Method      :  BoxLineal_Constructor 
**     Description :  Constructor del Box Lineal
** ===================================================================
*/
void BoxLineal_Constructor(void * _self, va_list * args){
  struct BoxLineal * _box = _self;
  void * Block =  va_arg(*args,void*);
  _box->Obj=  va_arg(*args,void*);
  ObjBox_Constructor(_self,(uchar)va_arg(*args,int));
  _box->NumProp=0;
  _box->pBlockSelf=Block;
  BoxLineal_setBox(_box);
    
}

/*
** ===================================================================
**     Method      :  BoxLineal_Destructor 
**     Description :  Destructor del Box Lineal
** ===================================================================
*/
void * BoxLineal_Destructor(void* _self){
  struct BoxLineal * _box = _self;
  deleteAndNil(&(struct Tclass **)_box->prop_actual);
  return _self; 
}

/*
** ===================================================================
**     Method      :  BoxLineal_setBox 
**     Description :  Setea los valores de la Propiedad correspondiente
** ===================================================================
*/

void BoxLineal_setBox(struct BoxLineal *_self){
  struct BoxLineal * _box=_self;
  struct PropWInc * prop =pProp_Constructor(_box->pBlockSelf->props[_box->NumProp],_box->Obj); 
  char * desc;
   
  _box->prop_actual=prop; 
  _box->save=FALSE;
   
  desc = PropVisual_getDescripcion(prop);
  ObjBox_PrintDescription(_self,desc,_DPY_INF); 
  _GetterPrint(prop,_DPY_SUP);
}

/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Refresca los valores del Box Lineal
** ===================================================================
*/
void BoxLineal_Refresh(void* _self){
  struct BoxLineal * _box=_self;
  struct ObjBox * _Objbox=(struct ObjBox *)_self;
   
  PropWInc_Refresh(_box->prop_actual);
  
  _GetterPrint(_box->prop_actual,_DPY_SUP);

}
/*
** ===================================================================
**     Method      :  BoxLineal_Refresh 
**     Description :  Procesa la tecla
** ===================================================================
*/
BOX_State BoxLineal_ProcKey(void* _self,uchar tecla){
  struct BoxLineal * _box=_self;
  
  if ((tecla=='u') || (tecla=='d')){ // Fue presionada una Tecla UP o Down???
			  if(tecla=='u')
			    vPropWInc_Inc(_box->prop_actual);
			  if(tecla=='d')
			    vPropWInc_Dec(_box->prop_actual);			  
			  _box->save=TRUE;							            // Grabar parametros
			  _GetterPrint(_box->prop_actual,_DPY_SUP);
			  return STAY_BOX;
  } else if (tecla=='r'){
    if(_box->save)
	    PropWInc_Save(_box->prop_actual);	
    deleteAndNil(&_box->prop_actual);
    _box->NumProp++;  //siguiente propiedad
    if(_box->pBlockSelf->props[_box->NumProp]==NULL)
      return EXIT_BOX;
    
    BoxLineal_setBox(_self); 
    return STAY_BOX;
  } 
  
  return STAY_BOX;  

}

/*
** ===================================================================
**     Method      :  BoxLineal_getNext 
**     Description :  Devuelve el Bloque Constructor siguiente del BoxLineal 
** ===================================================================
*/

struct BlockConstruct * BoxLineal_getNext(void * _self,uchar tecla){
  struct BoxLineal * _box=_self;
  struct BlockCnstrBoxLin * Block = _box->pBlockSelf;
  if(tecla=='r')
    return Block->pNextBlckConst;
  return NULL;
}