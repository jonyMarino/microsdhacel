/*MODULE: DiagramaNavegacion.c*/

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "teclas.h"
#include "Object.h"
#include "DiagramaNavegacion.h"
#include "CompilationOptions.h"
#include "display.h"
#include "FTimer.h"
#include "ArrayList.h"
#include "Comparator.h"
#include "FstBoxPointer.h"
#include "BoxList.h"

#include "PropWithInc.h"
#include "BoxCondicional.h"
#include "TitleBox.h"
#include "BoxAccess.h"
#include "Access.h"

#pragma DATA_SEG DIAGRAMA_NAVEGACION_DATA 
#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE
#pragma CONST_SEG DEFAULT

static void DN_ShowCompilacion(void);
void DN_goPrincipal(void);
static void DN_JumpToOperador(void);



struct DiagNaveg{
  struct ArrayList *accesos;
  struct BoxList *BoxesOp;			 //Boxes de operador
  uchar BoxListCount;
  uchar ListCount;
  uchar AccessCount;
  struct Box * BoxActual;  
};

struct DiagNaveg DN;
struct FTimer * DN_timer;


/*
** =====================================================================
**    Function      :  DN_StaticInit 
**    Description :    Inicializa el Diagrama de Navegacion con listas
**                    y accesos  ya inicializados y constanter
** =====================================================================
*/
void DN_staticInit(struct BoxList *BoxesOp,struct ArrayList *accesos){
  //Mostrar: Dhacel version,y compilacion
  DN_timer= new(&FTimer,(ulong)_VERSION_TIME,DN_ShowCompilacion);
  
  PasarASCII(_STR_MODELO,_DPY_SUP);
  PasarASCII(_STR_VERSION,_DPY_INF);
  
  DN.accesos = accesos;
  DN.BoxesOp = BoxesOp;
  
  if(!DN_timer)			  // si no pude poner el Timer intentar saltar a principal
    DN_goPrincipal();
}
/*
** =====================================================================
**    Function      :  DN_Init 
**    Description :    Inicializa el Diagrama de Navegacion
** =====================================================================
*/
void DN_Init(struct BlockBoxConstruct * pri){
  //Mostrar: Dhacel version,y compilacion
  DN_timer= new(&FTimer,(ulong)_VERSION_TIME,DN_ShowCompilacion);
  
  
  PasarASCII(_STR_MODELO,_DPY_SUP);
  PasarASCII(_STR_VERSION,_DPY_INF);
  
  DN.accesos=new(&ArrayList);
  DN.BoxActual=NULL;
  DN.BoxesOp=new(&BoxList,"op");
  DN_AddBox(0,"op",pri,NULL,0);
  
  if(!DN_timer)			  // si no pude poner el Timer intentar saltar a principal
    DN_goPrincipal();
}



void DN_InitSized(struct BlockBoxConstruct * pri,int nParametrosOperador){
  DN_timer= new(&FTimer,(ulong)_VERSION_TIME,DN_ShowCompilacion);
  
  PasarASCII(_STR_MODELO,_DPY_SUP);
  PasarASCII(_STR_VERSION,_DPY_INF);
  
  DN.accesos=new(&ArrayList);
  ArrayList_expandInit(DN.accesos,1);
  DN.BoxActual=NULL;
  DN.BoxesOp=new(&BoxList,"op");
  ArrayList_expandInit(DN.BoxesOp,nParametrosOperador);
  DN_AddBox(0,"op",pri,NULL,0);  
  
  if(!DN_timer)			  // si no pude poner el Timer intentar saltar a principal
    DN_goPrincipal();

}
/*
** =====================================================================
**    Function      :  DN_ShowCompilacion 
**    Description :    Muestra las opciones de compilacion
** =====================================================================
*/
static void DN_ShowCompilacion(void){
  const long comp_options = _COMP_OPTIONS;
  PasarHexaNum(comp_options / 0x10000,_DPY_SUP);
  PasarHexaNum(comp_options % 0x10000,_DPY_INF);
  FTimer_ChangeFunction(DN_timer,DN_JumpToOperador);
  Timer_setTime(DN_timer,_VERSION_TIME*2);
}
/*
** =====================================================================
**    Function      :  DN_goPrincipal 
**    Description :    Vuelve al Box Principal
** =====================================================================
*/
void DN_goPrincipal(void){
  struct FstBoxPointer * fb;
  DN.ListCount=0;
  DN.BoxListCount=1;
  DN.AccessCount=0;
  deleteAndNil(&DN.BoxActual);
  fb=ArrayList_get(DN.BoxesOp,0);
  DN.BoxActual= vBoxes_Construct(fb->Cbox,NULL,0);
}
/*
** =====================================================================
**    Function      :  DN_JumpToOperador 
**    Description :    Salta al Operador
** =====================================================================
*/
static void DN_JumpToOperador(void){
  deleteAndNil(&DN_timer);
  DN_goPrincipal();
}

