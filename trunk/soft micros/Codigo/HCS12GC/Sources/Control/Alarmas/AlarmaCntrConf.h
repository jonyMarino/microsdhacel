#ifndef _ALARMACNTRCONF_H
#define _ALARMACNTRCONF_H

#include "AlarmaConf.h"
#include "ConfLazoCntrAlCntr.h"

struct AlarmaCntrConf{
  struct AlarmaConf super;
  struct ConfLazoCntrAlCntr lazoCntrAlConf;

};


#define  _AlarmaCntrConf_getLazoCntrAlConf(self)\
 ( &((struct AlarmaCntrConf*)self)->lazoCntrAlConf  )


//Control
#define _AlarmaCntrConf_getControl(self) \
  _ConfLazoCntrAlCntr_getControl( _AlarmaCntrConf_getLazoCntrAlConf(self) )  

#define _AlarmaCntrConf_setControl(self,valor) \
  _ConfLazoCntrAlCntr_setControl( _AlarmaCntrConf_getLazoCntrAlConf(self) , valor )  

//Adaptador Salida
#define _AlarmaCntrConf_getAdaptadorSalida(self) \
  _ConfLazoCntrlAlSen_getAdaptadorSalida( _AlarmaCntrConf_getLazoCntrAlConf(self) )  

#define _AlarmaCntrConf_setAdaptadorSalida(self,valor) \
  _ConfLazoCntrlAlSen_setAdaptadorSalida( _AlarmaCntrConf_getLazoCntrAlConf(self) , valor )  

//Valor Control
#define _AlarmaCntrConf_getValorControl(self) \
  _ConfLazoCntrlAlSen_getValorControl( _AlarmaCntrConf_getLazoCntrAlConf(self) )    

#define _AlarmaCntrConf_setValorControl(self,valor) \
  _ConfLazoCntrlAlSen_setValorControl( _AlarmaCntrConf_getLazoCntrAlConf(self) , valor )    

//Histeresis
#define _AlarmaCntrConf_getHisteresis(self) \
  _ConfLazoCntrlAlSen_getHisteresis( _AlarmaCntrConf_getLazoCntrAlConf(self) )    

#define _AlarmaCntrConf_setHisteresis(self,valor) \
  _ConfLazoCntrlAlSen_setHisteresis( _AlarmaCntrConf_getLazoCntrAlConf(self) , valor )    

//TipoSalida
#define _AlarmaCntrConf_getTipoSalida(self) \
  _ConfLazoCntrlAlSen_getTipoSalida( _AlarmaCntrConf_getLazoCntrAlConf(self) )    

#define _AlarmaCntrConf_setTipoSalida(self,valor) \
  _ConfLazoCntrlAlSen_setTipoSalida( _AlarmaCntrConf_getLazoCntrAlConf(self) , valor )    

#endif
