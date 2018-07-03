.386
PUBLIC _apx
.model flat

.const 
c0 dd 0
cn1 dd -1.0
c1 dd 1.0
c2 dd 2.0
minn dd -20

.data
a dd ?
buff dd ?
xxx dd ?

.code
_apx proc
finit
push ebp
mov ebp, esp
xor ebx, ebx
mov eax, [ebp+12]
mov xxx, eax
mov eax, [ebp+8]
mov a, eax
fld xxx
fcomp c0
fstsw ax
sahf
jnc normm
mov ebx, 1
fld xxx
fmul cn1
fstp xxx
normm:
mov ecx, 0
_cycle01:
	inc ecx
	push ecx
	fld c1
	cmp ecx, 0
	jz enddd
	jl isless
bigg:
	fmul c2
	loop bigg
	jmp enddd
isless:
	neg ecx
	divvvv:
	fdiv c2
	loop divvvv
	jmp enddd
enddd:
	pop ecx
	fcomp xxx
	fstsw ax
	sahf
	jc _cycle01
	jz _cycle01
fld c1
_cycle02:
	dec ecx
	cmp ecx, minn
	jl _away02
	push ecx
fld c1
cmp ecx, 0
jz enddd1
jl isless1
bigg1:
	fmul c2
	loop bigg1
	jmp enddd1
isless1:
	neg ecx
	divvvv1:
	fdiv c2
	loop divvvv1
	jmp enddd1
enddd1:
pop ecx
	fcomp xxx
	fstsw ax
	sahf
	jc _cont01
	jnz _cycle02
	_cont01:
	push ecx
	fld a
	cmp ecx, 0
	jz _ecx_is_0
	jl _ecxless0
_ecxgr0:
	fld st
	fmul
	loop _ecxgr0
	jmp _away
_ecxless0:
	neg ecx
	_cycecxless0:
	fsqrt
	loop _cycecxless0
	jmp _away
_ecx_is_0:
	fstp buff
	fld a
_away:
pop ecx

	fmul
	fld xxx
	push ecx
fld c1
cmp ecx, 0
jz enddd2
jl isless2
bigg2:
	fmul c2
	loop bigg2
	jmp enddd2
isless2:
	neg ecx
	divvvv2:
	fdiv c2
	loop divvvv2
	jmp enddd2
enddd2:
pop ecx
	fsub
	fstp xxx
	jmp _cycle02
_away02:
cmp ebx, 0
jz fin
fstp buff
fld c1
fld buff
fdiv
fin:
pop ebp
ret
_apx endp
end