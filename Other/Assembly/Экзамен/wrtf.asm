.386
PUBLIC _ary
PUBLIC _tryga
PUBLIC _laga

.model flat

.const
sotka dd 100
adzin dd 1

.data
buf dd ?

.code
_ary proc
push ebp
mov ebp, esp
mov eax, dword ptr [ebp+8]
mov buf, eax
finit
fld buf
fild sotka
fadd
pop ebp
ret
_ary endp

_tryga proc
push ebp
mov ebp, esp
mov eax, dword ptr [ebp+8]
mov buf, eax
finit 
fld buf
fcos
pop ebp
ret
_tryga endp

_laga proc
push ebp
mov ebp, esp
mov eax, dword ptr [ebp+8]
mov buf, eax
finit
fild adzin
fld buf
fyl2x
pop ebp
ret
_laga endp
end