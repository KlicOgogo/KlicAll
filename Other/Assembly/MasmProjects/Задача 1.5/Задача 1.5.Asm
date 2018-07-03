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
    arr1                db  100 dup(0)
    ashka               db 'a', 0
    bshka               db 'b', 0
    cshka               db 'c', 0
.code

MainProc	proc
            invoke  StdIn, addr arr1, 100
            xor eax, eax
            xor ecx, ecx
            xor edi, edi
            xor esi, esi
            xor ebx, ebx
gogo:
            mov al, arr1[ebx]
            cmp al, 97
            jne nota
            inc ecx
            inc ebx
            jmp gogo
nota:
            cmp al, 98
            jne notb
            inc edi
            inc ebx
            jmp gogo
notb:
            cmp al, 99
            jne outt
            inc esi
            inc ebx
            jmp gogo
outt:
            mov ebx, ecx 
ashki:
            cmp ebx, 0
            jng bshki
            invoke  StdOut, addr ashka
            dec ebx
            cmp ebx, 0
            jg ashki
bshki:
            cmp edi, 0
            jng cshki
            invoke  StdOut, addr bshka
            dec edi
            cmp edi, 0
            jg bshki
cshki:
            cmp esi, 0
            jng endd
            invoke  StdOut, addr cshka
            dec esi
            cmp esi, 0
            jg cshki
endd:
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
