#include "IO_Map.h"
#include "Display1.h"
#include "bits2ULN.h"
#include "bits5ULN.h"
#include "matriz.h"
#include "TimerFlag.h"
#include "Teclas.h"
#include "Object.h"
#include "Mydefines.h"
#include "display_teclas.h"
 
#pragma CONST_SEG DEFAULT

bool led[4];
struct TimerFlag ScrollTimer;
char  DigDpy[CANTIDAD_DISPLAYS][MAX_DIGITOS];		// caracteres decodificados del buffer ascii
byte Nletras[CANTIDAD_DISPLAYS];
static byte corrimiento[CANTIDAD_DISPLAYS];

#ifdef HD90
struct Timer HD90Timer;
#endif

void Display_Init(void){
  #ifdef HD90
  newAlloced(&HD90Timer,&Timer,(ulong)CHANGE_HD90_TEXT);
  #endif
  newAlloced(&ScrollTimer,&TimerFlag,(ulong)TIME_SCROLL);
}

void ResetScroll(void){
  int i;
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    corrimiento[i]=0;								//resetear variables de SCROLL
	Timer_setTime(&ScrollTimer,TIME_SCROLL*2);
	TimerFlag_reset(&ScrollTimer);
}

void PutValLed(bool val,byte num){
 led[num]=val;  
}

void Display_clrScreen(void){
  int i;
  ResetScroll();
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    Nletras[i]=0;  
}
/////////////////////////////////////////////////////////////////////
// Muestro texto en 7 segmentos y escaneo teclado
//
// IN:  nothing
// OUT: nothing
/////////////////////////////////////////////////////////////////////
static const byte  DigInfOn[DIGITOS]={0x10,0x20,0x40,0x80};		// señales de control del display
static const byte  DigSupOn[DIGITOS]={0x01,0x02,0x04,0x08};		// señales de control del display

#pragma INLINE
#ifdef HD90
void DpyAndSwitch(void)
{
  static byte digito=0;				// digito a visualizar (0-3)
  static byte display=_DPY_INF;		// display a refrescar (sup/inf) 	
  byte leds; //conjunto de leds a mostrar
  int i;
  //#ifdef HD90
  bool HD90_flag=Timer_isfinish(&HD90Timer);
  extern byte	KeyEdge;
  //#endif
 // bool Scroll=Timer_isfinish(&ScrollTimer);
  byte caracterAMostrar;
/* cada digito lo refresco cada 1 msg */
/* muestro display inferior */

  
  /*Corrimiento por scrolling*/
  if (TimerFlag_getFlag(&ScrollTimer)){
    bool scrolling=FALSE;
    byte dispActual = (HD90_flag)? _DPY_SUP:_DPY_INF;
    if (Nletras[dispActual]>DIGITOS)
    {
  	    corrimiento[dispActual]++;
        if (corrimiento[dispActual]==Nletras[dispActual]+DIGITOS)
          corrimiento[dispActual]=0;
        scrolling=TRUE;  		    
    }
    if(scrolling){
      TimerFlag_reset(&ScrollTimer);
      Timer_setTime(&ScrollTimer,TIME_SCROLL);  
    }
  }
  
  if(display==_DPY_INF)
  {
    
/* escaneo la ultima tecla */
  if (digito<DIGITOS){
    #ifdef _TECLAS
      if(digito==0)
        Switches(DigInfOn[digito]);
    #endif
    

    	if(!HD90_flag && (KeyEdge=='u' || KeyEdge=='d'))
		  KeyEdge=0;
    
    if(!HD90_flag){     
      Display1_PutVal(0);		//PTA
  	  bits2ULN_PutVal(0);
  	  bits5ULN_PutVal(DigSupOn[digito]);  //PTM


        /*de acuerco al corriemiento seteo  el caracterAMostrar*/
        caracterAMostrar=corrimiento[1]+digito;
        //Par de arriba 
        if (caracterAMostrar<Nletras[1])
          Display1_PutVal(DigDpy[1][caracterAMostrar]);  //PTA
        else
          Display1_PutVal(0);			// caracter vacio para Scroll
    }else{
      Display1_PutVal(0);  
    }
  } else {										//Muestro los leds (los puertos que seleccionan el digito ya se encuentran en el DL2)
    Display1_PutVal(0);	 //PTA
    #if NUM_SALIDAS>0
      if (led[0]==TRUE)
        leds=1;
      else
        leds=0;
      #if NUM_SALIDAS > 1
  	  if (led[1]==TRUE)
        leds|=2;
  	  #if NUM_SALIDAS > 2
  	  if (led[2]==TRUE)
        leds|=4;
  	  #if NUM_SALIDAS > 3
  	  if (led[3]==TRUE)
        leds|=8;
  	  #endif
  	  #endif
  	  #endif
  	  bits5ULN_PutVal(leds); 	 //PTM
  	#endif  
  }
  
  if(++digito==5)
  {
    digito=0;
    display=_DPY_SUP;
  }
  }  
  
/* muestro display superior */

  else
  {
  
/* el escaneo del teclado se hace luego del envio de la señal de ON
   del digito para que el pin PULL se encuentre estable */
  #ifdef _TECLAS    
  	if(digito>0)
  	  Switches(DigSupOn[digito]);
  #endif	
 
		
  #ifdef HD90
  	if(!HD90_flag && (KeyEdge=='u' || KeyEdge=='d'))
  	  KeyEdge=0;
    if (KeyEdge=='r' || KeyEdge=='f'){
      HD90_flag = 0;
     
       Timer_setTime(&HD90Timer,CHANGE_HD90_TEXT);
     
    }
   
     
  #endif
  
  if(HD90_flag){
  	Display1_PutVal(0);		 //PTA
  	bits2ULN_PutVal(0);
  	bits5ULN_PutVal(DigSupOn[digito]);  //PTM
      /*de acuerco al corriemiento seteo  el caracterAMostrar*/
      caracterAMostrar=corrimiento[0]+digito;
      if (caracterAMostrar<Nletras[0])
        Display1_PutVal(DigDpy[0][caracterAMostrar]);  //PTA
      else
        Display1_PutVal(0);			// caracter vacio para Scroll
  }else{
    Display1_PutVal(0);  
  }
  if(++digito==4)
  {
    digito=0;

    display=_DPY_INF;


  }
  }  
		  
  

}


