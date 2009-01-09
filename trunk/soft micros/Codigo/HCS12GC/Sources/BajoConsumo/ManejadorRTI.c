#include <assert.h>
#include "IO_Map.h"
#include "RTI.h"
#include "ManejadorRTI.h"
#include "ManejadorRTI_private.h"

#pragma DATA_SEG ManejadorRTI_DATA                                            
#pragma CODE_SEG ManejadorRTI_CODE 
#pragma CONST_SEG DEFAULT


static struct ManejadorRTI mRTI;
static struct ManejadorRTI * instance = NULL;

void ManejadorRTI_defConstructor(void * _self,va_list * args);;

const struct Class ManejadorRTI={
  CLASS_INITIALIZATION(Class,
                       ManejadorRTI,
                       ManejadorInterrupcion,
                       ManejadorRTI_defConstructor,
                       Object_dtor,
                       Object_differ,
                       Object_puto)  
};

void ManejadorRTI_constructor(void * _self){
  RTI_Init();
  assert(ManejadorRTI_onRTIInterrupt == *(((void**)0xFF80)+56) );  
}

void ManejadorRTI_defConstructor(void * _self,va_list * args){
  ManejadorRTI_constructor(_self);
}

void * ManejadorRTI_getInstance(void){
  if(!instance){    
    newAlloced(&mRTI,&ManejadorRTI);
    instance = &mRTI;   
  }
  return instance;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED

__interrupt void ManejadorRTI_onRTIInterrupt(void){
 // CRGFLG = 128;                        /* Reset interrupt request flag */
  onInterrupt(&mRTI);
  CRGFLG = 128;                        /* Reset interrupt request flag */

}
#pragma CODE_SEG ManejadorRTI_CODE 


void ManejadorRTI_enable(void * _self){
  RTI_Enable();
}

void ManejadorRTI_disable(void * _self){
  RTI_Disable();
}



