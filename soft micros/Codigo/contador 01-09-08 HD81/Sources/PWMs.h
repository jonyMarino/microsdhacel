#ifndef PWMs_H
#define PWMs_H
#include "Cpu.h"
/* Constants for period mode */
#define PWM_100ms       0         /* Constant for switch to mode 0 */
#define PWM_200ms       1         /* Constant for switch to mode 1 */
#define PWM_500ms       2         /* Constant for switch to mode 2 */
#define PWM_1sec        3         /* Constant for switch to mode 3 */
#define PWM_2sec        4         /* Constant for switch to mode 4 */
#define PWM_5sec        5         /* Constant for switch to mode 5 */
#define PWM_10sec       6         /* Constant for switch to mode 6 */
#define PWM_20sec       7         /* Constant for switch to mode 7 */
#define PWM_50sec       8         /* Constant for switch to mode 8 */
#define PWM_Anl         9         /* Constant for switch to mode 9 */

void PWM01_Init(void);
void PWM45_Init(void);
void PWM23_Init(void);

void PWM_SetPeriodMode(byte Mode, byte salida);
void setPWM_period(int Mode, byte salida);
void PWM_SetRatio16(word Ratio,byte salida);

#endif