#ifndef _CONTROL_MATH_H
#define _CONTROL_MATH_H

int duty_onoff(int valcontrol, 	          //variable
              int his 	                  //histeresis
              );
              
              
int duty_prop (int valcontrol,
              int ab,
              int pinf,           //pot inf
              int psup           //pot sup
              );
              
#endif