#else


void DpyAndSwitch(void)
{
  static byte digito=0;				// digito a visualizar (0-3)
  static byte display=_DPY_INF;		// display a refrescar (sup/inf) 	
  byte leds; //conjunto de leds a mostrar
  int i;
  //#ifdef HD90
  //bool HD90_flag=Timer_isfinish(&HD90Timer);
  //extern byte	KeyEdge;
  //#endif
 // bool Scroll=Timer_isfinish(&ScrollTimer);
  byte caracterAMostrar;
/* cada digito lo refresco cada 1 msg */
/* muestro display inferior */

  
  /*Corrimiento por scrolling*/
  if (TimerFlag_getFlag(&ScrollTimer)){
    bool scrolling=FALSE;
    for(i=0;i<CANTIDAD_DISPLAYS;i++){
      if (Nletras[i]>DIGITOS)
      {
    	    corrimiento[i]++;
          if (corrimiento[i]==Nletras[i]+DIGITOS)
            corrimiento[i]=0;
          scrolling=TRUE;  		    
      }
      if(scrolling){
        TimerFlag_reset(&ScrollTimer);
        Timer_setTime(&ScrollTimer,TIME_SCROLL);  
      }
    }
  }
  
  if(display==_DPY_INF)
  {
    
/* escaneo la ultima tecla */
  if (digito<DIGITOS){

      
    #ifdef _TECLAS
      if(digito==0)
        Switches(DigInfOn[digito]);
    #endif
    
    #ifdef HD90
    	if(!HD90_flag && (KeyEdge=='u' || KeyEdge=='d'))
		  KeyEdge=0;
    #endif
    
    Display1_PutVal(0);		//PTA
    if(digito<2)					// PTM
    {  
      bits2ULN_PutVal(0);		//PTJ
      bits5ULN_PutVal(DigInfOn[digito]); //PTM
    }
    
    else 
    {
      bits5ULN_PutVal(0);
      bits2ULN_PutVal(DigInfOn[digito]);		// PTJ
      
    };
      /*de acuerco al corriemiento seteo  el caracterAMostrar*/
      caracterAMostrar=corrimiento[1]+digito;
      //Par de arriba 
      if (caracterAMostrar<Nletras[1])
        Display1_PutVal(DigDpy[1][caracterAMostrar]);  //PTA
      else
        Display1_PutVal(0);			// caracter vacio para Scroll
  } else {										//Muestro los leds (los puertos que seleccionan el digito ya se encuentran en el DL2)
    Display1_PutVal(0);	 //PTA
    #if NUM_SALIDAS>0
      if (led[outc1L]==TRUE)
        leds=1;
      else
        leds=0;
      #if NUM_SALIDAS > 1
  	  if (led[outa1L]==TRUE)
        leds|=2;
  	  #if NUM_SALIDAS > 2
  	  if (led[outa2L]==TRUE)
        leds|=4;
  	  #if NUM_SALIDAS > 3
  	  if (led[outa3L]==TRUE)
        leds|=8;
  	  #endif
  	  #endif
  	  #endif
  	  bits5ULN_PutVal(leds); 	 //PTM
  	#endif  
  }
  
  if(++digito==5)
  {
    digito=0;
    display=_DPY_SUP;
  }
  }  
  
/* muestro display superior */

  else
  {
  
/* el escaneo del teclado se hace luego del envio de la señal de ON
   del digito para que el pin PULL se encuentre estable */
  #ifdef _TECLAS    
  	if(digito>0)
  	  Switches(DigSupOn[digito]);
  #endif	
 
		
  #ifdef HD90
  	if(!HD90_flag && (KeyEdge=='u' || KeyEdge=='d'))
  	  KeyEdge=0;
    if (KeyEdge=='r' || KeyEdge=='f'){
      HD90_flag = 0;
      Timer_setTime(&HD90Timer,CHANGE_HD90_TEXT);
    }
  #endif
  
	Display1_PutVal(0);		 //PTA
	bits2ULN_PutVal(0);
	bits5ULN_PutVal(DigSupOn[digito]);  //PTM
    /*de acuerco al corriemiento seteo  el caracterAMostrar*/
    caracterAMostrar=corrimiento[0]+digito;
    if (caracterAMostrar<Nletras[0])
      Display1_PutVal(DigDpy[0][caracterAMostrar]);  //PTA
    else
      Display1_PutVal(0);			// caracter vacio para Scroll
  if(++digito==4)
  {
    digito=0;

    display=_DPY_INF;


  }
  }  
		  
  

}

