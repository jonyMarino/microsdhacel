/*Module: SearchLib.c */

#include "stdtypes.h"
#include "SearchLib.h"


LinState BinSearchLin(int x,int * y,const  int * xdat,const int* ydat, int r){
  
  if (x <= xdat[0]) {			 // VX es menor igual que el valor minimo en la tabla???
    * y = ydat[0];					 // VX =  valor minimo en la tabla
    if (x < xdat[0])      // VX es menor que el valor minimo en la tabla???
      return UF;				 // devolver UF
  }else if (x > xdat[r]) {	 // VX es mayor que el valor maximo en la tabla???
     * y = ydat[r];				 // VX =  valor maximo en la tabl
     return OF;					 // devolver OF
  }else {						 				 // VX esta dentro de los rangos???
     int l = 0, i = 0, eq = 0;

     while ((l < r) && (r - l > 1)) {		// Algoritmo de busqueda de los 2 valores mas cercanos hacia arriba y hacia abajo
       i = (l + r) / 2;
       if (x > xdat[i])
         l = i;
       else
         if (x < xdat[i])
           r = i;
         else {
           eq = 1;
           break;
         }
     }
     if (eq)
       * y = ydat[i];		// Concuerda con un valor de la tabla
     else * y = ydat[l] + ((ulong)(x - xdat[l])  * (ydat[r] - ydat[l]))/ (xdat[r] - xdat[l]);		// Linealizacion
  }
  return OK;	 // Devolver OK

}