/*
** =====================================================================
**    Function      :  DN_AddBox 
**    Description :    Agrega los Boxes a una lista de parametros
** =====================================================================
*/
byte DN_addBoxList(uchar access,const char * str,int nBoxes){
  void * boxList_tmp=new(&BoxList,str);
  if(!boxList_tmp)
    return ERR_MEM;
  ArrayList_expandInit(boxList_tmp,nBoxes);
  ArrayList_Add(ArrayList_get(DN.accesos,access),boxList_tmp);  
}
/*
** =====================================================================
**    Function      :  DN_AddBox 
**    Description :    Agrega los Boxes a una lista de parametros
** =====================================================================
*/
void DN_AddBox(uchar access,const char * str,struct BlockBoxConstruct* Cbox,void * Obj,uchar num_obj){ 
 DN_AddIndexedBox(access,str,Cbox, Obj,num_obj,LIST_LAST_POSITION);
}
/*
** =====================================================================
**    Function      :  DN_AddBox 
**    Description :    Agrega los Boxes a una lista de parametros
** =====================================================================
*/
void DN_AddIndexedBox(uchar access,const char * str,struct BlockBoxConstruct* Cbox,void * Obj,uchar num_obj,int index){
  if(!strcmp(str, "op")){		 //operador
    BoxList_addIndexedBox(DN.BoxesOp,Cbox,Obj,num_obj,index);
  } else
    Access_addIndexedBox(ArrayList_get(DN.accesos,access),str,Cbox,Obj,num_obj,index);
  
}
/*
** =====================================================================
**    Function      :  DN_AddAccess 
**    Description :    Agrega un nuevo acceso
** =====================================================================
*/
uchar DN_AddAccess(const char * str,int * Cod){
  struct Access * newAccess;
  
  newAccess=new(&Access,str,Cod);
  if(!newAccess)
    return ERR_MEM;
  ArrayList_Add(DN.accesos, newAccess);
  
}

uchar DN_AddSizedAccess(const char * str,int * Cod,uint nListas){
  struct Access * newAccess;
  
  newAccess=new(&Access,str,Cod);
  if(!newAccess)
    return ERR_MEM;
  ArrayList_expandInit(newAccess,nListas);
  ArrayList_Add(DN.accesos, newAccess);
  
}  
    

/*
** =====================================================================
**    Function      :  DN_Refresh 
**    Description :    Refresca los valores del Box Actual
** =====================================================================
*/
void DN_Refresh(void){
  vBox_Refresh(DN.BoxActual);  
}
/*
** =====================================================================
**    Function      :  DN_OpgetObj 
**    Description :    Obtiene el objeto que esta tratando el box
** =====================================================================
*/
void*DN_OpgetFstBoxP(void){
  struct FstBoxPointer * fb=ArrayList_get(DN.BoxesOp,DN.BoxListCount-1);  
  return fb;
}
/*
** =====================================================================
**    Function      :  DN_getActualObj 
**    Description :    Obtiene el objeto que esta tratando el box
** =====================================================================
*/
struct FstBoxPointer* DN_getActualFstBoxP(void){
  struct Access * access;
  struct BoxList * boxList;
  struct FstBoxPointer * fb;
  if(DN.AccessCount==0) //Estoy en operador
    return DN_OpgetFstBoxP();
  if(DN.ListCount==0)		//Estoy en acceso
    return NULL;
  if(DN.BoxListCount==0)//Estoy en lista
    return NULL;
  
