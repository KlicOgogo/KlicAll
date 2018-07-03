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
    numm                db  15  dup(0)
    sign1               db  "^", 0 
    sign2               db  "*", 0
    db_dzeln            db  10  dup(0)
    db_degg             db  10  dup(0)
    likk                dd  0
    degg                dd  0
    dzeln               dd  0
    minus               db  "-", 0
    zerr                db  "0 hasn't this division"
.code

MainProc	proc
            invoke StdIn, addr numm, 15
            invoke atol, addr numm
            mov likk, eax
            mov ebx, 2
            cmp eax, 0
            jg gogo
            je zero
            neg eax
            mov likk, eax
            invoke StdOut, addr minus
            mov ebx, 2 
            mov eax, likk
            jmp gogo
zero:
            invoke StdOut, addr zerr
gogo:
            cdq
            idiv ebx
            cmp edx, 0
            je dzel
            mov eax, likk
            cmp degg, 0
            jne outttt
            inc ebx
            cmp eax, ebx
            jl fin
            jmp gogo
dzel:
            mov dzeln, ebx
            inc degg
            mov likk, eax
            jmp gogo
outttt:
            invoke  dwtoa, dzeln, addr db_dzeln
            invoke  dwtoa, degg, addr db_degg
            invoke  StdOut, addr db_dzeln
            invoke  StdOut, addr sign1
            invoke  StdOut, addr db_degg
            mov eax, likk
            cmp eax, 1
            je fin
            invoke  StdOut, addr sign2
            mov eax, likk
            inc ebx
            mov degg, 0
            cmp eax, ebx
            jl fin
            jmp gogo
fin:
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
