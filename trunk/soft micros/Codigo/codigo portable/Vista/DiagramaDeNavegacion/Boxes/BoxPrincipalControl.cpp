#include "BoxPrincipalControl.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementable.hpp"
#include "obtenciondisplay.hpp"
#include "Box.hpp"
#include "Memoria/Prom/PromBkp.hpp"

#pragma DATA_SEG BoxPrincipalControl_DATA                                            
#pragma CODE_SEG BoxPrincipalControl_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */


const struct BoxPrincipalControlFactory boxPrincipalControlFactory; 
PropGetterVisual * BoxPrincipalControl::parametroAMostrar=NULL;
bool BoxPrincipalControl::priIsProp=FALSE; 

BoxPrincipalControl::BoxPrincipalControl(struct ConstructorBoxPrincipalControl * _constructor):BoxPrincipal((struct ConstructorBoxPrincipal*)_constructor),timerProp(TIME_BETWEEN_PARS),timerGrab(PRI_PAR_SECONDS),timerRefresh(REFRESH_SECONDS){
  
  par_seconds=0;
  propCambio=FALSE;
  propRefres=TRUE;
   
  constructor=(struct ConstructorBoxPrincipal*)_constructor;
  
  if(parametroAMostrar){
    if(priIsProp)
      ((PropiedadIncrementable*)parametroAMostrar)->refrescar();  
    parametroAMostrar->print(getDisplay(1));
  }
  
}

BoxPrincipalControl::~BoxPrincipalControl(){
}

Box * BoxPrincipalControl::procesarTecla(uchar tecla,TEstadoBox& estado){
  PropiedadIncrementable * p=NULL;
  char* mjs;
  
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
    constructor->snsr1->print(getDisplay(0));
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


void BoxPrincipalControl::MostrarGetter(const ConstructorPropGetterVisual * _getter,void * obj){
  if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_getter->getPropiedad(obj,0);
  priIsProp=FALSE;

}

void BoxPrincipalControl::MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj){
 if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_prop->getPropiedad(obj,0);
  priIsProp=TRUE;
  
}

void BoxPrincipalControl::Refresh(){
  
  if(parametroAMostrar){
    if(priIsProp && propRefres){
      ((PropiedadIncrementable *)parametroAMostrar)->refrescar();
      parametroAMostrar->print(getDisplay(1));
      propRefres = FALSE;
      }
    }
}

void BoxPrincipalControl::setRefresh(void){
     propRefres = TRUE;;
}

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT  