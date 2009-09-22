#ifndef _FORMAS_CONTEO_H
#define _FORMAS_CONTEO_H

typedef enum{
  MODO_UP,
  MODO_DOWN
}TModoCuenta;

typedef enum{
  MODO_SPA_CUENTA,
  MODO_SPA_TOT_CUENTA,
  MODO_SPA_TOT_ON_SPP
}TModoSP_Auxiliar;

typedef enum{
  ACCION_CONTINUE,
  ACCION_STOP,
  ACCION_AUTO_RESET
}TAccionSP;

/*  Cuenta  */
long Cnt_getCuenta(void);

long Cnt_getCuentaEscalada(void);

void Cnt_setCuenta(long val);

void ResetCuenta(void);

void FormasConteo_Contador(void);

/*  SP Auxiliar */
TModoSP_Auxiliar Cnt_getModoSPaux(void);

byte  Cnt_setModoSPaux(TModoSP_Auxiliar mod);

long Cnt_getValCmpSPA(void);

void Cnt_clrValCmpSPA(void);

void Cnt_OnValEqualToSPA(void);

#endif