#endif
///////////////////////////////////////////////////////////////////////
// Rutina de decodificacion de caracteres ASCII a 7 segmentos
//
// IN:  Buffer conteniendo caracteres ASCII.
// OUT: Buffer decodificado para 7 segmentos.
///////////////////////////////////////////////////////////////////////

void AsciiTo7Seg(char* ptrs, byte Num_display,byte Dot)
{
  byte i, Temp8, DigTmp;
	
	if(Nletras[Num_display]>4)		 // En el anterior hubo scrolling?
    ResetScroll();	
	  

	Nletras[Num_display]=0;
		 
  for(i=0; *ptrs!='\0'; i++)	// los N digitos
  {
    Temp8=*ptrs;
    Temp8-='-';
    
    if(*ptrs=='.' && Nletras[Num_display]){			 // Agrego el punto en el digito anterior 	
      ptrs++;
      DigDpy[Num_display][Nletras[Num_display]-1]|=0x80;
      continue;
    }
 	
    if((*ptrs)!=' ')
      DigTmp=(byte)Car_Ini[Temp8];
    else 	
      DigTmp=0x00;

    /* enciendo punto decimal de acuerdo a Cdt en la pantalla principal */
    if(Dot==3-Nletras[Num_display])
      DigTmp|=0x80;  
    if(Dot==0 && Nletras[Num_display]==3)
      DigTmp&=0x7F; 

    
    DigDpy[Num_display][Nletras[Num_display]]=DigTmp;
    Nletras[Num_display]++;
    
    ptrs++;    
  
  }
  
  
} 