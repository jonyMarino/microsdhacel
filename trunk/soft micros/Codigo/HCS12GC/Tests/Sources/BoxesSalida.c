/* BoxesSalida.c*/
#include <stddef.h>

#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "PWM_Class.h"
#include "DiagramaNavegacion.h"
#include "PWM_Hmi.h"
#include "PropNumerica.h"
#include "PropTextual.h"
#include "BoxProp.h"
#include "Sets.h"
#include "FTimer.h"
#include "DobleList.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const TConfPWM config;
#pragma CONST_SEG DEFAULT
struct PropNum Priprop;
struct MessageOut msj1;
Message Msj1,Msj2,Msj3,Msj4;
struct FTimer * timer;

const struct ConstPropNum T_ParAjGanT={
    PWM_getDuty,NULL,NULL,NULL,PropNum,"Pri ",2
};


  	

const struct BlockConstBoxProp CBox_Pri2={
      BoxProp,							/* funcion que procesa al box*/
      &T_ParAjGanT,
      NULL						
};


const struct BlockConstBoxPri1c CBox_Pri={
      BoxPri1c,							/* funcion que procesa al box*/
      &Priprop,
      &msj1							
};

void ChangeMessage(void){
  MessageOut_DeleteMessage(&msj1,Msj2);  
  MessageOut_DeleteMessage(&msj1,Msj3);
  MessageOut_DeleteMessage(&msj1,Msj4);
  Msj4= MessageOut_AddMessage(&msj1,"bUEn");
  Msj3= MessageOut_AddMessage(&msj1,"un  ");
//  Timer_Stop(timer);
  
}


void main (void){

  char tecla; 
  struct PropNum* prop;
  struct BoxCondl *_box;
  struct Timer * timer2;
  int val;
  struct PWM * pwm;
  struct DobleList * lst;
  int a=1,b=2,c=3,d=4;
  int *pa=&a,*pb=&b,*pc=&c,*pd=&d;
  struct NodoDbl * n1,*n2,*n3;
  
  extern const struct ConstPropTxt ParPeriodo;
  extern const struct ConstrGetterNum GetterPot;
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  PWM_Init();
  
/*  PRUEBA DE LISTA */
  lst = newObj(DobleList);
  n1=DobleList_InsertFirst(lst,pa);
  n2=DobleList_InsertFirst(lst,pb);   
  n3=DobleList_InsertFirst(lst,pc);
  
  DobleList_getDato(lst,0,&pc);
  if((*pc)!=c)
    while(1);
  DobleList_DeleteNodo(lst,n3);
    
  DobleList_getDato(lst,2,&pc);
  if(pc!=NULL)
    while(1);
  n3=DobleList_InsertFirst(lst,pd);
  
  DobleList_getDato(lst,2,&pc);
  if(*pc!=a)
    while(1);
  DobleList_DeleteNodo(lst,n1); 
  DobleList_DeleteNodo(lst,n2);
  
  DobleList_getDato(lst,0,&pc);
  if(*pc!=d)
    while(1);
  
  
/* FIN: PRUEBA DE LISTA*/

  pwm = newObj(PWM,&config,0);
//  timer = newObj(FTimer,(ulong)14000,ChangeMessage);
  timer2 = newObj(Timer,(ulong)14000);
  newAllocObj(&msj1,MessageOut);
  newAllocObj(&Priprop,PropNum,&T_ParAjGanT,pwm);
  
  Msj1=MessageOut_AddMessage(&msj1,"tESt");
  Msj2=MessageOut_AddMessage(&msj1,"un  ");
  Msj3=MessageOut_AddMessage(&msj1,"ES  ");
  Msj4=MessageOut_AddMessage(&msj1,"EStE");
  
  
  BoxPri1c_ShowProp(&ParPeriodo,pwm);
   
  DN_Init(&CBox_Pri);
  Sets_Init();
  PWM_Hmi_Add(pwm,0);

  Sets_AddBoxes();

 	_Salida_setDuty(pwm,500);	
 														 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);
    if(timer2 && Timer_isfinish(timer2)){
      deleteObj(&timer2);
      ChangeMessage();
    }
  }
}