#ifndef _ADAPTSALIDACONF_H
#define _ADAPTSALIDACONF_H

#include "Configuracion.h"


struct AdaptSalidaConf{
//  struct Configuracion super;
// %-  
 int histeresis; 
 fbyte tipoSalida;
};


#define AdaptSalidaConf_getHisteresis(self) ((struct AdaptSalidaConf*)self)->histeresis
#define AdaptSalidaConf_setHisteresis(self,valor) \
  CONFIGURACION_SET_WORD( self,histeresis,AdaptSalidaConf,valor)
    
#define AdaptSalidaConf_getTipoSalida(self) ((struct AdaptSalidaConf*)self)->tipoSalida
#define AdaptSalidaConf_setTipoSalida(self,valor) \
  CONFIGURACION_SET_BYTE( self,tipoSalida,AdaptSalidaConf,valor)


#endif
