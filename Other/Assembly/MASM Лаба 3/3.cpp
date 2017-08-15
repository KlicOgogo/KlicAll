#include <iostream>

using namespace std;

int main()
{
	int arr1[]={13, 123, 14, 4, 6, 19, 132, 56, 12, 8}, arr2[]={1, 123, 4, 17, 34, 65, 49, 132, 12, 69};
	int uni[20], intersec[10];
	int kol, kol1;
	__asm
	{
		mov esi, 0
		mov ecx, 10
unii:
		mov eax, arr2[esi*4]
		mov uni[esi*4], eax
		inc esi
		loop unii
		mov esi, 0
		mov edi, 0
		mov ecx, 0
		mov edx, 0
ebxloo:
		mov eax, arr1[esi*4]
		mov ebx, arr2[edi*4]
		cmp eax, ebx
		je eqqq
		jne neq
eqqq:	
		
		mov intersec[edx*4], ebx
		inc edx
		inc esi
		mov edi, 0
		cmp esi, 10
		jng ebxloo
		jmp fin
neq:
		inc edi
		cmp edi, 10
		jng ebxloo
		mov uni[40+ecx*4], eax
		inc ecx
		inc esi
		mov edi, 0
		cmp esi, 10
		jng ebxloo
fin:
		dec edx
		mov kol, edx
		mov kol1, ecx
	}
	for (int i=0; i<kol; i++)
	{
			cout << intersec[i] << "\t";
	}
	cout << endl << endl;
	for (int i=0; i<kol1+10; i++)
		cout << uni[i] << "\t";
	return 0;
}