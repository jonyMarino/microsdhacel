#include "BoxPrincipalControlSD.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementable.hpp"
#include "obtenciondisplay.hpp"
#include "Box.hpp"
#include "Memoria/Prom/PromBkp.hpp"

#pragma DATA_SEG BoxPrincipalControl_DATA                                            
#pragma CODE_SEG BoxPrincipalControl_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */


const struct BoxPrincipalControlSDFactory boxPrincipalControlSDFactory; 
PropGetterVisual * BoxPrincipalControlSD::parametroAMostrar=NULL;
bool BoxPrincipalControlSD::priIsProp=FALSE; 

BoxPrincipalControlSD::BoxPrincipalControlSD(struct ConstructorBoxPrincipalControlSD * _constructor):Box(),timerPri(TIME_BETWEEN_PARS),timerProp(TIME_BETWEEN_PARS),timerGrab(PRI_PAR_SECONDS),timerRefresh(REFRESH_SECONDS){
  msj_index=0;
  par_seconds=0;
  propCambio=FALSE;
  propRefres=TRUE;
   
  constructor=_constructor;
  
  if(parametroAMostrar){
    if(priIsProp)
      ((PropiedadIncrementable*)parametroAMostrar)->refrescar();  
    parametroAMostrar->print(getDisplay(1));
  }
  
}

BoxPrincipalControlSD::~BoxPrincipalControlSD(){
}

Box * BoxPrincipalControlSD::procesarTecla(uchar tecla,TEstadoBox& estado){
  PropiedadIncrementable * p=NULL;
  char* mjs;
  char i;
  
  if(priIsProp)
    p = (PropiedadIncrementable *)parametroAMostrar;
  
  if(timerPri.getFlag()){ 
     mjs=NULL;
    
    if(constructor->msjs){     
       
       if(par_seconds==0){
         mjs=constructor->msjs->getMessage(msj_index);
       }else
         par_seconds --;
       
        if( mjs ){
          ++msj_index; 
          getDisplay(1).write(mjs);
        }else{
           if(parametroAMostrar)        
               parametroAMostrar->print(getDisplay(1));
           msj_index=0;
        }
     }
     for(i=0;i<CANTIDAD_CANALES;i++){
      
        constructor->snsrs[i]->print(getDisplay(i));
      
     }
  		timerPri.reset();
  	}
  
  if(timerRefresh.getFlag()){
      Refresh(); 
    }
  	
  if(propCambio && timerProp.getFlag()){    
      if(timerGrab.getFlag()){
         propCambio=FALSE;
         p->guardar();
      }
  }
  if(parametroAMostrar && p && msj_index==0 )	 //no hay mensaje que mostrar
  {
      
      if(tecla == 'd' || tecla == 'u'){
        par_seconds=PRI_PAR_SECONDS;
        if(tecla == 'd') 
          p->decrementar();
        else  
          p->incrementar();
        
        propCambio=TRUE; 
        timerGrab.reset();
        timerGrab.restart();              
        timerProp.reset();
        timerRefresh.reset();
        timerRefresh.restart();
        parametroAMostrar->print(getDisplay(1));
        
        estado = STAY_BOX;
        return NULL;
      } 
   }
    
    
  if(constructor->flash->grabacionOBorradoEnEspera() ){
      
      estado = STAY_BOX;
      return NULL;
  }

  if(tecla=='r' || tecla=='f'){
    if(propCambio && p){
        propCambio=FALSE;
        p->guardar(); 
        estado = STAY_BOX;
        return NULL; 
    }
    estado = EXIT_BOX;
    return NULL;
  }
    
  estado = STAY_BOX;
  return NULL;
} 


void BoxPrincipalControlSD::MostrarGetter(const ConstructorPropGetterVisual * _getter,void * obj){
  if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_getter->getPropiedad(obj,0);
  priIsProp=FALSE;

}

void BoxPrincipalControlSD::MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj){
 if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_prop->getPropiedad(obj,0);
  priIsProp=TRUE;
  
}

void BoxPrincipalControlSD::Refresh(){
  
  if(parametroAMostrar){
    if(priIsProp && propRefres){
      ((PropiedadIncrementable *)parametroAMostrar)->refrescar();
      parametroAMostrar->print(getDisplay(1));
      propRefres = FALSE;
      }
    }
}

void BoxPrincipalControlSD::setRefresh(void){
     propRefres = TRUE;;
}

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT  