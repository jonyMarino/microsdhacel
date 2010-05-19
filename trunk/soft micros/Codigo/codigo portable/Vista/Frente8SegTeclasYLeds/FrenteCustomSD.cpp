#include "FrenteCustomSD.hpp"
#include "TimerHard/int1ms_40ms_handler/timer_interrupt.h"

/*FrenteCustom()*/
FrenteCustomSD::FrenteCustomSD():scrollTimer(TIME_SCROLL),leds(0),barrido(0),barridoTeclas(0),teclasPresionadas(0),posiblesTeclas(0),debounce(0){      
  mOn1ms.pmethod = on1msStatic;
  mOn1ms.obj = this;
  add1msListener(&mOn1ms);
}

void FrenteCustomSD::on1msStatic(void*_self){
  FrenteCustomSD * self = (FrenteCustomSD *)_self;
  self->on1ms();    
}

/*setLed()*/
void FrenteCustomSD::setLed(bool val,byte num){
 if(val)
  leds|= 1<<num;
 else
  leds&=~(1<<num);
}

/*resetScroll()*/
void FrenteCustomSD::resetScroll(void){
  int i;
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    getDisplay(i)->resetearCorrimiento();	//resetear variables de SCROLL
	scrollTimer.setTime(TIME_SCROLL*2);
	scrollTimer.reset();
}
/*borrar()*/
void FrenteCustomSD::borrar(void){
  int i;
  resetScroll();
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    getDisplay(i)->borrar();  
}
/*on1ms()*/
void FrenteCustomSD::on1ms(){
  /* refresco todo el frente cada 1 msg*barridos */
  
  
  if(barrido==DIGITOS*CANTIDAD_DISPLAYS){    //llegue al final?
    encenderLeds(leds);
    barrido=0;
    return;
  }
  
  DisplaySD * display = getDisplay(barrido/DIGITOS);
  
  /* Tengo que encender un digito o checkear una tecla*/
  /*Corrimiento por scrolling*/
  if (scrollTimer.getFlag()){
    bool scrolling=FALSE;
    for(int i=0;i<CANTIDAD_DISPLAYS;i++){
      DisplaySD * d = getDisplay(i);
      if (d->isScrolling())
      {
    	    d->incrementarCorrimiento();
          scrolling=TRUE;  		    
      }
    }
    if(scrolling){
      scrollTimer.reset();
      scrollTimer.setTime(TIME_SCROLL);  
    }
  }
  
  /* el escaneo del teclado se hace luego del envio de la señal de ON
   del digito para que el pin PULL se encuentre estable */  
  actualizarTeclas();
  display->apagar();
  seleccionarDigito(barrido);
  display->imprimirDigito(barrido%DIGITOS);
  ++barrido;  //actualizo el paso de barrido
}

/* se fija si se encuentra el barrido en la posicion para leer una tecla, el barrido se encuentra en la posicion anterior para mayor estabilidad*/
void FrenteCustomSD::actualizarTeclas(){
  byte tecla = getTeclaPosicion(barrido);
  if(!tecla) return;  //no es la posicion del barrido que corresponde a la lectura de una letra
  
  if(isTeclaPresionada()) teclasPresionadas|=tecla;
                     
	barridoTeclas++;
	if(barridoTeclas!=CANTIDAD_TECLAS)
	  return;	  
  barridoTeclas=0;				// reinicia
	
  if(teclasPresionadas!=posiblesTeclas) // proceso del debounce
  {
	  debounce=CANTIDAD_VALIDACIONES;
	  posiblesTeclas=teclasPresionadas;
  }
  teclasPresionadas=0;
  

  if(debounce!=0) {
  	--debounce;
  	return;		
  }
  //la posible tecla realmente fue presionada y se debe procesar
  teclas.presionar(posiblesTeclas);
  
}

byte FrenteCustomSD::getTecla(){
  return teclas.getTecla();
}

Teclas& FrenteCustomSD::getTeclas(){
  return teclas;
}
