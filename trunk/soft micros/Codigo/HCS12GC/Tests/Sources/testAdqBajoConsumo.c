/* */
#include "stddef.h"
#include "stdtypes.h"
#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Object.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "DiagramaNavegacion.h"
#include "SnsHmi.h"
#include "BoxProp.h"
#include "Sets.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "RlxMTimer.h"
#include "Adquisidor.h"
#include "AdquisidorHmi.h"
#include "com_events.h"
#include "Terminal.h"
#include "termio.h"
#include "hidef.h"
#include "stdio.h"
#include "FlashBkpEnFlash.h"
#include "Termometro.h"
#include "timer_interrupt.h"
#include "ModBusHmi.h"
#include "BoxPriAdquisidor.h"
#include "AdquisidorSimple.h"
#include "System.h"
#include "dateTimeVista.h"
#include "RTIEsperaPowUp.h"
#include "OnPowDown.h"
#include "BaseTiempoBajoConsumo.h"
#include "ArrayList.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"

#include "Cpu.h"
#include "Display1.h"
#include "bits5ULN.h"
#include "bits2ULN.h"
#include "ADC.h"
#include "O2.h"
#include "AS1.h"
#include "TI1.h"
#include "FlashBkp256.h"

#ifdef DEBUG
  #include "BTBajoConsumoSafe.h"
  void BTBajoConsumoSafe_onRTI(void * _self);
#endif

#define CNTR_TIME_DISCONECT 2000

#ifdef DEBUG
byte powdown;
byte simPowDown=0;
#endif

NEW_FLASH_BKP_256(flash,0x4200);
extern void * nico;
extern bool estado;
bool BajoConsumo = FALSE;

const struct ManejadorMemoria * pFlash = &flash;

struct AdquisidorSimple adquisidorSimple;
struct BaseTiempoBajoConsumo baseTiempoBajoConsumo;
struct Method coneccionMetodo,deconeccionMetodo,bajoConsumoMetodo;
void * esperaPowUp;

const struct BlockConstBoxPri CBox_Pri={                    
      &BoxPriAdquisidor,							/* funcion que procesa al box*/
      adquisidorSimple.termometro.sensor,
      &adquisidorSimple.mensajes						
};

/*  COMUNICACION  */
  /*Adquisidor*/
  static const NEW_NODO_IC_MODBUS(DateTime1Com,&DATE_TIME_GETTERS_ARRAY,1000,&baseTiempo);
  static const NEW_NODO_IC_MODBUS(Adq1Com,&ADQ_GETTERS_ARRAY,1054,_getAdquisidor(&adquisidorSimple));  
  /*Sensor*/
  static const NEW_NODO_IC_MODBUS(Sen1Com,&SNS_GETTERS_ARRAY,1100,_getSensor(&adquisidorSimple,0));
  /*Comunicacion*/
  static const NEW_NODO_IC_MODBUS(ModBusCom,&MODBUS_GETTERS_ARRAY,1400,NULL);
  /*Codigo*/
  static const NEW_NODO_IC_MODBUS(CodCom,&COD_GETTERS_ARRAY,1500,NULL);


  static const struct NodoICModBus *const  nodosComunicacion[]={
     //Base de tiempo
     &DateTime1Com,
     //Adquisidor
     &Adq1Com,
     //Sensor
     &Sen1Com,    
     //Comunicacion
     &ModBusCom,    
     //codigo
     &CodCom
  };
  static const NEW_ARRAY_LIST(arrayNodosComunicacion,nodosComunicacion);
/*  FIN COMUNICACION  */

/*  Diagrama de navegacion  */
//Operador
  //Principal
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);

static const struct FstBoxPointer *const OpArray[]={
  &Principal
};


static const NEW_BOX_LIST(OpList,OpArray,"op");


//ADQ
static const NEW_FST_BOX_POINTER(DateList,&DATE_TIME_BOX,&baseTiempo,0);
static const NEW_FST_BOX_POINTER(AdqList,&ADQ_FST_BOX,_getAdquisidor(&adquisidorSimple),0);

static const struct FstBoxPointer *const AdqArray[]={
  &DateList,
  &AdqList   
};

static const NEW_BOX_LIST(Adq,AdqArray,"Adq");

//CAL
static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,_getSensor(&adquisidorSimple,0),0);

