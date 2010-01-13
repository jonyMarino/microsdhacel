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