#include <assert.h>
#include "FTimer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "Grabacion.h"
#include "PropNumerica.h"
#include "BoxProp.h"
#include "Sets.h"
#include "page_save.h"
#include "MethodContainer.h"
#include "FunctionContainer.h"
#include "OnPowDown.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"

#pragma CONST_SEG PARAMETERS_PAGE
#pragma CONST_SEG DEFAULT

struct FTimer *_timer;

void mesaggeOk2(void){
  PasarASCII("Ok 2",1);
};

void setLed1(void){
  PutValLed(1,0);
}
void setLed3(void * a){
  PutValLed(1,2);
}

void mesaggeErr(void){
  PasarASCII("Err3",0);
};

NEW_FLASH_BKP_EN_FLASH(flash,0x4400);

void main (void){

  char tecla; 
  uchar err;
  struct FncContainer  * FC=new(FncContainer);
  struct MethodContainer * MC=new(&MethodContainer);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/  
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  add1msListener(DpyAndSwitch,NULL);
//  DN_Init(&CBox_Pri);
//  Sets_Init();  
//  Sets_AddBoxes();

 	err=PageSave_open("TEST");														 
  if(!err)		// err deberia ser TRUE(no se encuentra)
    assert(1);  
  
  PageSave_ClrAll();			 // borrar para resetear pos
  while(PromBkp_grabacionOBorradoEnEspera(&flash))
    WDog1_Clear();
  PageSave_WriteOpen("TEST",4*sizeof(int));
  err|=PageSave_put(1);
  err|=PageSave_put(2);
  err|=PageSave_put(3);
  err|=PageSave_put(4);
  PageSave_WriteOpen("TEST1",2*sizeof(int));  
  err|=PageSave_put(3);
  err|=PageSave_put(4);
  if(err)
    assert(1);
  	 
  err=PageSave_open("TEST");														 
  if(!err){
    uint a;
    err|=PageSave_get(&a);
    if(a!=1)
      assert(2);
    err|=PageSave_get(&a);
    if(a!=2)
      assert(3);
    err|=PageSave_get(&a);
    if(a!=3)
      assert(4);
    err|=PageSave_get(&a); 
    if(a!=4)
      assert(5);     
  }else
    assert(6);// err deberia ser FALSE( se encuentra)
  
  if(err)
    assert(6);
  
  err=PageSave_open("TEST1");														 
  if(!err){
    uint a;
    PageSave_get(&a);
    if(a!=3)
      assert(7);
    PageSave_get(&a);
    if(a!=4)
      assert(8);
  }else
    assert(9);  // err deberia ser TRUE(no se encuentra)

  PasarASCII("OK 1",0);
  
  _timer=new(&FTimer,(ulong)1000,mesaggeErr);
  
  
  
  FncContainer_Add(FC,mesaggeOk2);
  FncContainer_Add(FC,setLed1);
  FncContainer_Execute(FC);
  MethodContainer_add(MC,new(&Method,Timer_Stop,_timer)); // Evito que aparesca mensaje de error
  MethodContainer_add(MC,new(&Method,delete,FC));		 // Elimino FC
  MethodContainer_execute(MC);
  
  OnPowDown_AddMethod(setLed3,NULL);
  OnPowDown_AddMethod(delete,MC);
  OnPowDown_OnPowDown();
  
  
  
  
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    
//    DN_Proc(tecla);
  }
}