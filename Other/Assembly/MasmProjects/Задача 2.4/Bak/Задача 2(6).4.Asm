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
    szHelloWorld        db  "Hello, world!", 13, 10,
                            "Press ENTER to continue...", 13, 10, 0
    buf                 db  300 dup(' ')
    in_lik              db  3   dup(0)
    out_lik             db  3   dup(0)
    lik                 dd  ?
    lik1                dd  ?
    lik2                dd  ?
    nod                 dd  ?
.code

Inn         proc
            invoke  StdIn, addr in_lik, 3
            invoke  atol, addr in_lik  
            ret
Inn         endp

Outt        proc
            invoke  dwtoa, lik, addr out_lik
            invoke  StdOut, addr out_lik
            ret
Outt        endp

MainProc	proc
            call Inn
            mov lik1, eax
            call Inn
            mov lik2, eax
            call FindNOD
            mov eax, nod
            
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
