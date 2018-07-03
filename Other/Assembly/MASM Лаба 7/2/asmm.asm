.386
PUBLIC @bezprob@8
.model flat
.data
str1 db 100 dup(?)
.code
@bezprob@8 proc
xor eax, eax
xor ebx, ebx
mov al, 32
xor esi, esi
gogo:
cmp al, [edx]
je prob
mov bl, [edx]
mov str1[esi], bl
inc esi
prob:
inc edx
loop gogo
lea eax, str1
ret
@bezprob@8 endp
end