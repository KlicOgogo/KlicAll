#include <iostream>

using namespace std;

int main()
{
	int x=0, y=0, m=4, n=4, maxx=0, maxy=0, mxx, mxy, myx, myy, xy=0;
	int matr[4][4];
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			cin  >> matr[i][j];
		cout << endl;
	}
	_asm
	{
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		xor edi, edi
		mov esi, m
		
Lb:
		mov eax, y
		imul esi
		mov ebx, x
		add ebx, eax
		mov ecx, matr[ebx*4]
		mov eax, y
		mov ebx, x
		cmp ecx, 0
		je L1
L0:
		add edi, 1
		add ebx, 1
		cmp ebx, m
		je Ll
		mov x, ebx
		jmp Lb
L1:
		cmp edi, maxx
		jl Lnm
		mov maxx, edi
		mov mxx, ebx
		mov mxy, eax
Lnm:
		xor edi, edi
		add ebx, 1
		cmp ebx, m
		je Ll
		mov x, ebx
		jmp Lb
Ll:
		mov x, 0
		cmp edi, maxx
		jl Lnm2
		mov maxx, edi
		mov mxx, ebx
		mov mxy, eax
Lnm2:
		xor edi, edi
		xor ebx, ebx
		add eax, 1
		cmp eax, n
		je Lk
		mov y, eax
		jmp Lb
Lk:
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		xor edi, edi
		mov esi, m
		mov x, eax
		mov y, eax
		
Kb:
		mov eax, y
		imul esi
		mov ebx, x
		add ebx, eax
		mov ecx, matr[ebx*4]
		mov eax, x
		mov ebx, y
		cmp ecx, 0
		je K1
K0:
		add edi, 1
		add ebx, 1
		cmp ebx, n
		je Kk
		mov y, ebx
		jmp Kb
K1:
		cmp edi, maxy
		jl Knm
		mov maxy, edi
		mov myx, ebx
		mov myy, eax
Knm:
		xor edi, edi
		add ebx, 1
		cmp ebx, n
		je Kk
		mov y, ebx
		jmp Kb
Kk:
		mov y, 0
		cmp edi, maxy
		jl Knm2
		mov maxy, edi
		mov myx, ebx
		mov myy, eax
Knm2:
		xor edi, edi
		xor ebx, ebx
		add eax, 1
		cmp eax, m
		je Kl
		mov x, eax
		jmp Kb
Kl:

		mov eax, mxx
		sub eax, 1
		cmp eax, myy
		jl e
		sub eax, maxx
		cmp eax, myy
		jg e

		mov eax, myx
		sub eax, 1
		cmp eax, mxy
		jl e
		sub eax, maxy
		cmp eax, mxy
		jg e

		mov xy, 1
e:
	}
	//cout << maxx << " " << maxy;
	cout << endl;
	//if (xy)
	cout <<"x"<< myy+1 << "y" << mxy+1;
	cout << endl;
	//system("pause");
	//
	x=0,y=0, m=4;
	int mn=16,count = 0;
	
	int arr2[4][4]={0,0,0,0, 
		            0,0,0,0,
				    0,0,0,0,
	                0,0,0,0};
	
	_asm
	{
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		xor edi, edi
		mov esi, m
begin_n:
		mov eax, matr[ebx*4]
		cmp eax, 0
		je nnn
m3:
		add ebx, 1
		cmp ebx, mn
		je eee
		jmp begin_n
nnn:
		mov eax, arr2[ebx*4]
		mov arr2[ebx*4], 1
		cmp eax, 0
		jne m3
		add edi, 1
		mov x, ebx
nb:
		cmp ebx, m
		jl fl
		mov edx, ebx
		sub edx, m

		mov eax, arr2[edx*4]
		cmp eax, 1
		je fl
		mov arr2[edx*4], 1
		push edx
		add ecx, 1
fl:
		mov eax, mn
		sub eax, m
		cmp ebx, eax
		jg llll
		mov edx, ebx
		add edx, m

		mov eax, arr2[edx*4]
		cmp eax, 1
		je llll
		mov arr2[edx*4], 1
		push edx
		add ecx, 1
llll:
		mov eax, ebx
m1:
		cmp eax, m
		jl m2
		sub eax, m
		jmp m1
m2:
		cmp eax, 0
		je fk
		mov edx, ebx
		sub edx, 1
		mov eax, arr2[edx*4]
		cmp eax, 1
		je fk
		mov arr2[edx*4], 1
		push edx
		add ecx, 1
fk:
		mov edx, m
		sub edx, 1
		mov y, edx
		cmp eax, y
		je lllk
		mov edx, ebx
		add edx, 1

		mov eax, arr2[edx*4]
		cmp eax, 1
		je lllk
		mov arr2[edx*4], 1
		push edx
		add ecx, 1
lllk:
		cmp ecx, 0
		mov ebx, x
		je m3
		pop ebx
		sub ecx, 1
		mov eax, matr[ebx*4]
		cmp eax, 0
		je nb
		jmp lllk

eee:
		mov count, edi
	}
	

	count++;
	count--;
	cout<<count << endl;;
	return 0;
}

	