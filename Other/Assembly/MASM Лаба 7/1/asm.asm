.386
PUBLIC @ispal@8
.model flat
.data
str1 db 100 dup(?)
str2 db 100 dup(?)
.code
@ispal@8 proc
xor ebx, ebx
xor esi, esi
mov edi, ecx
pereg:
mov bl, [edx]
mov str1[esi], bl
inc esi
inc edx
loop pereg
mov ecx, edi
xor esi, esi
mov eax, ecx
mov ebx, 1
sub eax, ebx
xor ebx, ebx
rever:
mov bl, str1[esi]
mov str2[eax], bl
dec eax
inc esi
loop rever
mov ecx, edi
xor esi, esi
xor eax, eax
prov:
mov al, str1[esi]
cmp al, str2[esi]
jne nepal
inc esi
loop prov
mov eax, 1
jmp fin
nepal:
mov eax, 0
fin:
ret
@ispal@8 endp
end