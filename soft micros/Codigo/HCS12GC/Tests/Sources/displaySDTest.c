/*
PROGRAMA DE TEST DEL DISPLAY:
Se van mostrando los textos comentados abajo.
Se ve que el doble Scrolling no funciona bien si se quiere modificar.
*/

#include "Cpu.h"
#include "Timer.h"
#include "display.h"
#include "Display1.h"
#include "Display2.h"
#include "bits2ULN.h"
#include "bits5ULN.h"
#include "WDog1.h"
#include "Class.h"
#include "ComunLeds.h"


void main (void){
  struct Timer * t1=newObj(Timer,(ulong)1000); 
  struct Timer *t2=newObj(Timer,(ulong)4000);
  struct Timer *t3=newObj(Timer,(ulong)6000);
  struct Timer *t4=newObj(Timer,(ulong)8000);
  struct Timer *t5=newObj(Timer,(ulong)10000);
  struct Timer *t6=newObj(Timer,(ulong)12000);
  struct Timer *t7=newObj(Timer,(ulong)18000); 
  int a = 1;
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Display_Init(); // Inicializacion del display
  PutValLed(1,0);  
  
  
 //lrReg8Bits(TIE, 1);
  /*ComunLeds_SetVal();
  
  for(;;){
    WDog1_Clear();
    Display2_PutVal(a);
   
    if(Timer_isfinish(t1)){
      a<<=1;
      Timer_Restart(t1);
      if(a==0)
        a=1;
    }
  //  clrReg8Bits(DDRA, DDRA_BIT0_MASK);
    setReg8Bits(PORTA,0);
    bits5ULN_PutVal(0);
  }
  
    */
    
  for(;;){
    WDog1_Clear();
    if(t1 && Timer_isfinish(t1)){
      PasarASCII("Ok88",0); //texto fijo
      deleteObj(&t1);
    }
    if(t2 &&Timer_isfinish(t2)){
      deleteObj(&t2);
      PasarASCII("P.8o.8",1);  //texto fijo con punto
    }
    if(t3 &&Timer_isfinish(t3)){
      deleteObj(&t3);
      Pasar_Numero(2568,1,0);   //paso numero de 4 cifras
    }
    if(t4 &&Timer_isfinish(t4)){
      deleteObj(&t4);
      Pasar_Numero(25681,0,1);   //paso numero de 5 cifras
    }
    if(t5 &&Timer_isfinish(t5)){
      deleteObj(&t5);
       PasarASCII("P.dhAcEL",0);  //texto scroll con punto
    }
    if(t6 &&Timer_isfinish(t6)){
      deleteObj(&t6);
       PasarASCII("V 000.7",1);  //texto scroll con punto
    }
    if(t7 &&Timer_isfinish(t7)){
      deleteObj(&t7);
       PasarASCII("JoniM",1);  //texto scroll con punto
    }  
      
  }
  
}