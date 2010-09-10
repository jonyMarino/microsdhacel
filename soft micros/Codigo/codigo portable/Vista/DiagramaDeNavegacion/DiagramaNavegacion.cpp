/*MODULE: DiagramaNavegacion.c*/
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//#include "Teclas.hpp"
//#include "Object.h"
#include "DiagramaNavegacion.hpp"
#include "opcionescompilacion.h"
//#include "obtenciondisplay.hpp"
//#include "Array.h"

//#include "RlxMTimer.h"
#include "Box.hpp"
#include "Access.hpp"

//#include "PropWithInc.h"
//#include "BoxCondicional.h"
//#include "TitleBox.h"
//#include "BoxAccess.h"
//#include "Access.h"

#pragma DATA_SEG DIAGRAMA_NAVEGACION_DATA 
#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE
#pragma CONST_SEG DEFAULT







/*
** =====================================================================
**    Function      :  DN_StaticInit 
**    Description :    Inicializa el Diagrama de Navegacion con listas
**                    y accesos  ya inicializados y constanter
** =====================================================================
*/
DiagramaNavegacion::DiagramaNavegacion(const struct BoxList * _boxesOp,const struct Array *_accesos,FrenteCustom * _frente){
  //Mostrar: Dhacel version,y compilacion
  frente = _frente;
  metodoParaTimer.pmethod=showCompilacion;
  metodoParaTimer.obj=this;
  
  timer= new RlxMTimer(_VERSION_TIME,metodoParaTimer);
  
  frente->getDisplay(0)->write(getModelo());
  frente->getDisplay(1)->write(getVersion());
  
  accesos = _accesos;
  boxesOp = _boxesOp;
  boxActual=NULL;
  
  if(!timer)			  // si no pude poner el Timer intentar saltar a principal
    goPrincipal();
}

/*
** =====================================================================
**    Function      :  DN_ShowCompilacion 
**    Description :    Muestra las opciones de compilacion
** =====================================================================
*/
void DiagramaNavegacion::showCompilacion(void*self){
  DiagramaNavegacion * dn = (DiagramaNavegacion *)self;
  const long comp_options = getOpcionesCompilacion();
  char str[5];
  sprintf(str,"%x",comp_options / 0x10000);
  dn->frente->getDisplay(0)->write(str);
  sprintf(str,"%x",comp_options % 0x10000);
  dn->frente->getDisplay(1)->write(str);
  dn->metodoParaTimer.pmethod = jumpToOperador;
  dn->timer->setMetodo(dn->metodoParaTimer);
  dn->timer->setTime(_VERSION_TIME);
}
/*
** =====================================================================
**    Function      :  DN_goPrincipal 
**    Description :    Vuelve al Box Principal
** =====================================================================
*/

bool DiagramaNavegacion::isBoxPrincipal(){
  if(accessCount==0&&boxListCount==1&&listCount==0)
    return TRUE;
  else
    return FALSE;  
}

void DiagramaNavegacion::goPrincipal(){
  struct FstBoxPointer * fb;
  listCount=0;
  boxListCount=1;
  accessCount=0;
  if(boxActual)
    delete boxActual;
  fb=(struct FstBoxPointer *)Array_get((void*)boxesOp,0);
  boxActual= &fb->getNextBox();//vBoxes_Construct(fb->Cbox,NULL,0);
}
/*
** =====================================================================
**    Function      :  DN_JumpToOperador 
**    Description :    Salta al Operador
** =====================================================================
*/
void DiagramaNavegacion::jumpToOperador(void*self){
  DiagramaNavegacion * dn = (DiagramaNavegacion *)self;
  delete dn->timer;
  dn->goPrincipal();
}

