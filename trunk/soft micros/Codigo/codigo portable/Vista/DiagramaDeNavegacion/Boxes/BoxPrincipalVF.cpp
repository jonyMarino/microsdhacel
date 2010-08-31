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
/*
** ===================================================================
**     Method      :  BoxPri_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
BoxPrincipalVF::BoxPrincipalVF(struct ConstructorBoxPrincipalVF * _constructor):BoxPrincipal((struct ConstructorBoxPrincipal*)_constructor)
{
  constructor=(struct ConstructorBoxPrincipal*)_constructor;  
  getDisplay(1).write("Fin");
}

/*
** ===================================================================
**     Method      :  BoxPri_Destructor 
**     Description :  Destructor del Box
** ===================================================================
*/
BoxPrincipalVF::~BoxPrincipalVF(){
  constructor->flash->deshabilitar();
}

/*
** ===================================================================
**     Method      :  BoxPri_ProcKey 
**     Description :  Procesa la tecla ingresada
** ===================================================================
*/
Box * BoxPrincipalVF::procesarTecla(uchar tecla,TEstadoBox& estado){
  if(timerPri.getFlag()){
      if(constructor->msjs){     
        char * msj=constructor->msjs->getMessage(msj_index);
        if( msj ){
          ++msj_index; 
          getDisplay(1).write(msj);
        }else{
          if(msj_index==0)		 //no hay mensajes?
            getDisplay(1).write("Fin");
          else
            msj_index=0;
        }
      }
      constructor->snsr1->print(getDisplay(0));
  		timerPri.reset();
  }
  
  if(tecla == 'd' || tecla == 'u'){
      
        
        
        estado = STAY_BOX;
        return NULL;
      } 
  
  if(tecla=='r' || tecla=='f'){ 
    estado = EXIT_BOX;
    return NULL;
  }
  estado = STAY_BOX;
  return NULL;
}

