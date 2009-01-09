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


void main (void){
  int teclas=0;
  char tecla;
  struct Timer * timer=newObj(Timer,(ulong)30); 
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  
    
  for(;;){
    WDog1_Clear();
    tecla=get_key();

    if(tecla=='u'){
      PasarASCII(" uP ",0); //texto fijo
      teclas++;
    }

    if(tecla=='d'){
      PasarASCII("down",0); //texto fijo
      teclas++;
    }

    if(tecla=='r'){
      PasarASCII("enter",0);
      teclas++;
    }

    if(tecla=='k'){
      PasarASCII("eSc ",0); //texto fijo
      teclas++;
    }

    if(tecla=='f'){
      PasarASCII("MAntEnidA",0); //texto fijo
      teclas++;      
    }

    if(tecla=='s'){
      PasarASCII("StoP",0); //texto fijo
      teclas++;      
    }
    
    
    if(Teclas_TimePass() && Timer_isfinish(timer)){
      PasarASCII("tiEMPo",0); //texto fijo     
      teclas=0; 
      Timer_Restart(timer);
    }
    

    
    if(Timer_isfinish(timer)){
      
      Pasar_Numero(teclas,1,0);
      Timer_Restart(timer);
    }

      
  }
}