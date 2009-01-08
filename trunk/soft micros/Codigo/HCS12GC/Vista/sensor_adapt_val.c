#include "sensor_adapt_val.h"
#include "Math.h"


int adaptValOut(const void * sensor,int val){
  return val / pow10(_getDifDecView(sensor));

}

int adaptValIn(const void * sensor,int val){
  return val * pow10(_getDifDecView(sensor));
}


int adaptValOutLong(const void * sensor,long val){
  return val / pow10(_getDifDecView(sensor));

}

long adaptValInLong(const void * sensor,int val){
  return val * pow10(_getDifDecView(sensor));
}