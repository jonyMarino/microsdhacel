#include "SalidaRetenidaBajo.hpp"
#include "controlmath.h"
#include "AdaptadorSalida.hpp"


SalidaRetenidaBajo::SalidaRetenidaBajo(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion):SalidaRetenida(salida,configuracion){
  salida.setTipoSalida(SALIDA_ONOFF);
}

int SalidaRetenidaBajo::calcularDuty(int valorDeControl){    
     
    if( SalidaRetenida::getRetenida() == FALSE){      
      int duty;          
      int ha = AdaptadorSalida::getHisteresis();
      
      duty = duty_onoff(valorDeControl,ha);	           
      
      if(duty==0)
		    SalidaRetenida::setRetenida(TRUE);          
      return duty;                    
    }
    return 0;
}