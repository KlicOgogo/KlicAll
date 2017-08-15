.386
PUBLIC _summm1
PUBLIC _summm2@12
.model flat

.code
_summ1 proc
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov ebx, [ebp+12]
mov ecx, [ebp+16]
imul ebx
add eax, ecx
pop ebp
ret
_summ1 endp

_summ2@12 proc
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov ebx, [ebp+12]
mov ecx, [ebp+16]
imul ebx
add eax, ecx
pop ebp
ret
_summ2@12 endp
end