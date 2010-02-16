
#include "SensorTermoPT100.hpp"
#include "Memoria/ManejadorMemoria.hpp"
#include "IAdc.hpp"
#include "Adc.hpp"
#include "WDog1.h"
#include "Math.h"
#include "funciones.h"
//#include "controlmath.h"
#include "PTSL.h"
#include "ADC.h"
#include "Math.hpp"
#include "CharPointer.hpp"

int * SensorTermoPT100::compensacionTempAmb=NULL;

SensorTermoPT100::SensorTermoPT100(Adc & _adc_, const SensorTermoPT100::TConfSensor & _conf, ManejadorMemoria & _manejadorMemoria):_adc(_adc_),configuracion(_conf),manejadorMemoria(_manejadorMemoria) {
  while(!_adc.isNewVal()) //Espera a q haya una conversión
    WDog1_Clear();
 
  setSensor(getSensor());  // inicializo Tipo con el valor guardado   
  procesar();  // Como hay un valor nuevo lo mando a procesar
}

unsigned char SensorTermoPT100::getDecimales() {
  return SENSOR_Decimales_Mostrar(getSensor());
}


void SensorTermoPT100::setDecimales(int val){
  manejadorMemoria.setByte((unsigned int * const)&configuracion.decimales,val);
}


Sensor::TSensorState SensorTermoPT100::getEstado() {
  return estado;
}

int SensorTermoPT100::getLimiteInferior() {
  int min_sens=SENSOR_Minimo(getSensor());      
  byte decimal_chan = SENSOR_Decimales(getSensor());      
  byte decimales=getDecimales();

  return min_sens/Math::pow10(decimal_chan-decimales);
}

int SensorTermoPT100::getLimiteSuperior() {
  int max_sens=SENSOR_Maximo(getSensor());
  byte decimal_chan = SENSOR_Decimales(getSensor());      
  byte decimales=getDecimales();

  if(SENSOR_is_Lineal(getSensor()))
    return max_sens; 
  else
    return max_sens/Math::pow10(decimal_chan-decimales); 
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
    int Ta_Temp= _adc.getTemperaturaAmbiente()  + *compensacionTempAmb*10/Math::pow10(SENSOR_Decimales(sensor));  //El menos inicial es porque el diodo esta conectado alreves 
    Sens_getColdComp(Ta_Temp,&CompTempAmb,sensor);
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
   
  switch (estado){
    case SENSOR_OK:
        byte sensor = getSensor();
        uchar decimales= SENSOR_Decimales_Mostrar(sensor);
        int val=valor;      											 
        val/= Math::pow10(SENSOR_Decimales(sensor)-decimales);  			//Ajusto el valor a mostrar por la cantidad de decimales del sensor
        os.writeAsFloat(val,decimales);
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
  return configuracion.sensor;
}

void SensorTermoPT100::setSensor(fbyte _sensor) {
  char err;
  
  err=manejadorMemoria.setByte((unsigned int * const)&configuracion.sensor , (fbyte)_sensor );
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
  return configuracion.filtro;
}

void SensorTermoPT100::setFiltro(unsigned char val) {
  manejadorMemoria.setByte((unsigned int * const)&configuracion.filtro,val);

}

int SensorTermoPT100::getOffset() {
  return configuracion.offset;
}

void  SensorTermoPT100::setOffset(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.offset,valor);
}

int SensorTermoPT100::getGanancia() {
  return configuracion.ganancia;
}

void  SensorTermoPT100::setGanancia(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.ganancia,valor);
}

int SensorTermoPT100::getCeroTermopar() {
  return configuracion.ceroTermopar;
}

void  SensorTermoPT100::setCeroTermopar(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.ceroTermopar,valor);
}

int SensorTermoPT100::getGananciaTermopar() {
  return configuracion.gananciaTermopar;
}

void  SensorTermoPT100::setGananciaTermopar(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.gananciaTermopar,valor);
}

int SensorTermoPT100::getCeroPT100() {
  return configuracion.ceroPT100;
}

void  SensorTermoPT100::setCeroPT100(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.ceroPT100,valor);
}

int SensorTermoPT100::getGananciaPT100() {
  return configuracion.gananciaPT100;
}

void  SensorTermoPT100::setGananciaPT100(int valor) {
  manejadorMemoria.setWord((unsigned int * const)&configuracion.gananciaPT100,valor);
}

int SensorTermoPT100::getAjusteTemperaturaAmbiente() {
  return *compensacionTempAmb;
}

void  SensorTermoPT100::setAjusteTemperaturaAmbiente(int valor) {
  manejadorMemoria.setWord((unsigned int * const)compensacionTempAmb,valor);
}

int SensorTermoPT100::getTiempoMuestreo() {
  return _TIEMPO_AD_EN_MILISEGUNDOS;
}

void SensorTermoPT100::addOnNuevoValorListener(const struct Method* metodo){
  Sensor::addOnNuevoValorListener(metodo);
}