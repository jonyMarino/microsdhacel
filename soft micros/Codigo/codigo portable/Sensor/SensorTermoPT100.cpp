
#include "SensorTermoPT100.hpp"
#include "ManejadorMemoria.h"
#include "IAdc.hpp"
#include "Adc.hpp"
#include "WDog1.h"
#include "Math.h"
#include "funciones.h"
#include "str_lib.h"
#include "PTSL.h"
#include "ADC.h"
#include "Math.h"

int * SensorTermoPT100::compensacionTempAmb=NULL;

SensorTermoPT100::SensorTermoPT100(Adc & _adc_, const SensorTermoPT100::TConfSensor & _conf, struct ManejadorMemoria & _manejadorMemoria):_adc(_adc_),configuracion(_conf),manejadorMemoria(_manejadorMemoria) {
  while(!_adc.isNewVal()) //Espera a q haya una conversión
    WDog1_Clear();
 
  setSensor(getSensor());  // inicializo Tipo con el valor guardado   
  procesar();  // Como hay un valor nuevo lo mando a procesar
}

unsigned char SensorTermoPT100::getDecimales() {
  return SENSOR_Decimales_Mostrar(getSensor());
}


void SensorTermoPT100::setDecimales(int val){
  _MANEJADOR_MEMORIA_SET_BYTE(&manejadorMemoria,(unsigned int * const)&configuracion.decimales,val);
}


Sensor::TSensorState SensorTermoPT100::getEstado() {
  return estado;
}

int SensorTermoPT100::getLimiteInferior() {
  int min_sens=SENSOR_Minimo(getSensor());      
  byte decimal_chan = SENSOR_Decimales(getSensor());      
  byte decimales=getDecimales();

  return min_sens/pow10(decimal_chan-decimales);
}

int SensorTermoPT100::getLimiteSuperior() {
  int max_sens=SENSOR_Maximo(getSensor());
  byte decimal_chan = SENSOR_Decimales(getSensor());      
  byte decimales=getDecimales();

  if(SENSOR_is_Lineal(getSensor()))
    return max_sens; 
  else
    return max_sens/pow10(decimal_chan-decimales); 
}

int SensorTermoPT100::getVal() {
  return valor;
}

/**
 * reesmplazo de SenTPT_Handler
 */
bool SensorTermoPT100::checkADC()
{
  if( _adc.isNewVal() ){
    procesar();
    return TRUE;
  }else
     return FALSE;
}

void SensorTermoPT100::procesar() {
  long ValProv;
  int ValLin;
  TSensorState err; 
  long vx= _adc.getVal();
  t_sensor sensor=configuracion.sensor; 
  int ceroTP=configuracion.ceroTermopar;					 //Cero Termopar
  int ganTP = configuracion.gananciaTermopar;
  int ceroPT = configuracion.ceroPT100;
  int ganPT=configuracion.gananciaPT100;
  int offset= configuracion.offset;
  int ganancia = configuracion.ganancia;
  int filtro = configuracion.filtro;
  int CompTempAmb=0;
  
  if (sensor<SENSOR_PT){  
    int Ta_Temp= _adc.getTemperaturaAmbiente()  + *compensacionTempAmb*10/pow10(SENSOR_Decimales(sensor));  //El menos inicial es porque el diodo esta conectado alreves 
    Sens_getColdComp(Ta_Temp,&CompTempAmb,sensor);
    setConfiguracionTemperaturaAmbiente(&Ta_Temp);
  }
  vx=(vx+ceroTP)*(1000+ganTP)/1000;
  vx = vx*MAXMV/MAXAD;//Convierte de lineal a microvolts para los sensores correspondientes 
  err = Linealizar(vx+CompTempAmb,sensor,&ValLin);
  ValProv=ValLin;  
	if(sensor==SENSOR_PT)
    ValProv = ((ValProv+ceroPT)*(1000+ganPT)/1000);  
	 
	ValProv=(ValProv+offset)*ganancia/1000;         //preciso para pasar a long
  ValProv= filtrar ((int)ValProv,filtro,10,200,&bufferFiltro);
  
  Cpu_DisableInt();
  valor=ValProv;
  estado=err;
  Cpu_EnableInt();         
  
  //Eventos
  callOnNuevoValorListeners();
  //Fin Eventos
}

