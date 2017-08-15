#include <iostream>

using namespace std;

int main()
{
	int a, rez;
	cout << "Enter the number: ";
	cin >> a;
	cout << endl;
	__asm
	{
		mov eax, a
		mov ecx, 0
		mov ebx, 10
		cmp eax, 0
		jg ddi
		mov edx, -1
		imul edx
ddi:
		cdq
		idiv ebx
		add ecx, edx
		cmp eax, 0
		jg ddi
		mov rez, ecx
	}
	cout << rez << endl;
	
	__asm
	{
		mov eax, a
		mov esi, 0
		cmp eax, 0
		jg dddi
		mov ebx, -1
		imul ebx
dddi:
		mov ebx, 10
		cdq
		idiv ebx
		mov ecx, eax
		mov eax, edx
		mov ebx, 2
		cdq
		idiv ebx
		mov eax, ecx
		cmp eax, 0
		je finnn
		cmp edx, 0
		jg dddi
		jmp nofin
finnn:
		cmp edx, 0
		je nofin
		jg fff
nofin:
		inc esi
fff:
		mov rez, esi
		cmp ecx, 0
		mov eax, ecx
		jg dddi
	}
	cout << rez << endl;
	__asm
	{
		mov eax, a
		mov ecx, 0
		mov ebx, 10
		cmp eax, 0
		jg fdi
		mov edx, -1
		imul edx
fdi:
		cdq
		idiv ebx
		inc ecx
		cmp eax, 0
		jg fdi
		mov rez, ecx
	}
	__asm
	{
		mov eax, a
		mov ecx, rez
		mov ebx, 10
		mov esi, 0
		cmp eax, 0
		jg sdd
		mov edx, -1
		imul edx
sdd:
		cdq
		idiv ebx
		mov rez, eax
		mov eax, edx
		mov edi, ecx
rev:
		imul ebx
		loop rev
		idiv ebx
		mov ecx, edi 
		dec ecx
		add esi, eax
		mov eax, rez
		cmp eax, 0
		jg sdd
		mov eax, a
		cmp eax, 0
		jg ggg
		mov edx, -1
		imul edx
ggg:
		cmp eax, esi
		je yeeee
		jne noooo
yeeee:
		mov ebx, 1
		mov rez, ebx
		jmp enddd
noooo:
		mov ebx, 0
		mov rez, ebx
enddd:
	}
	if (rez==1)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	return 0;
}