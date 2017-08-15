.386
public @sixttn@8
public @tentth@8
.model flat
.code

@sixttn@8 proc
mov ebx, ecx
mov ecx, edx
xor esi, esi
prov:
mov dl, [ebx]
cmp dl, 47
jng fin
cmp dl, 57
jng likkk
cmp dl, 96
jng fin
cmp dl, 102
jg fin
likkk:
inc ebx
loop prov
mov eax, 1
jmp endd
fin:
mov eax, 0
endd:
ret
@sixttn@8 endp

@tentth@8 proc
mov ebx, ecx
mov ecx, edx
xor eax, eax
mov esi, 16
xor edi, edi
xor edx, edx
makelik:
mov dl, [ebx]
cmp dl, 57
jg litrr
sub edx, 48
mov edi, edx
imul esi
add eax, edi
jmp endmake
litrr:
sub edx, 87
mov edi, edx
imul esi
add eax, edi
endmake:
cmp eax, 0
je fall
inc ebx
loop makelik
fall:
ret
@tentth@8 endp

end