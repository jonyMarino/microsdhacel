/*
PROGRAMA DE TEST DE MEMORIA DINAMICA:
El resultado es igual que el del display anterior pero se utiliza memoria dinamica 
para optimizar el uso de memoria.
Se van mostrando los textos comentados abajo.
*/

#include "Cpu.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include <stdlib.h>


void main (void){
  struct Timer * t1; 
  struct Timer *t2;
  struct Timer *t3;
  struct Timer *t4;
  struct Timer *t5;
  struct Timer t6;
  char * mem[200];
  ulong cuenta;
  byte i;
   
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Timer_Construct(&t6,120000);
  for(i=0;i<50;i++){
    mem[i]=malloc(sizeof(char));  
    free(mem[i/10]);
  }
  t1=malloc(sizeof(struct Timer));
  
  t2=malloc(sizeof(struct Timer));
  free(t1);
  t3=malloc(sizeof(struct Timer));
  t4=malloc(sizeof(struct Timer));
  t4=realloc(t4,sizeof(struct Timer)*2); //duplico la memoria innecesariamente 
  t5=malloc(sizeof(struct Timer));
  free(t4);
  t1=malloc(sizeof(struct Timer));
  t4=malloc(sizeof(struct Timer));
  
  cuenta=Timer_getCuenta(&t6);
  if(cuenta>2)
    while(1);
  
  Timer_Construct(t1,1000);
  Timer_Construct(t2,4000);
  Timer_Construct(t3,6000);
  Timer_Construct(t4,8000);
  Timer_Construct(t5,10000);
  
  Display_Init(); // Inicializacion del display
    
  for(;;){
    WDog1_Clear();
    if(Timer_isfinish(t1)){
      PasarASCII("Ok88",0); //texto fijo
      Timer_Destruct(t1);
      free(t1);
    }
    if(Timer_isfinish(t2)){
      Timer_Destruct(t2);
      PasarASCII("P.8o.8",1);  //texto fijo con punto
      free(t2);
    }
    if(Timer_isfinish(t3)){
      Timer_Destruct(t3);
      Pasar_Numero(2568,1,0);   //paso numero de 4 cifras
      free(t3);
    }
    if(Timer_isfinish(t4)){
      Timer_Destruct(t4);
      Pasar_Numero(25681,0,1);   //paso numero de 5 cifras
      free(t4);
    }
    if(Timer_isfinish(t5)){
      Timer_Destruct(t5);
       PasarASCII("P.dhAcEL",0);  //texto scroll con punto
       free(t5);
    }
    if(Timer_isfinish(&t6)){
      Timer_Destruct(&t6);
  //     PasarASCII("V 000.7",1);  //texto scroll con punto
    }
      
      
  }
}