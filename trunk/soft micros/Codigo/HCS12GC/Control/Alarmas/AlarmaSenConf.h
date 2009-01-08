#ifndef _ALARMA_SEN_CONF_H
#define _ALARMA_SEN_CONF_H

#include "Configuracion.h"
#include "RetransmisionConf.h"
#include "ConfLazoCntrlAlSen.h"


struct AlarmaSenConf {

  struct AlarmaConf super;

  struct ConfLazoCntrlAlSen lazoCntrAlConf;

};

#define  _AlarmaSenConf_getLazoCntrAlConf(self)\
 ( &((struct AlarmaSenConf*)self)->lazoCntrAlConf  )


//Adaptador Salida
#define _AlarmaSenConf_getAdaptadorSalida(self) \
  _ConfLazoCntrlAlSen_getAdaptadorSalida( _AlarmaSenConf_getLazoCntrAlConf(self) )  

#define _AlarmaSenConf_setAdaptadorSalida(self,valor) \
  _ConfLazoCntrlAlSen_setAdaptadorSalida( _AlarmaSenConf_getLazoCntrAlConf(self) , valor )  

//Valor Control
#define _AlarmaSenConf_getValorControl(self) \
  _ConfLazoCntrlAlSen_getValorControl( _AlarmaSenConf_getLazoCntrAlConf(self) )    

#define _AlarmaSenConf_setValorControl(self,valor) \
  _ConfLazoCntrlAlSen_setValorControl( _AlarmaSenConf_getLazoCntrAlConf(self) , valor )    

//Valor Control
#define _AlarmaSenConf_getHisteresis(self) \
  _ConfLazoCntrlAlSen_getHisteresis( _AlarmaSenConf_getLazoCntrAlConf(self) )    

#define _AlarmaSenConf_setHisteresis(self,valor) \
  _ConfLazoCntrlAlSen_setHisteresis( _AlarmaSenConf_getLazoCntrAlConf(self) , valor )    

#endif
