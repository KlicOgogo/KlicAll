#include <iostream>

using namespace std;

int main()
{
	int a, end, endd, endd1, end1, is=0, div=1;
	cout << "Enter the number: ";
	cin >> a;
	cout << endl;
	__asm
	{
		mov ecx, a
		mov eax, ecx
		imul eax
		imul eax
		mov ebx, 2
		sub eax, ebx
		mov ebx, 4
		sub ecx, ebx
		cmp ecx, 0
		jz is_four
		cmp eax, -2
		je one
		cmp eax, -1
		je one
		idiv ecx
		mov end, eax
		mov end1, edx
		mov eax, 1
		mov is, eax
		jmp fin
one:
		mov end, 0
		mov end1, eax
		mov ebx, 1
		mov is, ebx
fin:
is_four:
	}
	if (is==1)
		cout << end << "   " << end1 << endl;
	if (is==0)
		cout << "You can't divide by 0" << endl;
	return 0;
}

