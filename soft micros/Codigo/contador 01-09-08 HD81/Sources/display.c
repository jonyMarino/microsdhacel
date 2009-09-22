/********************************************************************
*
* Rutinas de visualizacion en display de 7 segmentos. Llama a la 
* funcion de escaneo del teclado ya que comparte pines.
*
********************************************************************/

/* archivos include */
#include "bits5ULN.h"
#include "Display1.h"
#include "Display2.h"
#include "IO_Map.h" 
#include "Mydefines.h"
#include "matriz.h"
#include "display.h"
#include "DL2.h"
/* definiciones */
#define _DPY_SUP			0							// dpy inferior
#define _DPY_INF			1							// dpy superior

/* variables de este modulo */
#pragma CONST_SEG DEFAULT
static const byte  DigOn[6]={0x01,0x02,0x04,0x08,0x10,0x20};		// señales de control del display

/*variables externas*/
bool led[2];
byte b,d;
byte c;
char DigitoParpadeante=NO_DIGIT;
extern unsigned int cont;
extern byte DotNum[CANTIDAD_DISPLAYS];
byte Nletras[CANTIDAD_DISPLAYS];
/* funciones externas */
extern void Switches(byte);
/* variables externas */
char  DigDpy[CANTIDAD_DISPLAYS][10];		// caracteres decodificados del buffer ascii
char  Digitos[CANTIDAD_DISPLAYS][10];	// buffer de caracteres ascii a visualizar en 7 segmentos

/////////////////////////////////////////////////////////////////////
// Muestro texto en 7 segmentos y escaneo teclado
//
// IN:  nothing
// OUT: nothing
/////////////////////////////////////////////////////////////////////
#pragma INLINE
void DpyAndSwitch(void)
{
  static byte digito=0;				// digito a visualizar (0-3)	
  byte leds; //conjunto de leds a mostrar
/* cada digito lo refresco cada 1 msg */
/* muestro display inferior */

  
/* el escaneo del teclado se hace luego del envio de la señal de ON
   del digito para que el pin PULL se encuentre estable */
/* Al final de recorrer los displays se prenden los leds, poniendo DL2 en uno,
y cuando se reinicia el recorrido se pone DL2 en 0*/  
  if(digito<3)
	    Switches(DigOn[digito]);
  if(++digito==7){
    digito=0;
    DL2_PutVal(0);
  }
	Display1_PutVal(0);		 //PTA
	Display2_PutVal(0);
	if (digito<6)
  {    
    bits5ULN_PutVal(DigOn[digito]);  //PTM
	  
	  if (Nletras[_DPY_SUP]>DIGITOS_DISPLAY+1)
    {
      if (cont==0) 
      {
  	    d++;
        if (d==(Nletras[_DPY_SUP]+1))
        {
        d=0;  
		    cont=2*SCROLL;
        } else cont=SCROLL;
      }
      c=d+digito;
      if (c>=Nletras[_DPY_SUP])
      {
        c=c-Nletras[_DPY_SUP];
      }
    }else {
      c=digito;
      if(cont==0)cont=SCROLL;
    }
   if (c!=DigitoParpadeante  || cont>(SCROLL/2)){
    
    Display1_PutVal(DigDpy[_DPY_SUP][c]);  //PTA   
    if(DigitoParpadeante!=NO_DIGIT && c>=DigitoParpadeante && DigDpy[_DPY_SUP][c]==0x00) //el digito parpadeante u otro anterior es vacio??
      Display1_PutVal(0x7D); //mostrar ceros cuando va corriendo el digito parpadeante 
   }
   Display2_PutVal(DigDpy[_DPY_INF][digito]);  //PTB
 }else
  {
    leds= (led[0]==TRUE)?1:0;
	  if (led[1]==TRUE)
      leds|=4;
	  bits5ULN_PutVal(leds); 	 //PTM
    DL2_PutVal(1);
  }
}

///////////////////////////////////////////////////////////////////////
// Rutina de decodificacion de caracteres ASCII a 7 segmentos
//
// IN:  Buffer conteniendo caracteres ASCII.
// OUT: Buffer decodificado para 7 segmentos.
///////////////////////////////////////////////////////////////////////

void AsciiTo7Seg(byte Num_display)
{
  byte i, Temp8, DigTmp;
  char *ptrs;
  

  ptrs = Digitos[Num_display];
 										 
  for(i=0; i<Nletras[Num_display]; i++)	// los N digitos
  {
    Temp8=*ptrs;
    Temp8-='-'; 	
 	
 	if((*ptrs)!=' ')
 	      {
	      DigTmp=(byte)Car_Ini[Temp8];
 	      } else 	DigTmp=0x00;
	      /* enciendo punto decimal de acuerdo a Cdt en la pantalla principal */
	  		if(DotNum[Num_display]==DIGITOS_DISPLAY-i)
	    	DigTmp|=0x80;  
    		if(DotNum[Num_display]==0 && i==DIGITOS_DISPLAY)
	    	DigTmp&=0x7F; 

	DigDpy[Num_display][i]=DigTmp;
	 
	ptrs++;    
  
  }
  
} 

///////////////////////////////////////////////////////////////////////
// Rutina de pasaje de los textos de los boxes al buffer de caracteres ASCII
//
// IN:  Texto.
// OUT: Buffer conteniendo caracteres ASCII y Cantidad de letras
///////////////////////////////////////////////////////////////////////
void PasarASCII(char *PtrText,byte Num_display){
for (Nletras[Num_display]=0;*PtrText!='\0'; Nletras[Num_display]++)
		{
		Digitos[Num_display][Nletras[Num_display]]=*PtrText;
		PtrText++;
		}
DotNum[Num_display]=0;
AsciiTo7Seg(Num_display);
}

///////////////////////////////////////////////////////////////////////
// Rutina de codificacion de numeros a caracteres ASCII 
//
// IN:  Numero.
// OUT: Numero en ASCII.
///////////////////////////////////////////////////////////////////////

static const char UF[]="  UF  ";
static const char OF[]="  OF  ";

void Pasar_Numero(long valor,byte Num_display){
  long valortemp;
  char * PtrTexto;
  long divisor;
  byte i;
  Nletras[Num_display]=DIGITOS_DISPLAY+1;
  PtrTexto = Digitos[Num_display];
		
//	if(valor>MAX_INDICACION_DISP){
//	  PasarASCII(OF,Num_display);
//	  return;
//	}
/*  MODIFICAR EL VALOR DE ABAJO PARA LA CANTIDAD DE DISPLAYS CORRESPONDIENTES*/	
	divisor = 100000;
	
	if (valor<0){
		valor=0-valor;
		
		if (((valor/divisor)%10)<1)		// 0 
		  *PtrTexto='-';
		   else if(((valor/divisor)%10)<2) // 1
		  *PtrTexto=':';		 // "-1"
		   else  
		  *PtrTexto= (valor/divisor)%10+'0';
		  
		}else if (((valor/divisor)>0) || (DotNum[Num_display]>4))
		*PtrTexto=(valor/divisor)%10+'0';
		else *PtrTexto = ' ';
	valortemp = valor;
	valor %= divisor;
	divisor/=10;
	PtrTexto++;
	
	
	for(i=DIGITOS_DISPLAY; i>0; i--){
	  if (((valortemp/divisor)>0) || (DotNum[Num_display]>i-2)) 
	    *PtrTexto= valor/divisor +'0';
	  else *PtrTexto = ' ';
	  valor = valor % divisor;
	  divisor/=10;
	  PtrTexto++;
	}


AsciiTo7Seg(Num_display);	  
}





