
#include "SalidaRetenidaBajo.h"
#include "SalidaRetenida_protected.h"
#include "stddef.h"
#include "funciones.h"

int SalidaRetenidaBajo_calcularDuty(void * _self,int valorDeControl);

const struct AdaptacionSalidaClass SalidaRetenidaBajo={
  CLASS_INITIALIZATION(AdaptacionSalidaClass,SalidaRetenidaBajo,SalidaRetenida,SalidaRetenida_defConstructor,Object_dtor,Object_differ,Object_puto),
  SalidaRetenidaBajo_calcularDuty,
  SalidaRetenida_getTipoSalidaAdaptador,
  SalidaRetenida_setTipoSalidaAdaptador
};

int SalidaRetenidaBajo_calcularDuty(void * _self,int valorDeControl){    
    struct SalidaRetenidaBajo * self =(struct SalidaRetenidaBajo *)_self;  
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
