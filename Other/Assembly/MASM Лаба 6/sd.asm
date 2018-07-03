.386
PUBLIC @center@8
PUBLIC @second@8
PUBLIC @mider@8
.model flat
.data
a dd 0
arr1 dd 100 dup(?)
arr2 dd 100 dup(?)
arr3 dd 100 dup(?)
aa dd 0
aa1 dd 0
.code
@second@8 proc
xor ebx, ebx
mov edi, ecx
peregon:
mov esi, [edx]
mov arr1[ebx*4], esi
inc ebx
add edx, 4
loop peregon
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
lea eax, arr1+4
ret
@second@8 endp

@center@8 proc
xor ebx, ebx
mov edi, ecx
peregon:
mov esi, [edx]
mov arr2[ebx*4], esi
inc ebx
add edx, 4
loop peregon
mov ecx, edi
xor eax, eax
mov ebx, ecx
mov esi, edi
dec ecx
dec ebx
sorrt:
maxnav:
mov edi, arr2[eax*4]
cmp edi, arr2[eax*4+4]
jng dnoo
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
mov ebx, offset arr2
mov eax, esi
mov ecx, 2
cdq
idiv ecx
cmp edx, 0
jne niac
add ebx, esi
add ebx, esi
mov eax, ebx 
jmp endddd
niac:
add ebx, esi
add ebx, esi
sub ebx, ecx
mov eax, ebx
endddd:
ret
@center@8 endp

@mider@8 proc
xor eax, eax
mov edi, ecx
mov aa, ecx
mov ebx, edx
mov aa1, edx
summm:
mov esi, [edx]
add eax, esi
add edx, 4
loop summm
mov a, eax
mov ecx, edi
mov edx, ebx
xor ebx, ebx
mov eax, a
peregon:
mov esi, [edx]
imul esi, edi
sub esi, eax
cmp esi, 0
jnl krasava
neg esi
krasava:
mov arr3[ebx*4], esi
inc ebx
add edx, 4
loop peregon
mov ecx, edi
xor eax, eax
mov ebx, ecx
dec ecx
dec ebx
sorrt:
maxnav:
mov edi, arr3[eax*4]
cmp edi, arr3[eax*4+4]
jng dnoo
mov edx, arr3[eax*4+4]
mov arr3[eax*4+4], edi
mov arr3[eax*4], edx
dnoo:
inc eax
loop maxnav
dec ebx
mov ecx, ebx
xor eax, eax
cmp ebx, 0
jg sorrt
xor ebx, ebx
mov eax, arr3[ebx*4]
mov ecx, a
add eax, ecx
mov edi, aa
cdq
idiv edi
mov esi, aa1
mov ecx, aa
findd:
cmp eax, [esi]
je norm
mov edx, 4
add esi, edx
loop findd
xor ebx, ebx
mov eax, arr3[ebx*4]
neg eax
add eax, a
cdq
idiv edi
norm:
mov arr3[ebx*4], eax
lea eax, arr3
ret
@mider@8 endp

end