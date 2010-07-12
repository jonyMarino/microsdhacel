
#include "AutoSintonia.hpp"

#define TIEMPO_ABIERTO_MAXIMO 4000
#define HISTERESIS_AUTO_SINTONIA 4

int AutoSintonia::ConfValControl::getValorControlador(){
  return setPointControl;
}

AutoSintonia::ConfAdaptSalida::getHisteresis(){
  return  HISTERESIS_AUTO_SINTONIA;
}

TipoSalida AutoSintonia::ConfAdaptSalida::getTipoSalida(){
  return SALIDA_ONOFF;
}

void AutoSintonia::addOnChangeListener(const struct Method& metodo){
  onChange.add((void*)&metodo);
}
void AutoSintonia::deleteOnChangeListener(const struct Method& metodo){
  onChange.moveOut((void*)&metodo);
}


AutoSintonia::AutoSintonia(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion):LazoControl(sensor),valControl(confValControl,sensor),adaptSalida(salida,confAdaptSalida),confControl(configuracion),contadorTiempoAbierto(TIEMPO_ABIERTO_MAXIMO){
  init(configuracion);
}

AutoSintonia::AutoSintonia(Sensor& sensor,ISalida& salida,const ConfiguracionControl& configuracion,MethodContainer& listenersOnChange):LazoControl(sensor),valControl(confValControl,sensor),adaptSalida(salida,confAdaptSalida),confControl(configuracion),contadorTiempoAbierto(TIEMPO_ABIERTO_MAXIMO),onChange(listenersOnChange){
  init(configuracion);
}

void AutoSintonia::init(const ConfiguracionControl& configuracion){
  confValControl.setPointControl = configuracion.getSetPoint();
  LazoControl::valorControl = &valControl;
  LazoControl::adaptadorSalida = &adaptSalida;
  paso = 0;
  byte paso = 0;
  valorPrevio = 0;
  maximo = 0;
  minimo = 0;
}

bool AutoSintonia::isDetenido(){
  if(paso == 5 || paso ==6) 
    return TRUE;
  return FALSE;
}

//bool AutoSintonia::error(){
//  return FALSE;
//}                                                                                                                                                                                      

int AutoSintonia::getNumeroEstado(){
  return paso;
}

int AutoSintonia::getConfiguracionSetPoint(){
  return  confControl.getSetPoint();
}

void AutoSintonia::setConfiguracionSetPoint(int val){
  confControl.setSetPoint(val);
}

void AutoSintonia::onNuevoValorSensor(){
  LazoControl::onNuevoValorSensor();

// primero hago el control onoff  

       /* Prop = proporcional (ValFinal[chan],								        //calculo señal de error
													 spaut
													 );
  
        dutystn =  duty_onoff(dutystn,                              //hago accion onoff
                              Prop, 
                              -HISTERESIS_AUTO_SINTONIA 
                              );
        */
  if(paso == 5 || paso==6)
    return;
  
  /*if (contadorTiempoAbierto.getFlag()){    
    paso=6;                              //veo si me pase y pongo error
    return;
  } */  //comento para poderlo probar manualmente
  
 int valorSensor = getSensor().getVal();  

 switch(paso){							          					             //estoy en el paso cero que es comienzo abajo. 


//En paso 0 no hago nada hasta que suba la temp por arriba del sp. Cuando sube pongo paso 1
   case 0: 
   			  if (valorSensor>= (confControl.getSetPoint()+HISTERESIS_AUTO_SINTONIA/2)){    //Si subo pongo paso 1
            paso++;																		 //
				    contadorTiempoAbierto.restart();																 //paro el abort
          } 
   break;																										 //y me voy

//En paso 1 solo espero pasar abajo
   case 1: 
          if (valorSensor <= (confControl.getSetPoint()-HISTERESIS_AUTO_SINTONIA/2)){ //si bajo
            paso++;														         //pongo paso 2
            contadorTiempoAbierto.restart();																 //paro el abort
            valorPrevio = valorSensor;                           //e inicio detector de minima
          }
   break;

//En paso 2 detecto minimo, comienzo cuenta, y espero paso siguiente
   case 2: 
          if (valorSensor < valorPrevio)                   //es minimo?
            valorPrevio = valorSensor;    								       //si, nuevo minimo
          if (valorSensor>= (confControl.getSetPoint()+HISTERESIS_AUTO_SINTONIA/2)){    //pase el sp?
            paso++;                             				        //pongo paso 3
    				contadorTiempoAbierto.restart();										//paro el abort
            minimo = valorPrevio;                               //pero guardo minimo
          }
	 break;

//En paso 3 busco maximo
   case 3: 
        if (valorSensor > valorPrevio)									   //es maximo?
          valorPrevio = valorSensor;            							 //nuevo maximo
        if (valorSensor<= (confControl.getSetPoint()-HISTERESIS_AUTO_SINTONIA/2)){    //pase el sp?
          paso++;                             				 //pongo paso 4
  				contadorTiempoAbierto.restart();																 //paro el abort
          maximo = valorPrevio;                               //pero guardo maximo
        }
   break;

//En paso 4 busco nuevo munimo
   case 4: 
      if (valorSensor<valorPrevio)										   //busco minimo
        valorPrevio = valorSensor;  
      if (valorSensor>= (confControl.getSetPoint()+HISTERESIS_AUTO_SINTONIA/2)){    //pase el sp?
        paso++;                             				 //pongo paso 5 (ciclo terminado)
  			uint contadorSegundos=contadorTiempoAbierto.getCuenta();
  			confControl.setHisteresis((maximo-minimo)*2);																 
        confControl.setIntegral(contadorSegundos);
        confControl.setDerivada(contadorSegundos/10);
      }
	 break;

 }
}
