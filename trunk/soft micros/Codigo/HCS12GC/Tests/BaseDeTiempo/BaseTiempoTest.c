#include <string.h>
#include <stdlib.h>
#include "BaseTiempoTest.h"
#include "Timer.h"
#include "BaseTiempo.h"

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
bool BaseTiempoTest_test(void * _self){
  struct BaseTiempoTest * self = _self;
  TIMEREC time;
  DATEREC date;
  
  void * baseTiempo = new(&BaseTiempo,2009,1,1,0,0,0);
  
  long i;
  int j;
  for(i=0;i<86400;i++){   //1 dia en segundos
    for(j=0;j<1000;j++)   //1 segundo en milisegundos
      IncTimers(1);
    RlxMTimer_Handler();
  }
  
  TmDt1_GetTime(baseTiempo,&time);
  if(time.Hour!=0)
    return EXIT_FAILURE;
  if(time.Min)
    return EXIT_FAILURE;
  if(time.Sec)
    return EXIT_FAILURE;
  
  TmDt1_GetDate(baseTiempo,&date);
  
  if(date.Day!=2)
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
