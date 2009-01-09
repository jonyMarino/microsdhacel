#include "IO_Map.h"
#include "Display1.h"
#include "Display2.h"
#include "bits2ULN.h"
#include "bits5ULN.h"
#include "matriz.h"
#include "Timer.h"
#include "Teclas.h"
#include "Object.h"
#include "Mydefines.h"
#include "display_teclas.h"
#include "ComunLeds.h"
 
#pragma CONST_SEG DEFAULT

bool led[8];
struct Timer ScrollTimer;
char  DigDpy[CANTIDAD_DISPLAYS][MAX_DIGITOS];		// caracteres decodificados del buffer ascii
byte Nletras[CANTIDAD_DISPLAYS];
static byte corrimiento[CANTIDAD_DISPLAYS];
  
void Display_Init(void){
  newAlloced(&ScrollTimer,&Timer,(ulong)TIME_SCROLL);
}

void ResetScroll(void){
  int i;
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    corrimiento[i]=0;								//resetear variables de SCROLL
	Timer_setTime(&ScrollTimer,TIME_SCROLL*2);
}

void PutValLed(bool val,byte num){
 led[num]=val;  
}

/*
Borra la pantalla
*/
void Display_clrScreen(void){
  int i;
  for(i=0;i<CANTIDAD_DISPLAYS;i++)
    Nletras[i]=0; 
  ResetScroll();   
}

// Pone el puerto A para digitos
/////////////////////////////////////////////////////////////////////
// Muestro texto en 7 segmentos y escaneo teclado
//
// IN:  nothing
// OUT: nothing
/////////////////////////////////////////////////////////////////////
static const byte  DigInfOn[DIGITOS]={0x10,0x20,0x40,0x80};		// señales de control del display
static const byte  DigSupOn[DIGITOS]={0x01,0x02,0x04,0x08};		// señales de control del display

#pragma INLINE
void DpyAndSwitch(void)
{
  static byte digito=0;				// digito a visualizar (0-3)
  static byte display=_DPY_INF;		// display a refrescar (sup/inf) 	

  int i;
  bool Scroll=Timer_isfinish(&ScrollTimer);
  byte caracterAMostrar;
/* cada digito lo refresco cada 1 msg */
/* muestro display inferior */
  
  /*Corrimiento por scrolling*/
  if (Scroll){
    bool scrolling=FALSE;
    for(i=0;i<CANTIDAD_DISPLAYS;i++){      
      if (Nletras[i]>DIGITOS)
      {
    	    corrimiento[i]++;
          if (corrimiento[i]==Nletras[i]+DIGITOS)
            corrimiento[i]=0;
          scrolling=TRUE;  		    
      }
      if(scrolling)
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
      
      Display1_PutVal(0);		//PTA
      Display2_PutVal(0);		//PTB
      if(digito<2)					
      {  
        bits2ULN_PutVal(0);		//PTJ
        bits5ULN_PutVal(DigInfOn[digito]); //PTM
      }else 
      {
        bits5ULN_PutVal(0);
        bits2ULN_PutVal(DigInfOn[digito]);		// PTJ   
      }
      
      /*de acuerco al corriemiento seteo  el caracterAMostrar*/
      caracterAMostrar=corrimiento[1]+digito;
      //Par de arriba 
      if (caracterAMostrar<Nletras[1])
        Display1_PutVal(DigDpy[1][caracterAMostrar]);  //PTA
      else
        Display1_PutVal(0);			// caracter vacio para Scroll
        
      //Par de abajo
      /*de acuerco al corriemiento seteo  el caracterAMostrar*/
      caracterAMostrar=corrimiento[3]+digito;
      if (caracterAMostrar<Nletras[3])
        Display2_PutVal(DigDpy[3][caracterAMostrar]);  //PTA
      else
        Display2_PutVal(0);			// caracter vacio para Scroll
        
    } else {										//Muestro los leds (los puertos que seleccionan el digito ya se encuentran en el DL2)
      byte leds=0; //conjunto de leds a mostrar
      Display2_PutVal(0);
      bits5ULN_PutVal(0);		// PTM
      bits2ULN_PutVal(0);	  // PTJ         
      Display1_PutVal(0);	  // PTA
      ComunLeds_ClrVal();
      for(i=0;i<8;i++){     
        if (led[i])
          leds|=1<<i;
      }
  	  Display2_PutVal(leds); 	 //PTB
    }
  
    if(++digito==DIGITOS+1)
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
    
  	Display1_PutVal(0);		 //PTA
  	Display1_PutVal(0);		 //PTA
  	bits2ULN_PutVal(0);
  	ComunLeds_SetVal();
  	bits5ULN_PutVal(DigSupOn[digito]);  //PTM
  
    //Par de arriba
    /*de acuerco al corriemiento seteo  el caracterAMostrar*/
    caracterAMostrar=corrimiento[0]+digito;
    if (caracterAMostrar<Nletras[0])
      Display1_PutVal(DigDpy[0][caracterAMostrar]);  //PTA
    else
      Display1_PutVal(0);			// caracter vacio para Scroll
        
    //Par de abajo
    caracterAMostrar=corrimiento[2]+digito;
    if (caracterAMostrar<Nletras[2])
      Display2_PutVal(DigDpy[2][caracterAMostrar]);  //PTA
    else
      Display2_PutVal(0);			// caracter vacio para Scroll
        
    if(++digito==DIGITOS)
    {
      digito=0;
      display=_DPY_INF;
    }
  }  
		  
  

}
///////////////////////////////////////////////////////////////////////
// Rutina de decodificacion de caracteres ASCII a 7 segmentos
//
// IN:  Buffer conteniendo caracteres ASCII.
// OUT: Buffer decodificado para 7 segmentos.
///////////////////////////////////////////////////////////////////////

void AsciiTo7Seg(char* ptrs, byte Num_display,byte Dot)
{
  byte i, Temp8, DigTmp;
	
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

    //Transformacion para el SD		( el puerto A tiene los segmentos cambiados respecto del B)
    if(Num_display==0 || Num_display==1){
      uchar c=DigTmp;
      uchar bit1=(c&2)>>1;
      uchar bit2=(c&1)<<1;
      uchar bit3=(c&8)>>1;
      uchar bit4=(c&4)<<1;
      c&=0xfe;
      c|=bit1;
      c&=0xfd;
      c|=bit2;
      c&=0xfb;
      c|=bit3;
      c&=0xf7;
      c|=bit4;
      DigTmp=c;
    }
    
    DigDpy[Num_display][Nletras[Num_display]]=DigTmp;
    Nletras[Num_display]++;
    
    ptrs++;    
  
  }
  
  if(Nletras[Num_display]>4)		 // Activar scrolling
    ResetScroll();
  
} 