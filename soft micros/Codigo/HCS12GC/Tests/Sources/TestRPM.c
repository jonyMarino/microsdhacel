#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "CapturadorTI7.h"
#include "thread_adjuntable.h"
#include "SensorRPM.h"
#include "CapturadorSimulado.h"
#include "CapturadorPT2.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const SensorRpmConf config=DEFAULT_SENSOR_RPM_CONF;
#pragma CONST_SEG DEFAULT
struct Timer * timer;

//#define _ENTRADA_SIMULADA

#ifdef _ENTRADA_SIMULADA
  #define GET_INSTANCE() CapturadorSimulado_getInstancia()
#else
  #define GET_INSTANCE() CapturadorPT2_getInstancia()
#endif

struct Capturador * cap;
struct ThreadAdjuntable mainThread;
struct SensorRpm sensorRpm;

void main (void){
  timer= newObj(Timer,(ulong)500); 
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  Grabacion_Init();
  
  newAllocObj(&mainThread,ThreadAdjuntable);
  cap=GET_INSTANCE();
  #ifdef _ENTRADA_SIMULADA
  CapturadorSimulado_setMicroSegundos(cap,100000000);
  CapturadorSimulado_setPulsos(cap,2);
  #endif
  {
    void * adjuntador= ThreadAdjuntable_getAdjuntador(&mainThread);
    newAllocObj(&sensorRpm,SensorRpm,adjuntador,1000,cap,&config,"SEn rPM");
    deleteObj(&adjuntador);
  }
 	
 	  														 
  for(;;){
    WDog1_Clear();
    
    
    
    if(Timer_isfinish(timer)){
      Timer_Restart(timer);
      _GetterPrint(&sensorRpm,1);
    //  Pasar_Numero(Capturador_getMicroSegundos(cap)/1000,0,0);
    //  Pasar_Numero(Capturador_getPulsos(cap),1,0);
     // CapturadorSimulado_setPulsos(cap,CapturadorSimulado_getPulsos(cap)+1);
    }

    //Eventos
    MethodContainer_Execute(&mainThread);
  }
}