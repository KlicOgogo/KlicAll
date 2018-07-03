.386
PUBLIC _poww
.model flat
.code

_poww proc
push ebp
mov ebp, esp
mov esi, [ebp+8]
mov edi, [ebp+12]
mov ecx, edi
mov edi, [ebp+8]
mov eax, edi
dec ecx
mov ebx, eax

_pow_:
imul ebx
loop _pow_
pop ebp
ret 
_poww endp
end