.386
PUBLIC _integ
.model flat

.const
stepc dd 100000
c05 dd 0.5

.data
step dd ?
a dd ?
b dd ?
sum dd 0

.code
_integ proc
push ebp
mov ebp, esp
mov eax, dword ptr [ebp+8]
mov a, eax
mov eax, dword ptr [ebp+12]
mov b, eax
finit
fld b
fld a
fsub
fild stepc
fdiv
fstp step
gogo:
fld sum
fld a
fld a
fcos
fmul
fld a
fld step
fadd
fst a
fld st
fcos
fmul
fadd
fadd
fstp sum
fld a
fld b
fcompp
xor eax, eax
fstsw ax
sahf
jc fin
jmp gogo
fin:
fld sum
fld step
fmul
fld c05
fmul
pop ebp
ret
_integ endp
end