#include "CuentaCalculada.h"
/* Modulo de Entrada Calculadas */ 
#include <math.h>

#define T 10000
#define W0 (2* 3.1416)/T
long t;

bool vx1_GetVal(void){
  t++;
 // if(cos(W0 * t)>=0.5)
  if(!(t%777))
    return 1;
  return 0;  
}


bool vx2_GetVal(void){
  return 0; //  Siempre ascendente
}