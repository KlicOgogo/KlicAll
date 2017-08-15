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
    fin db 300 dup(?)
.code
    
    

MainProc	proc
            ;invoke  StdOut, addr szHelloWorld
            mov eax, 1
            xor ebx, ebx
            mov ecx, 256
            gooog:
            mov fin[ebx], al 
            inc ebx
            mov esi, eax
            cdq
            mov edi, 10
            idiv edi
            cmp edx, 9
            jne nedes
            mov fin[ebx], 10
            inc ebx
            nedes:
            mov eax, esi
            inc eax
            loop gooog
            ;mov fin[eax], 0
            invoke  StdOut, addr fin
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
