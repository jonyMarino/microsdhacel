/*  MODULE: PropNumerica.c*/

#include "stdtypes.h"
#include "stddef.h"
#include "PropFecha.h"
#include "display.h"

void PropWInc_DefConstructor(void * self,va_list*args);
void PropFecha_Print(void*self,uchar num_display);
void PropFecha_Inc(void*self);
void PropFecha_Dec(void*self);

const struct TPropWInc TablePropNum={
  sizeof(struct PropNum),
  PropWInc_DefConstructor,
  NULL,
  NULL,
  NULL,
  PropFecha_Print,
  PropFecha_Inc,
  PropFecha_Dec
};

const void * PropNum=&TablePropNum;




void PropFecha_Print(void*self,uchar num_display){
  struct GetterVisual* _prop=self;

  struct ConstPropFecha* Block= (struct ConstPropNum*) _prop->_CGetter; 
  int _val= PropWInc_getValorTmp(self);
  
  Pasar_Numero(_val,num_display,2);
  
}

void PropFecha_Inc(void*self){
}
  
void PropFecha_Dec(void*self){
}
  