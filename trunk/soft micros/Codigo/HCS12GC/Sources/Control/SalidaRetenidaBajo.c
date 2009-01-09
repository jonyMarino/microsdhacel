
#include "SalidaRetenidaBajo.h"
#include "SalidaRetenida_protected.h"
#include "stddef.h"
#include "funciones.h"

int SalidaRetenidaBajo_calcularDuty(struct SalidaRetenidaBajo * self,int valorDeControl);

const struct AdaptacionSalidaClass SalidaRetenidaBajo={
  &AdaptacionSalidaClass,
  "SalidaRetenidaBajo",
  &SalidaRetenida,
  sizeof(struct SalidaRetenida),
  SalidaRetenida_defConstructor,
  NULL,
  Object_differ, // differ
  Object_puto, // puto
  SalidaRetenidaBajo_calcularDuty,
  SalidaRetenida_getTipoSalidaAdaptador,
  SalidaRetenida_setTipoSalidaAdaptador
};

int SalidaRetenidaBajo_calcularDuty(struct SalidaRetenidaBajo * self,int valorDeControl){    
      
    if( SalidaRetenida_getRetenida(self) == FALSE){      
      int duty;          
      int ha = AdaptacionSalida_getHisteresis(self);
      
      duty = duty_onoff(valorDeControl, 	//variable
                          ha 	            //histeresis
                          );	           
      
      if(duty==0)
		    SalidaRetenida_setRetenida(self, TRUE);          
      return duty;                    
    }
    return 0;
}
