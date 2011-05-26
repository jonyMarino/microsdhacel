#include "Teclas.hpp"

#define TRETURN 30000 
#define TIME_TIMER 4						 
/*  Definicion de nombre de tecla y su forma de ser invocada*/

/* definiciones del teclado */
#define KEY_RAMPA_INI	60 /*A los cuantos ingresos(la primera vez) iguales se repite la salida para ese pulsador*/
#define KEY_RAMPA_FIN	0  /*Maxima velociadad de ingresos iguales a los que se repite la salida para ese pulsador*/
#define KEY_DELTA	1  /*Variacion de velociadad una vez realizada la salida*/

/* Posicion de cada tecla*/
#if defined( DEBUG) && !defined(_DISPLAY_2x4)
  #define KEY_NULL		0X00
  #define KEY_UP      0x04
  #define KEY_DOWN    0x02
  #define KEY_RESET   0x10
  #define KEY_ENTER   0x01
#else

  #define KEY_NULL		0X00
  #define KEY_UP      0x04
  #define KEY_DOWN    0x08
  #define KEY_RESET   0x10
  #define KEY_ENTER   0x02

#endif


typedef struct {
  char nombre;
  byte teclas;
}t_key;

const t_key keys[]={
  'c',KEY_UP | KEY_ENTER,
  's',KEY_DOWN | KEY_RESET,
  'p',KEY_UP | KEY_DOWN | KEY_RESET,
  0,0
};

typedef struct {
  char nombre;				// se va a activar al soltar la tecla
  char nombre_hold;
  byte tecla;
  byte factor; //sobre 10
  bool restart;
}t_hold_key;

const t_hold_key hold_keys[]={
  'k','m',KEY_RESET,9,TRUE,
  'r','f',KEY_ENTER,9,TRUE,
  'u','u',KEY_UP,10,FALSE,
  'd','d',KEY_DOWN,10,FALSE,
  'v','v',KEY_ENTER|KEY_UP,4,FALSE,
  0,0,0,0
};


															
Teclas::Teclas():contadorTimePass(0),teclas(0),teclaAnterior(0),teclaAnteriorTmp(0),rampa(0),contadorRampa(0){
  mOnTime.obj = this;
  mOnTime.pmethod = Teclas::onTimeStatic;
  timer = new RlxMTimer(TIME_TIMER,mOnTime);
}


void Teclas::onTimeStatic(void * _self){
  Teclas * self = (Teclas*)_self;
  self->onTime();
}

void Teclas::onTime(){
     if(contadorTimePass)
      contadorTimePass--;
     if (teclaAnterior!=teclasIngresadas){
  	  for(int i=0;keys[i].nombre!=0;i++){
  	    if(keys[i].teclas==teclasIngresadas){
  	     tecla=keys[i].nombre;
  	     break;
  	    }
  	 }

  	  if(teclasIngresadas==KEY_NULL){
  	    for(int i=0;hold_keys[i].nombre!=0;i++){				 // Al soltar para los que tienen otra funcion en toque mantenido
    	    if(hold_keys[i].tecla==teclaAnterior && hold_keys[i].nombre_hold!=teclaAnteriorTmp){
    	     tecla=hold_keys[i].nombre;
    	     break;
    	    }
  	    }
  	    teclaAnteriorTmp=' ';
  	  }
  	  resetTimePass();
  	  teclaAnterior = teclasIngresadas;
  	  contadorRampa=0;
  	  rampa=KEY_RAMPA_INI;
  }
	  
  /*  Parte de Teclas Sostenidas  */
  if(teclaAnterior==0) return;
  if(contadorRampa<rampa)
	  contadorRampa++;
  else{
	  contadorRampa=0;
	  if(rampa>KEY_RAMPA_FIN)
		  rampa-=KEY_DELTA;

		for(int i=0;hold_keys[i].nombre!=0;i++){				 // Al soltar para los que tienen otra funcion en toque mantenido
  	    if(hold_keys[i].tecla==teclaAnterior && rampa<=(word)KEY_RAMPA_INI*hold_keys[i].factor/10){
  	     teclaAnteriorTmp=tecla=hold_keys[i].nombre_hold;
  	     if(hold_keys[i].restart)
  	      rampa=KEY_RAMPA_INI;
  	     break;
  	    }
		}
	  resetTimePass();
  }  
}

void Teclas::presionar(byte teclas){
  teclasIngresadas = teclas;  
}


/*  Obtiene la tecla presionada*/
byte Teclas::getTecla(void){  
  byte t = tecla;
  tecla = 0; 
  return t;
}

void Teclas::resetTimePass(){
  contadorTimePass = TRETURN/TIME_TIMER;  
}

/*  Avisa si paso el tiempo de espera de tecla */
bool Teclas::isTimePass(void){
  return contadorTimePass==0;
}