#ifndef _BASETIEMPO_DS1307_H
#define _BASETIEMPO_DS1307_H


#include "TmDt1.h"
#include "IBaseTiempo.h"

#include "RlxMTimer.h"



struct BaseTiempoDS1307 {
  struct IBaseTiempo super;
};

  
extern const struct IBaseTiempoClass BaseTiempoDS1307;


#endif
