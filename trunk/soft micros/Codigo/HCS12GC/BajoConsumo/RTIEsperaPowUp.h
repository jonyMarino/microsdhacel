#ifndef _RTIESPERAPOWUP_H
#define _RTIESPERAPOWUP_H


#include "ManejadorRTI.h"


struct RTIEsperaPowUp {
  struct Object super;
//%-  private:
//  struct ManejadorRTI mRTI;

  unsigned long interrupciones;
  struct MethodContainer listenersSalirBajoConsumo;
  struct MethodContainer listenersBajoConsumo;     
  struct Method onRTI;
  struct Method onPowDown;
  bool conectado;
  uint despierto;
};

void * RTIEsperaPowUp_getInstance(void);

//%+  public:
void RTIEsperaPowUp_addOnSalirListener(void * _self,struct Method * metodo);
void RTIEsperaPowUp_addOnBajoConsumoListener(void * _self,struct Method * metodo);
void RTIEsperaPowUp_addOnLuegoEntrarBajoConsumoListener(void * _self,struct Method * metodo);
void RTIEsperaPowUp_addOnRTIListener(void * _self,struct Method * metodo);
void RTIEsperaPowUp_deleteOnRTIListener(void * _self,struct Method * metodo);

ulong RTIEsperaPowUp_getSegundosEsperados(void * _self);

uint RTIEsperaPowUp_getMSegundosEsperados(void * _self);

bool RTIEsperaPowUp_getConectado(void * _self);

void RTIEsperaPowUp_despertar(void * _self);

void RTIEsperaPowUp_dormir(void * _self);
     
#endif
