#ifndef _CLASS_LONG_SENSOR_H
#define _CLASS_LONG_SENSOR_H

#include "Object.h"
#include "stdtypes.h"

struct LongSensorClass{
  struct Class _class;
  long (*_getVal)(void *);  // Obtiene valor del sensor
  uchar (*_isnew)(void *);  // marca si hay algun valor nuevo
};

#define _LSgetVal(sensor) \
          ((*(struct TLongSensor **)sensor)->_getVal(sensor))

#define _LSisnew(sensor) \
          ( (*((*(struct TLongSensor **)sensor)->_isnew))(sensor))

uchar LS_isnew(void *);

long LS_getVal(void *);

#endif