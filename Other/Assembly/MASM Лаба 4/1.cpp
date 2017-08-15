#include <iostream>

using namespace std;

int main()
{
	int n=4, m=4;
	int matr[4][4];
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
			cin  >> matr[i][j];
		cout << endl;
	}
	int Brr[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	_asm
	{
		mov ecx, 0
nnnn:
		mov ebx, 0
mmmm:
		mov eax, ecx
		sub eax, 1
		cmp eax, -1
		je inc1
		mov eax, m
		mul ecx
		add eax, ebx
		mov esi, eax
		mov edi, ecx
		sub edi, 1
		mov eax, m
		mul edi
		add eax, ebx
		mov edi, eax
		mov eax, matr[edi*4]
		cmp matr[esi*4], eax
		jnl inc1
		inc ebx
		cmp ebx, m
		jl mmmm
		inc ecx
		cmp ecx, n
		jl nnnn
		jmp fin
inc1:
		mov eax, ebx
		add eax, 1
		cmp eax, n
		je inc2
		mov eax, m
		mul ecx
		add eax, ebx
		mov esi, eax
		mov eax, m
		mul ecx
		add eax, ebx
		add eax, 1
		mov edi, eax
		mov eax, matr[edi*4]
		cmp matr[esi*4], eax
		jnl inc2
		inc ebx
		cmp ebx, m
		jl mmmm
		inc ecx
		cmp ecx, n
		jl nnnn
		jmp fin
inc2:
		mov eax, ecx
		add eax, 1
		cmp eax, m
		je inc3
		mov eax, m
		mul ecx
		add eax, ebx
		mov esi, eax
		mov edi, ecx
		add edi, 1
		mov eax, m
		mul edi
		add eax, ebx
		mov edi, eax
		mov eax, matr[edi*4]
		cmp matr[esi*4], eax
		jnl inc3
		inc ebx
		cmp ebx, m
		jl mmmm
		inc ecx
		cmp ecx, n
		jl nnnn
		jmp fin
inc3:
		mov eax, ebx
		sub eax, 1
		cmp eax, -1
		je inc4
		mov eax, m
		mul ecx
		add eax, ebx
		mov esi, eax
		mov eax, m
		mul ecx
		add eax, ebx
		sub eax, 1
		mov edi, eax
		mov eax, matr[edi*4]
		cmp matr[esi*4], eax
		jnl inc4
		inc ebx
		cmp ebx, m
		jl mmmm
		inc ecx
		cmp ecx,n
		jl nnnn
		jmp fin
inc4:
		mov eax, m
		mul ecx
		add eax, ebx
		mov esi, eax
		mov Brr[esi*4], 1
		inc ebx
		cmp ebx, m
		jl mmmm
		inc ecx
		cmp ecx,n
		jl nnnn
		jmp fin
	}
fin:
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << Brr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//
	int count=0,temp;
	_asm
	{
beg:
		mov ecx,0
begnn:
		mov ebx,0
begmm:
		mov eax,ecx
		add eax,1
		cmp eax,m
		je _next33
		mov eax,m
		mul ecx
		add eax,ebx
		mov esi,eax
		mov edi,ecx
		add edi,1
		mov eax,m
		mul edi
		add eax,ebx
		mov edi,eax
		mov eax,matr[edi*4]
		cmp matr[esi*4],eax
		jg jjj1
		je jjj2
		inc ecx
		cmp ecx,n
		jl begnn
		inc count
		mov eax,count
		cmp eax,n
		jl beg
		jmp oout
jjj2:
		inc ebx
		cmp ebx,m
		jl begmm
		inc ecx
		cmp ecx,n
		jl begnn
		inc count
		mov eax,count
		cmp eax,n
		jl beg
		jmp oout
jjj1:
		mov ebx,0
aaa1:
		mov eax,m
		mul ecx
		add eax,ebx
		mov esi,eax
		mov edi,ecx
		add edi,1
		mov eax,m
		mul edi
		add eax,ebx
		mov edi,eax
		mov eax,matr[esi*4]
		mov temp,eax
		mov eax,matr[edi*4]
		mov matr[esi*4],eax
		mov eax,temp
		mov matr[edi*4],eax
		inc ebx
		cmp ebx,m
		jl aaa1
		inc ecx
		cmp ecx,n
		jl begnn
		inc count
		mov eax,count
		cmp eax,n
		jl beg
		jmp oout
_next33:
		inc count
		mov eax,count
		cmp eax,n
		jl beg
		jmp oout
	}
oout:
	for(int i=0; i<m; i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<matr[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	//
	count=0;
	_asm
	{
begin_count1:
		mov ecx,0
begin_n1:
		mov ebx,0
begin_m1:
		mov eax,ecx
		add eax,1
		cmp eax,m
		je _next3
		mov eax,m
		mul ecx
		add eax,ebx
		mov esi,eax
		mov edi,matr[esi*4]
		inc ebx
_aga11:
		mov eax,m
		mul ecx
		add eax,ebx
		mov esi,eax
		cmp edi,matr[esi*4]
		jg _next1
		mov edi,matr[esi*4]
_next1:
		inc ebx
		cmp ebx,m
		jl _aga11
		mov ebx,0
		mov temp,edi
		mov edx,ecx
		inc edx
		mov eax,m
		mul edx
		add eax,ebx
		mov esi,eax
		mov edi,matr[esi*4]
		inc ebx
_aga2:
		mov eax,m
		mov edx,ecx
		inc edx
		mul edx
		add eax,ebx
		mov esi,eax
		cmp edi,matr[esi*4]
		jg _next2
		mov edi,matr[esi*4]
_next2:
		inc ebx
		cmp ebx,m
		jl _aga2
		cmp edi,temp
		jl _jmp11
		inc ecx
		cmp ecx,n
		jl begin_n1
		inc count
		mov eax,count
		cmp eax,n
		jl begin_count1
		jmp _out1
_jmp11:
		mov ebx,0
aga3:
		mov eax,m
		mul ecx
		add eax,ebx
		mov esi,eax
		mov edi,ecx
		add edi,1
		mov eax,m
		mul edi
		add eax,ebx
		mov edi,eax
		mov eax,matr[esi*4]
		mov temp,eax
		mov eax, matr[edi*4]
		mov matr[esi*4],eax
		mov eax,temp
		mov matr[edi*4],eax
		inc ebx
		cmp ebx,m
		jl aga3
		inc ecx
		cmp ecx,n
		jl begin_n1
		inc count
		mov eax,count
		cmp eax,n
		jl begin_count1
		jmp _out1
_next3:
		inc count
		mov eax,count
		cmp eax,n
		jl begin_count1
		jmp _out1
	}
_out1:
	for(int i=0; i<m; i++)
		{
		for(int j=0; j<n; j++)
		{
			cout << matr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return 0;
}	