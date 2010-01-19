/*  MODULE: TitleBox.c*/


#include <stddef.h>
#include "obtenciondisplay.hpp"
#include "BoxTitle.hpp"





/*
** ===================================================================
**     Method      :  DataBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
BoxTitulo::BoxTitulo(const char*str1,const char*str2):Box(0){
  getDisplay(0).write(str2);
  getDisplay(1).write(str1);     
}

/*
** ===================================================================
**     Method      :  DataBox_ProcKey 
**     Description :  Procesa la tecla
** ===================================================================
*/
Box * BoxTitulo::procesarTecla(uchar tecla,TEstadoBox& estado)
{
  if (tecla=='r' || tecla=='f'){ 
	  estado= EXIT_BOX;
	  return NULL;
  }
  estado = STAY_BOX;
  return NULL;
}




