#include <iostream>

using namespace std;

int main()
{
	int a, rez, t=0;
	cout << "Enter the number: ";
	cin >> a;
	cout << endl;
	__asm
	{
		mov eax, a
		mov ebx, a
		mov ecx, 1
		cmp eax, 1
		je loh
		cmp eax, -1
		je loh
		cmp eax, 0
		je loh
		mov edx, 1
		mov t, edx
circ:
		imul ebx
		mov a, eax
		jo dno
		inc ecx
		jmp circ
dno:
		mov rez, ecx
loh:
	}
	if (t!=0)
		cout << rez << endl;
	else
		cout << "Incorrect a" << endl;
	return 0;
}