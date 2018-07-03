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
    slovy               db  300 dup(' ')
    slova               db  300 dup(0)
    kolk                dd  0
    lokk                dd  0
    finish              db  15  dup(' ')
.code

Lik         proc
            xor ecx, ecx
            xor edi, edi
prov:
            mov cl, slova[edi]
            cmp cl, 48
            jl noo
            cmp cl, 57
            jg noo
            inc edi
            jmp prov
            
noo:
            cmp cl, 0
            je yeah
            mov lokk, 0
            jmp endd
yeah:
            mov lokk, 1
endd:
            ret
Lik         endp

MainProc	proc
            invoke StdIn, addr slovy, 300
            xor eax, eax
            xor ebx, ebx
            xor esi, esi
razbiu:
            mov al, slovy[ebx]
            cmp al, 32
            je probel
            mov slova[esi], al
            cmp al, 0
            je fin
            inc esi
            inc ebx
            jmp razbiu
probel:
            mov slova[esi], 0
            call Lik
            xor esi, esi
            mov ecx, 300
slovaa:
            mov slova[esi], 48
            inc esi
            loop slovaa
            xor esi, esi
            xor ecx, ecx 
            inc ebx
            mov edx, lokk
            add kolk, edx
            jmp razbiu
            
fin:
            mov slova[esi], 0
            call Lik
            mov edx, lokk
            add kolk, edx
            mov eax, kolk
            invoke  dwtoa, kolk, addr finish
            invoke StdOut, addr finish
            ;invoke StdOut, addr kolk
            ;invoke  StdOu, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc