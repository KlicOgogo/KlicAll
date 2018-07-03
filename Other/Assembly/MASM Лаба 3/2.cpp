#include <iostream>

using namespace std;

int main()
{
	int f1[4], f2[4];
	for (int i=0; i<4; i++)
		cin >> f1[i];
	for (int i=0; i<4; i++)
		cin >> f2[i];
	int sum[4], mul[7];
	__asm
	{
		lea eax, f1
		lea ebx, f2
		mov ecx, 4
		mov esi, 0
		mov edx, 4
summm:
		mov edi, 0
		add edi, [eax]
		add edi, [ebx]
		mov sum[esi*4], edi
		add ebx, edx
		add eax, edx
		inc esi
		loop summm
	}
	for (int i=0; i<4; i++)
		cout << sum[i] << "\t";
	cout << endl;
	__asm
	{
		//0
		mov esi, 0
		mov ecx, 0
		mov eax, f2
		mov ebx, f1
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//6
		mov esi, 6
		mov ecx, 0
		mov eax, f1+12
		mov ebx, f2+12
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//1
		mov esi, 1
		mov ecx, 0
		mov eax, f1
		mov ebx, f2+4
		imul ebx
		add ecx, eax
		mov eax, f1+4
		mov ebx, f2
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//5
		mov esi, 5
		mov ecx, 0
		mov eax, f1+12
		mov ebx, f2+8
		imul ebx
		add ecx, eax
		mov eax, f1+8
		mov ebx, f2+12
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//2
		mov esi, 2
		mov ecx, 0
		mov eax, f1+4
		mov ebx, f2+4
		imul ebx
		add ecx, eax
		mov eax, f1+8
		mov ebx, f2
		imul ebx
		add ecx, eax
		mov eax, f1
		mov ebx, f2+8
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//4
		mov esi, 4
		mov ecx, 0
		mov eax, f1+8
		mov ebx, f2+8
		imul ebx
		add ecx, eax
		mov eax, f1+12
		mov ebx, f2+4
		imul ebx
		add ecx, eax
		mov eax, f1+4
		mov ebx, f2+12
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
		//3
		mov esi, 3
		mov ecx, 0
		mov eax, f1+8
		mov ebx, f2+4
		imul ebx
		add ecx, eax
		mov eax, f1+4
		mov ebx, f2+8
		imul ebx
		add ecx, eax
		mov eax, f1+12
		mov ebx, f2
		imul ebx
		add ecx, eax
		mov eax, f1
		mov ebx, f2+12
		imul ebx
		add ecx, eax
		mov mul[esi*4], ecx
	}
	for (int i=0; i<7; i++)
		cout << mul[i] << "\t";
	return 0;
}