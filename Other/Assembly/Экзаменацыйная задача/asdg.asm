.386
.model flat
PUBLIC @NoInSecond@8
PUBLIC @Biggest@4

.data
arr1 dd 100 dup(?)
arr1c dd 0
arr2 dd 100 dup(?)
arr2c dd 0
count dd 0

.code
@NoInSecond@8 proc
mov eax, ecx
mov ebx, edx
mov esi, 10
xor edi, edi
arrr1:
cdq
idiv esi
mov arr1[edi*4], edx
inc edi
cmp eax, 0
jg arrr1
mov arr1c, edi
mov eax, ebx
xor edi, edi
arrr2:
cdq
idiv esi
mov arr2[edi*4], edx
inc edi
cmp eax, 0
jg arrr2
mov arr2c, edi

mov ecx, arr2c
mov ebx, arr1c
xor edx, edx
xor esi, esi
xor edi, edi

find:
mov eax, arr1[edi*4]
cmp eax, arr2[esi*4]
jne noteq
inc edx
noteq:
inc esi
loop find
cmp edx, 0
jz incedi
inc count
incedi:
inc edi
mov ecx, arr2c
dec ebx
xor esi, esi
xor edx, edx
cmp ebx, 0
jg find
mov eax, arr1c
sub eax, count
ret
@NoInSecond@8 endp

@Biggest@4 proc
mov eax, ecx
xor ebx, ebx
mov esi, 10
divvv:
cdq
idiv esi
cmp edx, ebx
jl notb
mov ebx, edx
notb:
cmp eax, 0
jg divvv
mov eax, ebx
ret
@Biggest@4 endp
end
