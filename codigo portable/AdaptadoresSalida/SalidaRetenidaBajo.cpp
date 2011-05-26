#include "SalidaRetenidaBajo.hpp"
#include "funciones.h"


SalidaRetenidaBajo::SalidaRetenidaBajo(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion):SalidaRetenida(salida,configuracion){

}


int SalidaRetenidaBajo::calcularPotencia(int valorControl){
     if( getRetenida() == FALSE){      
      int duty;          
      int ha = getHisteresis();
      
      duty = duty_onoff(valorControl, 	//variable
                          ha 	            //histeresis
                          );	           
      
      if(duty==0)
		    setRetenida(TRUE);          
      return duty;                    
    }
    return 0;
}