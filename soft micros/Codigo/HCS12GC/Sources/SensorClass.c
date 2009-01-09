/*IMPLEMENTATION MODULE Sensores; */
#include "Mydefines.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "limits.h"
#include "ADC.h"
#include "IFsh10.h"
#include "PTSL.h"
#include "Events.h"
#include "Math.h"
#include "Errores.h"
#include "ClassSensor.h"
#include "Sensores.h"


/*  Funciones internas  */
void  SenTPT_DefConstruct(struct TSensor_TermoPT * self,va_list * args);
TError Sensor_ChangeTipo(int val,const struct TSensor_TermoPT * sensor);
void Sensor_Procesar(struct TSensor_TermoPT * self);


unsigned char Linealizar(long Vx, t_sensor sensor, int * Vy);
bool SENSOR_is_Lineal(t_sensor sensor);

int filtrar (int val_x,
            int Tf,
            int DEL_T,
            int TfMAX,
            long *buffer_fil
            ); 
            
/************************/

const struct TSensor TableSenTPT={ 
  sizeof(TSensor_TermoPT),		 //size
  SenTPT_DefConstruct, // constructor
  NULL, // const_copia
  NULL, // destructor
  NULL, // differ
  SenTPT_getValue, // get_Val
  SenTPT_isnew, // is_new? 
};

const struct TableSenTPT * TSensor_TermoPT = &TableSenTPT;

#pragma CONST_SEG PARAMETERS_PAGE
volatile const int iCompensacionTempAmb; 
#pragma CONST_SEG DEFAULT

            
/*
** ===================================================================
**     Method      :  Sensor_Construct 
**     Description :  Constructor del Sensor
** ===================================================================
*/

void  SenTPT_Construct(struct TSensor_TermoPT * self,struct TAdc* adc,const SensorConf * conf){
  while(!SenTPT_isnew(adc)) //Espera a q haya una conversión
    WDog1_Clear();
  self->Adc=adc;
  self->conf=conf; 
  set_Sensor(self,Sensor_getTipo(self));  // inicializo Tipo con el valor guardado   
  SenTPT_Handler(self);  // Como hay un valor nuevo lo mando a procesar
}

/*
** ===================================================================
**     Method      :  Sensor_DefConstruct 
**     Description :  Constructor por defecto del Sensor
** ===================================================================
*/

void  SenTPT_DefConstruct(struct TSensor_TermoPT * self,va_list * args){
  SenTPT_Construct(self,va_arg(*args,void*),va_arg(*args,void*));  
}

/*
** ===================================================================
**     Method      :  SensorHandler 
**     Description :  Checkea si hay un nuevo valor del AD, 
**                    y si lo hay lo procesa.
** ===================================================================
*/
void SenTPT_Handler(struct TSensor_TermoPT * self){
  if(AD_isnew(self->Adc))
    Sensor_Procesar(self);
}
/*
** ===================================================================
**     Method      :  SenTPT_getValue 
**     Description :  Devuelve el último valor procesado del AD
** ===================================================================
*/
int SenTPT_getValue(struct TSensor_TermoPT * self){
  int val;
  val= self->ProcVal;
  Cpu_DisableInt();
  self->newVal=0;
  Cpu_EnableInt();  
  return val;
}
/*
** ===================================================================
**     Method      :  SenTPT_isnew 
**     Description :  Indica si hay un nuevo valor obtenido del sensor
** ===================================================================
*/
bool SenTPT_isnew(struct TSensor_TermoPT * self){
  return self->newVal;
}
/*
** ===================================================================
**     Method      :  getDecProcVal 
**     Returns		 :  Valor del Proceso con decimales
** ===================================================================
*/
//int SENSOR_getDecProcVal(byte chan){
//  return ProcVal[chan];
//}
/*
** ===================================================================
**     Method      :  Sensor_Procesar 
**     Description :  Procesa el nuevo valor del AD
**                    y obtiene un nuevo valor del sensor
** ===================================================================
*/
void Sensor_Procesar(struct TSensor_TermoPT * self){
  long ValProv;
  int ValLin;
  TSensorState err; 
  long vx= AD_getValue(self->Adc);
  t_sensor sensor=self->conf->eSensor; 
  int ceroTP=self->conf->iCeroTermopar;					 //Cero Termopar
  int ganTP = self->conf->iGananciaTermopar;
  int ceroPT = self->conf->iCeroPT100;
  int ganPT=self->conf->iGananciaPT100;
  byte decimales=self->conf->iDecimales;
  int offset= self->conf->iOffset;
  int ganancia = self->conf->iGanancia;
  int filtro = self->conf->iFiltro;
  
  vx=(vx+ceroTP)*(1000+ganTP)/1000;
  err = Linealizar(vx,sensor,&ValLin);
  ValProv=ValLin;  
	if(sensor==SENSOR_PT)
    ValProv = ((ValProv+ceroPT)*(1000+ganPT)/1000);  
	if (sensor<SENSOR_PT)
    ValProv=ValProv- ADC_getTA() + iCompensacionTempAmb;   
  if (!SENSOR_is_Lineal(sensor))
      ValProv/= pow10(SENSOR_Decimales(sensor)-decimales);  
	ValProv=(ValProv+offset)*ganancia/1000;         //preciso para pasar a long
  ValProv= filtrar ((int)ValProv,filtro,10,200,& self->buffer_fil);
  Cpu_DisableInt();
  self->ProcVal=ValProv;
  Cpu_EnableInt();
  self->state=err;
  return;
}




