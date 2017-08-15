#include <iostream>

using namespace std;

int main()
{
	int a, b, fina, finb, t=0;
	cout << "Enter int a: ";
	cin >> a;
	cout << endl;
	cout << "Enter unsigned int b: ";
	cin >> b;
	cout << endl;
	__asm
	{
		jmp norm
zerob:
		mov eax, 1
		mov t, eax
		jmp enddddd
norm:
		mov eax, a
		cmp eax, 0
		jg ogg
		mov edx, -1
		imul edx
ogg:
		mov ebx, b
		cmp ebx, 0
		je zerob
		mov ecx, 1
		jmp doo
fail:	
		imul ecx
		mov esi, eax
		mov eax, ebx
		imul ecx
		add eax, edi
		mov ebx, eax
		mov eax, esi
		jmp doo
doww:
		imul ecx
		add eax, edi
doo:
		inc ecx
doooo:
		cmp ecx, eax
		jg endd
		cdq
		idiv ecx 
		mov edi, edx
		cmp edx, 0
		jg doww
		mov esi, eax
		mov eax, ebx
		cdq
		idiv ecx
		mov ebx, eax
		mov eax, esi
		mov edi, edx
		cmp edx, 0
		je doooo
		jg fail
endd:
		mov ecx, a
		cmp ecx, 0
jg ogggo
		mov edx, -1
		imul edx
ogggo:
		mov fina, eax
		mov finb, ebx
enddddd:
	}
	if (t==0)
		cout << fina << "\t" << finb<< endl;
	else
		cout << "You can't make b equal by zero" << endl;
	return 0;
}