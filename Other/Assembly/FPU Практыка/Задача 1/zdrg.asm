.386
PUBLIC _raunn
.model flat

.const
c1 dd 1.0
zer dd 0.
c11 dd 11.
c16 dd 0.0625
cn10 dd -10.0
c10 dd 10.0
cn1 dd -1.0
dva dd 2.
mala dd 0.00001

.data
a dd 0
b dd 0
cc dd 0
i1 dd 0
cur_ dd 0
sign_ dd 0
pre_ dd 0
bin_ dd ?
bin2_ dd ?
ave_ dd 0
low_ dd 0
high_ dd 0
root_ dd ?
roots_ dd 4 dup(?)

.code 
_raunn proc
finit				
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov a, eax
mov eax, [ebp+12]
mov b, eax
mov eax, [ebp+16]
mov cc, eax
mov ecx, 1
fld cn10			
fstp i1
push i1
call signnn
fld sign_
fstp cur_
fld i1
fadd c16
fstp i1
_cycle_01:	
	fld cur_
	fstp pre_
	push i1
	call signnn
	fld sign_
	fstp cur_
	fld pre_
	fcomp cur_
	fstsw ax
	sahf
	jz _cont_03
		fld i1
		fsub c16
		fld i1
		call rofind
		cmp ecx,1
		jz _root
			mov eax, [roots_ +ecx*4 - 4]
			cmp eax, root_
			jz no_root
		_root:
			mov eax, root_
			mov [roots_ + ecx*4], eax
			inc ecx
		no_root:
_cont_03:
	fld i1			
	fadd  c16
	fstp i1
	fld i1
	fcomp  c10
	fstsw ax
	sahf
	jc _cycle_01
	jz _cycle_01
_away_01:
dec ecx
mov [roots_], ecx
lea eax, roots_
pop ebp
ret 
_raunn endp

signnn proc
push ebp
mov ebp, esp
fld dword ptr [ebp+8]	
fmul dword ptr [ebp+8]
fmul dword ptr [ebp+8]
fmul a
fld dword ptr [ebp+8]
fmul dword ptr [ebp+8]
fmul c11
fmul a
faddp st(1),st
fld dword ptr [ebp+8]
fmul cc
;fdiv a
faddp st(1), st
fld cc
fmul c11
fadd b
;fdiv a
faddp st(1), st
fcomp zer				
fstsw ax
sahf
jc _minus3
jnz _plus3
	fld zer
	fstp sign_
	jmp _cont_01
_minus3:
	fld cn1
	fstp sign_
	jmp _cont_01
_plus3:
	fld c1
	fstp sign_
_cont_01:
pop ebp
ret 4
signnn endp

rofind proc
_cycle011:
fstp bin_				
fst low_
push low_
call signnn
fld sign_
fstp low_
fld bin_
fst high_				
push high_
call signnn
fld sign_
fstp high_
fld st					
fadd st,st(2)
fdiv dva
fst bin_
push bin_
call signnn
fld sign_
fstp ave_
fld low_				
fcomp zer
fstsw ax
sahf
jnz _cont011
fld st(2)
fstp root_
jmp _ready
_cont011:
fld high_				
fcomp zer
fstsw ax
sahf
jnz _cont022
fld st(1)
fstp root_
jmp _ready
_cont022:
fld ave_				
fcomp zer
fstsw ax
sahf
jnz _cont033
fld st(0)
fstp root_
jmp _ready
_cont033:
fld low_				
fcomp ave_
fstsw ax
sahf
jz _cont0111
	fstp bin_			
	fstp st
	fld bin_
_cont0111:
fld high_				
fcomp ave_
fstsw ax
sahf
jz _cont0222
	fstp bin_			
	fstp bin2_
	fstp st
	fld bin_
	fld bin2_
_cont0222:
fld st
fsub st, st(2)
fcomp mala
fstsw ax
sahf
jnc _cycle011
	fld st
	fstp root_
_ready:
fstp st
fstp st
ret
rofind endp
end