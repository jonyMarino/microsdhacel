#include "Mydefines.h"
#include "boxes.h" 
#include "boxesset.h"
#include "Timer.h" 
#include "FuncionVF.h" 
#include "bkr.h"  
#include "O2.h"
#include "presentaValor.hpp"
#include "EPM203Manejador.hpp"

/*#define ENDVF 0
#define RUNVF  1
#define RMPVF 0
#define MSTVF 1
  */
extern int ValFinal[4];
extern word minutos;
extern dword rampa_mestaTime;
extern ManejadorImpresionPersistente mi;
extern EPM203Manejador os;
long tempActVF;
char puntoDecimalVF;
char contProtecRuido;   
        
char VFmod;
char VFstatus; 
                      
char EtapaCorr=0;
char CantEtapas=0;
char Kdec= 0;
bool fistTimeInicio=TRUE;
bool fistTimeFin=TRUE;
 

PresentaValor cartelInicio(NULL,"Comienzo de Ciclo");
PresentaValor cartelFin(NULL,"Fin de Ciclo");

#define Te_MES_ANT PRom[R_Tmpm1+EtapaCorr-2]                              //temp meseta etapa anterior  
#define Te_MES     PRom[R_Tmpm1+EtapaCorr-1]                              //temp meseta etapa actual
#define Ve_RMP     PRom[R_Vrmp1+EtapaCorr-1]  
#define Ti_MES     PRom[R_Tiem1+EtapaCorr-1]
#define MaxMin     10                                                     //fija los limites de sobrepaso de la temperatura de meseta
#define PROTEC     2                                                      //cantidad de veces que compruebo la condicion de fin de rampa

void calculoTempInstYtiempoMesetaVF (void){     

   if(EtapaCorr==0)
    VFstatus = ENDVF;

 /* calculo de la temperatura de la rampa cada 1 segundos y             */
/* calculo del tiempo transcurrido una ves llegado a la temp de meseta */  
  puntoDecimalVF = PRom[R_Decimales];

  if(VFstatus == RUNVF){                                                  //estoy corriendo?
     if(fistTimeInicio){
       if(mi.getHabilitado()!=1)   
          mi.setHabilitado(1);
       fistTimeInicio=FALSE;
       fistTimeFin=TRUE;
       cartelInicio.imprimirValor(os);
     }
 /*/////////////////calculo del setpoint(tmpAct)/////////////// */
  
   if(VFmod==RMPVF) {                                                     //si, es rampa?
    
      if(puntoDecimalVF == 0)                                             //si, pongo decimales
        Kdec = 10;
      else
        Kdec = 1;
      
       
       if(Te_MES > Te_MES_ANT){                                           //pendiente positiva?
        tempActVF = Te_MES_ANT + (Ve_RMP*rampa_mestaTime)/(60 * Kdec);    //si, calculo sp
 /*///////////////control de fin de rampa//////////////////////// */
        if(ValFinal[0]>=Te_MES){                                           //verifico la condicion contProtecRuido veces
           contProtecRuido++;
           
           if(contProtecRuido==PROTEC)
              contProtecRuido=0;
            else
              return;
            
            tempActVF =Te_MES; 
            rampa_mestaTime=0;
            VFmod=MSTVF;                                                     //comienzo de meseta
            //ResetScroll();
            return;
        }
          
        //verifico la condicion para el limite max
        if(tempActVF>=(Te_MES+MaxMin))                                       //me pase?
          tempActVF=Te_MES+MaxMin;                                           //limito
        else
          return;         //retorno por que no llegue al limite max
        
       }
       
       if(Te_MES < Te_MES_ANT){                                               //pendiente negativa?
        tempActVF = Te_MES_ANT - (Ve_RMP*rampa_mestaTime)/(60 * Kdec);
        /*/////////control de fin de rampa/////////////////// */
        if(ValFinal[0]<=Te_MES){
           contProtecRuido++;
           
           if(contProtecRuido==PROTEC)
              contProtecRuido=0;
            else
              return;
            
            tempActVF =Te_MES; 
            rampa_mestaTime=0;
            VFmod=MSTVF;                                                      //comienzo de meseta
            //ResetScroll();
            return;
        }
          
        //verifico la condicion para el limite min
        if(tempActVF<=(Te_MES-MaxMin))
          tempActVF=Te_MES-MaxMin;
        else
          return;                                                             //retorno por que no llegue al limite max
        
       }
       
       if(Te_MES == Te_MES_ANT){                                               //iguales?
          tempActVF =Te_MES;
          rampa_mestaTime=0;
          contProtecRuido=0;
          VFmod=MSTVF;                                                         //comienzo de meseta
          //ResetScroll();
          return;     
       }
      
  }
   
/*/////////////control de fin de meseta//////////////////////////*/  
  
  else if((Ti_MES*60) <= rampa_mestaTime){                                    //si no era rampa es meseta 
    rampa_mestaTime = 0;
    minutos=1;
    EtapaCorr++;
    if((EtapaCorr-1)<CantEtapas){                                              //supere la cantidad de etapas?
      VFmod=RMPVF;      //INICIA RAMPA
      //ResetScroll();
      return;
    }else {                                                                     // si supere -> fin
      tempActVF =Te_MES_ANT; 
      VFstatus = ENDVF;
      //ResetScroll(); 
    }
  }

 
}else{                                                                           //si no era run era stop  
  rampa_mestaTime = 0;                                                           // reseteo todo
  contProtecRuido=0;
  VFmod=RMPVF;
  tempActVF=0;
  if(fistTimeFin){
    if(mi.getHabilitado()!=0)
     mi.setHabilitado(0);    
    fistTimeInicio=TRUE;
    fistTimeFin=FALSE;
    cartelFin.imprimirValor(os);
   }
 // ResetScroll();      
}
}




