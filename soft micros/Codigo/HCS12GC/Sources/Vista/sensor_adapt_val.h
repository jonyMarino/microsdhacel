#ifndef _SENSOR_ADAPT_VAL_H
#define _SENSOR_ADAPT_VAL_H

#include "Sensor.h"

int adaptValOut(const void * sensor,int val);
int adaptValIn(const void * sensor,int val); 

int adaptValOutLong(const void * sensor,long val);
long adaptValInLong(const void * sensor,int val); 


#endif