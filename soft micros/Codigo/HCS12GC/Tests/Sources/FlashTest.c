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
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"

volatile const word a @0x4019=0;

void main (void){
  int teclas=0;
  char tecla;
  bool Ok1=FALSE;
  bool Ok2=FALSE;
  struct Timer * timer=newObj(Timer,(ulong)5000); 
  struct TAdc * AD1 = newObj(TAdc,0);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  Grabacion_Init();
  
  EscribirWord(0x4019,1);
  if(IFsh10_getWord(0x4019)!=1){  
		PasarASCII("Err1",0);
		while(1);
  }else
    PasarASCII("Ok1 ",1);  
  
  Grabacion_Disable();
  EscribirWord(0x4000,65);
  Grabacion_DelaySave(6000);
    
  for(;;){
    WDog1_Clear();
		  
		  if(!Ok1){
		    
  		  if(IFsh10_getWord(0x4000)!=65){		    
  		    PasarASCII("Err2",0);
  		    while(1);
  		  }
  		  
  		  if(Timer_isfinish(timer))
  		    Grabacion_Enable();
  		  
  		  if(!Fsh_to_save() && IFsh10_getWord(0x4000)==65 && !Ok1){
  		    Ok1=TRUE;
  		    PasarASCII("Ok2 ",1);  
  		  }		 
		  } else if(!Ok2){
		    static bool init=FALSE;
		    
		    if(!init){
		      Timer_setTime(timer,2000);  
		      WriteWord(0x4400,33); //grabacion directa en la flash
		      Grabacion_Disable();
		      Grabacion_BorrarPag(0x4000); 
		      Grabacion_BorrarPag(0x4400);
		      init=TRUE;
		    }
		    
		    if(Timer_isfinish(timer))
  		    Grabacion_Enable();
		    
		    if(!Fsh_to_save() && IFsh10_getWord(0x4000)==-1 && IFsh10_getWord(0x4400)==-1 && !Ok2){
  		    Ok2=TRUE;
  		    PasarASCII("Ok3 ",1);  
  		  }		
		     
		  }
      
  }
}