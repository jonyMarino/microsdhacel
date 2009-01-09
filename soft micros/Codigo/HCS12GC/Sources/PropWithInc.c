/* MODULE: PropWithInc Propiedad con incremento*/

#include <stddef.h>
#include "PropWithInc.h"
#include "display.h"

void PropWInc_DefConstructor(void* _self,va_list * args);
void PropWInc_Print(void* self,uchar num_display);
void PropWInc_Inc(void *_self);
void PropWInc_Dec(void *_self);

const struct Class PropWIncClass;

const struct PropWIncClass PropWInc={
  PROP_W_INC_CLASS_INITIALIZATION(PropWIncClass,
                                  PropWInc,
                                  PropVisual,
                                  PropWInc_DefConstructor,
                                  NULL,
                                  NULL,
                                  NULL,
                                  Prop_getVal,
                                  PropWInc_Print,
                                  PropVisual_getDescripcion,
                                  PropWInc_Inc,
                                  PropWInc_Dec)  
};


/*
** ===================================================================
**     Method      :  PropWInc_Constructor 
**     Description :  Constructor de la propiedad con incremento
** ===================================================================
*/
void PropWInc_Constructor(void* _self,void * Block,void*Obj){
   struct PropWInc * p=_self;
   
   Prop_Constructor(_self,Block,Obj);
   
   PropWInc_Refresh(_self);  
   
   //	 Corrijo posible error en la grabacion de la FLASH
   if( p->ValorTmp < p->LimInf )
    p->ValorTmp=p->LimInf;
   if( p->ValorTmp > p->LimSup )
    p->ValorTmp=p->LimSup;
}

/*
** ===================================================================
**     Method      :  PropWInc_DefConstructor 
**     Description :  Constructor por defecto de la propiedad con incremento
** ===================================================================
*/
void PropWInc_DefConstructor(void* _self,va_list * args){
  PropWInc_Constructor(_self,va_arg(*args,void*),va_arg(*args,void*));      
}
/*
** ===================================================================
**     Method      :  PropWInc_Print 
**     Description :  Imprime por pantalla el dato de la propiedad con 
**                    su formato correspondiente
** ===================================================================
*/

void PropWInc_Print(void* self,uchar num_display){
  struct PropWInc * p=self;
  int val;
  
  val= p->ValorTmp;
  Pasar_Numero(val,num_display,0);    
}

/*
** ===================================================================
**     Method      :  PropWInc_Save 
**     Description :  Graba el valor temporal que se fue 
**                    incrementando/decrementando
** ===================================================================
*/
TError PropWInc_Save(void *_self){
	 struct PropWInc * p=_self; 
	 
	 return Prop_setVal(_self,p->ValorTmp);
	 
}

/*
** ===================================================================
**     Method      :  PropWInc_Refresh 
**     Description :  Actualiza el valor del dato si es que hubo un cambio
**                  en su valor de la FLASH
** ===================================================================
*/
void PropWInc_Refresh(void *_self){
	 struct PropWInc * p=_self; 
	 
   p->ValorTmp= Prop_getVal(_self);
   p->LimInf=		Prop_getLimInf(_self);
   p->LimSup=		Prop_getLimSup(_self);
}

/*
** ===================================================================
**     Method      :  PropWInc_Inc 
**     Description :  Incrementa el valor temporal
** ===================================================================
*/
void PropWInc_Inc(void *_self){
	 struct PropWInc * p=_self; 
	 if(p->ValorTmp<p->LimSup)
	  p->ValorTmp++;   
}

/*
** ===================================================================
**     Method      :  PropWInc_getValorTmp 
**     Description :  Obtiene el valor temporal
** ===================================================================
*/
int PropWInc_getValorTmp(void *_self){
	 struct PropWInc * p=_self; 
	 return p->ValorTmp;  
}

/*
** ===================================================================
**     Method      :  PropWInc_getLimInf 
**     Description :  Obtiene el Limite inferior
** ===================================================================
*/
int PropWInc_getLimInf(void *_self){
	 struct PropWInc * p=_self; 
	 return p->LimInf;  
}

/*
** ===================================================================
**     Method      :  PropWInc_getLimInf 
**     Description :  Obtiene el Limite superior
** ===================================================================
*/
int PropWInc_getLimSup(void *_self){
	 struct PropWInc * p=_self; 
	 return p->LimSup;  
}

/*
** ===================================================================
**     Method      :  PropWInc_setValorTmp 
**     Description :  Setea el valor temporal
** ===================================================================
*/
byte PropWInc_setValorTmp(void *_self,int val){
	 struct PropWInc * p=_self; 
	 p->ValorTmp=val; 
	 return ERR_OK; 
}

/*
** ===================================================================
**     Method      :  vPropWInc_Inc 
**     Type         : Virtual
**     Description :  Incrementa el valor temporal
** ===================================================================
*/
void vPropWInc_Inc(void *_self){
	 struct PropWIncClass ** p=_self; 
	 
	 (*p)->inc(_self);  
}

/*
** ===================================================================
**     Method      :  PropWInc_Dec 
**     Description :  Incrementa el valor temporal
** ===================================================================
*/
void PropWInc_Dec(void *_self){
	 struct PropWInc * p=_self; 
	 if(p->ValorTmp>p->LimInf)
	  p->ValorTmp--;      
}
/*
** ===================================================================
**     Method      :  vPropWInc_Dec 
**     Type         : Virtual
**     Description :  Decrementa el valor temporal
** ===================================================================
*/
void vPropWInc_Dec(void *_self){
	 struct PropWIncClass ** p=_self; 
	 
	 (*p)->dec(_self);  
}


