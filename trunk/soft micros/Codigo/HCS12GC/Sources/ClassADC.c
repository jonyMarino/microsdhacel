/*MODULE: ClassADC*/
#include <stdarg.h>

#include "stddef.h"
#include "ADC.h"
#include "MethodTimer.h"
#include "Object.h"
#include "ClassADC.h"
#include "display.h"
#include "TI1.h"

#pragma DATA_SEG CLASS_ADC_DATA                                            
#pragma CODE_SEG CLASS_ADC_CODE 
#pragma CONST_SEG DEFAULT

void AD_DefConstructor(struct Adc * self,va_list * args);
int AD_DefgetValue(struct Adc * self);
bool AD_Defisnew(struct Adc * self);

const struct AdcClass Adc={ 
  CLASS_INITIALIZATION(AdcClass,Adc,Object,AD_DefConstructor,Object_dtor,Object_differ,Object_puto),
  AD_DefgetValue,  // get_Val
  AD_Print,
  AD_Defisnew     // is_new? 
};



struct MethodTimer ADtimer;
bool fst_time=TRUE;
const int AD_CONVERTING_TIME =_TIEMPO_AD_EN_MILISEGUNDOS-TIEMPO_GRABACION; 
const int ADTIME = _TIEMPO_AD_EN_MILISEGUNDOS;

static void AD_Start(void*_self){
  ADC_Start();  
}
/*
** ===================================================================
**     Method      :  AD_Constructor 
**    Description : Constructor del AD
** ===================================================================
*/
void AD_Constructor(struct Adc * self,byte pin){
  if(fst_time){ //si es que ya no esta iniciado
    fst_time=FALSE;
    ADC_Start();  //Inicia el ADC 
    newAlloced(&ADtimer,&MethodTimer,(ulong)ADTIME,AD_Start,&Adc); //cada  ADTIME se va a ejecutar una nueva medición
  }
  self->pin=pin;  
}

/*
** ===================================================================
**     Method      :  AD_Constructor 
**    Description : Constructor por defecto del AD
** ===================================================================
*/
void AD_DefConstructor(struct Adc * self,va_list * args){
  AD_Constructor(self,(uchar)va_arg(*args,int));
}

/*
** ===================================================================
**     Method      :  AD_DefgetValue 
**    Description : Obtiene valor del AD basico
** ===================================================================
*/
int AD_DefgetValue(struct Adc * self){
  return ADC_getVal(self->pin);
}

/*
** ===================================================================
**     Method      :  AD_Print 
**    Description :   Imprime el valor del AD
** ===================================================================
*/
void AD_Print(struct Adc * self,uchar num_disp){
  Pasar_Numero(ADC_getVal(self->pin),num_disp,0);
}


/*
** ===================================================================
**     Method      :  AD_Defisnew 
**    Description : (Por Defecto)se fija si el valor del AD es nuevo
** ===================================================================
*/
bool AD_Defisnew(struct Adc * self){
  return ADC_isread(self->pin);
}

/*
** ===================================================================
**     Method      :  getSate 
**    Description : Obtiene el estado de los AD
** ===================================================================
*/
AD_State getState(void){
  if(Timer_getCuenta(&ADtimer)>AD_CONVERTING_TIME)
    return AD_WAITING;
  else
    return AD_CONVERTING;
}


