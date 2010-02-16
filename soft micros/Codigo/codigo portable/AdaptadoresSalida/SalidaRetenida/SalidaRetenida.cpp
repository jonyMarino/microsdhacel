
#include "SalidaRetenida.hpp"
#include "../Control/controlmath.h"


SalidaRetenida::SalidaRetenida(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion):AdaptadorSalida(salida,configuracion),retenida(FALSE){
	salida.setTipoSalida(SALIDA_ONOFF);
}

void SalidaRetenida::setTipoSalida(TipoSalida tipoSalida) {
  return;
}

int SalidaRetenida::calcularPotencia(int valorControl) {

      if(retenida == FALSE){      
        int duty;          
        int ha = getHisteresis();
        
        duty = duty_onoff(valorControl, 	//variable
                            ha 	            //histeresis
                            );	           
        
        if(duty==1000)
  		    retenida = TRUE;          
        return duty;                    
      }
      return 1000;
}

void SalidaRetenida::setRetenida(bool value) {
  retenida = value;
}

