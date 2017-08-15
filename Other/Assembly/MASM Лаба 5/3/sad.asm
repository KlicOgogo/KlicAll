.386
PUBLIC _concatt@16
.model flat
.data
fin db 200 dup(?)
.code

_concatt@16 proc
push ebp
mov ebp, esp
mov eax, [ebp+8]
mov ecx, [ebp+12]
xor edx, edx
xor esi, esi
plusfir:
mov dl, [eax]
mov fin[esi], dl
inc esi
inc eax
loop plusfir
mov eax, [ebp+16]
mov ecx, [ebp+20]
plussec:
mov dl, [eax]
mov fin[esi], dl
inc eax
inc esi
loop plussec
lea eax, fin
pop ebp
ret 16
_concatt@16 endp
end