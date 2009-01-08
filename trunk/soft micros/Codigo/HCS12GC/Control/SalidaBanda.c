#include "SalidaBanda.h"
#include "SalidaBanda_protected.h"
#include "AdaptacionSalida_protected.h"
#include "stddef.h"
#include "funciones.h"

const struct AdaptacionSalidaClass SalidaBanda={
  &Class,
  "",
  &Object,
  sizeof(struct SalidaBanda),
  AdaptacionSalida_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
  SalidaBanda_calcularDuty,
  AdaptacionSalida_getTipoSalidaAdaptador,
  AdaptacionSalida_setTipoSalidaAdaptador
};





int SalidaBanda_calcularDuty(struct SalidaBanda * self,int valorDeControl){
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