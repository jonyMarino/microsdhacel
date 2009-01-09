#ifndef _CONFIGURACION_H
#define _CONFIGURACION_H

#include "ManejadorMemoria.h"

//struct Configuracion{
//};

/**** Definicion del unico manejador de memoria ****/
extern struct ManejadorMemoria * const pFlash;
#define pManejadorDeMemoria pFlash
/*********/


#define CONFIGURACION_SET_WORD(self,atributo,subclass,valor)\
  _MANEJADOR_MEMORIA_SET_WORD( pManejadorDeMemoria,  \
                               &( (struct subclass*)self)->atributo,      \
                               valor                                               \
                              )

#define CONFIGURACION_GET_WORD( self,atributo,subclass) \
  _MANEJADOR_MEMORIA_GET_WORD( pManejadorDeMemoria,  \
                               &( (struct subclass*)self)->atributo      \
                              )


#define CONFIGURACION_SET_BYTE(self,atributo,subclass,valor)\
  _MANEJADOR_MEMORIA_SET_BYTE( pManejadorDeMemoria,  \
                               &( (struct subclass*)self)->atributo,      \
                               valor                                               \
                              )
#define CONFIGURACION_GET_BYTE( self,atributo,subclass) \
  _MANEJADOR_MEMORIA_GET_BYTE( pManejadorDeMemoria,  \
                               &( (struct subclass*)self)->atributo      \
                              )
#endif