#include "ClassLongSensor.h"

uchar LS_isnew(void * self){
  struct TLongSensor ** sensor=self;
  return (*((*sensor)->_isnew))(sensor);
}

long LS_getVal(void * self){
  struct TLongSensor ** sensor=self;
  return (*((*sensor)->_getVal))(sensor);
}