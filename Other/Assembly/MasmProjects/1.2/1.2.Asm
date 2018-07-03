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
    interf1             db  "Enter m:", 13, 10, 0
    interf2             db  "Enter n:", 13, 10, 0
    interf3             db  "The answer is: ", 0
    sum                 dd  0
    buf                 db  300 dup(' ')
    zero                db  48, 0

.code

MainProc	proc
            invoke  StdOut, addr interf1
            invoke  StdIn, addr buf, 300
            invoke  atol, addr buf
            mov esi, eax
            invoke  StdOut, addr interf2
            invoke  StdIn, addr buf, 300 
            invoke  atol, addr buf
            mov ecx, esi
            cmp ecx, 0
            je endd
findsum:
            cdq
            mov ebx, 10
            idiv ebx
            add sum, edx
            loop findsum
            invoke dwtoa, sum, addr buf
            invoke StdOut, addr interf3
            invoke StdOut, addr buf
            jmp enddd
endd:
            invoke StdOut, addr interf3
            invoke StdOut, addr zero 
enddd:
            invoke StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
