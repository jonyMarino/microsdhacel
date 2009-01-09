/*
PROGRAMA DE TEST DEL DISPLAY:
Se van mostrando los textos comentados abajo.
Se ve que el doble Scrolling no funciona bien si se quiere modificar.
*/

#include "Cpu.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "Class.h"
#include "ArrayList.h"
#include "Comparator.h"
#include <stddef.h>

struct TimerComparatorByTime{
  struct Comparator _base;
  ulong time;  
};

bool TimerComparatorByTime_Equals(void * self,void * timer){
  struct TimerComparatorByTime * _self = self;
  struct Timer * _timer=timer;
  
  return _self->time==Timer_getTime(_timer);
    
}

struct TComparator TableTimerComparatorByTime={
  sizeof(struct TimerComparatorByTime),
  NULL,
  NULL,
  NULL,
  TimerComparatorByTime_Equals,
  NULL
};


const void *const TimerComparatorByTime =&TableTimerComparatorByTime;


void main (void){
  struct Timer * t1=newObj(Timer,(ulong)1000); 
  struct Timer *t2=newObj(Timer,(ulong)4000);
  struct Timer *t3=newObj(Timer,(ulong)6000);
  struct Timer *t4=newObj(Timer,(ulong)8000);
  struct Timer *t5=newObj(Timer,(ulong)10000);
  struct Timer *t6=newObj(Timer,(ulong)12000);
  struct Timer *t7=newObj(Timer,(ulong)18000); 
  struct ArrayList * array=newObj(ArrayList);
  struct TimerComparatorByTime * comparator= newObj(TimerComparatorByTime); 
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  Display_Init(); // Inicializacion del display
  PutValLed(1,0);  
  for(;;){
    WDog1_Clear();

      if(ArrayList_get(array,0)){        
        PasarASCII("Err get",0); //texto fijo  
        break;
      }
      //agrego      
      ArrayList_Add(array,t1);
      ArrayList_Add(array,t2);
      
      if(ArrayList_get(array,0)!=t1 || ArrayList_get(array,1)!=t2){        
        PasarASCII("Err Add o get",0); //texto fijo  
        break;
      }
      
      ArrayList_Put(array,t3,1);
      
      if(ArrayList_get(array,0)!=t1 
      || ArrayList_get(array,1)!=t3
      || ArrayList_get(array,2)!=t2){        
        PasarASCII("Err Add o get",0); //texto fijo  
        break;
      }
      
      comparator->time=6000;  //igual a t3
      
      if(ArrayList_search(array,comparator)!=t3){
        PasarASCII("Err Search 1",0); //texto fijo  
        break;        
      }
      
      comparator->time=4564645;  //Tiempo no existente 
      
      if(ArrayList_search(array,comparator)!=NULL){
        PasarASCII("Err Search 2",0); //texto fijo  
        break;        
      }
      
      PasarASCII("Ok  ",0); 
      
      break;
      

  }
  
  for(;;)
    WDog1_Clear();
}