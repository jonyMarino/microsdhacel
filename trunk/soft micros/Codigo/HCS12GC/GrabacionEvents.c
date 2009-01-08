/*  MODULE GrabacionEvents*/
#include "GrabacionEvents.h"

#include "DiagramaNavegacion.h"
#include "Display1.h"


void PreWrite(void){
  Display1_PutVal(0);		/* Borro el display */  
}

void OnWrite(void){ 
  #ifdef _DN
  DN_Refresh();
  #endif 
}

