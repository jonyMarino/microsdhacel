
#include "RTIEsperaPowUp.h"
#include "OnPowDown.h"
#include "PWSN.h"
#include "PE_Timer.h"
#include "Thread.h"
#include "TimerInt2ms.h"
#include "timer_interrupt_2ms.h"

void RTIEsperaPowUp_defConstructor(void *_self,va_list * args);
void RTIEsperaPowUp_onRTI(void * _self);
static void RTIEsperaPowUp_onPowDown(void * _self);
static void RTIEsperaPowUp_checkDesconeccion(void * _self);
static void RTIEsperaPowUp_checkearRecuperacion(void * _self);

const struct Class RTIEsperaPowUp={
  CLASS_INITIALIZATION(Class,
                       RTIEsperaPowUp,
                       Object,
                       RTIEsperaPowUp_defConstructor,
                       Object_dtor,
                       Object_differ,
                       Object_puto)   
};

static void * instance = NULL;
struct Method metodoCheckearRecuperacion;
static byte vecesEnAlto=0;
                                                    
void RTIEsperaPowUp_constructor(void *_self){
  struct RTIEsperaPowUp * self = _self;
  void *thread;
  self->conectado = TRUE;
  self->despierto = 0;
  newAlloced(&self->listenersSalirBajoConsumo,&MethodContainer); 
  newAlloced(&self->listenersBajoConsumo,&MethodContainer); 
  newAlloced(&self->onRTI,&Method,RTIEsperaPowUp_onRTI,_self);
  addOnInterruptListener(ManejadorRTI_getInstance(),&self->onRTI);
  newAlloced(&self->onPowDown,&Method,RTIEsperaPowUp_onPowDown,_self);
  OnPowDown_addPowDownListener(OnPowDown_getInstance(),&self->onPowDown);
  pthread_create(&thread,NULL,RTIEsperaPowUp_checkDesconeccion,_self);
 // newAlloced(&metodoCheckearRecuperacion,&Method,RTIEsperaPowUp_checkearRecuperacion,_self);
}

void RTIEsperaPowUp_defConstructor(void *_self,va_list * args){
  super_ctor(&RTIEsperaPowUp,_self,args);
  RTIEsperaPowUp_constructor(_self);
}


void * RTIEsperaPowUp_getInstance(void){
  if(!instance)
    instance = new(&RTIEsperaPowUp);
  return instance;
}

static void RTIEsperaPowUp_onPowDown(void * _self){
  struct RTIEsperaPowUp * self = _self;
  self->conectado = FALSE;
  ManejadorRTI_enable(ManejadorRTI_getInstance()); 
}


static void RTIEsperaPowUp_wakeUp(void * _self){
  struct RTIEsperaPowUp * self = _self;
  ManejadorRTI_disable(ManejadorRTI_getInstance());
  self->conectado = TRUE;
}


static void RTIEsperaPowUp_checkearRecuperacion(void * _self){
  struct RTIEsperaPowUp * self = _self;
  
  
  if (!PWSN_GetVal()){
    vecesEnAlto++;
    if(vecesEnAlto==5){
      void * t = TimerInt2ms_getInstance();
      RTIEsperaPowUp_wakeUp(_self);
      ManejadorRTI_disable(ManejadorRTI_getInstance()); 
      deleteOnInterruptListener(t,&metodoCheckearRecuperacion);
      disable(t); 
    }
  }else if(vecesEnAlto-1){
    vecesEnAlto--;    
  }else{
    //por las dudas primero lo saco y despues lo decremento para que no se agregue 2 veces el metodo
    void * t = TimerInt2ms_getInstance();
    deleteOnInterruptListener(t,&metodoCheckearRecuperacion);
    disable(t); 
    vecesEnAlto--;
    RTIEsperaPowUp_dormir(_self);
  }
}

void RTIEsperaPowUp_onRTI(void * _self) {
  struct RTIEsperaPowUp * self = _self;
  #ifdef DEBUG
  extern byte powdown;
  
  if(!powdown){
  #else  
  if (!PWSN_GetVal()){  //posible recuperacion de energia
  #endif
    //set RTI ~ 1ms
    //entrar en modo de espera de 50 cambios de estado (aprox 1 seg).
    //si pasan 120 ms sin cambio de estado, completamos hasta los 131 ms
    //  y salimos del estado "ver si se recupero la energia establemente" 
    //si no, reactivar el micro
    /*if(!vecesEnAlto){
      void * t = TimerInt2ms_getInstance();
      RTIEsperaPowUp_despertar(_self);
      vecesEnAlto++; 
      addOnInterruptListener(t,&metodoCheckearRecuperacion);
      timer_interrupt_2ms_Init();
    }
    */
    RTIEsperaPowUp_wakeUp(_self);
    ManejadorRTI_disable(ManejadorRTI_getInstance()); 
  }
}

void RTIEsperaPowUp_despertar(void * _self){
  struct RTIEsperaPowUp * self = _self;
  if(!self->despierto++)
      PLL_Init(); 
}

void RTIEsperaPowUp_dormir(void * _self){
  struct RTIEsperaPowUp * self = _self;
  if(self->despierto){
      self->despierto--; 
  }
}

static void RTIEsperaPowUp_checkDesconeccion(void * _self){
  struct RTIEsperaPowUp * self = _self;
  if(!RTIEsperaPowUp_getConectado(self)){
      MethodContainer_execute(&self->listenersBajoConsumo);
      
      while(!RTIEsperaPowUp_getConectado(_self)){
          if(!self->despierto)
            Cpu_SetStopMode();
            
      }      
      //sali de desconectado 
      PLL_Init();

      MethodContainer_execute(&self->listenersSalirBajoConsumo);
      OnPowDown_enable( OnPowDown_getInstance() ); // habilito deteccion de bajo consumo
  }
}

void RTIEsperaPowUp_addOnSalirListener(void * _self,struct Method * metodo){
  struct RTIEsperaPowUp * self = _self;
  MethodContainer_add(&self->listenersSalirBajoConsumo,metodo);
}

void RTIEsperaPowUp_addOnRTIListener(void * _self,struct Method * metodo){
    addOnInterruptListener(ManejadorRTI_getInstance(),metodo);  
}

void RTIEsperaPowUp_deleteOnRTIListener(void * _self,struct Method * metodo){
    deleteOnInterruptListener(ManejadorRTI_getInstance(),metodo);  
}

void RTIEsperaPowUp_addOnBajoConsumoListener(void * _self,struct Method * metodo){
  struct RTIEsperaPowUp * self = _self;
  MethodContainer_add(&self->listenersBajoConsumo,metodo);
}

bool RTIEsperaPowUp_getConectado(void * _self){
  struct RTIEsperaPowUp * self = _self;
  return self->conectado;
}