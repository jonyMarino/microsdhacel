
#include "PWMSoft.hpp"
#include "pwm_periodos.h"

void onCambio(void * self);

PWMSoft* PWMSoft::pwmSoft_=NULL;

static const ulong periodos[]={   
  100,											//100 ms
  200,											//200 ms
  500 ,											//500 ms
  1000 ,											//1s
  2000 ,											//2s
  5000, 											//5s
  10000, 											//10s
  20000,											//20s
  50000,											//50s
  5   											  //5ms
};




const struct Method PWMSoft::onChg={
onCambio,NULL
};


PWMSoft::PWMSoft(struct ManejadorMemoria &_manejadorMemoria,byte * _salida,TConfPWM &_conf, uchar pin_out):PWM(_manejadorMemoria,_conf){
  pwmSoft_=this;
  salida=_salida;
  mascara=1<<pin_out;
  time=new MethodTimer(periodos[_conf.periodo],onChg);
  ((MethodTimer*)time)->stop(); 
}

void PWMSoft::setPotencia(unsigned int potencia){
  if(getTipoSalida()==SALIDA_ONOFF){		    
    if(potencia==0)
      clrReg8Bits(*salida, mascara);             
    else
      setReg8Bits(*salida, mascara);            
  }
  PWM::setPotencia(potencia);
}   

void PWMSoft::setPotenciaGuardada(){

  unsigned int potencia = getPotencia();
  if(getTipoSalida()==SALIDA_PROPORCIONAL){ 
   ((MethodTimer*)time)->stop();  
    if(potencia!=0){
      setReg8Bits(*salida, mascara);  
      ((MethodTimer*)time)->setTime(periodos[getPeriodo()]* potencia/1000);
    }else{
      clrReg8Bits(*salida, mascara);  
      ((MethodTimer*)time)->setTime(periodos[getPeriodo()]);
    }  
  }
}

unsigned char PWMSoft::setPeriodo(TPeriod period){
  unsigned char err;
  if(period<0 || period>PWM_MAX_VALUE_PERIODS)
    return ERR_VALUE; //error
  err= PWM::setPeriodoConfiguracion(period);
  if(!err){
    if(getTipoSalida()==SALIDA_PROPORCIONAL)
      setPotenciaGuardada();
  }
  return err;
}

void PWMSoft::setTipoSalida(TipoSalida tipoSalida){

  if(tipoSalida==SALIDA_ONOFF){
    ((MethodTimer*)time)->stop();
   }else{
     ((MethodTimer*)time)->restart(); 
     setPotenciaGuardada();
   }
}

TipoSalida PWMSoft::getTipoSalida(){
 return (((MethodTimer*)time)->isFinished())?SALIDA_ONOFF:SALIDA_PROPORCIONAL;
}


bool PWMSoft::getEstadoSalida (){
return (bool)(*salida|mascara);
}

void onCambio(void * self){
  PWMSoft* pwmSoft=PWMSoft::pwmSoft_;
  int pot = ((PWM*)pwmSoft)->getPotencia();
  unsigned long tiempoEnUno=(unsigned long)(periodos[((PWM*)pwmSoft)->getPeriodo()]* pot)/1000;
  if(testReg8Bits(*(((PWMSoft*)pwmSoft)->salida),((PWMSoft*)pwmSoft)->mascara)){    
    if( pot == 1000 )
      return;
    else{
      unsigned long tiempo = (unsigned long)(periodos[((PWM*)pwmSoft)->getPeriodo()]* (1000-pot))/1000;
      if((periodos[((PWM*)pwmSoft)->getPeriodo()]-tiempoEnUno)>tiempo)
        tiempo=(periodos[((PWM*)pwmSoft)->getPeriodo()]-tiempoEnUno);
      if(!tiempo)  //no alcanzo la resolucion
        return;
      clrReg8Bits(*(((PWMSoft*)pwmSoft)->salida),((PWMSoft*)pwmSoft)->mascara);
      ((MethodTimer*)(((PWMSoft*)pwmSoft)->time))->setTime(tiempo);
    }
  }else{
    if( pot == 0 )
      return;
    else{
      unsigned long tiempo=tiempoEnUno;
      if(!tiempo) //no alcanzo la resolucion
        return;
      setReg8Bits(*(((PWMSoft*)pwmSoft)->salida),((PWMSoft*)pwmSoft)->mascara);
      ((MethodTimer*)(((PWMSoft*)pwmSoft)->time))->setTime(tiempo);
    }
  }
  
}

