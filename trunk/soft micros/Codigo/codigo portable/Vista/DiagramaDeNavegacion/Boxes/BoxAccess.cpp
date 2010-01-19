/*MODULE: BoxAccess.c*/


#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

#include "obtenciondisplay.hpp"
#include "BoxAccess.hpp"

  
#pragma DATA_SEG BOX_ACCESS_DATA                                            
#pragma CODE_SEG BOX_ACCESS_CODE
#pragma CONST_SEG DEFAULT


/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void BoxAccess::BoxAccess(const char*str,int _codigo):Box(0){

  valorTmp=0;
  codigo=_codigo;
  getDisplay(1).write(str);
  getDisplay(0).write("   0");   
}



/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxAccess::procesarTecla(uchar tecla,TEstadoBox& estado)
{
  char str[5];
  if(tecla=='u' || tecla=='d'){
    if(tecla=='d' && valorTmp>0)
      valorTmp--;
    else if(valorTmp<9999)
      valorTmp++;   
    sprintf(str,"%(4)i",valorTmp);
    getDisplay(0).write(str);
  }else if (tecla=='r'){
    
	  estado= EXIT_BOX;
	  return NULL;
  }else if(tecla=='f'){
    if(valorTmp== codigo){
      
      estado = EXIT_BOX;
      return NULL;
    }else{
      getDisplay(0).write("   0"); 
    } 
  }
  
  
  estado = STAY_BOX;  
  return NULL;
}



