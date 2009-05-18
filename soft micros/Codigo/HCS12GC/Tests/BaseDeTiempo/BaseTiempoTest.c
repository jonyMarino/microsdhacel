#include <string.h>
#include <stdlib.h>
#include "BaseTiempoTest.h"
#include "Timer.h"
#include "BaseTiempo.h"
#include "Thread.h"
#include "timer_interrupt.h"

void BaseTiempoTest_defCtor(void * self,va_list * args);


#define CAMBIO1

const struct TestCaseClass BaseTiempoTest={
  &TestCaseClass,
  "BaseTiempoTest",
  &TestCase,
  sizeof(struct BaseTiempoTest),
  BaseTiempoTest_defCtor,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};


/*
*/

void * thread;

void pthread_create(void ** _self,void * attr,void*(*pf)(void*),void* args){
  thread = new(&Method,pf,args);
  *_self = thread;    
}


bool BaseTiempoTest_test(void * _self){
  struct BaseTiempoTest * self = _self;
  TIMEREC time;
  DATEREC date;
  
  void * timer = new(&Timer,(ulong)60*1000);
  void * baseTiempo = new(&BaseTiempo,2009,1,1,0,0,0);
  
  
  while(!Timer_isfinish(timer)) {
    TI1ms_OnInterrupt();
    Method_execute(thread);
  }
  
  getTiempo(baseTiempo,&time);
  if(time.Hour!=0)
    return EXIT_FAILURE;
  if(time.Min!=1)
    return EXIT_FAILURE;
  if(time.Sec)
    return EXIT_FAILURE;
  
  getFecha(baseTiempo,&date);
  
  if(date.Day!=1)
    return EXIT_FAILURE;
  if(date.Month!=1)
    return EXIT_FAILURE;
  if(date.Year!=2009)
    return EXIT_FAILURE;
  
  return ERR_OK;
}

/*
*/
void BaseTiempoTest_constructor(void *self){
  struct BaseTiempoTest * _self = self;
  TestCase_constructor(self);
                       
  //tests 
  TESTCASE_ADD_TEST(self,BaseTiempoTest_test);	 
}
/**/
void BaseTiempoTest_defCtor(void * self,va_list * args){
  BaseTiempoTest_constructor(self);  
}
