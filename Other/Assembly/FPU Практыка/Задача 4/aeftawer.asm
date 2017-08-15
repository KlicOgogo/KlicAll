.386
PUBLIC _pokazat
.model flat


.data
x dd ?
aa dd ?
bud dd ?

.code
_pokazat proc

push ebp
mov ebp, esp
mov eax, dword ptr[ebp+8]
mov aa, eax
mov eax, dword ptr[ebp+12]
mov x, eax
finit
fld x
fld aa
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
pop ebp
ret
_pokazat endp
end