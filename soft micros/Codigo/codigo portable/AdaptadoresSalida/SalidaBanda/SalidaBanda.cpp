#include "SalidaBanda.hpp"
#include "../Control/controlmath.h"


int SalidaBanda::calcularPotencia(int valorControl){
      struct ISalida& salida = getSalida();
      int ha = getHisteresis();
      int duty;
      
      if( salida.getTipoSalida() == SALIDA_ONOFF)
      {
        duty = duty_onoff(valorControl, //variable
                          ha 	          //histeresis
                          );	          //valor del duty  
          
      } 
      else duty = duty_prop(valorControl, 	  //variable
                          ha,                 //histeresis
                          0,                  //pot inf
                          1000                //pot sup
                          ); 
      return duty;
}



