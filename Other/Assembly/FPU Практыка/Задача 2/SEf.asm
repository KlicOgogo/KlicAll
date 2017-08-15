.386
PUBLIC _lndva
PUBLIC _llndva
.model flat

.const
mnogo dd 10000000
c1 dd 1
cm1 dd -1
.data
sum dd 0.0
k dd 1
sgn dd 1
kk dd 1
summ dd 0.0
sgnn dd 1
.code 

_llndva proc
gogoo:
finit
fld summ
fild sgnn
fild kk
fdiv
fadd
fstp summ
fild sgnn
fild cm1
fmul
fistp sgnn
inc kk
mov eax, kk
cmp eax, mnogo
jng gogoo
fld summ
ret
_llndva endp

_lndva proc
gogo:
mov eax, k
inc eax
mov ebx, 2
cdq
idiv ebx
cmp edx, 0
je cotn
mov sgn, -1
jmp go
cotn:
mov sgn, 1
go:
finit
fld sum
fild sgn
fild k
fdiv
fadd 
fstp sum
inc k
mov eax, k
cmp eax, mnogo
jng gogo
fld sum
ret
_lndva endp

end

