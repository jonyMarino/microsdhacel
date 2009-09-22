/*IMPLEMENTATION MODULE Linealizacion; */
#include "Mydefines.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "Linealizacion.h"
#include "limits.h"
////////Tablas de linealización (X= microvolt/10, Y= ºC*10)/////////////////////
static const int   J_X[14]  = {  -580,   -196,   0,    526,   1022,    1188,   1466,   1964,   2461,    1964,    2964,   3975,   4291,   5187};
static const int   J_Y[14]  = { -1300,   -400,   0,   1000,   1900,    2200,   2700,   3600,   4500,    3600,    5400,   7100,   7600,   9000};

static const int  n_X[9]   = { -261,    -51,   0,    898,   1598,    2531,   3470,   4495,   4751};
static const int  n_Y[9]   = { -1100,  -200,   0,   2900,   4800,    7200,   9600,  12300,  13000};

static const int   K_X[8]   = {  -385,   -77,   0,  1179,  1979,   2996,  3970,   4992};
static const int   K_Y[8]   = { -1100,  -200,   0,  2900,  4800,   7200,  9600,  12300};

static const int   s_X[10]  = { -155,     0,  59,   299,   619,    939,  1260,   1500,   1740,  1819};
static const int   s_Y[10]  = { -310,     0, 930,  3720,  6920,   9830, 12540,  14520,  16530, 17220};

static const int   r_X[11]  = { -150,    0,  59,   302,   619,    940,  1260,   1499,   1739,  1900,  2059};
static const int   r_Y[11]  = { -310,    0, 930,  3600,  6530,   9150, 11550,  13260,  14960, 16110, 17280};

static const int  t_X[14]  = {  -580,  -196,   0,   526,  1022,   1188,  1466,  1964,  2461,   1964,   2964,  3975,  4291,  5187};
static const int  t_Y[14]  = { -1300,  -400,   0,  1000,  1900,   2200,  2700,  3600,  4500,   3600,   5400,  7100,  7600,  9000};

static const int  Pt_X[4]  = { -625, -2153,   0,  2087}; 
static const int  Pt_Y[4]  = { -270,   -60,   0,   400}; 

static const int   Lin_X[3] = {MINAD,   0,    MAXAD};
static const int   Lin_Y[3] = {MINAD,   0,    MAXAD};   

static const int   milv_X[3]= {MINAD,   0,   MAXAD}; 
static const int   milv_Y[3]= {MINMV,   0,   MAXMV};
////////////////////////////////////////////////////////////////////////////////
/*
** ===================================================================
**     Method      :  Linealizar 
**     Parameters  : Vx, sensor
**     Returns     : Vy
**     El instrumento se ajusta primero para que con 10000 cuentas en el 
**     a/d marque 50,00 mv.
**     Entro en la funcion con un valor que va de -2000 a 12000.
**     Para hacer las tablas de termopar en mv, preciso hacer la conversion
** ===================================================================
*/
byte Linealizar(long Vx, byte sensor, int * Vy)
{
 int r;
 const int * xdat;
 const int * ydat;
  
if (sensor<6)Vx = Vx*MAXMV/MAXAD;//Convierte de lineal a microvolts para los sensores correspondientes 
  
  switch (sensor){				 //Cargar Tabla del sensor correspondiente
    case 0:														
          
          xdat = J_X;		 // Tabla abcisas
          ydat = J_Y;		 // Tabla ordenadas
          r = 13;				 // Cantidad de puntos -1 
          break;
    case 1:
    			xdat = n_X;
          ydat = n_Y;
          r = 8;
          break;
    case 2:
          xdat = K_X;
          ydat = K_Y;
          r = 7;
          break;
    case 3:
          xdat = s_X;
          ydat = s_Y;
          r = 9;
          break;
    case 4:
          xdat = r_X;
          ydat = r_Y;
          r = 10;
          break;
    case 5:
          xdat = t_X;
          ydat = t_Y;
          r = 3;
    			break;
    case 6:
          xdat = Pt_X;
          ydat = Pt_Y;
          r = 3;
    			break;
    case 7:
          xdat = Lin_X;
          ydat = Lin_Y;
          r = 2;
    			break;
    case 8:
          xdat = milv_X;
          ydat = milv_Y;
          r = 2;
  };
  
  
  if (Vx <= xdat[0]) {			 // VX es menor igual que el valor minimo en la tabla???
    * Vy = ydat[0];					 // VX =  valor minimo en la tabla
    if (Vx < xdat[0])				 // VX es menor que el valor minimo en la tabla???
      return ERR_UF;				 // devolver UF
     }
   else if (Vx > xdat[r]) {	 // VX es mayor que el valor maximo en la tabla???
     * Vy = ydat[r];				 // VX =  valor maximo en la tabla
     return ERR_OF;					 // devolver OF
   }
   else {						 				 // VX esta dentro de los rangos???
     int l = 0, i = 0, eq = 0;

     while ((l < r) && (r - l > 1)) {		// Algoritmo de busqueda de los 2 valores mas cercanos hacia arriba y hacia abajo
       i = (l + r) / 2;
       if (Vx > xdat[i])
         l = i;
       else
         if (Vx < xdat[i])
           r = i;
         else {
           eq = 1;
           break;
         }
     }
     if (eq)
       * Vy = ydat[i];		// Concuerda con un valor de la tabla
     else * Vy = ydat[l] + (dword)((Vx - xdat[l])  * (ydat[r] - ydat[l]))/ (xdat[r] - xdat[l]);		// Linealizacion
   }
return ERR_OK;	 // Devolver OK
}


