/********************************************************************
*
* Rutinas de visualizacion en display de 7 segmentos. Llama a la 
* funcion de escaneo del teclado ya que comparte pines.
*
********************************************************************/

/* archivos include */
#include "stdtypes.h" 
#include "display.h"
#include "Math.h"
#include "Mydefines.h"


///////////////////////////////////////////////////////////////////////
// Rutina de pasaje de los textos de los boxes al buffer de caracteres ASCII
//
// IN:  Texto.
// OUT: Buffer conteniendo caracteres ASCII y Cantidad de letras
///////////////////////////////////////////////////////////////////////
void PasarASCII(const char *PtrText,byte Num_display){
  byte i;
  char  Digitos[MAX_DIGITOS];	// buffer de caracteres ascii a visualizar en 7 segmentos

  
  for (i=0;*PtrText!='\0'; i++)
  {
  		Digitos[i]=*PtrText;
  		PtrText++;
  }
  Digitos[i]='\0';
  AsciiTo7Seg(Digitos,Num_display,0);
}

///////////////////////////////////////////////////////////////////////
// Rutina de codificacion de numeros a caracteres ASCII 
//
// IN:  Valor a mostrar, Display en el cual mostrar, Punto decimal 
//      del valor a mostrar.
// OUT: Numero en ASCII.
///////////////////////////////////////////////////////////////////////

void Pasar_Numero(int valor,byte Num_display,byte Dot){
  int valortemp;
  char Digitos[5];
  char *PtrTexto = Digitos;
  
	
	if (valor<0){
		valor=0-valor;
		
		if (((valor/1000)%10)<1)		// 0 
		  *PtrTexto='-';
		else if(((valor/1000)%10)<2) // 1
		  *PtrTexto=':';		 // "-1"
		else  
		  *PtrTexto= (valor/1000)%10+'0';
		  
	}else if (((valor/1000)>0) || (Dot>2))
		*PtrTexto=(valor/1000)%10+'0';
  else *PtrTexto = ' ';
	valortemp = valor;
	valor %= 1000;
	PtrTexto++;
	
	if (((valortemp/100)>0) || (Dot>1)) 
	*PtrTexto= valor/100 +'0';
	else *PtrTexto = ' ';
	valor = valor % 100;
	PtrTexto++;
	
	if (((valortemp/10)>0) || (Dot>0)) 
	*PtrTexto= valor/10 +'0';
	else *PtrTexto = ' ';
	valor = valor % 10;					 
	PtrTexto++;
	
	*PtrTexto= valor+'0';
	
	PtrTexto++;
	*PtrTexto='\0';

  AsciiTo7Seg(Digitos,Num_display,Dot);	  
}

/*
** =====================================================================
**    Function      :  PasarHexaNum 
**    Description :    Muestra numero en hexa
** =====================================================================
*/
void PasarHexaNum(word valor,byte Num_display){
uchar i;
char Digitos[5]; 
  for(i=0;i<4;i++){
    Digitos[3-i]= get_HexDig(valor%16);
    valor/=16;    
  }
  Digitos[4]= '\0';
  AsciiTo7Seg(Digitos,Num_display,0);
  
}

///////////////////////////////////////////////////////////////////////
// Rutina de codificacion de numeros a notacion exponencial en ASCII 
//
// IN:  Valor a mostrar, Display en el cual mostrar, Punto decimal 
//      del valor a mostrar como si fuese no exponencial
// OUT: Numero en ASCII.
///////////////////////////////////////////////////////////////////////
void Pasar_Numero_Expo(int valor,byte Num_display, byte Dot) {
byte e;
char expo;
int div;
char Digitos[5];  

if(valor<0){
  Digitos[0]='E';
  Digitos[1]='r';
  Digitos[2]='r';
  Digitos[3]='D';
}else{
  div=10;
  for(e=0;(valor/div)>0;e++)
    div*=10;
  if(e==0){
    Digitos[0]=valor+'0';
    Digitos[1]='0';
  } else{
    Digitos[0]=(int)valor/(div/10)+'0';
    Digitos[1]=((int)valor/(div/100))%10+'0';
  }
  expo= e-Dot;
  if(expo<0){
    expo=-expo;
    Digitos[2]='-';
  }else
    Digitos[2]=' ';  
  Digitos[3]=expo+'0';  
}
Digitos[4]='\0';


AsciiTo7Seg(Digitos,Num_display,3);	
}

void Pasar_NumeroNatural_Expo(uint valor,byte Num_display, byte Dot) {
byte e;
char expo;
ulong div;
char Digitos[5];  

  div=10;
  for(e=0;(valor/div)>0;e++)
    div*=10;
  if(e==0){
    Digitos[0]=valor+'0';
    Digitos[1]='0';
  } else{
    Digitos[0]=valor/(div/10)+'0';
    Digitos[1]=(valor/(div/100))%10+'0';
  }
  expo= e-Dot;
  if(expo<0){
    expo=-expo;
    Digitos[2]='-';
  }else
    Digitos[2]=' ';  
  Digitos[3]=expo+'0';  

Digitos[4]='\0';


AsciiTo7Seg(Digitos,Num_display,3);	
}

void Pasar_NumeroGrande(long val,byte Num_display, byte Dot){
  if(val>MAX_NUM_DISPLAY)
    Pasar_NumeroNatural_Expo((uint)val,Num_display,Dot);
  else if (val<MIN_NUM_DISPLAY)
    Pasar_Numero_Expo( (int)val, Num_display, Dot);
  else
    Pasar_Numero((int)val, Num_display, Dot);
}

