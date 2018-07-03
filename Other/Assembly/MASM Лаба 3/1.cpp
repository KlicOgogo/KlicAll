#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	vector<int> aaa(8);
	int a[8], aa, ind, fin=0;
	cout << "Enter 8 different numbers: ";
	for (int i=0; i<8; i++)
		cin >> aaa[i];
	cout << endl;
	sort (aaa.begin(), aaa.end());
	for (int i=0; i<8; i++)
		a[i]=aaa[i];
	cout << "Enter thr number: ";
	cin >> aa;
	cout << endl;
	__asm
	{
		mov ecx, 0
		lea ebx, a+16
		mov eax, aa
		cmp eax, [ebx]
		jg gre
		jl lee
		inc ecx
		mov ind, 4
		mov fin, ecx
gre:
		lea ebx, a+24
		cmp eax, [ebx]
		jg gre1
		jl lee1
		inc ecx
		mov ind, 6
		mov fin, ecx
gre1:
		lea ebx, a+28
		cmp eax, [ebx]
		jne endd
		inc ecx
		mov ind, 7
		mov fin, ecx
lee1:
		lea ebx, a+20
		cmp eax, [ebx]
		jne endd
		inc ecx
		mov ind, 5
		mov fin, ecx
lee:
		lea ebx, a+4
		cmp eax, [ebx]
		jg gre2
		jl lee2
		inc ecx
		mov ind, 1
		mov fin, ecx
lee2: 
		lea ebx, a
		cmp eax, [ebx]
		jne endd
		inc ecx
		mov fin, ecx
		mov ind, 0
gre2:
		lea ebx, a+12
		cmp eax, [ebx]
		jg endd
		jl lee3
		inc ecx
		mov fin, ecx
		mov ind, 3
lee3:
		lea ebx, a+8
		cmp eax, [ebx]
		jne endd
		inc ecx
		mov fin, ecx
		mov ind, 2
endd:
	}
	if (fin)
		cout << "YES: " << ind << endl;
	else
		cout << "NO" << endl;
	return 0;
}