.386
PUBLIC _graal
.model flat

.const
c0 dd 0
step dd 0.00002
step2 dd 0.00001

.data
a dd ?
b dd ?
graa dd ?

.code
_graal proc
finit
push ebp
mov ebp, esp
fld dword ptr [ebp+8]
fstp a
fld dword ptr [ebp+12]
fstp b
fld a
fstp graa
fld c0
gra:
	fld graa
	fadd step2
	fld st
	fcos
	fmul
	fmul step
	fadd
	fld graa
	fadd step
	fcom b
	fstp graa
	fstsw ax
	sahf
	jc gra
pop ebp
ret
_graal endp

end