.386
PUBLIC @showord@8
.model flat
.code

@showord@8 proc
mov esi, ecx
xor edi, edi
xor ebx, ebx
xor eax, eax
mov bl, 32
posh:
mov al, [edx]
cmp al, bl
je endwo
inc edi
jmp afte
endwo:
cmp edi, 0
je afte
cmp edi, esi
jg afte1
mov esi, edi
afte1:
xor edi, edi
afte:
inc edx
loop posh
mov eax, esi
ret
@showord@8 endp
end