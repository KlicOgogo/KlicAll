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
nota:
            cmp al, 98
            jne notb
            inc edi
notb:
            inc esi
            inc ebx
            cmp arr1[ebx], 13
            jne gogo 
            mov ebx, ecx 
ashki:
            invoke  StdOut, addr ashka
            dec ebx
            cmp ebx, 0
            jg ashki
bshki:
            invoke  StdOut, addr bshka
            dec edi
            cmp edi, 0
            jg bshki
cshki:
            invoke  StdOut, addr cshka
            dec esi
            cmp esi, 0
            jg cshka
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