  access=ArrayList_get(DN.accesos,DN.AccessCount-1);
  boxList=ArrayList_get(access,DN.ListCount-1);
  fb=ArrayList_get(&boxList,DN.BoxListCount-1);
  return fb;    
}

/*
** =====================================================================
**    Function      :  DN_Proc 
**    Description :    Procesa el Box Actual y le pasa el valor de la tecla
** =====================================================================
*/
void DN_Proc(uchar tecla){
  struct BlockBoxConstruct* Cbox;
  BOX_State state;
  struct BlockBoxConstruct * pbox_next;
  void * Obj;
  
  if(!DN.BoxActual)			 // Todavia no se cargo el box inicial?
    return;
  
  state=vBox_ProcKey(DN.BoxActual,tecla);



  if(tecla=='k' || (Teclas_TimePass() && !(DN.AccessCount==0 && DN.ListCount==0)) ){					//Exit
    DN_goPrincipal();
    return;
  } 


  if(state==STAY_BOX)
    return;
  
 

  pbox_next=vBox_getNextBlockConstr(DN.BoxActual,tecla);
  
  deleteAndNil(&DN.BoxActual);
  Display_clrScreen(); // borro la pantalla para que quede limpia para el siguiente box
  
  if(pbox_next){							 // Me mantengo en el mismo objeto??
    struct FstBoxPointer* fbp;
    void *Obj;
    uchar num_obj;
    
    if(DN.AccessCount==0)				 //Estoy en op
      fbp= ArrayList_get(DN.BoxesOp,DN.BoxListCount-1);
    else{
      struct Access * access= ArrayList_get(DN.accesos,DN.AccessCount-1);      
      struct BoxList * boxList=ArrayList_get(access,DN.ListCount-1);
      fbp=ArrayList_get(boxList,DN.BoxListCount-1);
    }
    Obj=fbp->Obj;
    num_obj= fbp->num_obj;
    DN.BoxActual= vBoxes_Construct(pbox_next,Obj,num_obj);  
  } else if(DN.AccessCount==0){			//Estoy en op
    if(tecla=='f'){
      DN.BoxListCount=0;
      DN.AccessCount++;
      if(DN.AccessCount<=ArrayList_count(DN.accesos))
        DN.BoxActual= Access_getNextBox(ArrayList_get(DN.accesos,DN.AccessCount-1),DN.ListCount,DN.BoxListCount);
      else
        DN.BoxActual=NULL;
    }else{							 //'r' o 0
      DN.BoxListCount++;
      DN.BoxActual= List_getNextBox(DN.BoxesOp,DN.BoxListCount);  
    }
  } else{
      if(DN.ListCount==0){		//Estoy en ACCESO
        if(tecla=='r')
          DN.AccessCount++;            
        else if(tecla=='f')
          DN.ListCount++;
      } else if(DN.BoxListCount==0) {  //Estoy en Lista
        if(tecla=='r')
          DN.BoxListCount++;
        else if(tecla=='f')
          DN.ListCount++;
      }else{
        //tecla=='r'
        DN.BoxListCount++;  
      }
      // Obtener Box a partir de la nueva posición
      if(DN.AccessCount<=ArrayList_count(DN.accesos))
        DN.BoxActual= Access_getNextBox(ArrayList_get(DN.accesos,DN.AccessCount-1),DN.ListCount,DN.BoxListCount);
  		else
  		  DN.BoxActual=NULL;
  }
  
  if(DN.BoxActual==NULL)		 // Se llego a algun extremo?	 o no se puedo cargar el box
    DN_goPrincipal();  
  
  
}	 





#pragma CODE_SEG DIAGRAMA_NAVEGACION_CODE

