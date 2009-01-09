#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "PWM.h"
#include "DiagramaNavegacion.h"
#include "Sets.h"
#include "Grabacion.h"
#include "ControlPID.h"
#include "PropNumPV.h"
#include "MessagesOut.h"
#include "TestAlarmaControl.h"
#include "PE_Types.h"
#include "timer_interrupt.h"
#include "RlxMTimer.h"
#include "TI1.h"
#include "RamSimulaFlash.h"

struct TestAlarmaControl test;

NEW_RAM_SIMULA_FLASH(flash);  
struct ManejadorMemoria * pFlash = &flash; 



void main (void){
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
 // PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  clrReg8Bits(COPCTL, 71); // kill the dog!
   
  newAlloced(&test,&TestAlarmaControl);
  
  TestCase_runTest(&test);
  
  for(;;){
  }
}
