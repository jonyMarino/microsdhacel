#include "propiedadesControl.hpp"
#include "BoxLineal.hpp"
#include "BoxSaltoCondicional.hpp"
#include "BoxPropiedadEntradaCondicional.hpp"
#include "BoxLinealCondicional.hpp"


#include "ControlPID.hpp"
#include "SensorTermoPT100.hpp"
#include "CoordinadorControladorSintonizador.hpp"
#include "AutoSintonia.hpp"

//#include "VistaPWM.hpp"
#include "VistaControl.hpp"
#include "MessagesOut.hpp"





bool getCondicionEntrada (void* control){
  if(((ControlPID*)control)->getModoSalida() != ControlPID::_MAN && ((CoordinadorControladorSintonizador*)control)->getModo() != AUTOSINTONIA)
    return TRUE;
  else
    return FALSE;  
}

bool getCondicionEntrada2 (void* control){
  if(((ControlPID*)control)->getModoSalida() == ControlPID::_MAN)
    return TRUE;
  else
    return FALSE;  
}

bool getCondicionEntradaAut (void* control){
  if(((CoordinadorControladorSintonizador*)control)->getModo() == AUTOSINTONIA)
    return TRUE;
  else
    return FALSE;  
}

bool getCondicionEntradaAut2 (void* control){
  if(((CoordinadorControladorSintonizador*)control)->getModo() != AUTOSINTONIA)
    return TRUE;
  else
    return FALSE;  
}
   
 /***********************/
 /****** BOXES  *********/
 
bool getCondicionEntradaSint (void* control){
  if(((CoordinadorControladorSintonizador*)control)->getModo() != AUTOSINTONIA)
    return TRUE;
  else
    return FALSE;  
}


const struct ConstructorBoxPropiedad cBoxModos={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadModos
}; 

  

const struct ConstructorPropGetterVisual *const propSintonia[]=	{
  			  //(const struct ConstructorPropGetterVisual*)&cPropiedadReset,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadHisteresis,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadIntegral,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadDerivada,
  			  NULL
};

const struct ConstructorBoxLineal cBoxesSintonia={
        &boxLinealFactory,						       
  		  propSintonia,
  		  NULL						 //Proximo box	
};



const struct ConstructorBoxPropiedadEntradaCondicional cBoxesHisteresis={
      &boxPropiedadEntradaCondicionalFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadHisteresis,
			getCondicionEntradaSint
};


const struct ConstructorBoxPropiedadEntradaCondicional cBoxesDerivada={
      &boxPropiedadEntradaCondicionalFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadDerivada,
			getCondicionEntradaSint
};

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesIntegral={
      &boxPropiedadEntradaCondicionalFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadIntegral,
			getCondicionEntradaSint
};

const struct ConstructorBoxPropiedadEntradaCondicional cBoxesReset={
      &boxPropiedadEntradaCondicionalFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadReset,
			getCondicionEntradaSint
};


const struct ConstructorBoxPropiedad cBoxesSetPoint={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadSetPoint
};  

const struct ConstructorBoxPropiedadEntradaCondicional cBoxModoSalida={
      &boxPropiedadEntradaCondicionalFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadModoSalida,
      getCondicionEntradaAut2
};
   
/* const struct ConstructorBoxPropiedad cBoxModoSalida={
      &boxPropiedadFactory,	
			(const struct ConstructorPropGetterVisual*)&cPropiedadModoSalida,
      
};*/

const struct ConstructorBoxPropiedadEntradaCondicional cBoxPotInst ={
   &boxPropGetterEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadGetPotenciaInst,
   getCondicionEntrada
};
 
const struct ConstructorBoxPropiedadEntradaCondicional cBoxPotMan ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadPotManual,
   getCondicionEntrada2
}; 

const struct ConstructorBoxPropiedadEntradaCondicional cBoxSetPoint ={
   &boxPropiedadEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadSetPoint,
   getCondicionEntrada
}; 

const struct ConstructorBoxPropiedadEntradaCondicional cBoxSetPointAut ={
   &boxPropGetterEntradaCondicionalFactory,
   (const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAutoSintonia,
   getCondicionEntradaAut
};
/*
const struct ConstructorPropGetterVisual*const propsPot[]=	{
			  (const struct ConstructorPropGetterVisual*)&cPropiedadSetPoint,
			  NULL,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadPotManual,
			  NULL,
			  (const struct ConstructorPropGetterVisual*)&cPropiedadSetPointAutoSintonia,
			  NULL
};
const struct ConstructorBoxLinealCondicional cBoxPotMan={
      &boxLinealCondicionalFactory,								
			propsPot,
			NULL,
			nextSetProp
};	 
     */
const struct ConstructorPropGetterVisual *const propLimites[]=	{
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfSpAs,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupSpAs,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfPotAs,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupPotAs,
  			  NULL,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfSp,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupSp,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimInfPot,
  			  (const struct ConstructorPropGetterVisual*)&cPropiedadLimSupPot,
  			  NULL
};


uchar nextLimProp (void * obj){
  if(((CoordinadorControladorSintonizador*)obj)->getModo() == AUTOSINTONIA)
    return 0;
  else
    return 5;
}

const struct ConstructorBoxLinealCondicional cBoxesLimites={
        &boxLinealCondicionalFactory,						       
  		  propLimites,
  		  NULL,						 //Proximo box
  		  nextLimProp	
}; 

void setMensajeEstadoAutosintonia(CoordinadorControladorSintonizador* conf,MessagesOut* msjOutAs){
    
    static MessagesOut::Message msj_AutoSintonia;
    static char mensaje[6];
 
    if(((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->isDetenido() == TRUE){ //AutoSintonia detenida?
      
       if(((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->getNumeroEstado()==6){
            if(msj_AutoSintonia){
              msjOutAs->deleteMessage(msj_AutoSintonia);
              msj_AutoSintonia = NULL;
            }
            mensaje[0]='E';
            mensaje[1]='r';
            mensaje[2]='r';
            mensaje[3]='o';
            mensaje[4]='r';  
            mensaje[5]='\0';
            if(!msj_AutoSintonia)
              msj_AutoSintonia = msjOutAs->addMessage(mensaje);
        }else if(msj_AutoSintonia)
          msjOutAs->deleteMessage(msj_AutoSintonia); 
        
      }else if(((((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->getNumeroEstado()))<5) {
        //estoy en autoSintonia presento los carteles
            mensaje[0]='S';
            mensaje[1]='t';
            mensaje[2]=' ';
            mensaje[3]=(char)((((AutoSintonia*)(((CoordinadorControladorSintonizador*)conf)->getAutoSintonia()))->getNumeroEstado())+0x30);  
            mensaje[4]='\0';
       
        if(!msj_AutoSintonia)
         msj_AutoSintonia = msjOutAs->addMessage(mensaje);
      }else{
        if(msj_AutoSintonia){ 
          msjOutAs->deleteMessage(msj_AutoSintonia); 
          msj_AutoSintonia=NULL;
        }
        
      }
 }
