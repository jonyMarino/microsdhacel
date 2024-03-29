/*
PROGRAMA DE TEST DEL MODULO DE TECLAS:
Hay dos formas de hacer el test:

1_Sin definir _TECLAS:

  Se ingresan directamente las teclas presionadas desde el main
  (o sea no es una entrada desde el exterior, se checkea el soft)
  y se van mostrando mensajes de checkeo.

2_Definiendo _TECLAS:
  El ingreso de las teclas es desde el frente.
*/

#include "Cpu.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "FlashBkp256.h"
#include "PromBkpProtected.h"
#include "LinkedList.h"
#include "IFsh10.h"
#include "TI1.h"
#include "timer_interrupt.h"



//Pruebo si puedo construir todos como macros:
struct LinkedList list={
  INICIALITATION_LINKED_LIST()
};
/*
struct FlashBkpEnFlash manejador={ 
  INITIALIZATION_MANEJADOR_DE_PROM(FlashBkpEnFlash)
};
struct FlashBkpEnFlash bkp={
  INITIALIZATION_PROM_BKP(FlashBkpEnFlash)
};
  */
NEW_FLASH_BKP_256(flash,0x4200);

//fin prueba macros
void Test_on1ms(void * t){


    if(PromBkp_listoParaGrabarOBorrar(&flash))
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void Test_on40ms(void * t){

    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&flash);

}

void main (void){
  int teclas=0;
  char tecla;
  bool Ok1=FALSE;
  bool Ok2=FALSE,Ok3=FALSE;
  struct Timer * timer=new(&Timer,(ulong)5000);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
  add1msListener(Test_on1ms,NULL);  //agregar a la interrupcion del timer cuando dura 1ms
  add40msListener(Test_on40ms,NULL);//agregar a la interrupcion del timer cuando dura 40ms

  WriteWord((word*)0x4002,1);
  PromBkp_deshabilitar(&flash);
  _MANEJADOR_MEMORIA_SET_WORD(&flash,(word*)0x4000,65);
  PromBkp_demorarGrabado(&flash,6000);
    
  for(;;){
    WDog1_Clear();
		  
		  if(!Ok1){
		    
  		  if(_MANEJADOR_MEMORIA_GET_WORD(&flash,(word*)0x4000)!=65){		    
  		    PasarASCII("Err2",0);
  		    while(1);
  		  }
  		  
  		  if(Timer_isfinish(timer))
  		    PromBkp_habilitar(&flash);
  		  
  		  if(!PromBkp_getAGrabar(&flash) && (*(word*)0x4000)==65 && !Ok1){
  		    Ok1=TRUE;
  		    PasarASCII("Ok2 ",1);  
  		  }		 
		  } else if(!Ok2){
		    static bool init=FALSE;
		    
		    if(!init){
		    //  Timer_setTime(timer,2000);  
		      WriteWord((word*)0x4400,33); //grabacion directa en la flash
		    //  PromBkp_deshabilitar(&flash);
		      PromBkp_borrarPagina(&flash,(void*)0x4000);
		      PromBkp_borrarPagina(&flash,(void*)0x4400);
		      while(!LinkedList_Vacia(&flash.super.super.listaDireccionesABorrar))
		        WDog1_Clear(); 
		      init=TRUE;
		    }
		    
		   // if(Timer_isfinish(timer))
  		 //   PromBkp_habilitar(&flash);
		    
		    if(/*!PromBkp_getAGrabar(&flash) &&*/ _MANEJADOR_MEMORIA_GET_WORD(&flash,(word*)0x4000)==-1 && _MANEJADOR_MEMORIA_GET_WORD(&flash,(word*)0x4400)==-1 && !Ok2){
  		    Ok2=TRUE;
  		    init=FALSE;
  		    PasarASCII("Ok3 ",1);  
  		  }		
		     
		  } else if(!Ok3){
		    static bool init=FALSE;
		    
		    if(!init){
		      //Timer_setTime(timer,2000);  
		      //PromBkp_deshabilitar(&flash);
		      PromBkp_borrarPagina(&flash,(void*)0x4200);
		      while(!LinkedList_Vacia(&flash.super.super.listaDireccionesABorrar))
		        WDog1_Clear();
		      _MANEJADOR_MEMORIA_SET_WORD(&flash,(word*)0x4000,56);
		      init=TRUE;
		    }
		    
		    if(Timer_isfinish(timer))
  		    PromBkp_habilitar(&flash);
		    
		    if(!PromBkp_getAGrabar(&flash) && (*(word*)0x4000)==56){
  		    Ok3=TRUE;
  		    PasarASCII("Ok4 ",1);  
  		  }		
		     
		  }
		  
      
  }
}