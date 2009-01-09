#include "Cpu.h"
#include "RamSimulaFlash.h"
#include "TestRTIEsperaPowUp.h"

struct TestRTIEsperaPowUp test;

NEW_RAM_SIMULA_FLASH(flash);  
struct ManejadorMemoria * pFlash = &flash; 


void main (void){
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/    
  clrReg8Bits(COPCTL, 71); // kill the dog!
   
  newAlloced(&test,&TestRTIEsperaPowUp);
  
  TestCase_runTest(&test);
 
  for(;;);
}