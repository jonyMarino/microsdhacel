#include <string.h>
#include <stdlib.h>
#include "Timer.h"
#include "BaseTiempo.h"
#include "Thread.h"
#include "Method.h"
#include "timer_interrupt.h"
#include "BaseTiempoDS1307.h"
#include "BaseTiempoDS1307Test.h"
#include "PE_Error.h"


void BaseTiempoDS1307Test_defCtor(void * self,va_list * args);


#define CAMBIO1


const struct TestCaseClass BaseTiempoDS1307Test={
  &TestCaseClass,
  "BaseTiempoDS1307Test",
  &TestCase,
  sizeof(struct BaseTiempoDS1307Test),
  BaseTiempoDS1307Test_defCtor,
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


bool BaseTiempoDS1307Test_test(void * _self){
  struct BaseTiempoDS1307Test * self = _self;
  TIMEREC time;
  DATEREC date;
  
  void * timer = new(&Timer,(ulong)60*1000);
  void * baseTiempo = new(&BaseTiempoDS1307);
  
  setTiempo(baseTiempo,1,0,10);
  setFecha(baseTiempo,2009,3,2);
  
  while(!Timer_isfinish(timer))
    Method_execute(thread);
  
  getTiempo(baseTiempo,&time);
  if(time.Hour!=1)
    return EXIT_FAILURE;
  if(time.Min!=1)
    return EXIT_FAILURE;
  if(time.Sec!=10)
    return EXIT_FAILURE;
  
  getFecha(baseTiempo,&date);
  
  if(date.Day!=2)
    return EXIT_FAILURE;
  if(date.Month!=3)
    return EXIT_FAILURE;
  if(date.Year!=2009)
    return EXIT_FAILURE;
  
  return ERR_OK;
}

/*
*/
void BaseTiempoDS1307Test_constructor(void *self){
  struct BaseTiempoDS1307Test * _self = self;
  TestCase_constructor(self);
                       
  //tests 
  TESTCASE_ADD_TEST(self,BaseTiempoDS1307Test_test);	 
}
/**/
void BaseTiempoDS1307Test_defCtor(void * self,va_list * args){
  BaseTiempoDS1307Test_constructor(self);  
}
