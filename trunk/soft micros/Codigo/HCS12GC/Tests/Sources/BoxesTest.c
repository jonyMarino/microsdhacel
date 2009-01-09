#include "Timer.h"
#include "display.h"
#include "WDog1.h"
#include "teclas.h"
#include "Class.h"
#include "ClassADC.h"
#include "Grabacion.h"
#include "Sensores.h"
#include "SensorTPT_Class.h"
#include "DiagramaNavegacion.h"
#include "SnsHmi.h"
#include "PropNumerica.h"
#include "BoxProp.h"
#include "Sets.h"
#include "FlashBkpEnFlash.h"
#include "timer_interrupt.h"
#include "TI1.h"
#include "FstBoxPointer.h"
#include "BoxList.h"
#include "Access.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const SensorConf config=STPT_DEF_CONF;
volatile const SensorConf config2=STPT_DEF_CONF;
#pragma CONST_SEG DEFAULT
struct TAdc * AD1;
struct TSensor_TermoPT sensor;
struct TSensor_TermoPT * sensor2;

const struct ConstPropNum T_ParAjGanT={
    PropNum,get_GananciaTermopar,set_GananciaTermopar,NULL,NULL,"Ag ",1
};
  	

const struct BlockConstBoxPri CBox_Pri={
      BoxPri,							/* funcion que procesa al box*/
      &sensor						
};

NEW_FLASH_BKP_EN_FLASH(flash,0x4400);

void on1ms(void * termometro){
    IncTimers(1); //Contador Estandard

    if(PromBkp_listoParaGrabarOBorrar(&flash) && getState()==AD_WAITING)
      TI1_SetPeriodMode(TI1_Pm_40ms);
    
    DpyAndSwitch();
}

void on40ms(void * termometro){
    (void)TI1_SetPeriodMode(TI1_Pm_1ms); //Next interrupt is 1ms length

    PromBkp_grabarOBorrar(&flash);

    IncTimers(TIEMPO_GRABACION); //Contador Estandard
}
/*  Diagrama de navegacion  */
static const NEW_FST_BOX_POINTER(Principal,&CBox_Pri,NULL,0);

static const struct FstBoxPointer *const OpArray[]={
  &Principal  
};

static const NEW_BOX_LIST(OpList,OpArray,"op");

static const NEW_FST_BOX_POINTER(Sensor1List,&SNS_HMI_FST_BOX,&sensor,0);

static const struct FstBoxPointer *const CalArray[]={
  &Sensor1List 
};

static const NEW_BOX_LIST(Cal,CalArray,"CAL");

static const struct BoxList *const BoxListArray[]={
  &Cal
};

int * codigo = 0;

static const NEW_ACCESS(accesoComun,BoxListArray,"Cod",codigo);

static const struct Access *const AccessArray[]={
  &accesoComun
};

static const NEW_ARRAY_LIST(AccessList,AccessArray);


/****************/

void main (void){

  char tecla; 
  struct PropNum* prop;
  struct BoxCondl *_box;
  int val;
  
 /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
 /*** End of Processor Expert internal initialization.                    ***/
  add1msListener(on1ms,0);
  add40msListener(on40ms,0);
  
  AD1 = newObj(TAdc,0);
  newAllocObj(&sensor,TSensor_TermoPT,AD1,&config);
  sensor2 = newObj(TSensor_TermoPT,AD1,&config2);
  val= _Getter_getVal(&sensor);
  val= _getDec(&sensor);
  
  
  Teclas_Init();
  Display_Init(); // Inicializacion del display
  

/*   
    prop= pProp_Constructor(&T_ParAjGanT,sensor);
  _box=vBoxes_Construct(&T_CBox_Cod,NULL,0);
 
  val=Prop_getVal(prop);
  vBox_ProcKey(_box,'u');
  vBox_ProcKey(_box,'r');
  vBox_ProcKey(_box,'f');
*/  
  DN_staticInit(&OpList,&AccessList);				
	//	DN_Init(&CBox_Pri);
  //Sets_Init();
  
  //SnsHmi_Add(&sensor,1);
//  SnsHmi_Add(sensor2,2);
//  Sets_AddBoxes();

 															 
  for(;;){
    WDog1_Clear();
    tecla=get_key();  
    //Eventos
    SenTPT_Handler(&sensor);
    DN_Proc(tecla);
  }
}