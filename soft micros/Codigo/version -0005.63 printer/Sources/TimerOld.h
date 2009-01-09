#ifndef _TIMER_OLD_H
#define _TIMER_OLD_H

#define OPEN 1
#define CLOSE 2
#define REST 0

#define CONT_INIT 0

/*    ATENCION!!!!          */
/*    ATENCION!!!!          */
#ifdef jony_23_08
#define CANTIDAD_CONTADORES 8 /*Aumentar en 1 cada vez que se quiere utilizar otro contador*/
#else
#define CANTIDAD_CONTADORES 6 /*Aumentar en 1 cada vez que se quiere utilizar otro contador*/
#endif
/*    ATENCION!!!!          */
/*    ATENCION!!!!          */

/* tipos de contadores*/
#define CONTINUO_SET 0
#define CONTINUO_TOG 1
#define UNICO_SET 2
#define FIN 3

#ifdef jony_15_08
/*																			 
** ===================================================================
**     Method      :  HabilitarAccionPagApagado 
** ===================================================================
*/
void HabilitarAccionPagApagado(void);
#endif


byte Timer_Run(word tiempo,bool * flag, byte tipo);

/*
** =======================================================================
**     Method      :  Timer_Run 
**
**     Description :
**         Arranca un nuevo timer o reconfigura un timer existente 
**     basandose en la direccion del flag. No bloquea el micro. Y los 
**     cambios para CONTINUO_XXX se ejecutan a partir de que se termina 
**     la cuenta actual.
**      Esta funci�n est� pensada para contadores que se utilizan 
**     costantemente y no para ir agregando/desechando contadores de forma 
**     periodica, para lo cual habria que implementar una funci�n con 
**     "allocaci�n" de memoria.
**     Parameters  :
**         NAME            - DESCRIPTION
**         tiempo          - Tiempo de ejecuci�n del timer (en ms)
**       * flag            - Direcci�n del flag a modificar pasado el
**                           tiempo
**         tipo            - Forma de ejecutar el timer:
**                           UNICO_SET - se llega al tiempo indicado en 
**                            time y se pone el flag en 1
**													 CONTINUO_SET - se llega al tiempo indicado en 
**                            time, se pone el flag en 1 y se reinicia la
**                            la operaci�n. 
**                           CONTINUO_TOG - se llega al tiempo indicado en 
**                            time, se "togglea" el flag y se reinicia la
**                            la operaci�n. 
**                           
**
**     Returns     :
**         ---             - ERR_OK - OK
**                         - ERR_RANGE - Hay que aumentar	 
**                          CANTIDAD_CONTADORES en uno para que funcione
**
** =======================================================================
*/

byte Timer_Terminate(bool * flag);
/*
** ===================================================================
**     Method      :  TmDt1_GetTime (bean TimeDate)
**
**     Description :
**         Termina con el contador que se est� ejecutando.  
**     Parameters  :
**         NAME            - DESCRIPTION
**       * flag            - Direcci�n del flag que pertenece al contador
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_VALUE - El contador especificado no se encuentra.
** ===================================================================
*/

 
void TI40ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI40ms_OnInterrupt (module Events)
**
**     From bean   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1ms_OnInterrupt(void);
/*
** ===================================================================
**     Event       :  TI1ms_OnInterrupt (module Events)
**
**     From bean   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#endif