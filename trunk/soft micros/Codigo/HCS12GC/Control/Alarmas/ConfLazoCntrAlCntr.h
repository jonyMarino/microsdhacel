#ifndef _CONFLAZOCNTRALCNTR_H
#define _CONFLAZOCNTRALCNTR_H

#include "Configuracion.h"
#include "ConfLazoCntrlAlSen.h"

struct ConfLazoCntrAlCntr {
  struct ConfLazoCntrlAlSen super;
  fbyte control;
};


//Control
#define _ConfLazoCntrAlCntr_getControl(self) ((struct ConfLazoCntrAlCntr*)self)->control
#define _ConfLazoCntrAlCntr_setControl(self,valor) \
  CONFIGURACION_SET_BYTE( self,control,ConfLazoCntrAlCntr,valor)

#endif