static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List   
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");


//SET
  //Comunicacion
static const NEW_FST_BOX_POINTER(ModBusSet,&MOD_BUS_HMI_FST_BOX_SET,0,0);
  //SetC
static const NEW_FST_BOX_POINTER(SetsSet,&SETS_FST_BOX_SET,0,0);
  

static const struct FstBoxPointer *const SetArray[]={
  &ModBusSet,
  &SetsSet  
};

static const NEW_BOX_LIST(Set,SetArray,"SEt");


// Acceso comun
static const struct BoxList *const BoxListArray[]={
  &Adq,
  &Cal,
  &Set
};

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",CONTENEDOR_CODIGO);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);



  

void entrarBajoConsumo(void * n){
 
  TI1_Disable(); //deshabilito los timers
  ADC_Disable();
 
  BajoConsumo = TRUE;
  Adq_Stop(nico); // agrego nico
 
}

void onBajoConsumo(void * n){
      
      BajoConsumo = TRUE;
      Adq_Stop(nico); // agrego nico
     
      clrReg8Bits(COPCTL, 71); // kill the dog!
      TI1_Disable(); //deshabilito los timers
      ADC_Disable();      
      //borro el display      
      Display1_PutVal(0);
      bits5ULN_PutVal(0);
      bits2ULN_PutVal(0);
      //fin borro el display

      //desconecto la alimentacion del resto del equipo
      DDRP= 2; 
      O2_PutVal(0);
      DDRAD= 0;
      
      DDRT = 0;
      
      /* WOMS: WOMS2=0 */
      WOMS =  0;        
      AS1_Disable();
      DDRS = 0;
      PERS = 0;
      PTS=0;
}

void onSalirBajoConsumo(void * n){
  
      
  
      clrSetReg8Bits(COPCTL, 128, 71);  // revive the dog!
      //conecto la alimentacion del resto del equipo
      setReg8Bits(DDRP, 170); 
      O2_PutVal(0);
      
      setReg8Bits(DDRAD, 3);
      
      setReg8Bits(DDRT, 126);
        
      /* WOMS: WOMS2=0 */
      clrReg8Bits(WOMS, 4);    
      
      /* DDRS: DDRS2=1 */
      setReg8Bits(DDRS, 4); 
      /* ### Asynchro serial "AS1" init code ... */
      DDRS &= ~1;
      PTS |= 2;
      DDRS |= 2;
      AS1_Enable();
   
      // espero a que se estabilice la indicacion
      Cpu_Delay100US(10000);

      TmDt1_Inc(&baseTiempo, 1); 
      TI1_Enable(); //habilito los timers
      ADC_Enable();
      ADC_Start();
     
     if((nico != NULL)&&(estado == TRUE)){
      
      Adq_Start(nico); // agrego nico
     // estado = FALSE;
     }
     
     BajoConsumo = FALSE;
}



void main (void){

  char tecla; 
      
  newAlloced(&adquisidorSimple,&AdquisidorSimple,NULL,&flash);
  //conecto la alimentacion del resto del equipo
  O2_PutVal(0);
 
  com_initialization(&arrayNodosComunicacion);
  System_init();    
  
  DN_staticInit(&OpList,&AccessList);												 
  
  
  /* Bajo Consumo */
  
  esperaPowUp = RTIEsperaPowUp_getInstance();
  newAlloced(&coneccionMetodo,&Method,onSalirBajoConsumo,NULL);
  RTIEsperaPowUp_addOnSalirListener(esperaPowUp,&coneccionMetodo);
  
  OnPowDown_enable( OnPowDown_getInstance() );
  newAlloced(&deconeccionMetodo,&Method,entrarBajoConsumo,NULL);
  OnPowDown_addPowDownListener(OnPowDown_getInstance() ,&deconeccionMetodo);
    
  newAlloced(&bajoConsumoMetodo,&Method,onBajoConsumo,NULL); 
  RTIEsperaPowUp_addOnBajoConsumoListener(esperaPowUp,&bajoConsumoMetodo);
  
  /*FIN Bajo Consumo*/
  
  for(;;){		
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);  
    mainLoop(&adquisidorSimple);
    #ifdef DEBUG
    if(simPowDown)
      BTBajoConsumoSafe_onRTI(&baseTiempo);
    #endif
  }
}