/*
** =====================================================================
**    Function      :  DN_Refresh 
**    Description :    Refresca los valores del Box Actual
** =====================================================================
*/
void DiagramaNavegacion::refresh(void){
  boxActual->refresh();  
}
/*
** =====================================================================
**    Function      :  DN_OpgetObj 
**    Description :    Obtiene el objeto que esta tratando el box
** =====================================================================
*/
struct FstBoxPointer* DiagramaNavegacion::opgetFstBoxP(){
  return (struct FstBoxPointer*)Array_get((void*)boxesOp,boxListCount-1);  
}
/*
** =====================================================================
**    Function      :  DN_getActualObj 
**    Description :    Obtiene el objeto que esta tratando el box
** =====================================================================
*/
struct FstBoxPointer* DiagramaNavegacion::getActualFstBoxP(void){
  struct Access* access;
  struct BoxList* boxList;

  if(accessCount==0) //Estoy en operador
    return opgetFstBoxP();
  if(listCount==0)		//Estoy en acceso
    return NULL;
  if(boxListCount==0)//Estoy en lista
    return NULL;
  
  access= (struct Access*)Array_get(accesos,accessCount-1);
  boxList= (struct BoxList*)Array_get(access,listCount-1);
  return (struct FstBoxPointer*)Array_get(&boxList,boxListCount-1);   
}

/*
** =====================================================================
**    Function      :  DN_Proc 
**    Description :    Procesa el Box Actual y le pasa el valor de la tecla
** =====================================================================
*/
void DiagramaNavegacion::procesar(uchar tecla){
  struct ConstructorBox * Cbox;
  Box::TEstadoBox state;
  Box * pbox_next;
  void * Obj;
  
  if(!boxActual)			 // Todavia no se cargo el box inicial?
    return;
  
  if(tecla=='k' || (frente->getTeclas().isTimePass() && !(accessCount==0 && listCount==0)) ){					//Exit
    goPrincipal();
    return;
  } 

  pbox_next=boxActual->procesarTecla(tecla,state);

  if(state==Box::STAY_BOX)
    return;
  
 

  //pbox_next=vBox_getNextBlockConstr(DN.BoxActual,tecla);
  
  delete boxActual;
  //frente->borrar(); // borro la pantalla para que quede limpia para el siguiente box
  
  if(pbox_next){							 // Me mantengo en el mismo objeto??
    /*struct FstBoxPointer* fbp;
    void *Obj;
    uchar num_obj;
    
    if(accessCount==0)				 //Estoy en op
      fbp=(struct FstBoxPointer*) Array_get(boxesOp,boxListCount-1);
    else{
      struct Access* access= Array_get(accesos,accessCount-1);      
      struct BoxList boxList=Array_get(access,listCount-1);
      fbp=(struct FstBoxPointer*)Array_get(boxList,boxListCount-1);
    } */
    boxActual= pbox_next;  
  } else if(accessCount==0){			//Estoy en op
    if(tecla=='f'){
      boxListCount=0;
      accessCount++;
      if(accessCount<=Array_count(accesos)){
        struct Access * a = (struct Access *)Array_get(accesos,accessCount-1);
        boxActual= a->getNextBox(listCount,boxListCount);
      }else
        boxActual=NULL;
    }else{							 //'r' o 0
      boxListCount++;
      boxActual= boxesOp->getNextBox(boxListCount);  
    }
  } else{
      if(listCount==0){		//Estoy en ACCESO
        if(tecla=='r')
          accessCount++;            
        else if(tecla=='f')
          listCount++;
      } else if(boxListCount==0) {  //Estoy en Lista
        if(tecla=='r')
          boxListCount++;
        else if(tecla=='f')
          listCount++;
      }else{
        //tecla=='r'
        boxListCount++;  
      }
      // Obtener Box a partir de la nueva posición
      if(accessCount<=Array_count(accesos)) {
        struct Access * a=(struct Access *)Array_get(accesos,accessCount-1);
        boxActual= a->getNextBox(listCount,boxListCount);
      }else
  		  boxActual=NULL;
  }
  
  if(boxActual==NULL)		 // Se llego a algun extremo?	 o no se puedo cargar el box
    goPrincipal();  
  
  
}	 





#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE

