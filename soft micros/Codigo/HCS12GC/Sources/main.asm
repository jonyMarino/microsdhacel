;**************************************************************
;* This stationery serves as the framework for a              *
;* user application. For a more comprehensive program that    *
;* demonstrates the more advanced functionality of this       *
;* processor, please see the demonstration applications       *
;* located in the examples subdirectory of the                *
;* Metrowerks CodeWarrior for the HC12 Program directory      *
;**************************************************************

; export symbols
            XDEF asm_main
            ; we use export 'Entry' as symbol. This allows us to
            ; reference 'Entry' either in the linker .prm file
            ; or from C/C++ later on

; include derivative specific macros
            INCLUDE 'mc9s12a256.inc'

; variable/data section
MY_EXTENDED_RAM: SECTION
; Insert here your data definition. For demonstration, temp_byte is used.
temp_byte ds.b 1

; code section
MyCode:     SECTION
; this assembly routine is called by the C/C++ application
asm_main:
            CLI               ; enable interrupts

            MOVB #1,temp_byte ; just some demonstration code
            NOP               ; Insert here you own code

            RTC               ; return to caller
