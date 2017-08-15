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
    newline             db  13, 10, 0
    buf                 db  300 dup(' ')
    wword               db  100 dup(0)
    count               dd  1
    countt              db  100 dup(0)
    isword              dd  0
                
.code

MainProc	proc
            invoke  StdIn, addr buf, 300
            xor ebx, ebx
            mov ecx, 1
            mov wword[ebx], 32
start:       
            cmp buf[ebx], 10
            je enddd    
            cmp buf[ebx], 13
            je endd
            cmp buf[ebx], 32
            je space
            mov isword, 1
            mov dl, buf[ebx]
            mov wword[ecx], dl
            inc ecx
            inc ebx
            jmp start
space:
            cmp isword, 1
            jne neow
            mov wword[ecx], 0
            invoke dwtoa, count, addr countt 
            invoke StdOut, addr countt
            invoke StdOut, addr wword
            invoke StdOut, addr newline
            mov isword, 0
            inc ebx
            inc count
            mov ecx, 1
            jmp start
neow:
            inc ebx
            jmp start            
endd:       
            cmp buf[ebx-1], 32
            jne space
enddd:
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
