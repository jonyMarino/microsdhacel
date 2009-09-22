#ifndef _linealizacion_H
#define _linealizacion_H
unsigned char Linealizar(long Vx, unsigned char sensor, int * Vy);

int duty_prop( int sp, 	    //setpoint
              int vx, 	          //variable
              int ab, 	          //amp de banda
              int res,            //reset
              int pinf,
              int psup,
              byte salida	        //valor del duty
              );

 int duty_onoff( int sp, 	    //setpoint
              int vx, 	            //variable
              int his, 	            //histeresis
              int res,              //reset
              byte salida	          //valor del duty
              );

int v_cont_al (int tipoalarma,
               int modoalarma,
               int vx,
               int spcont,
               int spalar,
               int res,
               int hisalar,
               int abalar 
                );

/*long integral   (int sp,
                int vx,
                int ab,
                int kint,
                int modocont,
							  long *suminteg
                );
*/

void integral   (int sp,
                int vx,
                int ab,
                int kint,
                int modocont,
							  long *suminteg,
                int *integ
                );




void derivada   (int vx,
                int ab,
                int kder,
                int modocont,
							  int *buffer_deriv,
								int *timer_deriv,
								int *deriv
								);




#endif