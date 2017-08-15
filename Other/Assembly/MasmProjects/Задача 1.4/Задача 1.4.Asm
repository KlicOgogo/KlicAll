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
    szHelloWorld        db  "Press ENTER to continue...", 13, 10, 0
    buf                 db  300 dup(' ')
    lik                 db  100 dup(0)
    fin                 db 8 dup(?)
.code

MainProc	proc
            xor eax, eax
            ;invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr lik, 100
            invoke atol, addr lik
            mov ecx, 8
            mov ebx, 7
            dvaa:
            test eax, 1
            jp zer
            mov fin[ebx], 49
            jmp toloop
            zer:
            mov fin[ebx], 48
            toloop:
            dec ebx
            shr eax, 1
            loop dvaa 
            invoke  StdOut, addr fin
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
