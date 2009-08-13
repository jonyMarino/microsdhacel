#include "SalidaBanda.h"
#include "SalidaBanda_protected.h"
#include "AdaptacionSalida_protected.h"
#include "stddef.h"
#include "funciones.h"

const struct AdaptacionSalidaClass SalidaBanda={
   CLASS_INITIALIZATION(Class,SalidaBanda,Object,AdaptacionSalida_defConstructor,Object_dtor,Object_differ,Object_puto),
  SalidaBanda_calcularDuty,
  AdaptacionSalida_getTipoSalidaAdaptador,
  AdaptacionSalida_setTipoSalidaAdaptador
};





int SalidaBanda_calcularDuty(void * _self,int valorDeControl){
      struct SalidaBanda * self =(struct SalidaBanda *)_self;
      struct ISalida * salida = AdaptacionSalida_getSalida(self);
      int ha = AdaptacionSalida_getHisteresis(self);
      int duty;
      
      if( _getTipoSalida(salida) == SALIDA_ONOFF)
      {
        duty = duty_onoff(valorDeControl, 	      //variable
                          ha 	          //histeresis
                          );	            //valor del duty  
          
      } 
      else duty = duty_prop(valorDeControl, 	      //setpoint
                          ha,
                          0,                  //pot inf
                          1000                //pot sup
                          ); 
      return duty;                    
                          
}