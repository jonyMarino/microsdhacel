/*MODULE: PropTextual.c*/
#include "stdtypes.h"
#include "stddef.h"
#include "PropVisual.h"
#include "PropTextual.h"
#include "display.h"

void PropWInc_DefConstructor(void * self,va_list*args);
void PropTxt_Print(void*self,uchar num_display);
void PropWInc_Inc(void *_self);
void PropWInc_Dec(void *_self);

const struct PropWIncClass PropTxt={
  PROP_W_INC_CLASS_INITIALIZATION(PropWIncClass,
                                  PropTxt,
                                  PropWInc,
                                  PropWInc_DefConstructor,
                                  NULL,
                                  NULL,
                                  NULL,
                                  Prop_getVal,
                                  PropTxt_Print,
                                  PropVisual_getDescripcion,
                                  PropWInc_Inc,
                                  PropWInc_Dec)
};




void PropTxt_Print(void*self,uchar num_display){
  struct GetterVisual* _prop=(struct GetterVisual*)self;

  struct ConstPropTxt * Block=(struct ConstPropTxt *) _prop->_CGetter;
  char * _str=  (*(Block->_getTxt))((uchar)PropWInc_getValorTmp(self));
  
  PasarASCII(_str,num_display);
  
}