void SensorTermoPT100::print(OutputStream& os) {
  byte sensor = getSensor();
  byte decimales= SENSOR_Decimales_Mostrar(sensor);
  int Val=valor; 
  											 
  Val/= pow10(SENSOR_Decimales(sensor)-decimales);  			//Ajusto el valor a mostrar por la cantidad de decimales del sensor
   
  switch (estado){
    case SENSOR_OK:
        char str[6];
        FloatToStr(Val,str,6,decimales);
        os.write(str);//(uchar)_getDec(self));
    break;

    case SENSOR_OF:
        os.write(" OF ");
    break;

    case SENSOR_UF:
        os.write(" UF ");
    break;
  }
}

static void SensorTermoPT100::setConfiguracionTemperaturaAmbiente(int * ta){
  
  compensacionTempAmb = ta;
}


fbyte SensorTermoPT100::getSensor() {
  return TConfSensor.sensor;
}

void SensorTermoPT100::setSensor(fbyte _sensor) {
  char err;
  
  err=_MANEJADOR_MEMORIA_SET_BYTE((struct ManejadorMemoria*)&manejadorMemoria,(unsigned int * const)&configuracion.sensor , (fbyte)_sensor );
  if(!err){
    err= onSensorChange(_sensor);
  }
  
}

fbyte SensorTermoPT100::getLimSupSensor() {
  return NUM_SENSORES-1;  
}

char SensorTermoPT100::onSensorChange(fbyte val) {
   byte Lim_Dec;

    if (val==SENSOR_PT) 
      PTSL_PutBit(_adc.pin ,TRUE);
    else 
      PTSL_PutBit(_adc.pin,FALSE);  		    

    Lim_Dec = SENSOR_Decimales(val);
    
    bufferFiltro=0; // vuelvo el filtro a 0
    
    /*#if !defined(_APARATO_VIEJO)
      if ( Lim_Dec < getDecimales())
        set_Decimales(Lim_Dec,sensor);
    #else
      SenTPT_setDecimales(self,SENSOR_Decimales_Mostrar(val));
    #endif
      */
    return ERR_OK;

}

unsigned char SensorTermoPT100::getFiltro() {
  return TConfSensor.filtro;
}

void SensorTermoPT100::setFiltro(unsigned char val) {
  _MANEJADOR_MEMORIA_SET_BYTE(&manejadorMemoria,(unsigned int * const)&configuracion.filtro,val);

}

int SensorTermoPT100::getOffset() {
  return TConfSensor.offset;
}

void  SensorTermoPT100::setOffset(int valor) {
  _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria, (unsigned int * const)&configuracion.offset,valor);
}

int SensorTermoPT100::getGanancia() {
  return TConfSensor.ganancia;
}

void  SensorTermoPT100::setGanancia(int valor) {
 _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria, (unsigned int * const)&configuracion.ganancia,valor);
}

int SensorTermoPT100::getCeroTermopar() {
  return TConfSensor.ceroTermopar;
}

void  SensorTermoPT100::setCeroTermopar(int valor) {
  _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria,(unsigned int * const)&configuracion.ceroTermopar,valor);
}

int SensorTermoPT100::getGananciaTermopar() {
  return TConfSensor.gananciaTermopar;
}

void  SensorTermoPT100::setGananciaTermopar(int valor) {
  _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria,(unsigned int * const)&configuracion.gananciaTermopar,valor);
}

int SensorTermoPT100::getCeroPT100() {
  return TConfSensor.ceroPT100;
}

void  SensorTermoPT100::setCeroPT100(int valor) {
  _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria,(unsigned int * const)&configuracion.ceroPT100,valor);
}

int SensorTermoPT100::getGananciaPT100() {
  return TConfSensor.gananciaPT100;
}

void  SensorTermoPT100::setGananciaPT100(int valor) {
 _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria,(unsigned int * const)&configuracion.gananciaPT100,valor);
}

int SensorTermoPT100::getAjusteTemperaturaAmbiente() {
  return *compensacionTempAmb;
}

void  SensorTermoPT100::setAjusteTemperaturaAmbiente(int valor) {
  _MANEJADOR_MEMORIA_SET_WORD(&manejadorMemoria,(unsigned int * const)compensacionTempAmb,valor);
}

int SensorTermoPT100::getTiempoMuestreo() {
  return _TIEMPO_AD_EN_MILISEGUNDOS;
}

