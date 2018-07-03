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
    str                 db  100 dup(0)
.code

MainProc	proc
            invoke  StdIn, addr str, 100        
            xor eax, eax
            xor ebx, ebx
            mov al, str[ebx]
            cmp al, 97
            jl noo
            cmp al, 122
            jg noo
            sub al, 32
            mov str[ebx], al
noo:
            inc ebx
            cmp str[ebx], 13
            jne gogo
            Invoke  StdOut, addr str
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