/* calculo valor del duty en proporcional. Pongo
los limites */

int duty_prop(int sp, 	          //setpoint
              int vx, 	          //variable
              int ab, 	          //amp de banda
              int res,            //reset
              int pinf,           //pot inf
              int psup,           //pot sup
              byte salida	        //valor del duty
              ) {
    
   			long duty;

				if((vx + res)>=(sp + ab/2))
				  duty = 0;
				else if((vx + res)<=(sp - ab/2))  
					duty = 9999;
				else 
				duty=(10000*(long)(sp - vx -  res + ab/2))/(long)ab;
				if(duty>=psup)
				  duty = psup;
				else if(duty<=pinf)
				  duty = pinf;  
					
        return (int)duty;
}

/* calculo valor del duty en onoff.*/

int duty_onoff(int sp, 	            //setpoint
              int vx, 	            //variable
              int his, 	            //histeresis
              int res,              //reset
              byte salida	          //valor del duty
              ) {
                
      	int duty;

				if((vx + res)>=(sp + his/2))
				  duty = 0;
				else if((vx + res)<=(sp - his/2))  
					duty = 9999;
				else duty = -10;            //codigo para indicar que no cambia
				
        return (int)duty;
}

/*calculo del valor que controla la alarma*/

int v_cont_al (int tipoalarma,
               int modoalarma,
               int vx,
               int spcont,
               int spalar,
               int res,
               int hisalar,
               int abalar 
                ){
#define _rel  0
#define _abs  1
#define _refr 2
#define _ban  3
#define _seg  4
#define _eoc  5  
                
           int vxalar;               
		       int duty;
 
 switch (tipoalarma){				
    case _rel:														
          vxalar = vx-spcont;
          break;
 
    case _abs:														
          vxalar = vx;
          break;

    case _refr:														
          vxalar = vx+res-spcont;
          break;
          
    case _ban:														
          vxalar = abs(vx-spcont);
          break;

    case _seg:														
          vxalar = vx;
          break;

    default:
			    vxalar = vx;
          break;
 };

#define _e 0
#define _d 1
#define _eprop 2
#define _dprop 3
#define _eret 4
#define _dret 5
#define _dbloq 6
 
 switch (modoalarma){				
    case _e:														
       duty = duty_onoff(spalar, 	            //setpoint
                         vxalar, 	          //variable
                         hisalar, 	          //histeresis
                         0,                   //reset (ya esta en vxalar)
                         0);	                //valor del duty 
       break;
 
    case _d:														
       duty = duty_onoff(spalar, 	            //setpoint
                         vxalar, 	            //variable
                         hisalar, 	            //histeresis
                         0,              //reset
                         0);	          //valor del duty 
    if (duty != -10)
          duty = 10000-duty; 
          break;

    case _eprop:														
       duty = duty_prop(spalar, 	          //setpoint
                        vxalar, 	          //variable
                        abalar, 	          //amp de banda
                        0,            //reset
                        0,           //pot inf
                        10000,           //pot sup
                        0	        //valor del duty
                        );
         break;    

    case _dprop:														
       duty = duty_prop(spalar, 	          //setpoint
                        vxalar, 	          //variable
                        abalar, 	          //amp de banda
                        0,            //reset
                        0,           //pot inf
                        10000,           //pot sup
                        0	        //valor del duty
                        );
       duty = 10000-duty;
          break;

    case _eret:														
    case _dret:														
    case _dbloq:														
       duty = 0;   
          break;

        default:
			 duty = 0; 
          break; 
 };
 
        return duty;
                }



