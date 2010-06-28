#ifndef _PWM_PERIODOS_H
#define _PWM_PERIODOS_H

/* Constants for period mode */
typedef enum{
  PWM_100ms       =0,         /* Constant for switch to mode 0 */
  PWM_200ms       =1,         /* Constant for switch to mode 1 */
  PWM_500ms       =2,         /* Constant for switch to mode 2 */
  PWM_1sec        =3,         /* Constant for switch to mode 3 */
  PWM_2sec        =4,         /* Constant for switch to mode 4 */
  PWM_5sec        =5,         /* Constant for switch to mode 5 */
  PWM_10sec       =6,         /* Constant for switch to mode 6 */
  PWM_20sec       =7,         /* Constant for switch to mode 7 */
  PWM_50sec       =8,         /* Constant for switch to mode 8 */
  PWM_Anl         =9					/* Constant for switch to mode 9 */
}TPeriod;	 /* Data type for select modes */

#define PWM_MAX_VALUE_PERIODS 9
 
 typedef enum{
  timer_1ms       =625,         
  timer_40ms      =25000,       
  
}timComp;	 /* Data type for select modes */


#endif

 