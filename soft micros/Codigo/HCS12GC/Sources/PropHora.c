/*  MODULE: PropHora.c*/

#include "stdtypes.h"
#include "stddef.h"
#include "PropHora.h"
#include "display.h"

void PropWInc_DefConstructor(void * self,va_list*args);
void PropHora_Print(void*self,uchar num_display);
void PropHora_Inc(void*self);
void PropHora_Dec(void*self);

const struct PropWIncClass PropHora={
  PROP_W_INC_CLASS_INITIALIZATION(PropWIncClass,
                                  PropHora,
                                  PropWInc,
                                  PropWInc_DefConstructor,
                                  NULL,
                                  NULL,
                                  NULL,
                                  Prop_getVal,
                                  PropHora_Print,
                                  PropVisual_getDescripcion,
                                  PropHora_Inc,
                                  PropHora_Dec)
};



void PropHora_Print(void*self,uchar num_display){
  int _val= PropWInc_getValorTmp(self);
  
  Pasar_Numero(_val,num_display,2);
  
}

void PropHora_Inc(void*self){
  int Valor_Tmp= PropWInc_getValorTmp(self);
  int LimSup = PropWInc_getLimSup(self);
  
  if(Valor_Tmp<LimSup)
    Valor_Tmp++;
  if (((Valor_Tmp%100)%60)==0 && Valor_Tmp!=0) Valor_Tmp +=40;
	PropWInc_setValorTmp(self,Valor_Tmp);
}
  
void PropHora_Dec(void*self){
  int _val= PropWInc_getValorTmp(self);
	if (_val > 0){
	  
		if (_val%100==0) _val-=40;
		_val--; 
	}
	PropWInc_setValorTmp(self,_val);

}
  