/* integral. actualiza la suma sum (ei*deltati) y devuelve 
i=(1/kint)*sum(ei*deltati).Limita el valor de la integral a
+-ab o sea -ab<(1/kint)*sum(ei*deltati)<ab
-ab*kint/deltati<sum (ei)<ab*kint/deltati.Para no perder precision
pongo DELTAT en decimas */


/* long integral (int sp,
                int vx,
                int ab,
                int kint,
                int modocont,
							  long *suminteg
              ){

     long suma;
     long aux;
    #define _pid 1
    #define DELTAT 5

      aux = ((long)ab*(long)kint)*10/DELTAT;

          
   if ((modocont=_pid)&&(abs(vx-sp)<=(ab/2))&&(kint!=0)){
     		 suma = *suminteg + (vx - sp);
         if(suma>=aux)
         suma=aux;
         else if(suma<= -(aux))
         suma= -aux; 
   }
   else suma = 0;				
  
  			 *suminteg = suma;
  


         return ((suma*DELTAT)/kint)/10; 


   							};
*/  

 void integral (int sp,
                int vx,
                int ab,
                int kint,
                int modocont,
							  long *suminteg,
                int *integ
              ){

     long suma;
     long aux;
    #define _pid 1
    #define DELTAT 5

      aux = ((long)ab*(long)kint)*10/DELTAT;

          										
   if ((modocont==_pid)&&(abs(vx-sp)<=(ab/2))&&(kint!=0)){
     		 suma = *suminteg + (vx - sp);
         if(suma>=aux)
         suma=aux;
         else if(suma<= -(aux))
         suma= -aux; 
   }
   else suma = 0;				
  
  			 *suminteg = suma;
  


         *integ =(int)((suma*DELTAT)/kint)/10; 


   							};
  



/*derivada. Guardo vx cada kder/5. Tengo Vx(i) Vx(i-1)..... y calculo
derivada= kder* (Vx(i)-Vx(i-4))/(4*deltat)*/


/*  int derivada (int vx,
                int ab,
                int kder,
                int modocont,
							  int *buffer_deriv[],
                int *timer_deriv
                ){

        short i;
        int timer;
				int deltat;
				int derivada;
				#define DELTAT 5
				
   if ((modocont=_pid)&&(kder!=0)){           //veo si hay derivada
        *timer_deriv=*timer_deriv+DELTAT;			//cuento tiempo
        timer = *timer_deriv;
        if(timer>(10*kder/5)){
     		  deltat=timer;
     		  *timer_deriv =0;
     		  for(i=0,i<5,i++)
     		     *buffer_deriv[i+1]=*buffer_deriv[i];
     		  *buffer_deriv[0]=vx;
     		  derivada=kder*10*(*buffer_deriv[0]-*buffer_deriv[4])/deltat;   
     		    }
   }
   else for(i=0, i<5, i++)
          *buffer_deriv[i]=vx; 
   			*timer_deriv=0;
         derivada = 0;				
  
         return derivada; 


  */
  void derivada (int vx,
                int ab,
                int kder,
                int modocont,
							  int *buffer_deriv,
                int *timer_deriv,
                int *deriv
                ){

        short i;
        int timer;
				int deltat;
				#define DELTAT 5
				
   if ((modocont==_pid)&&(kder!=0)){           //veo si hay derivada
        *timer_deriv=*timer_deriv+DELTAT;			//cuento tiempo
        timer = *timer_deriv;
        if(timer>(10*kder/5)){
     		  deltat=timer;
     		  *timer_deriv =0;
     		  *deriv=kder*10*(vx-*buffer_deriv)/deltat;   
     		  *buffer_deriv=vx;
     		    } else *deriv=*deriv;
   }
   else {
             *buffer_deriv=vx; 
      			 *timer_deriv=0;
             *deriv = 0;				
   }
                };




/* END Linealizacion. */

