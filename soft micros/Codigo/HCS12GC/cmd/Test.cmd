/// Comandos de Testeo

DEFINE SPInit= 0x1400 /* Initial value for the stack. */
/* Make sure RAM memory is available at this address.*/
LF test.res /* Open log file. */
LOG CMDLINE=OFF, CMDFILE=ON, RESPONSES=ON, ERRORS=ON, NOTICES=OFF
RS SP= SPInit /* Initialize Stack Pointer. */
BS Pasar_Numero{1} /* Set a breakpoint at the beginning of Func. */
BS Pasar_Numero{-1} /* Set a breakpoint at the end of Func. */
G Pasar_Numero /* Start execution at function Func. */
WAIT 100;s /* Wait until breakpoint is reached. */
A valor=0x5 /* Set a to 5. */
A Num_display=0x1 /* Set b to 1. */
G /* Continue Execution. */
WAIT 100;s /* Wait until second breakpoint is reached. */
printf ("valor = %d",valor)
NOLF