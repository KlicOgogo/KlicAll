.586
PUBLIC _pokazat
.model flat
.const 
con_0 dd 0
con_n1 dd -1.0
con_1 dd 1.0
con_2 dd 2.0
min_ dd -20
.data
a dd ?
buf_ dd ?
xx dd ?
.code
;---------------------------------------
_pokazat proc
finit
mov ebx, 0
mov eax, [esp+8]
mov xx, eax
mov eax, [esp+4]
mov a, eax
fld xx
fcomp con_0
fstsw ax
sahf
jnc _cont00
mov ebx, 1
fld xx
fmul con_n1
fstp xx
_cont00:
mov ecx, 0
_cycle01_AinX:
	inc ecx
	call _2inecx
	fcomp xx
	fstsw ax
	sahf
	jc _cycle01_AinX
	jz _cycle01_AinX
fld con_1
_cycle02_AinX:
	dec ecx
	cmp ecx, min_
	jl _away02_AinX
	call _2inecx
	fcomp xx
	fstsw ax
	sahf
	jc _cont01_AinX
	jnz _cycle02_AinX
	_cont01_AinX:
	call _Ain2
	fmul
	fld xx
	call _2inecx
	fsub
	fstp xx
	jmp _cycle02_AinX
_away02_AinX:
cmp ebx, 0
jz _finish
fstp buf_
fld con_1
fld buf_
fdiv
_finish:
;---
ret
_pokazat endp
;---------------------------------------
_Ain2 proc     ;ecx
push ecx
fld a
cmp ecx, 0
jz _ecx_is_0
jl _ecxless0
_ecxgr0:
	fld st
	fmul
	loop _ecxgr0
	jmp _away_Ain2
_ecxless0:
	neg ecx
	_cycecxless0:
	fsqrt
	loop _cycecxless0
	jmp _away_Ain2
_ecx_is_0:
	fstp buf_
	fld a
_away_Ain2:
pop ecx
ret
_Ain2 endp
;-----------------------------------------
_2inecx proc
push ecx
fld con_1
cmp ecx, 0
jz _ecxis0again
jl _ecxislessagain
_ecxbigger:
	fmul con_2
	loop _ecxbigger
	jmp _2inecx_away
_ecxislessagain:
	neg ecx
	_cycle1414:
	fdiv con_2
	loop _cycle1414
	jmp _2inecx_away
_ecxis0again:
	nop
_2inecx_away:
pop ecx
ret
_2inecx endp
end