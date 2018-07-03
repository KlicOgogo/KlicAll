#include <iostream>

using namespace std;

int main()
{
	int a, b, t=0, rez, fin=0;
	cout << "Enter two numbers: a and b ";
	cin >> a >> b;
	cout << endl;
	__asm
	{
		mov ebx, a
		mov eax, b
		cmp ebx, 0
		jz no
		mov edx, -1
		imul edx
		cmp eax, 0
		je zer
		idiv ebx
		cmp edx, 0
		jne yeah
		mov rez, eax
		mov t, eax
		jmp yeah
zer:
		mov eax, 0
		mov rez, eax
		mov ebx, 10
		mov t, ebx
		jmp yeah
no:
		cmp eax, 0
		jne yeah
		mov edx, 1
		mov fin, edx
yeah:		
	}
	if (fin==1)
		cout << "All answers are correct" << endl;
	else
		if (t!=0)
			cout << "The answer is: " << rez << endl;
		else
			cout << "The correct answer doesn't exist" << endl;
	return 0;
}
