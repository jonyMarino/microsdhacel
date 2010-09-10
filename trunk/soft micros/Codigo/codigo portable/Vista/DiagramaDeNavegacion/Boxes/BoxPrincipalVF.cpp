#include "BoxPrincipalVF.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementable.hpp"
#include "obtenciondisplay.hpp"
#include "Box.hpp"
#include "Memoria/Prom/PromBkp.hpp"
#include "obtenciondisplay.hpp"


#pragma DATA_SEG BoxPrincipalVF_DATA                                            
#pragma CODE_SEG BoxPrincipalVF_CODE                     
#pragma CONST_SEG DEFAULT       /* Constant section for this module */




const struct BoxPrincipalVFFactory boxPrincipalVFFactory;
PropGetterVisual * BoxPrincipalVF::parametroAMostrar=NULL;
bool BoxPrincipalVF::priIsProp=FALSE; 

BoxPrincipalVF::BoxPrincipalVF(struct ConstructorBoxPrincipalVF * _constructor):BoxPrincipal((struct ConstructorBoxPrincipal*)_constructor),timerProp(TIME_BETWEEN_PARS),timerGrab(PRI_PAR_SECONDS),timerRefresh(REFRESH_SECONDS),timerMsjDysSup(REFRESH_SECONDS){
  
  par_seconds=0;
  propCambio=FALSE;
  propRefres=TRUE;
  isPropGeter=FALSE;
  constructor=(struct ConstructorBoxPrincipal*)_constructor;
  getDisplay(1).write("Fin");
  
  if(parametroAMostrar){
    if(priIsProp)
      ((PropiedadIncrementable*)parametroAMostrar)->refrescar();  
    parametroAMostrar->print(getDisplay(1));
  }
  
}

BoxPrincipalVF::~BoxPrincipalVF(){
}

Box * BoxPrincipalVF::procesarTecla(uchar tecla,TEstadoBox& estado){
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
       
        if( mjs && !isPropGeter){
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
  
  if(timerMsjDysSup.getFlag()){
    if(constructor->msjsDysSup){     
        char* mjsDs=constructor->msjsDysSup->getMessage(msj_index_sup);
        if( mjsDs ){
          ++msj_index_sup; 
          getDisplay(0).write(mjsDs);
         }else
           msj_index_sup=0;    
    }
    
      timerMsjDysSup.reset();
        
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


void BoxPrincipalVF::MostrarGetter(const ConstructorPropGetterVisual * _getter,void * obj){
  if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_getter->getPropiedad(obj,0);
  priIsProp=FALSE;
  isPropGeter=TRUE;
}

void BoxPrincipalVF::MostrarProp( const ConstructorPropGetterVisual* _prop, void * obj){
 if(parametroAMostrar){
    delete parametroAMostrar;
  }
  
  parametroAMostrar=&_prop->getPropiedad(obj,0);
  priIsProp=TRUE;
  
  
}

void BoxPrincipalVF::Refresh(){
  
  if(parametroAMostrar){
    if(priIsProp && propRefres){
      ((PropiedadIncrementable *)parametroAMostrar)->refrescar();
      parametroAMostrar->print(getDisplay(1));
      propRefres = FALSE;
      }
    }
}

void BoxPrincipalVF::setRefresh(void){
     propRefres = TRUE;;
}
