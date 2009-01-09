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
#include "MethodTimer.h"
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
#include "TimerInt2ms.h"

#define CNTR_TIME_DISCONECT 2000

#define TIEMPO_RECUPERACION_ENTRADA 500

#define timerInterruptDisplay  TimerInt2ms_getInstance()

#define MEDIUM

void entrarBajoConsumo(void * n);
void onBajoConsumo(void * n);
void onSalirBajoConsumo(void * n);

#ifdef MEDIUM
  struct FlashBkpEnFlash flash={																				\

INITIALIZATION_PROM_BKP(&flashBkpEnFlashTable),              							\
    (const void*)0x4400,														\
    0,0,0,0,0,0,0,0,  							                \
    0,0,0,0,0,0,0,0,  						                	\
    0,0,0,0,0,0,0,0,  							                \
    0,0,0,0,0,0,0,0,  						                	\
    TRUE,																						\
    NULL
};
#else
NEW_FLASH_BKP_EN_FLASH(flash,0x4200);
#endif

const struct ManejadorMemoria * pFlash = &flash;

struct AdquisidorSimple adquisidorSimple;
struct BaseTiempoBajoConsumo baseTiempoBajoConsumo;
struct MethodTimer timerAdquirirBajo;
struct MethodTimer timerRecuperacion;
struct MethodTimer timerTiempoLectura;
struct MethodTimer timerDisplay;
//static const struct Method metodoDisplay,coneccionMetodo,deconeccionMetodo,bajoConsumoMetodo;
static const NEW_METHOD(metodoDisplay,DpyAndSwitch,NULL);

static const NEW_METHOD(deconeccionMetodo,entrarBajoConsumo,NULL);

static const NEW_METHOD(coneccionMetodo,onSalirBajoConsumo,NULL);

static const NEW_METHOD(bajoConsumoMetodo,onBajoConsumo,NULL);


  
  
void * esperaPowUp;
#ifdef DEBUG
byte powdown=0;
#endif

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
  if(Adq_getState(&adquisidorSimple.adquisidor))
    Timer_setTime(&timerAdquirirBajo,Adq_getIntervalo(&adquisidorSimple.adquisidor)*1000);
}

void onBajoConsumo(void * n){
      Display_clrScreen();
      TI1_Disable(); //deshabilito los timers
      ADC_Disable();      
      clrReg8Bits(COPCTL, 71); // kill the dog!
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
   
      //deshabilito por si quedo algun timer de bajo consumo a ejecutarse.
      Timer_Stop(&timerDisplay);
      Timer_Stop(&timerTiempoLectura);
      Timer_Stop(&timerRecuperacion);
      // espero a que se estabilice la indicacion
      Cpu_Delay100US(10000);

      //TmDt1_Inc(&baseTiempo, RTIEsperaPowUp_getSegundosEsperados(esperaPowUp)+1); 
      TI1_Enable(); //habilito los timers
      ADC_Enable();
      ADC_Start();
}

void encenderAnalogica(void * _self) {
 // DDRP= 2;
  O2_PutVal(1);
  Timer_Restart(&timerRecuperacion);  
}
void adquirir(void * _self);

void comenzarAD(void * _self){
  uint i;
  RTIEsperaPowUp_despertar(esperaPowUp);
  Timer_Stop(&timerRecuperacion);
  Timer_Restart(&timerTiempoLectura);
  ADC_Enable();
  ADC_Start();
}



void adquirir(void * _self){
  Timer_Stop(&timerTiempoLectura);
  Timer_Restart(&timerDisplay);
  while(!_AD_isnew(&adquisidorSimple.termometro.AD1));
  ADC_Disable();
  O2_PutVal(0);  //apago la parte analogica  
  SenTPT_Handler(&adquisidorSimple.termometro.sensor[0]); 
  SenTPT_Print(&adquisidorSimple.termometro.sensor[0],0);
  addOnInterruptListener(timerInterruptDisplay,&metodoDisplay);
  enable(timerInterruptDisplay);
  Adq_Handler(&adquisidorSimple.adquisidor);
  //Agregado
  //RTIEsperaPowUp_dormir(esperaPowUp); 
}

void finCicloAdquisicion(void * _self){
  Timer_Stop(&timerDisplay);
  disable(timerInterruptDisplay);
      //borro el display      
      Display1_PutVal(0);
      bits5ULN_PutVal(0);
      bits2ULN_PutVal(0);
      //fin borro el display
      
  deleteOnInterruptListener(timerInterruptDisplay,&metodoDisplay);
  RTIEsperaPowUp_dormir(esperaPowUp);  
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
  OnPowDown_enable( OnPowDown_getInstance() );
  
  OnPowDown_addPowDownListener(OnPowDown_getInstance() ,&deconeccionMetodo);
  esperaPowUp = RTIEsperaPowUp_getInstance();
  
  RTIEsperaPowUp_addOnSalirListener(esperaPowUp,&coneccionMetodo);
   
  RTIEsperaPowUp_addOnBajoConsumoListener(esperaPowUp,&bajoConsumoMetodo);
  
  newAlloced(&baseTiempoBajoConsumo,&BaseTiempoBajoConsumo);
  newAlloced(&timerRecuperacion, &MethodTimer,(ulong)TIEMPO_RECUPERACION_ENTRADA,comenzarAD,NULL);
  Timer_Stop(&timerRecuperacion);
  setBaseTimer(&timerRecuperacion,&baseTiempoBajoConsumo);
  
  
  newAlloced(&timerAdquirirBajo, &MethodTimer,(ulong)1000,encenderAnalogica,NULL);
  Timer_Stop(&timerAdquirirBajo);
  setBaseTimer(&timerAdquirirBajo,&baseTiempoBajoConsumo);
  
  newAlloced(&timerTiempoLectura, &MethodTimer,(ulong)_TIEMPO_AD_EN_MILISEGUNDOS,adquirir,NULL);
  Timer_Stop(&timerTiempoLectura);
  setBaseTimer(&timerTiempoLectura,&baseTiempoBajoConsumo);

  
  newAlloced(&timerDisplay, &MethodTimer,(ulong)400,finCicloAdquisicion,NULL);
  Timer_Stop(&timerDisplay);
  setBaseTimer(&timerDisplay,&baseTiempoBajoConsumo);

  /*FIN Bajo Consumo*/
  
  for(;;){		
    tecla=get_key();  
    //Eventos
    DN_Proc(tecla);  
    mainLoop(&adquisidorSimple);
  }
}
