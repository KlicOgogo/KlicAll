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
		mov ebx, a
		mov eax, 1
		mov ecx, 2
		mov edx, 0
		mov esi, 0
		mov edx, -1
		cmp ebx, 0
		jnl ddd
		je ggvp
		mov eax, ebx
		imul edx
		mov ebx, eax
		mov eax, 1
		mov edi, 0
ddd:
		inc esi
		imul ecx
		cmp ebx, eax
		jnl ddd
		cmp edi, 0
		je ddddd
		mov rez, esi
		jmp fin
ddddd:
		mov eax, 33
		sub eax, esi
		mov rez, eax
		jmp fin
ggvp:
		mov rez, 0
fin:
	}
	cout << rez << endl;
	return 0;
}