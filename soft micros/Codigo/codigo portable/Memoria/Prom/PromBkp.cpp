#include <limits.h>
#include <stdlib.h>
#include "stddef.h"

#include "PromBkp.hpp"

PromBkp::PromBkp(){

  aGrabar = FALSE;
  timer = NULL;
  disableCont=0;
  
}

/*
** ===================================================================
**    Function    :  PromBkp_deshabilitar 
**    Description : 
** ===================================================================
*/
void PromBkp::deshabilitar(){
  disableCont++;
  if(!disableCont) //pego la vuelta?
    disableCont=UINT_MAX;   
}

/*
** ===================================================================
**    Function    :  PromBkp_habilitar 
**    Description : 
** ===================================================================
*/
void PromBkp::habilitar(){

  disableCont--;
  if(disableCont==UINT_MAX) //pego la vuelta?
    disableCont=0;   
}


/*
** ===================================================================
**    Function    :  PromBkp_demorarGrabado 
**    Description : 
** ===================================================================
*/
void PromBkp::demorarGrabado(word time){
  if(!timer)
    timer=  new Timer(time);
  else
    timer->setTime(time);
}
/*
** ===================================================================
**    Function    :  PromBkp_listoParaGrabar 
**    Description : 
** ===================================================================
*/
bool PromBkp::listoParaGrabarOBorrar(){

  bool delayFlag;
  
  delayFlag=(timer)?timer->isFinished():TRUE;
  if(timer && delayFlag){ 
    delete timer;
    timer = NULL;
  }
  return (grabacionOBorradoEnEspera()
          && delayFlag
          && disableCont==0);
}
/*
** ===================================================================
**    Function    :  PromBkp_grabacionOBorradoEnEspera 
**    Description : 
** ===================================================================
*/
bool PromBkp::grabacionOBorradoEnEspera(){
  
  return ( aGrabar || ! listaDireccionesABorrar.isEmpty()); 
}
/*
** ===================================================================
**    Function    :  PromBkp_borrarPagina 
**    Description : 
** ===================================================================
*/
byte PromBkp::borrarPagina(void * Addr){
  if(Addr==NULL)
    return 1;
  return listaDireccionesABorrar.add(Addr);
}
 
/*
** ===================================================================
**    Function    :  PromBkp_grabarOBorrar 
**    Description :  template method
** ===================================================================
*/
byte PromBkp::grabarOBorrar(){
  void* direccion;
  direccion= listaDireccionesABorrar.eliminarPrimero();
  if(direccion!=NULL){     //borrar?
    //PromBkp_callPreEraseListeners(self,direccion);
    return borrarProm(direccion); 
    //PromBkp_callPreEraseListeners(self,direccion);

  } else if(aGrabar){
    direccion=grabarProm();   
    //PromBkp_callPostWriteListeners(self,direccion);
    return direccion!=NULL;
  } 
  return EXIT_FAILURE;
  
}


/*
** ===================================================================
**    Function    :  PromBkp_grabarOBorrar 
**    Description :  template method
** ===================================================================
*/
void PromBkp::setAGrabar(bool valor){
  aGrabar=valor;    
}


/*
** ===================================================================
**    Function    :  PromBkp_getAGrabar 
**    Description :  template method
** ===================================================================
*/
bool PromBkp::getAGrabar(){
  return aGrabar;    
}
