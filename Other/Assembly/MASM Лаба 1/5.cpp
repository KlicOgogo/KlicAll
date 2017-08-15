#include <iostream>

using namespace std;

int main()
{
	unsigned int rez, x, y, axx;
	unsigned int t=100, tt=6, ttt=2, tttt=0;
	__asm
	{
		mov eax, t
		mov ebx, tt
		mov ecx, ttt
		mov esi, tttt
go:
		sub eax, ebx
		mov axx, eax
		cdq
		div ecx
		mov x, eax
		mul ecx
		inc esi
		mov rez, esi
		mov eax, esi
		mul ecx
		mov y, eax
	}
	cout << x << "\t" << y << endl;

	__asm
	{
		mov eax, axx
		mov ebx, tt
		mov ecx, ttt
		mov esi, rez
		cmp eax, 6
		jg go

	}
	cout << rez << endl;
	return 0;
}