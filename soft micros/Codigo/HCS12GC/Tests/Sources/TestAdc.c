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
#include "FTimer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "ADC.h"
#include "Class.h"
#include "ClassADC.h"
#include "ClassSensor.h"

struct TAdc * AD1;
struct TAdc * AD2;

void mostrarADC1(void){
long a;  
  a=_Getter_getVal(AD1);  
//  a/=1000;
  Pasar_Numero(a,0,0);
}

void mostrarADC2(void){
long a;  
  a=_Getter_getVal(AD2); 
//  Pasar_Numero(a,1,0);
  Pasar_Numero(ADC_getTA(),1,0);
}


void main (void){
   
  struct FTimer * timer= newObj(FTimer,(ulong)100,mostrarADC1);
  struct FTimer * timer2= newObj(FTimer,(ulong)1000,mostrarADC2);
  AD1= newObj(TAdc,0);
  AD2= newObj(TAdc,1);
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Teclas_Init();
  Display_Init(); // Inicializacion del display
    
  for(;;){
    WDog1_Clear();
  
  }
}