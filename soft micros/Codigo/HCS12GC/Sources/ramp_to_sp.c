/*IMPLEMENTATION MODULE Ramp To Set Point */
#include "cnfbox.h" //SACAR: Es para el extern de PRom
#include "Programador.h"
#include "IFsh10.h"
#include "Mydefines.h"
#include "ramp_to_sp.h"


#ifdef PROG_SIMPLE_RSTP

#define RMP_CONTROL_CHANNEL 0
#define RMP_TO_SET_POINT_PROGRAM  0
#define VELOCITY_SEGMENT  0 
#define DWELL_SEGMENT			1

///////Arranque///////////////////
void RMP_Init(void){
  EscribirWord((word)&PRom[R_Programa+RMP_CONTROL_CHANNEL],RMP_TO_SET_POINT_PROGRAM+1);
  runPrograma(RMP_CONTROL_CHANNEL,RMP_TO_SET_POINT_PROGRAM,0,0);
  set_MainText("StoP");
  set_ProgState(PROG_RESETED,0);
}

///////Velocidad//////////////////
byte RMP_set_Velocity(int val,byte a){
  byte err= Prg_set_Time(val,RMP_TO_SET_POINT_PROGRAM,VELOCITY_SEGMENT);
  return err; 
}

int RMP_get_Velocity(byte a){
  return Prg_get_Time(RMP_TO_SET_POINT_PROGRAM,VELOCITY_SEGMENT);  
}

///////Set Point//////////////////
byte RMP_set_SetPoint(int val,byte a){
  byte err= Prg_set_SetPoint(val,RMP_TO_SET_POINT_PROGRAM,VELOCITY_SEGMENT);
  if(!err)
   err= Prg_set_SetPoint(val,RMP_TO_SET_POINT_PROGRAM,DWELL_SEGMENT);
  return err; 
}

int RMP_get_SetPoint(byte a){
  return Prg_get_SetPoint(RMP_TO_SET_POINT_PROGRAM,VELOCITY_SEGMENT);  
}

///////Tiempo Meseta//////////////////
byte RMP_set_DwellTime(int val,byte a){
  byte err= Prg_set_Time(val,RMP_TO_SET_POINT_PROGRAM,DWELL_SEGMENT);
  return err; 
}

int RMP_get_DwellTime(byte a){
  return Prg_get_Time(RMP_TO_SET_POINT_PROGRAM,DWELL_SEGMENT);  
}

///////Funcion: Esta en Meseta?////////////////
bool RMP_isDwell(void){
  bool isDwell; 
  
  isDwell=(get_iActualSegment(RMP_CONTROL_CHANNEL)==DWELL_SEGMENT);

  return  isDwell;
}

/////// Get Tiempo de Meseta corriendo/////////
int get_RunningDwellTime(void){
  if(!RMP_isDwell())
    return 0;
  else
    return get_SegmentTime(RMP_CONTROL_CHANNEL);
}

#endif
/*END MODULE Ramp To Set Point */
