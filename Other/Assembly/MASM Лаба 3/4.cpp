#include <iostream>

using namespace std;

int main()
{
	int arr1[]={13, 123, 14, 4, 6, 19, 132, 56, 12, 8}, arr2[]={1, 123, 4, 17, 34, 65, 49, 132, 12, 69};
	int kol;
	__asm
	{
		mov esi, 0
		mov edi, 0
		mov edx, 0
ebxloo:
		mov eax, arr1[esi*4]
		mov ebx, arr2[edi*4]
		cmp eax, ebx
		je eqqq
		jne neq
eqqq:	
		mov ecx, esi
eqqq1:
		mov edi, arr1[ecx*4+4]
		mov arr1[ecx*4], edi
		inc ecx
		cmp ecx, 9
		jl eqqq1
		inc edx
		//inc esi
		mov edi, 0
		cmp esi, 10
		jng ebxloo
		jmp fin
neq:
		inc edi
		cmp edi, 10
		jl ebxloo
		inc esi
		mov edi, 0
		cmp esi, 10
		jng ebxloo
fin:
		mov kol, edx
	}
	for (int i=0; i<10-kol; i++)
		cout << arr1[i] << "\t";
	return 0;
}