/// FUNCIONES DE SETEO Y OBTENCION DE VARIABLES 
/*
** ===================================================================
**     Method      :  get_LimInf_Sensor 
**     Description :  Limite inferior de temperatura del sensor
** ===================================================================
*/

int get_LimInf_Sensor(struct TSensor_TermoPT * self){
t_sensor sensor=self->conf->eSensor;
int min_sens=SENSOR_Minimo(sensor);      
byte decimal_chan = SENSOR_Decimales(sensor);      
byte decimales=self->conf->iDecimales;

  if(SENSOR_is_Lineal(sensor))
    return min_sens;
  else
    return min_sens/pow10(decimal_chan-decimales);
}

/*
** ===================================================================
**     Method      :  get_LimSup_Sensor 
**     Description :  Limite superior de temperatura del sensor
** ===================================================================
*/

int get_LimSup_Sensor(struct TSensor_TermoPT * self){
t_sensor sensor=self->conf->eSensor;
int max_sens=SENSOR_Maximo(sensor);
byte decimal_chan = SENSOR_Decimales(sensor);      
byte decimales=self->conf->iDecimales;

  if(SENSOR_is_Lineal(sensor))
    return max_sens/pow10(decimal_chan-decimales);
  else
    return max_sens; 
}



/*  Sensor  */
/*
** ===================================================================
**     Method      :  get_Sensor 
**     Description :  Obtiene el sensor actual(J,K,etc)
** ===================================================================
*/
int get_Sensor(const struct TSensor_TermoPT * self){
  return self->conf->eSensor;
}

/*
** ===================================================================
**     Method      :  set_Sensor 
**     Description :  Setea el sensor (J,K,etc)
** ===================================================================
*/
TError set_Sensor(struct TSensor_TermoPT * self,int sensor){
TError err;
  
  err=EscribirByte( (word)&(self->conf->eSensor) , sensor );
  if(!err){
    err= Sensor_ChangeTipo(self,sensor);
  }
  return err; 
}

/*
** ===================================================================
**     Function      :  get_LimInf_Sensores 
**     Type : Static 
**     Description :  Obtiene el minimo valor correspondiente a un int
**                    en el que se corresponde a un sensor. 
** ===================================================================
*/																				 
int get_LimInf_Sensores(void){
  return 0;
}

/*
** ===================================================================
**     Function      :  get_LimInf_Sensores
**     Type : Static  
**     Description :  Obtiene el minimo valor en integer
**                    en el que se corresponde a un sensor.
** ===================================================================
*/	
int get_LimSup_Sensores(void){
  return NUM_SENSORES-1;  
}


/*
** ===================================================================
**     Method      :  Sensor_ChangeTipo 
**    Description : Cambia el tipo de sensor (K,J,etc.)
** ===================================================================
*/
TError Sensor_ChangeTipo(struct TSensor_TermoPT * self,int val){
byte Lim_Dec;

    if (val==SENSOR_PT) 
      PTSL_PutBit(self->Adc->pin ,TRUE);
    else 
      PTSL_PutBit(self->Adc->pin,FALSE);  		    

    Lim_Dec = SENSOR_Decimales(val);
    
    #if !defined(_APARATO_VIEJO)
      if ( Lim_Dec < self->conf->iDecimales )
        set_Decimales(Lim_Dec,sensor);
    #else
      SENSOR_setDecimales(self,SENSOR_Decimales_Mostrar(val));
    #endif
      
 //   Sensores_OnSensorChange(num_canal);  
}
/*  Decimales */
/*
** ===================================================================
**     Method      :  SENSOR_setDecimales 
**    Description : Setea la cantidad de decimales
** ===================================================================
*/
byte SENSOR_setDecimales(struct TSensor_TermoPT * self, int val){
  byte err=EscribirByte((word)&(self->conf->iDecimales),val);
  														
//  Sensores_OnDecimalesChange(num_canal);
  
  return err;    
}

/*
** ===================================================================
**     Method      :  SENSOR_getDecimales 
**    Description :   Obtiene la cantidad de decimales
** ===================================================================
*/
int SENSOR_getDecimales(const struct TSensor_TermoPT * self){
  return self->conf->iDecimales;
}

/*
** ==========================================================================
**     Method      :  get_LimInf_Decimales 
**    Type:   Static
**    Description :   Obtiene el minimo valor de decimales que puede setearse
** ==========================================================================
*/
int get_LimInf_Decimales(void){
  return 0;
}

/*
** ==========================================================================
**     Method      :  get_LimSup_Decimales 
**    Description :   Obtiene el maximo valor de decimales que puede setearse
** ==========================================================================
*/
int get_LimSup_Decimales(const struct TSensor_TermoPT * self){
  return SENSOR_Decimales(self->conf->eSensor);
}

