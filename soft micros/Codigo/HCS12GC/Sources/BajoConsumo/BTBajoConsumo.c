#include "BTBajoConsumo.h"
#include "BaseTiempo_protected.h"
#include "RTIEsperaPowUp.h"
#include "BTBajoConsumo_protected.h"


#pragma DATA_SEG BTBajoConsumo_DATA                                            
#pragma CODE_SEG BTBajoConsumo_CODE 
#pragma CONST_SEG DEFAULT

const struct BTBajoConsumoClass BTBajoConsumo = {
    BASE_TIEMPO_CLASS_INITIALIZATION(BaseTiempoClass,
                             BTBajoConsumo,  
                             BaseTiempo,
                             BTBajoConsumo_defConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             BTBajoConsumo_GetTime,
                             BaseTiempo_setTime,
                             BTBajoConsumo_GetDate,
                             TmDt1_SetDate,
                             BaseTiempo_incUnSegundo),
                             BTBajoConsumo_onRTI  
};


static void checkearEnHora(void * _self);

/*
** ===================================================================
**     Method      :  BTBajoConsumo_constructor 
**
**     Description :
** ===================================================================
*/
void BTBajoConsumo_constructor(void * _self)
{
  struct BTBajoConsumo * self = _self; 
  struct BTBajoConsumoClass * class = classOf(_self);
  
  newAlloced(&self->onRTI,&Method,class->onRTI,_self);
  self->interrupciones = 0;
  self->microsegundos = 0;
  self->milisegundos = 0;
  RTIEsperaPowUp_addOnRTIListener(RTIEsperaPowUp_getInstance(),&self->onRTI);
}
/*
** ===================================================================
**     Method      :  BTBajoConsumo_defConstructor
**
**     Description :
** ===================================================================
*/
void BTBajoConsumo_defConstructor(void * self,va_list * args){
  BaseTiempo_defConstructor(self,args);
  BTBajoConsumo_constructor(self);  
}

ulong BTBajoConsumo_interrupcionesRTI(void * _self){
  struct BTBajoConsumo * self = _self;
  return self->interrupciones;
}

void BTBajoConsumo_onRTI(void * _self){
  struct BTBajoConsumo * self = _self;
  self->interrupciones ++;
}

void BTBajoConsumo_GetTime(void * _self,TIMEREC *time){
  struct BTBajoConsumo * self = _self;
  checkearEnHora(_self);
  super_getTime(&BTBajoConsumo,_self,time);
}

void BTBajoConsumo_GetDate(void * _self,DATEREC *date){
  struct BTBajoConsumo * self = _self;
  checkearEnHora(_self);
  super_getDate(&BTBajoConsumo,_self,date);
}

static void checkearEnHora(void * _self){
  struct BTBajoConsumo * self = _self;
  if(self->interrupciones){
    ulong interrupciones;
    long alta;
    long baja;
    ulong ms;
    ulong segundos;
    const ulong intervalo= getIntervaloMicroSeg(ManejadorRTI_getInstance());
    
    ManejadorRTI_disable(ManejadorRTI_getInstance());
    interrupciones = self->interrupciones;
    self->interrupciones=0;
    if(!RTIEsperaPowUp_getConectado(RTIEsperaPowUp_getInstance()))
      ManejadorRTI_enable(ManejadorRTI_getInstance()); 
     
    alta = interrupciones/1000;
    baja = interrupciones%1000;
    //1° los 131ms

    segundos = alta *(intervalo/1000);
    ms = baja *(intervalo/1000);    
      
    //2° los 72uS
    ms += alta*(intervalo%1000) + baja * (intervalo%1000) /1000;
    self->microsegundos += (baja * (intervalo%1000)) %1000;
    //Los microsegundos que llevo acumulados
    ms +=  self->milisegundos + self->microsegundos / 1000;
    self->microsegundos %= 1000;
    //corrijo los ms
    segundos += ms/1000;
    self->milisegundos = ms%1000;
    
    TmDt1_Inc( _self , segundos ); 
  }
}

