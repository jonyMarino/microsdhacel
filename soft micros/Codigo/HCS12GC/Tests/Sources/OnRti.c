#include "Cpu.h"
#include "OnRTI.h"
#include "display.h"
#include "LedTest.h"
#include "RTI.h"



__interrupt void OnRTI(void){
static long registro = 0;
  CRGFLG = 128;                        /* Reset interrupt request flag */
  
  registro++;
  
/*  set_Led(0);

  switch(registro){
    case 1:
      set_Led(1); 
      break;
    case 0:
      set_Led(2); 
      break;  
    case 9:
      set_Led(3); 
      break;       
  }
  */      
}