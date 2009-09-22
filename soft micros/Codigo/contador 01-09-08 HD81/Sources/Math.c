#include "Math.h"

word exp_diez (byte expo){
byte i;
word E=1;

if (expo>4) return 0;

for (i=0;i<expo;i++)
  E*=10;
  
return E;
}



///////////////////////////////////////////////////////////////////////
// Rutina de codificacion de numeros float a integer 
//
// IN:  Numero.
// OUT: Numero en ASCII.
///////////////////////////////////////////////////////////////////////
int FloatToInt(float valor,byte decimales)
{ int valor_int;
  byte i;		  
 
 for (i=0;i<decimales;i++)
  valor*=10;
 
 valor+=0.5;
 valor_int= valor;
 return valor_int;
}
