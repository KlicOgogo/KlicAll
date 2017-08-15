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
    prob                db  " "
    newline             db  10, 0
    db_lik              db  100 dup(0)
    
.code

hexx        proc
            xor ebx, ebx
gogo:
            cdq
            mov ecx, 16
            idiv ecx
            cmp edx, 10
            jnl letter
            add edx, 48
            mov db_lik[ebx], dl
letter:
            add edx, 55
            mov db_lik[ebx], dl
            inc ebx
            cmp eax, 0
            jg gogo
            ret
hexx        endp
MainProc	proc
            mov eax, 1
            mov edi, 1
            mov esi, 1
gogogo:
            imul edi
            call hexx
            invoke StdOut, addr db_lik
            invoke StdOut, addr prob
            mov eax, esi
            inc edi
            cmp edi, 16
            jl gogogo
            invoke StdOut, addr newline
            inc esi
            mov eax, esi
            mov edi, 1
            cmp esi, 16
            jl gogogo
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
