#ifndef _MANEJADORRTI_H
#define _MANEJADORRTI_H


#include "ManejadorInterrupcion.h"

#pragma DATA_SEG ManejadorRTI_DATA                                            
#pragma CODE_SEG ManejadorRTI_CODE 
#pragma CONST_SEG DEFAULT

struct ManejadorRTI {
  struct ManejadorInterrupcion super;  
};


void * ManejadorRTI_getInstance(void);

void ManejadorRTI_enable(void * _self);

void ManejadorRTI_disable(void * _self);


#define getIntervaloMicroSeg(self) (131072 * ( 1 + 9/305))  //error empirico

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif
