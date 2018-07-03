.386
PUBLIC _summa
.model flat

.const
adzin dd 1

.data
pramez dd ?
eps dd ?
x dd ?
xk dd ?
sum dd 0
k dd 1

.code
_summa proc
push ebp
mov ebp, esp
mov eax, dword ptr [ebp+8]
mov x, eax
mov eax, dword ptr [ebp+12]
mov eps, eax
finit
fld1
fstp xk
gogo:
fld sum
fld xk
fild k
fild adzin
fadd
fdiv 
fild k
fild adzin
fadd
fild adzin
fadd
fdiv
fst pramez
fadd
fstp sum
fld xk
fmul x
fstp xk
inc k
fld eps
fld pramez
fcompp
fstsw ax
sahf
jnc gogo
fld sum
pop ebp
ret
_summa endp
end