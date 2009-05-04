#include "BaseTiempoDS1307.h"




void BaseTiempoDS1307_defConstructor(void * self,va_list * args);
void BaseTiempoDS1307_getTiempo(void * self,TIMEREC *time);
byte BaseTiempoDS1307_setTiempoValidado(void * _self,byte horas,byte min,byte segs);
void BaseTiempoDS1307_getFecha(void * self,DATEREC *date);
byte BaseTiempoDS1307_setFechaValidada(void * self,word year,byte month,byte day);
bool BaseTiempoDS1307_getConfigurado(void * _self);

const struct IBaseTiempoClass BaseTiempoDS1307 = {
    I_BASE_TIEMPO_CLASS_INITIALIZATION(IBaseTiempoClass,
                             BaseTiempoDS1307,  
                             IBaseTiempo,
                             BaseTiempoDS1307_defConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             BaseTiempoDS1307_getTiempo,
                             BaseTiempoDS1307_setTiempoValidado,
                             BaseTiempoDS1307_getFecha,
                             BaseTiempoDS1307_setFechaValidada,
                             BaseTiempoDS1307_getConfigurado
                             )  
};



/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_constructor (bean TimeDate)
**
**     Description :
** ===================================================================
*/
void BaseTiempoDS1307_constructor(void * _self)
{
  struct BaseTiempoDS1307 * self = _self;
  /*struct BaseTiempoDS1307Class * class = classOf(_self);
  TmDt1_Constructor(_self,Year,Month,Day,Hour,Min,secs);
  self->configurado = FALSE;
  
  newAlloced(&self->timer,&RlxMTimer,(ulong)1000,class->inc1Segundo,_self);
  if(!start)
    Timer_Stop(&self->timer);
    */
}
/*
** ===================================================================
**     Method      :  TmDt1_DefConstructor (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void BaseTiempoDS1307_defConstructor(void * self,va_list * args){
  BaseTiempoDS1307_constructor(self);  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_setTiempo
** ===================================================================
*/
byte BaseTiempoDS1307_setTiempoValidado(void * _self,byte horas,byte min,byte segs){
  struct BaseTiempoDS1307 * self = _self;
  //super_setTiempoValidado(&BaseTiempoDS1307,_self,horas,min,segs);
  //self->configurado = TRUE;
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getTiempo
** ===================================================================
*/
void BaseTiempoDS1307_getTiempo(void * self,TIMEREC *time){
  time->Hour= 19;
  time->Min = 27;
  time->Sec = 5;
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_setFechaValidada
** ===================================================================
*/
byte BaseTiempoDS1307_setFechaValidada(void * self,word year,byte month,byte day){
  
}

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_getFechaValidada
** ===================================================================
*/
void BaseTiempoDS1307_getFecha(void * self,DATEREC *date){
  date->Day=3;
  date->Month=5;
  date->Year=2009;  
}
/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_incUnSegundo
**
**     Description :
** ===================================================================
*/
/*bool BaseTiempoDS1307_habilitada(void * _self){
  struct BaseTiempoDS1307 * self = _self;
  return Timer_isfinish(&self->timer)==FALSE;
}  */

/*
** ===================================================================
**     Method      :  BaseTiempoDS1307_incUnSegundo
**
**     Description :
** ===================================================================
*/
/*void BaseTiempoDS1307_habilitar(void * _self,bool habilitar){
  struct BaseTiempoDS1307 * self = _self;
  if(habilitar){
    if(Timer_isfinish(&self->timer))
      Timer_Restart(&self->timer);
  }else{
    Timer_Stop(&self->timer);    
  }
}  */

/*
** ===================================================================
**     Method      :  BTFechaPersistente_incUnSegundo
**
**     Description :
** ===================================================================
*/
bool BaseTiempoDS1307_getConfigurado(void * _self){
  struct BaseTiempoDS1307 * self = _self;
  return TRUE;
}

