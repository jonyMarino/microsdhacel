#include "FrenteCustomSD.hpp"
#include "TimerHard/int1ms_40ms_handler/timer_interrupt.h"


FrenteCustomSD::FrenteCustomSD(){      
  //FrenteCustom();
}

/*on1ms()*/
void FrenteCustomSD::on1ms(){
  /* refresco todo el frente cada 1 msg*barridos */
  
  
  if(barrido==DIGITOS*CANTIDAD_DISPLAYS){    //llegue al final?
    encenderLeds(leds);
    barrido=0;
    return;
  }
  
  DisplaySD * display1 = getDisplaySD(barrido/DIGITOS);
  Display * display2 = getDisplay(barrido/DIGITOS);
    
  /* Tengo que encender un digito o checkear una tecla*/
  /*Corrimiento por scrolling*/
  if (scrollTimer.getFlag()){
    bool scrolling=FALSE;
    for(int i=0;i<CANTIDAD_DISPLAYS/2;i++){
      DisplaySD * sd = getDisplaySD(i);
      Display * d = getDisplay(i);
      if (sd->isScrolling())
      {
    	    sd->incrementarCorrimiento();
          scrolling=TRUE;  		    
      }
      
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
  display1->apagar();
  display2->apagar();
  
  seleccionarDigito(barrido);
  display1->imprimirDigito(barrido%DIGITOS);
  display2->imprimirDigito(barrido%DIGITOS);
  ++barrido;  //actualizo el paso de barrido
}

