/*  MODULE: PropNumPV.c*/

#include "PropNumPV.h"
#include "display.h"

void PropWInc_DefConstructor(void * self,va_list*args);
void PropNumPV_Print(void*,uchar);
void PropWInc_Inc(void *_self);
void PropWInc_Dec(void *_self);

const struct PropWIncClass PropNumPV={
  PROP_W_INC_CLASS_INITIALIZATION(PropWIncClass,
                                  PropNumPV,
                                  PropWInc,
                                  PropWInc_DefConstructor,
                                  NULL,
                                  NULL,
                                  NULL,
                                  Prop_getVal,
                                  PropNumPV_Print,
                                  PropVisual_getDescripcion,
                                  PropWInc_Inc,
                                  PropWInc_Dec)
};

void PropNumPV_Print(void* self,uchar num_display){
  struct GetterVisual* _prop=(struct GetterVisual*)self;

  struct ConstPropNumPV* Block= (struct ConstPropNumPV*) _prop->_CGetter; 
  int _val= PropWInc_getValorTmp(self);
  uchar _dot= (*(Block->_getDec))(Prop_getObj(_prop));
  
  Pasar_Numero(_val,num_display,_dot);
}