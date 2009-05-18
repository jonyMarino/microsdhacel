#include "IO_Map.h"
#include "Object.h"
#include "TestCase.h"
#include "PE_Types.h"
#include "RamSimulaFlash.h"


extern TEST_OBJECT;

void * test;

NEW_RAM_SIMULA_FLASH(flash);  
struct ManejadorMemoria * pFlash = &flash; 



void main (void){
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
 // PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  clrReg8Bits(COPCTL, 71); // kill the dog!
   
  test = new(&TEST_OBJECT);
  
  TestCase_runTest(test);
  
  for(;;){
    
  }
}
