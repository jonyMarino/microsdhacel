/*  MODULE: PropNumerica.c*/

#include "stdtypes.h"
#include "stddef.h"
#include "PropVisual.h"
#include "PropNumerica.h"
#include "display.h"

void PropWInc_DefConstructor(void * self,va_list*args);
void PropNum_Print(void*self,uchar num_display);
void PropWInc_Inc(void *_self);
void PropWInc_Dec(void *_self);

const struct PropWIncClass PropNum={
  PROP_W_INC_CLASS_INITIALIZATION(PropWIncClass,
                                  PropNum,
                                  PropWInc,
                                  PropWInc_DefConstructor,
                                  NULL,
                                  NULL,
                                  NULL,
                                  Prop_getVal,
                                  PropNum_Print,
                                  PropVisual_getDescripcion,
                                  PropWInc_Inc,
                                  PropWInc_Dec)  
};




void PropNum_Print(void*self,uchar num_display){
  struct GetterVisual* _prop=(struct GetterVisual*)self;

  struct ConstPropNum* Block= (struct ConstPropNum*) _prop->_CGetter; 
  int _val= PropWInc_getValorTmp(self);
  uchar _dot= Block->dot;
  
  Pasar_Numero(_val,num_display,_dot);
  
}