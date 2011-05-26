#ifndef PROP_W_INC_H
#define PROP_W_INC_H

#include <stdtypes.h>
#include "PropVisual.h"

struct ConstructorPropWInc{
  struct ClassPropVisual _prop_base;
};

struct PropWInc{
  struct PropVisual _prop;
  int ValorTmp;
  int LimSup;
  int LimInf; 
};

struct PropWIncClass{ 
  struct GetterWNameClass super;
  void (*inc)(void*);
  void (*dec)(void*); 
};

#define PROP_W_INC_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,get,print,getName,inc,dec)\
  GETTER_W_NAME_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,get,print,getName),\
  inc,  \
  dec


extern const struct Class PropWIncClass;
extern const struct PropWIncClass PropWInc; 

/*
** ===================================================================
**     Method      :  PropWInc_Constructor 
**     Description :  Constructor de la propiedad con incremento
** ===================================================================
*/
void PropWInc_Constructor(void* _self,void * Block,void*Obj);

/*
** ===================================================================
**     Method      :  PropWInc_Save 
**     Description :  Graba el valor temporal que se fue 
**                    incrementando/decrementando
** ===================================================================
*/
TError PropWInc_Save(void *_self);

/*
** ===================================================================
**     Method      :  PropWInc_Refresh 
**     Description :  Actualiza el valor del dato si es que hubo un cambio
**                  en su valor de la FLASH
** ===================================================================
*/
void PropWInc_Refresh(void *_self);

/*
** ===================================================================
**     Method      :  vPropWInc_Inc 
**     Type         : Virtual
**     Description :  Incrementa el valor temporal
** ===================================================================
*/
void vPropWInc_Inc(void *_self);

/*
** ===================================================================
**     Method      :  vPropWInc_Dec 
**     Type         : Virtual
**     Description :  Decrementa el valor temporal
** ===================================================================
*/
void vPropWInc_Dec(void *_self);
/*
** ===================================================================
**     Method      :  PropWInc_getValorTmp 
**     Description :  Obtiene el valor temporal
** ===================================================================
*/
int PropWInc_getValorTmp(void *_self);
/*
** ===================================================================
**     Method      :  PropWInc_getLimInf 
**     Description :  Obtiene el Limite inferior
** ===================================================================
*/
int PropWInc_getLimInf(void *_self);

/*
** ===================================================================
**     Method      :  PropWInc_getLimInf 
**     Description :  Obtiene el Limite superior
** ===================================================================
*/
int PropWInc_getLimSup(void *_self);
/*
** ===================================================================
**     Method      :  PropWInc_getValorTmp 
**     Description :  Setea el valor temporal
** ===================================================================
*/
uchar PropWInc_setValorTmp(void *_self,int);


  
#endif 