/* MODULE Power Sense(powsns)*/
byte pwsn=0;
bool PwsnError=TRUE;

/*
** ===================================================================
**     Method      :  Habilitar_Grabado_PowDown 
** ===================================================================
*/
void POWSNS_Habilitar(void){
  PwsnError=FALSE;  
}

void POWSNS_Check(void){
      if (PWSN_GetVal() && !PwsnError)		    //Pwsn is high??
    {		 
    pwsn++;									// inc counter
      if (pwsn==30){  // is counter = 30?				
      Cpu_DisableInt();
      O2_PutVal(0);
			O4_PutVal(0);
			O6_PutVal(0);
			O7_PutVal(0);
      Display1_PutVal(0);
			#ifdef _PROGRAMADOR
      
      GuardarPrograma();
      
      #endif
      PwsnError=TRUE;
      Cpu_EnableInt();
      }
    }else pwsn=0;							 // put counter=0
}