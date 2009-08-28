/*IMPLEMENTATION MODULE Linealizacion; */
#include "Mydefines.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "limits.h"
#include "paramdefines.h"
#include "ADC.h"
#include "Sensores.h"				 

#pragma CONST_SEG DEFAULT
////////Tablas de linealizaci�n (X= microvolt/10, Y= �C*10)/////////////////////
static const int   J_X[14]  = {  -580,   -196,   0,    526,   1022,    1188,   1466,   1964,   2461,    2738,    2964,   3975,   4291,   4484};
static const int   J_Y[14]  = { -1300,   -400,   0,   1000,   1900,    2200,   2700,   3600,   4500,    5000,    5400,   7100,   7600,   7900};

static const int  n_X[9]   = { -261,    -51,   0,    898,   1598,    2531,   3470,   4495,   4751};
static const int  n_Y[9]   = { -1100,  -200,   0,   2900,   4800,    7200,   9600,  12300,  13000};

static const int   K_X[9]   = {  -385,   -77,   0,  1179,  1979,   2996,  3970,   4992,     5241};	 
static const int   K_Y[9]   = { -1100,  -200,   0,  2900,  4800,   7200,  9600,  12300,     13000};

static const int   s_X[10]  = { -155,     0,  59,   299,   619,    939,  1260,   1500,   1740,  1819};
static const int   s_Y[10]  = { -310,     0, 930,  3720,  6920,   9830, 12540,  14520,  16530, 17220};

static const int   r_X[11]  = { -150,    0,  59,   299,   619,    940,  1260,   1499,   1739,  1900,  2059};
static const int   r_Y[11]  = { -310,    0, 930,  3600,  6530,   9150, 11550,  13260,  14960, 16110, 17280};

static const int  t_X[9]  = {  -417,  -147,   0,   427,   875,   1036,  1313,  1842,  2086};
static const int  t_Y[9]  = { -1300,  -400,   0,  1000,  1900,   2200,  2700,  3600,  4000};


#ifdef Pt-200

static const int  Pt_X[12]  = { -1007,  -881,   -789,  -510, -253,  0,  247,   489,  714,  953, 1201, 1400}; 
static const int  Pt_Y[12]  = { -1930, -1700,  -1530, -1000, -500,  0,  500,  1000, 1470, 1980, 2520, 2960}; 

#else

static const int  Pt_X[12]  = {  -990, -490,  0,  480,   950, 1410, 1870, 2310, 2750, 3180, 3590, 4010}; 
static const int  Pt_Y[12]  = { -1000, -500,  0,  500,  1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500}; 

#endif


static const int  Pir_X[20]  = {25, 50, 112, 150, 181, 400, 650, 893, 1018, 1156, 1462, 1856, 2237, 3393, 3650, 3968, 4412, 4562, 4793 ,4862};  	
static const int  Pir_Y[20]  = {1,  3,   6,   8,  10,  25,  45,  70,   85,  100,  140,  210,  290,  780, 1000, 1400, 2300, 3000, 5500 ,9000};  

static const int  Pr1_X[20]  = {25, 50, 112, 150, 181, 400, 650, 893, 1018, 1156, 1462, 1856, 2237, 3393, 3650, 3968, 4412, 4562, 4793 ,4862};  	
static const int  Pr1_Y[20]  = {1,  3,   6,   8,  10,  25,  45,  70,   85,  100,  140,  210,  290,  780, 1000, 1400, 2300, 3000, 5500 ,9000};  


static const int   Lin_X[3] = {MINMV,   0,    MAXMV};
static const int   Lin_Y[3] = {MINAD,   0,    MAXAD};   

static const int   milv_X[3]= {MINMV,   0,   MAXMV}; 
static const int   milv_Y[3]= {MINMV,   0,   MAXMV};
////////////////////////////////////////////////////////////////////////////////
#ifdef _APARATO_VIEJO
const T_Sensor Sensor[NUM_SENSORES]={
  J_X,J_Y,13,1,1,
  J_X,J_Y,13,1,0,
  n_X,n_Y,8,1,0,
  K_X,K_Y,8,1,1,
  K_X,K_Y,8,1,0,
  s_X,s_Y,9,1,0,
  r_X,r_Y,10,1,0,
  t_X,t_Y,8,1,0,
  Pt_X,Pt_Y,11,1,1,
  #ifdef pirani
  Pir_X,Pir_Y,19,3,3,
  Pr1_X,Pr1_Y,19,3,3,
  #endif
  Lin_X,Lin_Y,2,3,0,
  Lin_X,Lin_Y,2,3,1,
  Lin_X,Lin_Y,2,3,2,
  Lin_X,Lin_Y,2,3,3,
  milv_X,milv_Y,2,2,2
};
#else
T_Sensor Sensor[NUM_SENSORES]={
  J_X,J_Y,13,1,
  n_X,n_Y,8,1,
  K_X,K_Y,7,1,
  s_X,s_Y,9,1,
  r_X,r_Y,10,1,
  t_X,t_Y,8,1,
  Pt_X,Pt_Y,11,1,
  #ifdef pirani
  Pir_X,Pir_Y,19,3,
  #endif
  Lin_X,Lin_Y,2,3,
  milv_X,milv_Y,2,2,
};
#endif
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
byte Linealizar(long Vx, t_sensor sensor, int * Vy)
{
 int r;
 const int * xdat;
 const int * ydat;
  
  Vx = Vx*MAXMV/MAXAD;//Convierte de lineal a microvolts para los sensores correspondientes 
       
  xdat = Sensor[sensor].xdat;		 // Tabla abcisas
  ydat = Sensor[sensor].ydat;		 // Tabla ordenadas
  r = Sensor[sensor].max_array;	 // Cantidad de puntos -1 

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




                

/*
FILTRO

Vf = Vx / (1 + sTf)
Vf + sTfVf = Vx
Vf + Tf DVf = Vx
Vfk + (Tf/h)(Vfk - Vfk-1) = Vxk
Vfk [1+(Tf/h)] = Vxk + (Tf/h)Vfk-1
Vfk [h+Tf] = h Vxk + Tf Vfk-1


MUCHO CUIDDO!!!!!EL TfMAX ES POR LOS ERRORES DE REDONDEO DE 
DIVISION ENTERA EN CALCULOS ITERATIVOS!!!. PERDI DOS DIAS CON ESO!!!!!

Empiezo con un Vx alto, y lo bajo al final

Vfk1 = (h Vxk TfMAX + Tf Vfk-1)/(h+Tf)

y despues

Vfk = Vfk1/TfMax

Tf en decimas de segundo
DEL_T idem

*/

int filtro (int val_x,
            int Tf,
            int DEL_T,
            int TfMAX,
            long *buffer_fil
            ){
 
*buffer_fil = ((long)TfMAX*(long)DEL_T*(long)val_x + (long)Tf**buffer_fil)/((long)DEL_T+(long)Tf);
return (int)(*buffer_fil/TfMAX);

            };


/* END Linealizacion. */