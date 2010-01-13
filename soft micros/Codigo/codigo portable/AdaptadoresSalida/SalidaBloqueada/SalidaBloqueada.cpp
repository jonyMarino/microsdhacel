
#include "SalidaBloqueada.hpp"
#include "../Control/controlmath.h"

SalidaBloqueada::SalidaBloqueada(ISalida& salida,AdaptadorSalidaConfiguracion& configuracion):AdaptadorSalida(salida,configuracion),bloqueada(FALSE){
	setTipoSalida(SALIDA_ONOFF);
}

int SalidaBloqueada::calcularPotencia(int valorControl) {
      
      if( !getSalida().getConectada())
        return 0;
      else{      
        int duty;          
        int ha = getHisteresis();
        
        duty = duty_onoff(valorControl, 	      //variable
                            ha 	          //histeresis
                            );	            //valor del duty  
        
        
        
        if(bloqueada == TRUE){
          
          if(duty==1000 ||    
          duty ==-1)  // -1 = dentro de la banda
  		      bloqueada = FALSE; 
          else 
            duty=1000;
        }
        
        if(duty ==-1)
            return -1;
        duty = 1000 - duty; //invierto la salida
        
        return duty;                    
      }
}

void SalidaBloqueada::setTipoSalida(int histeresis) {
  return;
}

