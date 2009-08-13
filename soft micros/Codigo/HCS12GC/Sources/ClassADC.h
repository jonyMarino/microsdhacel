#ifndef CLASS_ADC_H
#define CLASS_ADC_H

#include "Mydefines.h"
#include "PE_Types.h"
#include "Sensor.h"

#pragma DATA_SEG CLASS_ADC_DATA                                            
#pragma CODE_SEG CLASS_ADC_CODE 


extern const int ADTIME;

struct AdcClass{
  struct GetterClass super;
  bool (*isnew)(void*);
};


	 

struct Adc{
  const struct Object * super;
  byte pin;
};

extern const struct AdcClass Adc;

typedef enum{
  AD_CONVERTING,
  AD_WAITING
}AD_State;

void AD_Constructor(struct Adc *,byte pin);

int AD_getValue(struct Adc *);

bool AD_isnew(struct Adc *);

/*
** ===================================================================
**     Method      :  getSate 
**    Description : Obtiene el estado de los AD
** ===================================================================
*/
AD_State getState(void);

/*
** ===================================================================
**     Method      :  AD_Print 
**    Description :   Imprime el valor del AD
** ===================================================================
*/
void AD_Print(struct Adc * self,uchar num_disp);


#define _AD_isnew(ad) \
          (*(*(struct AdcClass**)ad)->isnew)(ad)

          
#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#endif