#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Method.h"
#include "timer_interrupt.h"
#include "Adc.hpp"
#include "IAdc.hpp"
#include "Termometro.hpp"
#include "RamSimulaFlash.h"
#include "ManejadorMemoria.h"
#include "OutputStream.hpp"
#include "Cpu.h"
#include "object_r.h"
#include "Object.h"
#include <termio.h>

void imprimir(void* a);

struct RamSimulaFlash ram;

class inicio {
  public:
    inicio(){ 
      PE_low_level_init();
      TERMIO_Init(); 
      EnableInterrupts;
      newAlloced(&ram,&RamSimulaFlash);
      
  }
}ini;


char i;
const NEW_METHOD(impresion,imprimir,NULL);

OutputStream os; 
 
Termometro termometro(*(struct ManejadorMemoria*)&ram/*,SensorTermoPT100 &sensor*/); 


void imprimir(void* a){
 #if CANTIDAD_CANALES == 1
  termometro.sensor0.print(os);
  os.write(" ");
 #else
  termometro.sensor0.print(os);
  os.write(" ");
  termometro.sensor1.print(os);
  os.write(" ");
 #endif  
}


void main(void) {
  
   os.write("comenzando...");
  //ram=new RamSimulaFlash;
  //Adc adc(0);
  //SensorTermoPT100 sensor(adc,sensor_config[0],*(struct ManejadorMemoria*)&ram);
  
   
  termometro.sensor0.addOnNuevoValorListener(&impresion);
  for(;;) {
    _FEED_COP(); /* feeds the dog */
    termometro.mainLoop();
    //if(termometro.sensor[0].checkADC()){
     // termometro.sensor[0].sensor.print(os);
      //os.write(" ");
    //}
  } /* loop forever */
  /* please make sure that you never leave main */
}
  