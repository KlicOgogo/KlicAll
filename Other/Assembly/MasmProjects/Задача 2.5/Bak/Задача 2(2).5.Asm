.486
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc
include gdi32.inc
include user32.inc
include kernel32.inc

includelib masm32.lib
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib

.data

    buf                 db  300 dup(' ')
    kolk                dd  ?
    db_kokk             db  100 dup(0)
    sum                 dd  0
    db_lik              db  100 dup(0)
    srafm               dq  ?
    db_srafm            db  100 dup(0) 
.code

MainProc	proc
            invoke  StdIn, addr db_kolk, 100
            invoke  atol, addr db_kolk
            mov kolk, eax
            mov esi, kolk
summ:       
            invoke  StdIn, addr db_lik, 100
            invoke  atol, addr db_lik
            add sum, eax
            dec esi
            cmp esi, 0
            jg summ
            finit
            fild summ
            fild kolk
            fdiv
            fstp srafm
            invoke  FloatToStr, srafm, addr db_srafm 
            invoke  StdOut, addr db_srafm
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
