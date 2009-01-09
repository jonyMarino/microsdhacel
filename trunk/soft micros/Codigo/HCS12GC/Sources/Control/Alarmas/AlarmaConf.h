#ifndef _ALARMACONF_H
#define _ALARMACONF_H

#include "Configuracion.h"
#include "RetransmisionConf.h"

struct AlarmaConf {
  struct RetransmisionConf retConf;
  fbyte lazo;
};

// Lazo
#define _AlarmaConf_getLazo(self)\
 CONFIGURACION_GET_BYTE( self,lazo,AlarmaConf)

#define _AlarmaConf_setLazo(self,valor) \
  CONFIGURACION_SET_BYTE( self,lazo,AlarmaConf,valor)
  
//Retransmision
#define  _AlarmaConf_getRetConf(self)\
  ( &((struct AlarmaConf*)self)->retConf ) 

#define _AlarmaConf_getRetLow(self) \
  _RetransmisionConf_getRetLow( _AlarmaConf_getRetConf(self) )  

#define _AlarmaConf_setRetLow(self,valor) \
  _RetransmisionConf_setRetLow( _AlarmaConf_getRetConf(self),valor )  

#define _AlarmaConf_getRetHi(self) \
  _RetransmisionConf_getRetHi( _AlarmaConf_getRetConf(self) )  

#define _AlarmaConf_setRetHi(self,valor) \
  _RetransmisionConf_setRetHi( _AlarmaConf_getRetConf(self),valor )  

#endif
