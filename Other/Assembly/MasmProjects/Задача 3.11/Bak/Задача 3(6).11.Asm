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
    db_n                db  100 dup(0)
    n                   dd  ?
    nnnn                dd  ?
    db_matrix           db  10  dup(?)
    matrix              dd  100 dup(?)
    newline             db  10, 0
    n_cyc               dd  ?
    tprob               db  " "
    yes                 db  "yes!", 0
    no                  db  "no!", 0
    counter             dd  0
.code

MainProc	proc
            invoke  StdIn, addr db_n, 100
            invoke  atol, addr db_n
            mov n, eax
            mov n_cyc, eax
            mov edi, n_cyc
            imul n
            mov edi, eax
            mov eax, n
            mov esi, 4
            imul esi
            mov nnnn, eax
            xor ebx, ebx
matr:
            invoke  StdIn,  addr db_matrix, 100
            invoke  atol, addr db_matrix 
            mov matrix[ebx*4], eax
            inc ebx
            dec edi
            cmp edi, 0
            jg matr
            ; вывад матрыцы
            xor edi, edi
            xor ebx, ebx
            mov esi, n
outt:       
            invoke dwtoa, matrix[edi][ebx], addr db_matrix
            invoke StdOut, addr db_matrix
            invoke StdOut, addr tprob
            add edi, 4
            dec esi
            cmp esi, 0
            jg outt
            invoke StdOut, addr newline
            xor edi, edi
            add ebx, nnnn
            mov esi, n
            mov edi, n_cyc
            dec n_cyc
            xor edi, edi 
            cmp n_cyc, 0
            jg outt
            ; праверка матрыцы
            mov eax, n
            mov n_cyc, eax
            xor edi, edi
            xor ebx, ebx
            mov esi, n
prov:
            cmp matrix[edi][ebx], 0
            jne notzer
            inc counter
notzer:
            add edi, 4
            dec esi
            cmp esi, 0
            jg prov
            mov eax, counter
            cmp eax, 1
            jne nooo
            xor eax, eax
            mov counter, eax
            xor edi, edi
            add ebx, nnnn
            mov esi, n
            mov edi, n_cyc
            dec n_cyc
            xor edi, edi 
            cmp n_cyc, 0
            jg prov
yeah:
            invoke StdOut, addr no
            jmp finn
nooo:
            invoke StdOut, addr no
finn:
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
