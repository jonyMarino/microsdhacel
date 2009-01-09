/* ###################################################################
**     @file   PWMManager01_45.h
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.1
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/08/2008, 14:39
**     @detail
**         Metodos de factoria que retornan instancias de clase que 
**     encapsulan el comportamiento del PWM01 y PWM45 manejados 
**     simultaneamente.
**      Para utilizar alguno de los dos por separado, utilize PWMHardXX. 
**
**		 Ancestor  : PWM
**
**     Autor     : Jonathan Marino
**     mail      : jonymarino@gmail.com
** ###################################################################*/

#ifndef _PWM_MANAGER_01_45_H_
#define _PWM_MANAGER_01_45_H_

#include "PWM.h"
/**
**  @fn struct PWM * PWMManager01_45_get01(TConfPWM * conf);
**
**  @brief Maneja el PWM01 del micro, si se sabe que 
**         se utilizara el PWM45
**          
**  @param conf - Direccion en memoria donde se encuentra 
**                la configuracion del PWM.
**  @return Instancia de @ref PWM que maneja el PWM01 
*/
struct PWM * PWMManager01_45_get01(TConfPWM * conf);

/**
**  @fn struct PWM * PWMManager01_45_get45(TConfPWM * conf);
**
**  @brief Maneja el PWM45 del micro, si se sabe que 
**         se utilizara el PWM01
**          
**  @param conf - Direccion en memoria donde se encuentra 
**                la configuracion del PWM.
**  @return Instancia de @ref PWM que maneja el PWM45 
*/
struct PWM * PWMManager01_45_get45(TConfPWM * conf);

#endif
