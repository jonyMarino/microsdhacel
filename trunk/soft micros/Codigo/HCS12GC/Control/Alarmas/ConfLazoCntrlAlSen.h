#ifndef _CONFLAZOCNTRLALSEN_H
#define _CONFLAZOCNTRLALSEN_H

#include "Configuracion.h"
#include "AdaptSalidaConf.h"
#include "ValorControlConf.h"

struct ConfLazoCntrlAlSen{

  fbyte adaptadorSalida;

  struct AdaptSalidaConf confAdaptador;

  struct ValorControlConf confControl;
  
};

#define _ConfLazoCntrlAlSen_getConfAdaptador(self) \
  &( ( (struct ConfLazoCntrlAlSen*)self )->confAdaptador)
    
#define _ConfLazoCntrlAlSen_getConfControl(self) \
  &( ( (struct ConfLazoCntrlAlSen*)self )->confControl)  

//Histeresis
#define _ConfLazoCntrlAlSen_getHisteresis(self) \
  AdaptSalidaConf_getHisteresis( _ConfLazoCntrlAlSen_getConfAdaptador(self) )
#define _ConfLazoCntrlAlSen_setHisteresis(self,valor) \
  AdaptSalidaConf_setHisteresis( _ConfLazoCntrlAlSen_getConfAdaptador(self) ,valor)

//TipoSalida
#define _ConfLazoCntrlAlSen_getTipoSalida(self) \
  AdaptSalidaConf_getTipoSalida( _ConfLazoCntrlAlSen_getConfAdaptador(self) )
#define _ConfLazoCntrlAlSen_setTipoSalida(self,valor) \
  AdaptSalidaConf_setTipoSalida( _ConfLazoCntrlAlSen_getConfAdaptador(self) ,valor)

//Valor Control
#define _ConfLazoCntrlAlSen_getValorControl(self) \
  ValorControlConf_getValorControlador( _ConfLazoCntrlAlSen_getConfControl(self) )
#define _ConfLazoCntrlAlSen_setValorControl(self,valor) \
  ValorControlConf_setValorControlador( _ConfLazoCntrlAlSen_getConfControl(self) ,valor)



//Adaptador salida
#define _ConfLazoCntrlAlSen_getAdaptadorSalida(self) ((struct ConfLazoCntrlAlSen*)self)->adaptadorSalida
#define _ConfLazoCntrlAlSen_setAdaptadorSalida(self,valor) \
  CONFIGURACION_SET_BYTE( self,adaptadorSalida,ConfLazoCntrlAlSen,valor)


#endif