/*  Filtro  */
/*
** ===================================================================
**     Method      :  get_filtro 
**    Description :   Obtiene el valor del filtro
** ===================================================================
*/
int get_filtro(const struct TSensor_TermoPT * self){
  return self->conf->iFiltro;
}

/*
** ===================================================================
**     Method      :  set_filtro 
**    Description :   Setea el valor del filtro
** ===================================================================
*/
byte set_filtro(struct TSensor_TermoPT * self,int val){
  return EscribirByte((word)&(self->conf->iFiltro),val);
}

/*
** ===================================================================
**    Method      :   get_LimInf_filtro 
**    Type        :   Static
**    Description :   Lim inf del valor del filtro
** ===================================================================
*/
int get_LimInf_filtro(void){
  return 0;
}

/*
** ===================================================================
**    Method      :   get_LimSup_filtro 
**    Type        :   Static
**    Description :   Lim sup del valor del filtro
** ===================================================================
*/
int get_LimSup_filtro(void){
  return MAX_BYTE;
}

/*  Offset  */
/*
** ===================================================================
**     Method      :  get_offset 
**    Description :   Obtiene el valor del Offset
** ===================================================================
*/
int get_offset(const struct TSensor_TermoPT * self){
  return self->conf->iOffset;
}

/*
** ===================================================================
**     Method      :  set_offset 
**    Description :   Setea el valor del Offset
** ===================================================================
*/
byte set_offset(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iOffset),val);
}

/*  Ganancia  */
/*
** ===================================================================
**     Method      :  get_offset 
**    Description :   Obtiene el valor de la Ganancia
** ===================================================================
*/
int get_ganancia(const struct TSensor_TermoPT * self){
  return self->conf->iGanancia;
}

/*
** ===================================================================
**     Method      :  set_offset 
**    Description :   Setea el valor de la Ganancia
** ===================================================================
*/
byte set_ganancia(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iGanancia),val);
}

/*  Cero  Termopar  */
/*
** ===================================================================
**     Method      :  get_CeroTermopar 
**    Description :   Obtiene el valor del ajuste de cero para termopar 
** ===================================================================
*/
int get_CeroTermopar(const struct TSensor_TermoPT * self){
  return  self->conf->iCeroTermopar;
}

/*
** ===================================================================
**     Method      :  set_CeroTermopar 
**    Description :   Setea el valor del ajuste de cero para termopar 
** ===================================================================
*/
byte set_CeroTermopar(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iCeroTermopar),val);
}

/*  Ganancia  Termopar  */
/*
** ========================================================================
**     Method      :  get_GananciaTermopar 
**    Description :   Obtiene el valor del ajuste de ganancia para termopar 
** ========================================================================
*/
int get_GananciaTermopar(const struct TSensor_TermoPT * self){
  return  self->conf->iGananciaTermopar;
}

/*
** ======================================================================
**     Method      :  set_GananciaTermopar 
**    Description :   Setea el valor del ajuste de ganancia para termopar 
** ======================================================================
*/
byte set_GananciaTermopar(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iGananciaTermopar),val);
}

/*  Cero  PT100  */
/*
** =====================================================================
**     Method      :  get_CeroPT100 
**    Description :   Obtiene el valor del ajuste de cero para PT100 
** =====================================================================
*/
int get_CeroPT100(const struct TSensor_TermoPT * self){
  return  self->conf->iCeroPT100;
}

/*
** ===================================================================
**     Method      :  set_CeroPT100 
**    Description :   Setea el valor del ajuste de cero para PT100 
** ===================================================================
*/
byte set_CeroPT100(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iCeroPT100),val);
}

/*  Ganancia  PT100  */
/*
** =====================================================================
**     Method      :  get_GananciaPT100 
**    Description :   Obtiene el valor del ajuste de ganancia para PT100 
** =====================================================================
*/
int get_GananciaPT100(const struct TSensor_TermoPT * self){
  return  self->conf->iGananciaPT100;
}

/*
** =====================================================================
**     Method      :  set_GananciaPT100 
**    Description :   Setea el valor del ajuste de ganancia para PT100 
** =====================================================================
*/
byte set_GananciaPT100(struct TSensor_TermoPT * self,int val){
  return EscribirWord((word)&(self->conf->iGananciaPT100),val);
}

/*  */
/*
** =====================================================================
**     Method      :  get_AjTempAmb 
**    Description :   Obtiene el valor del Ajuste para compensar 
**                    la temperatura ambiente 
** =====================================================================
*/
int get_AjTempAmb(void){
  return  iCompensacionTempAmb;
}

/*
** =====================================================================
**     Method      :  set_AjTempAmb 
**    Description :   Setea el valor del Ajuste para compensar 
**                    la temperatura ambiente 
** =====================================================================
*/
byte set_AjTempAmb(int val){
  return EscribirWord((word)&iCompensacionTempAmb,val);
}

/* END Sensores. */
