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

.const
    c10                 dq  10.0
    step                dq  0.5
    log2e               dd  1.44269504
    
.data
    buf                 db  300 dup(' ')
    a                   dd  ?
    ee                  dq  2.718281828
    db_a                db  100 dup(0) 
    x                   dq  1.0
    startline           db  "log2x      lnx     powex       powax", 10
    db_log2x            db  10 dup(0) 
    db_lnx              db  10 dup(0)
    db_powex            db  10 dup(0)
    db_powax            db  10 dup(0)
    log2x               dq  0
    lnx                 dq  0
    powex               dq  2.718281828
    powax               dq  ?
    poww                dq  ? 
    newline             db  10, 0
    prob                db  " "
.code
_pokazat    proc
            finit
            fld x
            fld a
            fyl2x
            fld st(0)
            frndint
            fxch st(1)
            fsub st(0), st(1)
            f2xm1   
            fld1
            fadd
            fscale
            fxch st(1)
            fstp st
            fstp poww    
            ret
_pokazat endp



MainProc	proc
            invoke  StdIn, addr db_a, 100
            invoke  atol, addr db_a
            mov a, eax
          ;  invoke  StdOut, addr startline
            finit
            fild a
            fstp powax
outt:
            invoke FloatToStr, log2x, addr db_log2x
            invoke StdOut, addr db_log2x
            invoke StdOut, addr prob
            invoke FloatToStr, lnx, addr db_lnx
            invoke StdOut, addr db_lnx
            invoke StdOut, addr prob
            invoke FloatToStr, powex, addr db_powex
            invoke StdOut, addr db_powex
            invoke StdOut, addr prob
            invoke FloatToStr, powax, addr db_powax
            invoke StdOut, addr db_powax
            invoke StdOut, addr prob
            invoke StdOut, addr newline
            fld x
            fld step
            fadd
            fstp x
            
            fld1
            fld x
            fyl2x
            fst log2x
            
            fld log2e
            fdiv
            fstp lnx
            
            fld powax
            fild a
            fsqrt
            fmul
            fstp powax
            
            fld powex
            fld ee
            fsqrt
            fmul
            fstp powex 
            
            fld x
            fld c10
            fcompp
            fstsw ax
            sahf
            jnc outt
           ; jz outt
            
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

end MainProc
