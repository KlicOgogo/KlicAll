#include <iostream>

using namespace std;

int main()
{
	int t, fin; 
	cout <<"Enter the number: ";
	cin >> t;
	cout << endl;
	__asm
	{
		mov eax, t
		mov ebx, eax
		imul eax
		imul ebx
		mov ecx, eax
		imul ebx
		imul ebx
		add eax, ebx
		add eax, ecx
		mov fin, eax
	}
	cout << "The result is: "<< fin << endl;
	return 0;
}