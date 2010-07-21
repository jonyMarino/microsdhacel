/*  MODULE: BoxPrincipal.c*/

#include <stddef.h>
#include "BoxPrincipal.hpp"
//#include "Mydefines.h"
//#include "Configuracion.h"
#include "obtenciondisplay.hpp"


#pragma DATA_SEG BoxPrincipal_DATA                                            
#pragma CODE_SEG BoxPrincipal_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */




const struct BoxPrincipalFactory boxPrincipalFactory;
/*
** ===================================================================
**     Method      :  BoxPri_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
BoxPrincipal::BoxPrincipal(struct ConstructorBoxPrincipal * _constructor):Box(),timerPri(TIME_BETWEEN_PARS)
{
  msj_index=0; 
  msj_index_sup=0; 
  constructor=_constructor;
  constructor->flash->habilitar();  
  constructor->snsr1->print(getDisplay(0));  
  getDisplay(1).write("MEdicion");
}

/*
** ===================================================================
**     Method      :  BoxPri_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
BoxPrincipal::~BoxPrincipal(){
  constructor->flash->deshabilitar();
}

/*
** ===================================================================
**     Method      :  BoxPri_ProcKey 
**     Description :  Procesa la tecla ingresada
** ===================================================================
*/
Box * BoxPrincipal::procesarTecla(uchar tecla,TEstadoBox& estado){
  if(timerPri.getFlag()){
      if(constructor->msjs){     
        char * msj=constructor->msjs->getMessage(msj_index);
        if( msj ){
          ++msj_index; 
          getDisplay(1).write(msj);
        }else{
          if(msj_index==0)		 //no hay mensajes?
            getDisplay(1).write("MEdicion");
          else
            msj_index=0;
        }
      }
      constructor->snsr1->print(getDisplay(0));
  		timerPri.reset();
  }
  if(tecla=='r' || tecla=='f'){ 
    estado = EXIT_BOX;
    return NULL;
  }
  estado = STAY_BOX;
  return NULL;
}


 

