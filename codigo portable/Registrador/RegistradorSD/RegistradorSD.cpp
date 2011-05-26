#include "RegistradorSD.hpp"
#include <stdio.h>
#include "System.hpp"

typedef struct{
  byte * texto;
  int tamanio;
}SerieTemporal;


RegistradorSD::RegistradorSD(const struct Array& serializables,ConfiguracionRegistrador& configuracion,SDFat& _sd):Registrador(serializables,configuracion),sd(_sd){
  //System::baseTiempo.addOnDateChangeListener(mCambioFecha);
 // int max = Array_count(&serializables);
 // texto.expandir(max*6); 
 // texto.setEstrategia(MINMEMORIA);
  //cambioFecha(this);
}

#warning medir cuanto tarda la ejecucion de este metodo
void RegistradorSD::registrar(){  

  const struct Array& serializables = getSerializables();
  int max = Array_count(&serializables);
  //texto.vaciar();
  int tamanioTotal=0;
  #warning esta funcion puede tardar mas del tiempo requerido, y enrealidad puede llamarse solo cuando hay un cambio de fecha, medir tiempos! Posible solucion: hace una base de tiempos que consulte al DS1307 cada tanto.
  cambioFecha(this);
  sd.fileOpen(nombreArchivo,MODIFY);
  FechaTiempo::TIMEREC time;
  System::getTime(time);
  char strTiempo[9];
  sprintf(strTiempo,"%02d:%02d:%02d",time.Hour,time.Min,time.Sec);
  sd.fileWrite((const VUINT8*)strTiempo,8);
  for(int i=0;i<max;i++){
    
    ElementoRegistrable * e = (ElementoRegistrable *)Array_get(&serializables,i); 
    if(e->getTipo()==ElementoRegistrable::TXT){
      int tamanio;
      const char* str = e->serializar(tamanio);
    //  texto.agregar(' ');
    //  texto.agregar(str);
    //  tamanioTotal+=tamanio;
      sd.fileWrite((const VUINT8*)"\t",1);
      sd.fileWrite((const VUINT8*)str,tamanio);
    }
  }
  sd.fileWrite((const VUINT8*)"\n",1);
  //sd.fileOpen(nombreArchivo,MODIFY);
  //sd.fileWrite((VUINT8*)texto.getCharP(),tamanioTotal);
  sd.fileClose();
}


void RegistradorSD::cambioFecha(void * self){
  FechaTiempo::DATEREC date;
  System::getDate(date);
  sprintf((char*)nombreArchivo,"LOG%d%02d%02d",date.Year,date.Month,date.Day);
}