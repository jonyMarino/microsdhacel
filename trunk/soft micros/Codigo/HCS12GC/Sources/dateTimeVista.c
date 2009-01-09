/* MODULE: dateTimeVista.c*/
#include "PropWithInc.h"
#include "PropHora.h"

#include "DiagramaNavegacion.h"
#include "ClassBoxLineal.h"

#include "com_events.h"

#include "TmDt1.h"

#include "dateTimeVista.h"

/*Funciones*/

/*
** ===================================================================
**     Method      :  dateTimeVista_setYear
**    Description  :  Setea el anio actual
** ===================================================================
*/
TError dateTimeVista_setYear(void * _self,int val){
  DATEREC date;
  
  getDate(_self,&date); 
  setDate(_self,val,date.Month,1);
  
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  dateTimeVista_getYear
**    Description  :  Obtiene el anio actual
** ===================================================================
*/
int dateTimeVista_getYear(void * _self){
  DATEREC date;
  
  getDate(_self,&date); 
  return date.Year;  
}

/*
** ===================================================================
**     Method      :  dateTimeVista_LimInfYear
**    Description  :  Limite Inferior de Anio
** ===================================================================
*/
int dateTimeVista_LimInfYear(void * _self){
  return 2008;
}
/*
** ===================================================================
**     Method      :  dateTimeVista_LimSupYear
**    Description  :  Limite Superior de Anio
** ===================================================================
*/
int dateTimeVista_LimSupYear(void * _self){
  return 2099;
}

/*
** ===================================================================
**     Method      :  dateTimeVista_setMonth
**    Description  :  Setea el mes actual
** ===================================================================
*/
TError dateTimeVista_setMonth(void * _self,int val){
  DATEREC date;
    
  getDate(_self,&date); 
  setDate(_self,date.Year,val,1);
  
  return ERR_OK;
  
}

/*
** ===================================================================
**     Method      :  dateTimeVista_getMonth
**    Description  :  Obtiene el mes actual
** ===================================================================
*/
int dateTimeVista_getMonth(void * _self){
  DATEREC date;
  
  getDate(_self,&date); 
  return date.Month;   
}

/*
** ===================================================================
**     Method      :  dateTimeVista_LimInfMonth
**    Description  :  Limite Inferior de mes actual
** ===================================================================
*/
int dateTimeVista_LimInfMonth(void * _self){
  return 1;  
}
/*
** ===================================================================
**     Method      :  dateTimeVista_LimSupMonth
**    Description  :  Limite Superior de mes actual
** ===================================================================
*/
int dateTimeVista_LimSupMonth(void * _self){
  return 12;
}


/*
** ===================================================================
**     Method      :  dateTimeVista_setDay
**    Description  :  Setea el dia actual
** ===================================================================
*/
TError dateTimeVista_setDay(void * _self,int val){
  DATEREC date;
  
  getDate(_self,&date); 
  setDate(_self,date.Year,date.Month,val);
  
  return ERR_OK;
  
}

/*
** ===================================================================
**     Method      :  dateTimeVista_getDay
**    Description  :  Obtiene el dia actual
** ===================================================================
*/
int dateTimeVista_getDay(void * _self){
  DATEREC date;
  
  getDate(_self,&date); 
  
  return date.Day; 
}

/*
** ===================================================================
**     Method      :  dateTimeVista_LimInfDay
**    Description  :  Limite Inferior de dia 
** ===================================================================
*/
int dateTimeVista_LimInfDay(void * _self){
  return 1;
}
/*
** ===================================================================
**     Method      :  dateTimeVista_LimSupDay
**    Description  :  Limite Superior de dia 
** ===================================================================
*/
int dateTimeVista_LimSupDay(void * _self){
  DATEREC date;
  
  getDate(_self,&date); 
  
  return TmDt1_GetMaxday(date.Year,date.Month);
}

/*
** ===================================================================
**     Method      :  dateTimeVista_setTime
**    Description  :  Setea el tiempo (Hora/min) actual
** ===================================================================
*/
TError dateTimeVista_setTime(void * _self,int val){
  byte hour = val/100;
  byte min  = val%100;
  
  setTime(_self,hour,min,0);
  
  return ERR_OK;
 
}

/*
** ===================================================================
**     Method      :  dateTimeVista_Sys_getTime
**    Description  :  Obtiene el tiempo (Hora/min) actual
** ===================================================================
*/
int dateTimeVista_Sys_getTime(void * _self){
  TIMEREC _time;
  
  getTime(_self,&_time);
  return (int)_time.Hour*100+_time.Min;
}
/*
** ===================================================================
**     Method      :  dateTimeVista_LimInfTime
**    Description  :  Limite Inferior de tiempo
** ===================================================================
*/
int dateTimeVista_LimInfTime(void * _self){
  return 0;
};
/*
** ===================================================================
**     Method      :  dateTimeVista_LimSupTime
**    Description  :  Limite Superior de tiempo
** ===================================================================
*/
int dateTimeVista_LimSupTime(void * _self){
  return 2359;
}


/*****************************/
/********PROPIEDADES**********/
/*****************************/

  /*Year*/
  const struct ConstructorPropWInc parYear={
    &PropiedadGenerica,dateTimeVista_getYear, dateTimeVista_setYear, dateTimeVista_LimInfYear, dateTimeVista_LimSupYear,&PropWInc,"A;o"
  };
  
  /*Month*/
    const struct ConstructorPropWInc parMonth={
    &PropiedadGenerica,dateTimeVista_getMonth, dateTimeVista_setMonth, dateTimeVista_LimInfMonth, dateTimeVista_LimSupMonth,&PropWInc,"MES "
  };
  
  /*Day*/
  const struct ConstructorPropWInc parDay={
    &PropiedadGenerica,dateTimeVista_getDay, dateTimeVista_setDay, dateTimeVista_LimInfDay, dateTimeVista_LimSupDay,&PropWInc,"diA "
  };
  
  /*Time*/
  const struct ConstPropHora parTime={
    &PropiedadGenerica,dateTimeVista_Sys_getTime, dateTimeVista_setTime, dateTimeVista_LimInfTime, dateTimeVista_LimSupTime,&PropHora,"horA"
  };



  const struct GetterGenerico *const dateTimeVistaProps[]={
    &parYear,
    &parMonth,
    &parDay,
    &parTime  
  };
  
  const NEW_ARRAY(arrayDateTimeGetters,dateTimeVistaProps);  
/*
** ===================================================================
**     Function      :  DateTimeVista_comuAdd 
**     Description :  Agrega la variable tipo DateTime a la comunicacion
** ===================================================================
*/

word dateTimeVista_comuAdd(const struct TmDt1 * adq,word dir_ini){
  word cant = sizeof(dateTimeVistaProps)/sizeof(struct GetterGenerico *)-1;

  com_Add(dateTimeVistaProps,adq,dir_ini,dir_ini+cant);

  return cant;
}

const struct BlockCnstrBoxLin cBoxDateTime;

/*
** ===================================================================
**     Function    :  AdqHmi_AddBoxes 
**     Description :  Agrega a los boxes el aquisidor
** ===================================================================
*/
void dateTimeVista_addBoxes(const struct BaseTiempo * bt,char * str,uchar num_obj){
  DN_AddBox(0,str,&cBoxDateTime,bt,num_obj);    
}



/*Boxes*/

const struct ConstructorPropWInc*const propsDateTime[]=	{
  			  &parYear,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
  			  &parMonth,
  			  &parDay,
  			  &parTime,
  			  NULL
};

const struct BlockCnstrBoxLin cBoxDateTime={
      &BoxLineal,
      propsDateTime,
			NULL
			};


