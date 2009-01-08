#ifndef _FUNCIONES_H
#define _FUNCIONES_H

//#include "ClassADC.h"
#include "stdtypes.h"

void MedidorFunciones_setDeltaTiempo(uint delta);

int filtrar (int val_x,
            int Tf,
            int DEL_T,
            int TfMAX,
            long *buffer_fil
            );
            
long filtrarL (long val_x,int Tf,int DEL_T,int TfMAX,long *buffer_fil);



int duty_prop( int valcontrol, 	    
              int ab,
              int pinf,
              int psup
              );

 int duty_onoff(int valcontrol, 	    //variable
              int his 	            //histeresis
              );

int integral(int vp, 			  // variable del proceso
            int spl,			  // setpoit con reset
            int abinf,		  // ancho de banda, valor inferior
            int absup,		  // ancho de banda, valor superior
            int kintl,		  // constante de integracion
            long * suminteg  // puntero a la variable de acumulacion
            );

int int_Trapecios(int *vp, // variable del proceso actual(0) y anterior(1)
            int sp,			  // setpoit con reset
            int abinf,		  // ancho de banda, valor inferior
            int absup,		  // ancho de banda, valor superior
            int kintl,		  // constante de integracion
            long * suminteg  // puntero a la variable de acumulacion
            );


int derivada   (int val_x,
                int val_x_ant,
                int kder,
							  long *buffer_deriv
								);
								
int derivada3p(int * val_T, //array con tres valores
               int kder	 //kder = 2 derivada exacta
              );

int proporcional (int val_x,
                int reset,
                int spt
                );


#endif 