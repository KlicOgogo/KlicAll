.386
PUBLIC @reper@8
PUBLIC @lowsum@8
.model flat
.data
kolk dd 0
arr1 dd 100 dup(?)
pak dd 0
zn dd 0
.code
@reper@8 proc
xor ebx, ebx
mov edi, ecx
mov eax, edx
mov kolk, ecx
peregon:
mov esi, [edx]
mov arr1[ebx*4], esi
inc ebx
add edx, 4
loop peregon
xor ebx, ebx
mov edx, eax
mov ecx, kolk
peregon2:
mov esi, [edx]
mov arr3[ebx*4], esi
inc ebx
add edx, 4
loop peregon2
xor ebx, ebx
mov pak, edx
mov ecx, edi
xor eax, eax
mov ebx, ecx
dec ecx
dec ebx
sorrt:
maxnav:
mov edi, arr1[eax*4]
cmp edi, arr1[eax*4+4]
jng dnoo
mov edx, arr1[eax*4+4]
mov arr1[eax*4+4], edi
mov arr1[eax*4], edx
dnoo:
inc eax
loop maxnav
dec ebx
mov ecx, ebx
xor eax, eax
cmp ebx, 0
jg sorrt
mov ebx, kolk
dec ebx
mov kolk, ebx
xor ebx, ebx
xor edx, edx
xor edi, edi
xor esi, esi
xor ecx, ecx
paraun:
mov eax, arr1[ebx*4]
cmp eax, arr1[ebx*4+4]
jne nooteq
inc edx
inc ebx
mov ecx, ebx
cmp ebx, kolk
jl paraun
jg fin
nooteq:
inc ebx
cmp edx, edi
jng niajs
mov edi, edx
mov esi, ecx
niajs:
xor edx, edx
cmp ebx, kolk
jl paraun
fin:
cmp edi, 0
je looo
mov eax, offset arr1
imul esi, 4
add eax, esi
jmp ennnn
looo:
lea eax, arr3
ennnn:
ret
@reper@8 endp

.data
liksums dd 100 dup(?)
arr2 dd 100 dup(?)
arr3 dd 100 dup(?)
kol1 dd 0
.code
@lowsum@8 proc
xor ebx, ebx
mov edi, ecx
mov kol1, ecx
peregon:
mov esi, [edx]
mov arr2[ebx*4], esi
inc ebx
add edx, 4
loop peregon
xor ebx, ebx
xor esi, esi
mov ecx, kol1
mov edi, 10
_peregon:
mov eax, arr2[ebx*4]
summm:
cdq
idiv edi
add esi, edx
cmp eax, 0
jg summm
mov liksums[ebx*4], esi
inc ebx
xor esi, esi
loop _peregon
mov ecx, kol1
xor eax, eax
mov ebx, ecx
dec ecx
dec ebx
sorrt:
maxnav:
mov edi, liksums[eax*4]
cmp edi, liksums[eax*4+4]
jng dnoo
mov edx, liksums[eax*4+4]
mov liksums[eax*4+4], edi
mov liksums[eax*4], edx
mov edi, arr2[eax*4]
mov edx, arr2[eax*4+4]
mov arr2[eax*4+4], edi
mov arr2[eax*4], edx
dnoo:
inc eax
loop maxnav
dec ebx
mov ecx, ebx
xor eax, eax
cmp ebx, 0
jg sorrt
lea eax, arr2
ret
@lowsum@8 endp
end