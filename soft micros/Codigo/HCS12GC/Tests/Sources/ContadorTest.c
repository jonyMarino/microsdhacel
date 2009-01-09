#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "Grabacion.h"
#include "DiagramaNavegacion.h"
#include "PropNumerica.h"
#include "BoxProp.h"
#include "Sets.h"

#pragma CONST_SEG PARAMETERS_PAGE
#pragma CONST_SEG DEFAULT

void main (void){

  char tecla; 
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/  
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display

//  DN_Init(&CBox_Pri);
//  Sets_Init();  
//  Sets_AddBoxes();

 															 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);
  }
}