#include "controlmath.h"


int DELTAT=1000;

void MedidorFunciones_setDeltaTiempo(unsigned int delta){
  DELTAT=delta;
}




/* calculo valor del duty en onoff.*/

int duty_onoff(int valcontrol, 	          //variable
              int his 	                  //histeresis
              )
{        
      	int duty;

				if(valcontrol>=his/2)
				  duty = 1000;
				else if(valcontrol<=(- his/2))  
					duty = 0;
				else duty = -1;             //codigo para indicar que no cambia
				
        return duty;
}

/* calculo valor del duty en proporcional. Pongo
los limites */

//dan-12-02
/*
int duty_prop (int valcontrol,
              int ab,
              int pinf,           //pot inf
              int psup           //pot sup
              ) {
   			long duty;

				if(valcontrol>= ab/2)
				  duty = 1000;
				else if(valcontrol<= - ab/2)  
					duty = 0;
				else 
				duty=(1000*(long)(valcontrol + ab/2))/(long)ab;
				if(duty>=(10*psup))
				  duty = 10*psup;
				else if(duty<=10*pinf)
				  duty = 10*pinf;  

        return (int)duty;
}
*/
 /**/
 int duty_prop (int valcontrol,
              int ab,
              int pinf,           //pot inf
              int psup           //pot sup
              ) 
{
   			long duty;

				if(valcontrol>= ab/2)
				  duty = psup;
				else if(valcontrol<= - ab/2)  
					duty = pinf;
				else 
				duty=pinf+(((psup-pinf)*(long)(valcontrol + ab/2))/(long)ab);
        return (int)duty;
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


int filtrar (int val_x,int Tf,int DEL_T,int TfMAX,long *buffer_fil){
 
  *buffer_fil = ((long)TfMAX*(long)DEL_T*(long)val_x + (long)Tf**buffer_fil)/((long)DEL_T+(long)Tf);
  return (int)(*buffer_fil/TfMAX);

};

long filtrarL (long val_x,int Tf,int DEL_T,int TfMAX,long *buffer_fil){
 
  *buffer_fil = ((long)TfMAX*(long)DEL_T*(long)val_x + (long)Tf**buffer_fil)/((long)DEL_T+(long)Tf);
  return (long)(*buffer_fil/TfMAX);

};
					  
/* Calculo el termino integral

INT:    I = K/sTi e; sI = K/Ti e. En temporal dI/dt = K/Ti e
        [Ik-I(k-1)]/h = K/Ti ek
        Ik = I(k-1) + (Kh/Ti) ek
guardo 
        Ti Ik =  Ti I(k-1) + K h ek
y saco
        Ik = I(k-1) + (K h / Ti) ek
uso K=1 para ponerlo despues en otro lado

        Ik = I(k-1) + (K h / Ti) ek


Anti windup
limito el valor acumulado de la integral al borde de la banda ya sumada 
al error (y al reset?)

- AB/2 < Pr + In < AB/2
-AB/2 < sp - vx + In < AB/2
- TiAB/2 < Tisp - Tivxk + Ti Ik < Ti AB/2
Ti(-AB/2 - sp + vxk) < Ti Ik < Ti (AB/2 -sp + vx) 


como el integrador esta al borde de la banda, evito que 
integre con variaciones fuera de ella. Si no lo hago, integra
fuera de la banda

*/


int integral(int vp, int spl,int absup,int abinf ,int kintl,long * suminteg){
int AbsIntSup=absup;
int AbsIntInf=abinf;
long tmp_long;																
int dif;
  
   if (kintl!=0){            				//integro?
   

    	dif = (int)(spl-vp);
      if(dif<AbsIntInf ||dif>AbsIntSup){ //anulo fuera de ab
        *suminteg = 0;
        return 0;
      }
      
    	*suminteg += ((long)(spl-vp)*DELTAT)/100; //acumulo
      //Ti Ik	 = Ti I(k-1)    +		 h			ek


  	  tmp_long = (long)kintl*(AbsIntSup-spl+vp);
  	  if( *suminteg/10>tmp_long)
        *suminteg = 10*tmp_long;
      else{
        tmp_long=(long)kintl*(AbsIntInf-spl+vp);
        if(*suminteg/10<tmp_long)
          *suminteg = 10*tmp_long;
      }
      

      

      
      return (int)(*suminteg/((long)kintl*10));							 //tomo valor de in
    }
    
      *suminteg = 0;				
      return 0;
}

int int_Trapecios(int *vp, int sp,int abinf,int absup,int kintl,long * suminteg){
int AbsIntSup=absup;
int AbsIntInf=abinf;
long tmp_long;																
int dif;
  
   if (kintl!=0){            				//integro?
    	
			dif = (int)(sp-vp[0]);
      if(dif<AbsIntInf ||dif>AbsIntSup)		 //anulo fuera de ab
        return *suminteg = 0;

    	*suminteg += (long)(2*sp-(vp[0]+vp[1]))*DELTAT/10/2; //acumulo
      //Ti Ik	 = Ti I(k-1)    +		 h			ek
      
  	  tmp_long = (long)kintl*(AbsIntSup-sp+vp[0]);
  	  if( *suminteg/10>tmp_long)
        *suminteg = 10*tmp_long;  
      else{
        tmp_long=(long)kintl*(AbsIntInf-sp+vp[0]);
        if(*suminteg/10<tmp_long)
          *suminteg = 10*tmp_long;  
      }
      
      return (int)(*suminteg/((long)kintl*10));							 //tomo valor de in
    }
    
      *suminteg = 0;				
      return 0;
}

/*
DER:    Saco la referencia e = r - x = -x
        Pongo filtro de tiempo Td/N  1 / (1 + sTd/N)
        D = KsTd(-x) / (1 + sTd/N)
        D (1 + sTd/N) = -K s Td x = D + sDTd/N
        en temporal
        D + (Td/N) (dD/dt) = - KTd (dx/dt)
        Dk + (Td/N) [D(k)-D(k-1)]/h = -KTd [x(k) - x(k-1)]/h
        Dk(1+Td/Nh) = D(k-1) (Td/Nh) - KTd delx /h
        Dk = Td/(Nh+Td) [ D(k-1) - NK delx ]
           = KTd/(Nh+Td) [ D(k-1)/K - N delx ]        
					 = Td/(Nh+Td) [ D(k-1) - NK delx ]
EN D guardo
        Dk = Td/(Nh+Td) [ D(k-1) -  NK delx ]   
uso K=1 para ponerlo despues en otro lado
  */

  int derivada (int val_x,
                int val_x_ant,
                int kder, 
							  long *buffer_deriv
                )
{






/*dan

				#define DELTAT 1
        #define NFIL 10
        
   if ((modocont==CNTR_PID)&&(kder!=0)){           //veo si hay derivada

		    *buffer_deriv = (*buffer_deriv-(long)(NFIL*(vx-*deriv)))*(long)kder/(long)(NFIL*DELTAT+kder); 
//          Dk        = [(D(k-1)			-          N			delx		]			Td	 /      (  N    h   + Td )  
  			*deriv = vx;
   }
   else {
             *deriv=vx; 
      			 *buffer_deriv=0;				
   }

  return (int)*buffer_deriv;


*/

long auxd;
long kfil=kder/5; 

   if (kder!=0){           //veo si hay derivada

    auxd = -(long)(val_x-val_x_ant)*(long)kder; 
		*buffer_deriv = ((1000*auxd) + kfil**buffer_deriv)/(1+kfil);
   }
   else {
    *buffer_deriv=0;				
   }

  return (int)((*buffer_deriv+500)/1000);

}


int derivada3p(int * val_T,
               int kder	 //kder = 2 derivada exacta
              )
{
  		return	(val_T[2]- 4*val_T[1] + 3*val_T[0]  ) *kder*100/ DELTAT;
}
                
/*
PROP
es simplemente P = K (vr - vx)
uso K=1 para ponerlo despues en otro lado
*/


  int proporcional (int val_x,
                int reset,
                int spt
                )
{
        int sp;
        sp = spt + reset;

  return (sp-val_x);

};

