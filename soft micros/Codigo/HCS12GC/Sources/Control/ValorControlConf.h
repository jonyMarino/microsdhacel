#ifndef _VALORCONTROLCONF_H
#define _VALORCONTROLCONF_H

#include "Configuracion.h"

struct ValorControlConf{
  int valorControlador;
};

//  struct Configuracion super;

#define ValorControlConf_getValorControlador(self)\
 ((struct ValorControlConf*)self)->valorControlador

#define ValorControlConf_setValorControlador(self,valor) \
  CONFIGURACION_SET_WORD( self,valorControlador,ValorControlConf,valor)

#endif
