#include "BoxPrincipalControlSD.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementable.hpp"
#include "obtenciondisplay.hpp"
#include "Box.hpp"
#include "Memoria/Prom/PromBkp.hpp"

#pragma DATA_SEG BoxPrincipalControl_DATA                                            
#pragma CODE_SEG BoxPrincipalControl_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */


const struct BoxPrincipalControlSDFactory boxPrincipalControlSDFactory; 

BoxPrincipalControlSD::BoxPrincipalControlSD(struct ConstructorBoxPrincipalControlSD * _constructor):Box(),timerPri(TIME_BETWEEN_PARS),timerRefresh(REFRESH_SECONDS){
  char i;
  for(i=0;i<CANTIDAD_CANALES;i++)
    msj_index[i]=0;
    
  timerPri.setFlag();   // Seteo el flag de manera tal que la primera vez no espere que pase  TIME_BETWEEN_PARS para actulizar el box
  constructor=_constructor;
   
}

BoxPrincipalControlSD::~BoxPrincipalControlSD(){
}

Box * BoxPrincipalControlSD::procesarTecla(uchar tecla,TEstadoBox& estado){
  
  char* mjs[CANTIDAD_CANALES];
  char i;
  
  for(i=0;i<CANTIDAD_CANALES;i++)
    mjs[i]=NULL;
  
  if(timerPri.getFlag()){ 
    
     for(i=0;i<CANTIDAD_CANALES;i++){
      
        constructor->snsrs[i]->print(getDisplay(i));
      
     }
  		timerPri.reset();
  	}
  
  if(timerRefresh.getFlag()){
    
    for(i=0;i<CANTIDAD_CANALES;i++){ 
     if(constructor->msjs[i]){     
        mjs[i]=constructor->msjs[i]->getMessage(msj_index[i]);
        if( mjs[i] ){
          ++msj_index[i]; 
          getDisplay(i).write(mjs[i]);
         }else
           msj_index[i]=0;    
      } 
    }   
     timerRefresh.reset();
      
    }
  	

  if(tecla=='r' || tecla=='f'){
    
    estado = EXIT_BOX;
    return NULL;
  }
    
  estado = STAY_BOX;
  return NULL;
} 





#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT  