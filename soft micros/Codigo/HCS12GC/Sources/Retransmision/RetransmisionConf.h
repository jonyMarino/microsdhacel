#ifndef _RETRANSMISIONCONF_H
#define _RETRANSMISIONCONF_H

#include "Configuracion.h"

struct RetransmisionConf {
  int retLow;
  int retHi;
};


//RetLow
#define  _RetransmisionConf_getRetLow(self) ((struct RetransmisionConf*)self)->retLow

#define  _RetransmisionConf_setRetLow(self,valor) \
  CONFIGURACION_SET_WORD( self,retLow,RetransmisionConf,valor)


//RetHi
#define  _RetransmisionConf_getRetHi(self) ((struct RetransmisionConf*)self)->retHi

#define  _RetransmisionConf_setRetHi(self,valor) \
  CONFIGURACION_SET_WORD( self,retHi,RetransmisionConf,valor)



#endif
