.386
PUBLIC _summm1
PUBLIC @mull@8
PUBLIC @summ@8
PUBLIC _summm2@12
.model flat

.code
_summm1 proc
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov ebx, [ebp+12]
mov ecx, [ebp+16]
imul ebx
add eax, ecx
pop ebp
ret
_summm1 endp

_summm2@12 proc
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov ebx, [ebp+12]
mov ecx, [ebp+16]
imul ebx
add eax, ecx
pop ebp
ret 12
_summm2@12 endp

@summ@8 proc
mov eax, ecx
add eax, edx
ret
@summ@8 endp

@mull@8 proc
mov eax, ecx
imul edx
ret
@mull@8 endp

end